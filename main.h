

#ifndef __UNA_MAIN_H

#define __UNA_MAIN_H


/* Exported macro ------------------------------------------------------------*/
#define  IRQ_Disable()        (_emi) = FALSE
#define  IRQ_Enable()         (_emi) = TRUE

// System Flags
#define  ChkSys_TimerIsr()    SYSTEM_F.bits.b0
#define  SetSys_TimerIsr()    SYSTEM_F.bits.b0 = TRUE
#define  ClrSys_TimerIsr()    SYSTEM_F.bits.b0 = FALSE

#define  ChkSys_Delay()       SYSTEM_F.bits.b1
#define  SetSys_Delay()       SYSTEM_F.bits.b1 = TRUE
#define  ClrSys_Delay()       SYSTEM_F.bits.b1 = FALSE

// Status Flags
#define  ChkSta_DevBusy()     (STATUS_F.value & 0xFF)
#define  SetSta_DevBusy()     
#define  ClrSta_DevBusy()     

#define  ChkSta_TxBusy()      STATUS_F.bits.b1
#define  SetSta_TxBusy()      STATUS_F.bits.b1 = TRUE
#define  ClrSta_TxBusy()      STATUS_F.bits.b1 = FALSE

#define  ChkSta_ButtonClick() STATUS_F.bits.b2
#define  SetSta_ButtonClick() STATUS_F.bits.b2 = TRUE
#define  ClrSta_ButtonClick() STATUS_F.bits.b2 = FALSE

#define  ChkSta_DebounceBusy   STATUS_F.bits.b3
#define  SetSta_DebounceBusy() STATUS_F.bits.b3 = TRUE
#define  ClrSta_DebounceBusy() STATUS_F.bits.b3 = FALSE


/* Inline function ------------------------------------------------------------*/
static inline void mcu_initial(void)
{   
   _lvrc = 0x55;
   _pawu = 0xFF;
   _papu = 0x3A;
   _pac  = 0x3A;
   _pa   = 0XFF;
   //_pbc  = 0xCF;     //LED PB4 Data 
   _pbc = 0xFF;
   _pbpu = 0xFF;  
}

//;clear RAM (080H--0FFH)
static inline void ClrRAM(void)
{      
   asm("mov a,80h");	 
   ASM_A2M(_mp1l);
   asm("mov a,80h");
   ASM_CLR(_iar1);
   ASM_INC(_mp1l);
   asm("sdz acc");
   asm("jmp $-3");        
   if(_mp1h == 0)
   {
     _mp1h =1;
     asm("jmp $-11");
   }
   _mp1h =0;
}

/*
 * @brief Power on Init
 * @param None
 * @retval None
*/
static void PowerOnInit(void) 
{
  _wdtc = 0xAF; //0x57;
  _scc =  0x20;				 //set system clock = 8MHz
  ClrRAM();
}

/*
 * @brief Wake up Init
 * @param None
 * @retval None
*/
static void WakeupInit(void) 
{
  _pwrc = 0x00;
  _wdtc = 0xAF; //0x57;
  
  GCC_CLRWDT();
  mcu_initial();
  MX_GPIO_Init();
  // GPIO_DebounceInit();
  // MX_RF_Init();
  // MX_Timer_Init();
  IRQ_Enable();
}

/*
 * @brief Deep Sleep 
 * @param None
 * @retval None
*/
static void SleepMode(void) 
{
  MX_GPIO_DeInit();
  // GPIO_DebounceDeInit();
  
  _wdtc = 0xAF;
  // MX_RF_DeInit();
  IRQ_Disable();
  
  //Entry deep_sleep mode
  _pwrc = 0x03;
  GCC_HALT();
}

#endif