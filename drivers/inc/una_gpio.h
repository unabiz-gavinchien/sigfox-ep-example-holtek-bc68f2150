/**
  ******************************************************************************
  * @file    una_gpio.h
  * @author  UNABIZ firmware team
  * @version 
  * @date    2022/Nov./10
  * @brief   For Holtek MCU
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UNA_GPIO_H
#define __UNA_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "typedef.h"

/* Private includes ----------------------------------------------------------*/
//#include "BC68F2130.h"
#include "BC68F2150.h"

/* Exported types ------------------------------------------------------------*/
typedef enum _e_gpio_dir {
  GPIO_OUTPUT= 0,
  GPIO_INPUT = 1,
} GPIO_DIR;

typedef enum _e_gpio_state {
  GPIO_LOW = 0,
  GPIO_HIGH = 1,
} GPIO_STATE;

/* Exported constants --------------------------------------------------------*/
/*
#define BIT_0           (1U<<0)
#define BIT_1           (1U<<1)
#define BIT_2           (1U<<2)
#define BIT_3           (1U<<3)
#define BIT_4           (1U<<4)
#define BIT_5           (1U<<5)
#define BIT_6           (1U<<6)
#define BIT_7           (1U<<7)
*/

/* GPIO PA 
  PA0: N/A
  PA1: Reserved
  PA2: N/A
  PA3: INT0, Botton input
  PA4: ITT1, Reserved
  PA5: Reserved
  PA6: Reserved
  PA7: Reserved
*/

/* PA3 - Botton interrupt */
#define INTR_BOTTON_PIN_PORT    (_pac3)
#define INTR_BOTTON_PIN         (_pa3)    // INT0
#define INTR_BOTTON_PIN_PULL    (_papu3)  // PULLUP control
#define INTR_BOTTON_PIN_WAKEUP  (_pawu3)  // wakeup control

/* GPIO PB 
  PB0: Reserved
  PB1: Power switch enable
  PB2: LED_R
  PB3: LED_G
  PB4: Reserved
  PB5: Reserved
*/
/* PB2 - Red LED */
#define LED_R_PORT            (_pbc2)
#define LED_R_PIN             (_pb2)
#define LED_R_PULL            (_pbpu2)
/* PB3 - Green LED */
#define LED_G_PORT            (_pbc3)
#define LED_G_PIN             (_pb3)
#define LED_G_PULL            (_pbpu3)


// Debounce
#define DEFAULT_DEBOUNCE_DURATION   (10)

/* Exported macro ------------------------------------------------------------*/
#define GPIO_SET_DIR(port,dir)              (port) = (dir)
#define GPIO_SET_INPUT_PULL(pxpux,en)       (pxpux) = (en)
#define GPIO_SET_INPUT_WAKEUP(pawux,en)     (pawux) = (en)
#define GPIO_GET_PIN_STATE(pin)             (pin)
#define GPIO_SET_PIN_STATE(pin,state)       (pin) = (state)

// LED Macros
#define LED_ON(led)       GPIO_SET_PIN_STATE(led,GPIO_LOW)
#define LED_OFF(led)      GPIO_SET_PIN_STATE(led,GPIO_HIGH)


/* Exported functions prototypes ---------------------------------------------*/
void MX_GPIO_Init(void);
void MX_GPIO_DeInit(void);
void GPIO_DebounceInit(void);
void GPIO_DebounceDeInit(void);
void GPIO_DebounceHandler(void);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __UNA_GPIO_H */

/************************ UNABIZ firmware team ********************************/
/***************** (C) COPYRIGHT Holtek Semiconductor Inc. *****END OF FILE****/
