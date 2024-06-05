/**
  ******************************************************************************
  * @file    una_gpio.c
  * @author  UNABIZ firmware team
  * @version 
  * @date    2022/Nov./10
  * @brief   For Holtek MCU
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "una_gpio.h"

/* Private includes ----------------------------------------------------------*/
//#include "main.h"
/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static byte_t io_state = {.value = 0};
static uint8 ButtonCurrentStatus = 0;
static uint8 ButtonPreviousStatus = 0;
static uint8 ButtonDebounceTime = 0;
static byte_t ButtonEvent = {.value=0x00};  // BIT0: initialized
                                            // BIT1: falling
                                            // BIT2: rising


/* Private functions prototypes ----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*
 * @brief GPIO initialization
 * @param None
 * @retval None
*/
void MX_GPIO_Init(void)
{
  // Input
  GPIO_SET_DIR(INTR_BOTTON_PIN_PORT, GPIO_INPUT);
  GPIO_SET_INPUT_PULL(INTR_BOTTON_PIN_PULL, TRUE);      // Enable pull up
  GPIO_SET_INPUT_WAKEUP(INTR_BOTTON_PIN_WAKEUP, TRUE);  // Enable sleep wakeup

  // Output
  GPIO_SET_DIR(LED_R_PORT, GPIO_OUTPUT);
  GPIO_SET_DIR(LED_G_PORT, GPIO_OUTPUT);
  GPIO_SET_PIN_STATE(LED_R_PIN, GPIO_HIGH); // High Disable
  GPIO_SET_PIN_STATE(LED_G_PIN, GPIO_HIGH); // High Disable
}

/*
 * @brief GPIO de-initialization
 * @param None
 * @retval None
*/
void MX_GPIO_DeInit(void)
{
  LED_OFF(LED_R_PIN);
  LED_OFF(LED_G_PIN);

  // Set all output as input except interrupt pins
  GPIO_SET_DIR(LED_R_PORT, GPIO_INPUT);
  GPIO_SET_DIR(LED_G_PORT, GPIO_INPUT);
}

#if 0
/*
 * @brief GPIO debounce Init
 * @param None
 * @retval None
*/
void GPIO_DebounceInit(void)
{
  // Default pull up
  // Detect LOW = true
  ButtonDebounceTime = DEFAULT_DEBOUNCE_DURATION;
  ButtonCurrentStatus = ButtonPreviousStatus = 0; 
  
  ClrSta_ButtonClick();
  ClrSta_DebounceBusy();
  ButtonEvent.value = BIT_0;
}

/*
 * @brief GPIO debounce de-init
 * @param None
 * @retval None
*/
void GPIO_DebounceDeInit(void)
{
  ButtonCurrentStatus = ButtonPreviousStatus = 0x00;
  ButtonEvent.value = 0x00;
}
/*
 * @brief GPIO debounce handler
 * @param None
 * @retval None
*/
void GPIO_DebounceHandler(void)
{
  // Check initialized
  if (!ButtonEvent.bits.b0) return;
  io_state.value = 0;
  io_state.bits.b0 = (GPIO_GET_PIN_STATE(INTR_BOTTON_PIN)) ? FALSE : TRUE;
  
  // Check status changed
  if(io_state.value ^ ButtonCurrentStatus) {
    ButtonCurrentStatus = io_state.value;
    ButtonDebounceTime = DEFAULT_DEBOUNCE_DURATION;
    SetSta_DebounceBusy();
    
  } else {
    
    if (!(--ButtonDebounceTime)) {
      ButtonDebounceTime = DEFAULT_DEBOUNCE_DURATION;
      ButtonPreviousStatus = ButtonCurrentStatus;
      
      // Check BIT-0
      if((ButtonEvent.bits.b1 == FALSE) && ((ButtonPreviousStatus & BIT_0) == BIT_0)) {
        ButtonEvent.bits.b1 = TRUE;
        ButtonDebounceTime = DEFAULT_DEBOUNCE_DURATION;
        
      }	else if(((ButtonPreviousStatus & BIT_0) == 0)  && (ButtonEvent.bits.b1 == TRUE)) {
        ButtonEvent.bits.b2 = TRUE;
        ButtonDebounceTime = DEFAULT_DEBOUNCE_DURATION;
      }
      
      // Set status if falling and rising edges have been detected
      if (ButtonEvent.value == (BIT_0 | BIT_1 | BIT_2)) {
        ButtonEvent.value &= ~(BIT_1 | BIT_2);
        SetSta_ButtonClick();
        ClrSta_DebounceBusy();
      }
    }
  }   
}
#endif
/************************ UNABIZ firmware team ********************************/
/***************** (C) COPYRIGHT Holtek Semiconductor Inc. *****END OF FILE****/
