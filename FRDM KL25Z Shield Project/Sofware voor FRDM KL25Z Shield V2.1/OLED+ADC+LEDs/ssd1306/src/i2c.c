/*! ***************************************************************************
 *
 * \brief     I2C low level peripheral driver
 * \file      i2c.c
 * \author    Hugo Arends
 * \date      April 2021
 *
 * \remark    Hardware connection
 * <pre>                                SSD1306 Oled display             </pre>
 * <pre>                           Vdd +-------------+                   </pre>
 * <pre>      FRDM-KL25Z            |  |             |                   </pre>
 * <pre>      -------------+        +--+Vcc          |                   </pre>
 * <pre>                   |   GND|----+GND          |                   </pre>
 * <pre>      I2C1_SCL/PTB0+-----------+SCL          |                   </pre>
 * <pre>      I2C1_SDA/PTB1+-----------+SDA          |                   </pre>
 * <pre>                   |           |             |                   </pre>
 * <pre>      -------------+           +-------------+                   </pre>
 *
 * \copyright 2020 HAN University of Applied Sciences. All Rights Reserved.
 *            \n\n
 *            Permission is hereby granted, free of charge, to any person
 *            obtaining a copy of this software and associated documentation
 *            files (the "Software"), to deal in the Software without
 *            restriction, including without limitation the rights to use,
 *            copy, modify, merge, publish, distribute, sublicense, and/or sell
 *            copies of the Software, and to permit persons to whom the
 *            Software is furnished to do so, subject to the following
 *            conditions:
 *            \n\n
 *            The above copyright notice and this permission notice shall be
 *            included in all copies or substantial portions of the Software.
 *            \n\n
 *            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *            OTHER DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/
#include <MKL25Z4.H>
#include "i2c.h"

/*!
 * \brief Initialises the I2C peripheral
 *
 * Initialises I2C0
 * The I2C baud rate is set to 375000 bps
 * The following I2C pins are configured:
 * - PTB0: SCL
 * - PTB1: SDA
 */
void i2c_init(void)
{
    // Clock i2c peripheral and port
    SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
    SIM->SCGC5 |= (SIM_SCGC5_PORTE_MASK);
    
    // Set pins to I2C function
    PORTE->PCR[0] |= PORT_PCR_MUX(6); //sda 
    PORTE->PCR[1] |= PORT_PCR_MUX(6); //scl
    
    // Make sure i2c is disabled
    I2C1->C1 &= ~(I2C_C1_IICEN_MASK);
        
    // MUL[1:0] : The MULT bits define the multiplier factor mul.
    // ICR[5:0] : Prescales the bus clock for bit rate selection.
    //
    // I2C baud rate = bus speed (Hz)/(mul × SCL divider)
    //        375000 =     24MHz     /( 1  *    64)
    I2C1->F = (I2C_F_MULT(0) | I2C_F_ICR(0x12));   
    
    // Clear any flags
    I2C1->S |= (I2C_S_ARBL_MASK | I2C_S_IICIF_MASK);
    
    // Enable i2c and set to master mode
    I2C1->C1 |= (I2C_C1_IICEN_MASK);
}

/*!
 * \brief Sends multiple commands to the Oled display
 *
 * All commands are transferred in a single I2C transfer to the Oled display.
 * If there is no response within the timeout, this function will return false.
 *
 * \param[in]  address  I2C address of the Oled display
 * \param[in]  cmd      Pointer to the array of commands to be transmitted
 * \param[in]  n        Number of commands
 *
 * \return True on successfull communication, false otherwise
 */
