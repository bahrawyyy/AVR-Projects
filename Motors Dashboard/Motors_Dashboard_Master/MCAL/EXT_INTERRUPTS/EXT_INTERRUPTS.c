/*
 * EXT_INTERRUPTS.c
 *
 * Created: 11/29/2022 7:21:01 PM
 *  Author: Abdallah
 */ 

#include "EXT_INTERRUPTS.h"

#define NULLPTR   ((void*)0)   // 0 casted to an address
// NULL Pointer is a pointer that doesn't point to anything
// A good practice you create you must put a data in it, so it doesn't point to a garbage value and create undefined behavior

/************************************************************************/
/* Generic Pointer to functions to be used in ISR (Generic takes void parameter and return void) Initialize to NULL ptr*/
/* NULLPTR is to make it more readable, They are global(in .bss), so they're initialized by zero already */
/* Why static ? So, it an't be used in other files */
/************************************************************************/
static void (*INT0_Fptr) (void) = NULLPTR;
static void (*INT1_Fptr) (void) = NULLPTR;
static void (*INT2_Fptr) (void) = NULLPTR;

/************************************************************************/
/* Call back functions   (it takes from the user which function he wants to execute within the interrupt)*/
/* For example he created a function to turn the LED on, he should pass it here, so that I send it to ISR */
/* A good design tip to create only a function and send to it which interrupt I want to use */
/* void (*LocalPtr)(void) is a local pointer to function */
/* The name of function without () is an address to that function */
/* The function he passes must take void and return void also */
/************************************************************************/

void EXI_Set_CallBack(EX_Interrupt_Source_type interrupt, void (*LocalPtr)(void)){
	switch(interrupt){
	case EX_INT0:
		INT0_Fptr = LocalPtr;
		break;
	case EX_INT1:
		INT1_Fptr = LocalPtr;
		break;
	case EX_INT2:
		INT2_Fptr = LocalPtr;
		break;
	}
}

/************************************************************************/
/*  Enabling and disabling the interrupt                                */
/************************************************************************/


void EXI_ENABLE(EX_Interrupt_Source_type interrupt){
	switch(interrupt){
	case EX_INT0:
		SET_BIT(GICR,INT0);
		break;
	case EX_INT1:
		SET_BIT(GICR,INT1);
		break;
	case EX_INT2:
		SET_BIT(GICR,INT2);
		break;
	}
}


void EXI_DISABLE(EX_Interrupt_Source_type interrupt){
	switch(interrupt){
	case EX_INT0:
		CLR_BIT(GICR,INT0);
		break;
	case EX_INT1:
		CLR_BIT(GICR,INT1);
		break;
	case EX_INT2:
		CLR_BIT(GICR,INT2);
		break;
	}
}

void EXI_TriggerEdge(EX_Interrupt_Source_type interrupt,Trigger_Edge_type edge){
	switch(interrupt){
	case EX_INT0:
		switch(edge){
		case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
		case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
		case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
		}
		break;
		case EX_INT1:
			switch(edge){
			case LOW_LEVEL:
				CLR_BIT(MCUCR,ISC10);
				CLR_BIT(MCUCR,ISC11);
				break;
			case ANY_LOGIC_CHANGE:
				SET_BIT(MCUCR,ISC10);
				CLR_BIT(MCUCR,ISC11);
				break;
			case FALLING_EDGE:
				CLR_BIT(MCUCR,ISC10);
				SET_BIT(MCUCR,ISC11);
				break;
			case RISING_EDGE:
				SET_BIT(MCUCR,ISC10);
				SET_BIT(MCUCR,ISC11);
				break;
			}
			break;
			case EX_INT2:
				switch(edge){
				case FALLING_EDGE:
					CLR_BIT(MCUCSR,ISC2);
					break;
				case RISING_EDGE:
					SET_BIT(MCUCSR,ISC2);
					break;
				default:   // Because we haven't handled all cases just cuz of data sheet
					CLR_BIT(MCUCSR,ISC2);
				}
				break;
	}
}



/************************************************************************/
/*                     ISR                                              */
/************************************************************************/

/* What if the user forgot to send a function to SetCallBack, We made an initialization with NULLPTR, So we can't call a NULLPTR, it will give undefined behavior  */

ISR(INT0_vect){
	if(INT0_Fptr != NULLPTR){
		INT0_Fptr();
	}
}

ISR(INT1_vect){
	if(INT1_Fptr != NULLPTR){
		INT1_Fptr();
	}
}

ISR(INT2_vect){
	if(INT2_Fptr != NULLPTR){
		INT2_Fptr();
	}
}
