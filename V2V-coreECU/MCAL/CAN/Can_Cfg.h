/***********************************************

Description : CFG FILE FOR Can DRIVER 

Date        : 24-11-2023

Author      : Mohamed Khaled

***********************************************/


#ifndef CAN_CFG_H
#define CAN_CFG_H

/**************************************************|| Pre Combile Config ||********************************************************************/

/*
 *  SET
 *  CLR
 */

#define  Transmit_mailbox_empty_interrupt_enable            CLR

#define  FIFO1_message_pending_interrupt_enable             CLR
																													 
#define  FIFO0_full_interrupt_enable                        CLR
																													 
#define  FIFO0_overrun_interrupt_enable                     CLR
																													 
#define  FIFO0_message_pending_interrupt_enable             CLR
																													 
#define  FIFO1_full_interrupt_enable                        CLR
																													 
#define  FIFO1_overrun_interrupt_enable                     CLR
																													 
#define  Error_warning_interrupt_enable                    CLR
																													 
#define  Error_passive_interrupt_enable                    CLR
																													 
#define  Busoff_interrupt_enable                           CLR
																													 
#define  Last_error_code_interrupt_enable                  CLR
																													 
#define  Error_interrupt_enable                            CLR
																													 
#define  Wakeup_interrupt_enable                           CLR
																													 
#define Sleep_interrupt_enable                             CLR

#endif