bool i2c_write_cmd(const uint8_t address, const uint8_t cmd[], const uint32_t n)
{
    // Set to transmit mode
    I2C1->C1 |= I2C_C1_TX_MASK;
    
    // Generate start condition
    I2C1->C1 |= I2C_C1_MST_MASK;
    
    // Send the address
    I2C1->D = address;
    
    // Wait for acknowledge
    // If timeout occurs, try to reinitialise i2c and return from this function
    uint32_t timeout = I2C_TIMEOUT;
    while((I2C1->S & I2C_S_IICIF_MASK)==0)
    {
        if(--timeout == 0)
        {
            return false;
        }
    }
        
    // Clear the flag
    I2C1->S |= I2C_S_IICIF_MASK;
                      
    // Datasheet 8.1.5.2: A control byte mainly consists of Co and D/C# bits 
    //                    following by six “0” ‘s
    // Bit 7 Co:   If the Co bit is set as logic “0”, the transmission of the 
    //             following information will contain data bytes only.
    // Bit 6 D/C#: The D/C# bit determines the next data byte is acted as a 
    //             command or a data. If the D/C# bit is set to logic “0”, it 
    //             defines the following data byte as a command. If the D/C# bit
    //             is set to logic “1”, it defines the following data byte as a 
    //             data which will be stored at the GDDRAM.
    //             The GDDRAM column address pointer will be increased by one 
    //             automatically after each data write.    
    
    // Send control byte: next byte is acted as a command
    I2C1->D = 0x00;
        
    // Wait for acknowledge
    // If timeout occurs, try to reinitialise i2c and return from this function
    timeout = I2C_TIMEOUT;
    while((I2C1->S & I2C_S_IICIF_MASK)==0)
    {
        if(--timeout == 0)
        {
            return false;
        }
    }        
        
    // Clear the flag
    I2C1->S |= I2C_S_IICIF_MASK;             
                           
    for(uint32_t i=0; i<n; ++i)
    {
        // Send the byte
        I2C1->D = cmd[i];
        
        // Wait for acknowledge
        // If timeout occurs, try to reinitialise i2c and return from this
        // function
        timeout = I2C_TIMEOUT;
        while((I2C1->S & I2C_S_IICIF_MASK)==0)
        {
            if(--timeout == 0)
            {
                return false;
            }
        }        
            
        // Clear the flag
        I2C1->S |= I2C_S_IICIF_MASK;
    }
    
    // Generate stop
    I2C1->C1 &= ~I2C_C1_MST_MASK;
    
    return true;
}

/*!
 * \brief Sends multiple data bytes to the Oled display
 *
 * All data bytes are transferred in a single I2C transfer to the Oled display.
 * If there is no response within the timeout, this function will return false.
 *
 * \param[in]  address  I2C address of the Oled display
 * \param[in]  data     Pointer to the array of data bytes to be transmitted
 * \param[in]  n        Number of data bytes
 *
 * \return True on successfull communication, false otherwise
 */
bool i2c_write_data(const uint8_t address, const uint8_t data[], const uint32_t n)
{
    // Set to transmit mode
    I2C1->C1 |= I2C_C1_TX_MASK;
    
    // Generate start condition
    I2C1->C1 |= I2C_C1_MST_MASK;
    
    // Send the address
    I2C1->D = address;
    
    // Wait for acknowledge
    // If timeout occurs, try to reinitialise i2c and return from this function
    uint32_t timeout = I2C_TIMEOUT;
    while((I2C1->S & I2C_S_IICIF_MASK)==0)
    {
        if(--timeout == 0)
        {
            return false;
        }
    }
        
    // Clear the flag
    I2C1->S |= I2C_S_IICIF_MASK;
                      
    // Datasheet 8.1.5.2: A control byte mainly consists of Co and D/C# bits 
    //                    following by six “0” ‘s
    // Bit 7 Co:   If the Co bit is set as logic “0”, the transmission of the 
    //             following information will contain data bytes only.
    // Bit 6 D/C#: The D/C# bit determines the next data byte is acted as a 
    //             command or a data. If the D/C# bit is set to logic “0”, it 
    //             defines the following data byte as a command. If the D/C# bit
    //             is set to logic “1”, it defines the following data byte as a 
    //             data which will be stored at the GDDRAM.
    //             The GDDRAM column address pointer will be increased by one 
    //             automatically after each data write.    

    // Send control byte: next byte is acted as a data
    I2C1->D = 0x40;
        
    // Wait for acknowledge
    // If timeout occurs, try to reinitialise i2c and return from this function
    timeout = I2C_TIMEOUT;
    while((I2C1->S & I2C_S_IICIF_MASK)==0)
    {
        if(--timeout == 0)
        {
            return false;
        }
    }
        
    // Clear the flag
    I2C1->S |= I2C_S_IICIF_MASK;  
    
    for(uint32_t i=0; i<n; ++i)
    {
        // Send the byte
        I2C1->D = data[i];

        // Wait for acknowledge
        // If timeout occurs, try to reinitialise i2c and return from this
        // function
        timeout = I2C_TIMEOUT;
        while((I2C1->S & I2C_S_IICIF_MASK)==0)
        {
            if(--timeout == 0)
            {
                return false;
            }
        }
            
        // Clear the flag
        I2C1->S |= I2C_S_IICIF_MASK;
    }
    
    // Generate stop
    I2C1->C1 &= ~I2C_C1_MST_MASK;
    
    return true;
}
