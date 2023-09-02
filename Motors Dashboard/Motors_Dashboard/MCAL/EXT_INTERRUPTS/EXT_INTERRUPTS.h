/*
 * EXT_INTERRUPTS.h
 *
 * Created: 11/29/2022 7:20:46 PM
 *  Author: Abdallah
 */ 


#ifndef EXT_INTERRUPTS_H_
#define EXT_INTERRUPTS_H_

#include "../../LIB/STD_Types.h"
#include "../Registers.h"
#include "../../LIB/Bit_Math.h"

typedef enum{
	EX_INT0 = 0,
	EX_INT1,
	EX_INT2	
}EX_Interrupt_Source_type;


// When the interrupt signal happen

typedef enum{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
}Trigger_Edge_type; 

// initialization 
// Here all flags are set, it doesn't need any initialization

// enable and disable

void EXI_ENABLE(EX_Interrupt_Source_type interrupt);
void EXI_DISABLE(EX_Interrupt_Source_type interrupt);
void EXI_TriggerEdge(EX_Interrupt_Source_type interrupt,Trigger_Edge_type edge);
void EXI_Set_CallBack(EX_Interrupt_Source_type interrupt, void (*LocalPtr)(void));

#endif /* EXT_INTERRUPTS_H_ */
