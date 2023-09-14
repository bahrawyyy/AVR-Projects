/*
 * KPD_interface.h
 *
 *  Created on: May 4, 2023
 *      Author: Abdallah
 */

#ifndef HAL_KPD_KPD_INTERFACE_H_
#define HAL_KPD_KPD_INTERFACE_H_

#include "../../LIB/ErrorState.h"
#include "../../LIB/STD_Types.h"

#define KPD_U8_NOT_PRESSED 0xff


ES_t KPD_ES_tGetKeyPressed(u8 *copy_pu8ReturnedKey);

#endif /* HAL_KPD_KPD_INTERFACE_H_ */
