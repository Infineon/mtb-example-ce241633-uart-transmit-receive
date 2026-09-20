/******************************************************************************
* File Name: main.c
*
* Description: This example demonstrates the UART transmit and receive
*              operation using PDL APIs
*
* Related Document: See Readme.md 
*
********************************************************************************
* (c) 2026, Infineon Technologies AG, or an affiliate of Infineon
* Technologies AG. All rights reserved.
* This software, associated documentation and materials ("Software") is
* owned by Infineon Technologies AG or one of its affiliates ("Infineon")
* and is protected by and subject to worldwide patent protection, worldwide
* copyright laws, and international treaty provisions. Therefore, you may use
* this Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software. If no license
* agreement applies, then any use, reproduction, modification, translation, or
* compilation of this Software is prohibited without the express written
* permission of Infineon.
*
* Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
* IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
* THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
* SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
* Infineon reserves the right to make changes to the Software without notice.
* You are responsible for properly designing, programming, and testing the
* functionality and safety of your intended application of the Software, as
* well as complying with any legal requirements related to its use. Infineon
* does not guarantee that the Software will be free from intrusion, data theft
* or loss, or other breaches ("Security Breaches"), and Infineon shall have
* no liability arising out of any Security Breaches. Unless otherwise
* explicitly approved by Infineon, the Software may not be used in any
* application where a failure of the Product or any consequences of the use
* thereof can reasonably be expected to result in personal injury.
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "cy_pdl.h"
#include "cybsp.h"


/*******************************************************************************
*            Global Functions
*******************************************************************************/
void handle_error(void);

/*******************************************************************************
* Function Name: handle_error
********************************************************************************
* Summary:
* User defined error handling function.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void handle_error(void)
{
     /* Disable all interrupts. */
    __disable_irq();

    CY_ASSERT(0);
}

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function.
* Reads one byte from the serial terminal and echoes back the read byte.
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    uint32_t read_value;
    uint32_t send_value;
    uint32_t count;

    cy_en_scb_uart_status_t init_status;
    cy_stc_scb_uart_context_t DEBUG_UART_context;

    /* Initialize the device and board peripherals */
    cybsp_init();

    /* Start UART operation */
    init_status = Cy_SCB_UART_Init(DEBUG_UART_HW, &DEBUG_UART_config, &DEBUG_UART_context);
    if (init_status!=CY_SCB_UART_SUCCESS)
       {
            handle_error();
       }
    Cy_SCB_UART_Enable(DEBUG_UART_HW);

    /* Transmit header to the terminal */
    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    Cy_SCB_UART_PutString(DEBUG_UART_HW, "\x1b[2J\x1b[;H");

    Cy_SCB_UART_PutString(DEBUG_UART_HW, "************************************************************\r\n");
    Cy_SCB_UART_PutString(DEBUG_UART_HW, "PSOC Control C3M/P8: UART transmit and receive\r\n");
    Cy_SCB_UART_PutString(DEBUG_UART_HW, "************************************************************\r\n\n");
    Cy_SCB_UART_PutString(DEBUG_UART_HW, ">> Start typing to see the echo on the screen \r\n\n");

    __enable_irq();

    for(; ;)
    {
        /* Start read operation  */
        read_value = Cy_SCB_UART_Get(DEBUG_UART_HW);
        /* Blocking read data */
        while(read_value == CY_SCB_UART_RX_NO_DATA)
        {
          read_value = Cy_SCB_UART_Get(DEBUG_UART_HW);
        }
        send_value = (uint8_t)read_value;

        /* Start send operation */
        count = Cy_SCB_UART_Put(DEBUG_UART_HW, send_value);

        /* Checking send data number */
        if(count == 0ul)
        {
          handle_error();
        }
    }
}

/* [] END OF FILE */
