/**************************************************************************//**
 * @file     startup_M2354.c
 * @version  V1.10
 * @brief    CMSIS Device Startup File for NuMicro M2354
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2026 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

#include <inttypes.h>
#include <stdio.h>
#include "NuMicro.h"

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void(*VECTOR_TABLE_Type)(void);

/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;
extern uint32_t __STACK_LIMIT;

extern __NO_RETURN void __PROGRAM_START(void);

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void);
void Default_Handler(void);

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */
void NMI_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)   __attribute__((weak, alias("Default_Handler")));

/* External Interrupts */
void BOD_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 0 */
void IRC_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 1 */
void PWRWU_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 2 */
void SRAM_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 3 */
void CLKFAIL_IRQHandler(void)     __attribute__((weak, alias("Default_Handler"))); /* 4 */
void RTC_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 6 */
void RTC_TAMPER_IRQHandler(void)  __attribute__((weak, alias("Default_Handler"))); /* 7 */
void WDT_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 8 */
void WWDT_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 9 */
void EINT0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 10 */
void EINT1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 11 */
void EINT2_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 12 */
void EINT3_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 13 */
void EINT4_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 14 */
void EINT5_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 15 */
void GPA_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 16 */
void GPB_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 17 */
void GPC_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 18 */
void GPD_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 19 */
void GPE_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 20 */
void GPF_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 21 */
void QSPI0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 22 */
void SPI0_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 23 */
void BRAKE0_IRQHandler(void)      __attribute__((weak, alias("Default_Handler"))); /* 24 */
void EPWM0_P0_IRQHandler(void)    __attribute__((weak, alias("Default_Handler"))); /* 25 */
void EPWM0_P1_IRQHandler(void)    __attribute__((weak, alias("Default_Handler"))); /* 26 */
void EPWM0_P2_IRQHandler(void)    __attribute__((weak, alias("Default_Handler"))); /* 27 */
void BRAKE1_IRQHandler(void)      __attribute__((weak, alias("Default_Handler"))); /* 28 */
void EPWM1_P0_IRQHandler(void)    __attribute__((weak, alias("Default_Handler"))); /* 29 */
void EPWM1_P1_IRQHandler(void)    __attribute__((weak, alias("Default_Handler"))); /* 30 */
void EPWM1_P2_IRQHandler(void)    __attribute__((weak, alias("Default_Handler"))); /* 31 */
void TMR0_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 32 */
void TMR1_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 33 */
void TMR2_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 34 */
void TMR3_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 35 */
void UART0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 36 */
void UART1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 37 */
void I2C0_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 38 */
void I2C1_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 39 */
void PDMA0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 40 */
void DAC_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 41 */
void EADC0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 42 */
void EADC1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 43 */
void ACMP01_IRQHandler(void)      __attribute__((weak, alias("Default_Handler"))); /* 44 */
void EADC2_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 46 */
void EADC3_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 47 */
void UART2_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 48 */
void UART3_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 49 */
void SPI1_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 51 */
void SPI2_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 52 */
void USBD_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 53 */
void USBH_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 54 */
void USBOTG_IRQHandler(void)      __attribute__((weak, alias("Default_Handler"))); /* 55 */
void CAN0_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 56 */
void SC0_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 58 */
void SC1_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 59 */
void SC2_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 60 */
void SPI3_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 62 */
void SDH0_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 64 */
void I2S0_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 68 */
void OPA0_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 70 */
void CRPT_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 71 */
void GPG_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 72 */
void EINT6_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 73 */
void UART4_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 74 */
void UART5_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 75 */
void USCI0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 76 */
void USCI1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 77 */
void BPWM0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 78 */
void BPWM1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 79 */
void I2C2_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 82 */
void QEI0_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 84 */
void QEI1_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 85 */
void ECAP0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 86 */
void ECAP1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 87 */
void GPH_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 88 */
void EINT7_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 89 */
void PDMA1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 98 */
extern void SCU_IRQHandler(void);                                                  /* 99 */
void LCD_IRQHandler(void)         __attribute__((weak, alias("Default_Handler"))); /* 100 */
void TRNG_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 101 */
void KS_IRQHandler(void)          __attribute__((weak, alias("Default_Handler"))); /* 109 */
void TAMPER_IRQHandler(void)      __attribute__((weak, alias("Default_Handler"))); /* 110 */
void EWDT_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 111 */
void EWWDT_IRQHandler(void)       __attribute__((weak, alias("Default_Handler"))); /* 112 */
void NS_ISP_IRQHandler(void)      __attribute__((weak, alias("Default_Handler"))); /* 113 */
void TMR4_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 114 */
void TMR5_IRQHandler(void)        __attribute__((weak, alias("Default_Handler"))); /* 115 */

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/
#if defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpedantic"
#endif

const VECTOR_TABLE_Type __VECTOR_TABLE[] __VECTOR_TABLE_ATTRIBUTE =
{
    (VECTOR_TABLE_Type)(&__INITIAL_SP),       /*       Initial Stack Pointer                             */
    Reset_Handler,                            /*       Reset Handler                                     */
    NMI_Handler,                              /*   -14 NMI Handler                                       */
    HardFault_Handler,                        /*   -13 Hard Fault Handler                                */
    0,                                        /*   -12 Reserved (No MemManage on Cortex-M23 baseline)   */
    0,                                        /*   -11 Reserved (No BusFault on Cortex-M23 baseline)    */
    0,                                        /*   -10 Reserved (No UsageFault on Cortex-M23 baseline)  */
    0,                                        /*    -9 Reserved                                          */
    0,                                        /*    -8 Reserved                                          */
    0,                                        /*    -7 Reserved                                          */
    0,                                        /*    -6 Reserved                                          */
    SVC_Handler,                              /*    -5 SVC Handler                                       */
    0,                                        /*    -4 Reserved (No DebugMon on Cortex-M23 baseline)    */
    0,                                        /*    -3 Reserved                                          */
    PendSV_Handler,                           /*    -2 PendSV Handler                                    */
    SysTick_Handler,                          /*    -1 SysTick Handler                                   */

    /* Interrupts */
    BOD_IRQHandler,                           /*    0: Brown Out detection                               */
    IRC_IRQHandler,                           /*    1: Internal RC                                       */
    PWRWU_IRQHandler,                         /*    2: Power down wake up                                */
    SRAM_IRQHandler,                          /*    3: SRAM parity error                                 */
    CLKFAIL_IRQHandler,                       /*    4: Clock detection fail                              */
    Default_Handler,                          /*    5: Reserved                                          */
    RTC_IRQHandler,                           /*    6: Real Time Clock                                   */
    RTC_TAMPER_IRQHandler,                    /*    7: RTC tamper                                        */
    WDT_IRQHandler,                           /*    8: Watchdog timer                                    */
    WWDT_IRQHandler,                          /*    9: Window watchdog timer                             */
    EINT0_IRQHandler,                         /*   10: External Input 0                                  */
    EINT1_IRQHandler,                         /*   11: External Input 1                                  */
    EINT2_IRQHandler,                         /*   12: External Input 2                                  */
    EINT3_IRQHandler,                         /*   13: External Input 3                                  */
    EINT4_IRQHandler,                         /*   14: External Input 4                                  */
    EINT5_IRQHandler,                         /*   15: External Input 5                                  */
    GPA_IRQHandler,                           /*   16: GPIO Port A                                       */
    GPB_IRQHandler,                           /*   17: GPIO Port B                                       */
    GPC_IRQHandler,                           /*   18: GPIO Port C                                       */
    GPD_IRQHandler,                           /*   19: GPIO Port D                                       */
    GPE_IRQHandler,                           /*   20: GPIO Port E                                       */
    GPF_IRQHandler,                           /*   21: GPIO Port F                                       */
    QSPI0_IRQHandler,                         /*   22: QSPI0                                             */
    SPI0_IRQHandler,                          /*   23: SPI0                                              */
    BRAKE0_IRQHandler,                        /*   24: BRAKE0                                            */
    EPWM0_P0_IRQHandler,                      /*   25: EPWM0 period 0                                    */
    EPWM0_P1_IRQHandler,                      /*   26: EPWM0 period 1                                    */
    EPWM0_P2_IRQHandler,                      /*   27: EPWM0 period 2                                    */
    BRAKE1_IRQHandler,                        /*   28: BRAKE1                                            */
    EPWM1_P0_IRQHandler,                      /*   29: EPWM1 period 0                                    */
    EPWM1_P1_IRQHandler,                      /*   30: EPWM1 period 1                                    */
    EPWM1_P2_IRQHandler,                      /*   31: EPWM1 period 2                                    */
    TMR0_IRQHandler,                          /*   32: Timer 0                                           */
    TMR1_IRQHandler,                          /*   33: Timer 1                                           */
    TMR2_IRQHandler,                          /*   34: Timer 2                                           */
    TMR3_IRQHandler,                          /*   35: Timer 3                                           */
    UART0_IRQHandler,                         /*   36: UART0                                             */
    UART1_IRQHandler,                         /*   37: UART1                                             */
    I2C0_IRQHandler,                          /*   38: I2C0                                              */
    I2C1_IRQHandler,                          /*   39: I2C1                                              */
    PDMA0_IRQHandler,                         /*   40: Peripheral DMA 0                                  */
    DAC_IRQHandler,                           /*   41: DAC                                               */
    EADC0_IRQHandler,                         /*   42: EADC0                                             */
    EADC1_IRQHandler,                         /*   43: EADC1                                             */
    ACMP01_IRQHandler,                        /*   44: ACMP0 and ACMP1                                   */
    Default_Handler,                          /*   45: Reserved                                          */
    EADC2_IRQHandler,                         /*   46: EADC2                                             */
    EADC3_IRQHandler,                         /*   47: EADC3                                             */
    UART2_IRQHandler,                         /*   48: UART2                                             */
    UART3_IRQHandler,                         /*   49: UART3                                             */
    Default_Handler,                          /*   50: Reserved                                          */
    SPI1_IRQHandler,                          /*   51: SPI1                                              */
    SPI2_IRQHandler,                          /*   52: SPI2                                              */
    USBD_IRQHandler,                          /*   53: USB device                                        */
    USBH_IRQHandler,                          /*   54: USB host                                          */
    USBOTG_IRQHandler,                        /*   55: USB OTG                                           */
    CAN0_IRQHandler,                          /*   56: CAN0                                              */
    Default_Handler,                          /*   57: Reserved                                          */
    SC0_IRQHandler,                           /*   58: Smart Card 0                                      */
    SC1_IRQHandler,                           /*   59: Smart Card 1                                      */
    SC2_IRQHandler,                           /*   60: Smart Card 2                                      */
    Default_Handler,                          /*   61: Reserved                                          */
    SPI3_IRQHandler,                          /*   62: SPI3                                              */
    Default_Handler,                          /*   63: Reserved                                          */
    SDH0_IRQHandler,                          /*   64: SDH0                                              */
    Default_Handler,                          /*   65: Reserved                                          */
    Default_Handler,                          /*   66: Reserved                                          */
    Default_Handler,                          /*   67: Reserved                                          */
    I2S0_IRQHandler,                          /*   68: I2S0                                              */
    Default_Handler,                          /*   69: Reserved                                          */
    OPA0_IRQHandler,                          /*   70: OPA0                                              */
    CRPT_IRQHandler,                          /*   71: Crypto                                            */
    GPG_IRQHandler,                           /*   72: GPIO Port G                                       */
    EINT6_IRQHandler,                         /*   73: External Input 6                                  */
    UART4_IRQHandler,                         /*   74: UART4                                             */
    UART5_IRQHandler,                         /*   75: UART5                                             */
    USCI0_IRQHandler,                         /*   76: USCI0                                             */
    USCI1_IRQHandler,                         /*   77: USCI1                                             */
    BPWM0_IRQHandler,                         /*   78: BPWM0                                             */
    BPWM1_IRQHandler,                         /*   79: BPWM1                                             */
    Default_Handler,                          /*   80: Reserved                                          */
    Default_Handler,                          /*   81: Reserved                                          */
    I2C2_IRQHandler,                          /*   82: I2C2                                              */
    Default_Handler,                          /*   83: Reserved                                          */
    QEI0_IRQHandler,                          /*   84: QEI0                                              */
    QEI1_IRQHandler,                          /*   85: QEI1                                              */
    ECAP0_IRQHandler,                         /*   86: ECAP0                                             */
    ECAP1_IRQHandler,                         /*   87: ECAP1                                             */
    GPH_IRQHandler,                           /*   88: GPIO Port H                                       */
    EINT7_IRQHandler,                         /*   89: External Input 7                                  */
    Default_Handler,                          /*   90: Reserved                                          */
    Default_Handler,                          /*   91: Reserved                                          */
    Default_Handler,                          /*   92: Reserved                                          */
    Default_Handler,                          /*   93: Reserved                                          */
    Default_Handler,                          /*   94: Reserved                                          */
    Default_Handler,                          /*   95: Reserved                                          */
    Default_Handler,                          /*   96: Reserved                                          */
    Default_Handler,                          /*   97: Reserved                                          */
    PDMA1_IRQHandler,                         /*   98: Peripheral DMA 1                                  */
    SCU_IRQHandler,                           /*   99: Secure Crypto Unit                                */
    LCD_IRQHandler,                           /*  100: LCD                                               */
    TRNG_IRQHandler,                          /*  101: True random number generator                      */
    Default_Handler,                          /*  102: Reserved                                          */
    Default_Handler,                          /*  103: Reserved                                          */
    Default_Handler,                          /*  104: Reserved                                          */
    Default_Handler,                          /*  105: Reserved                                          */
    Default_Handler,                          /*  106: Reserved                                          */
    Default_Handler,                          /*  107: Reserved                                          */
    Default_Handler,                          /*  108: Reserved                                          */
    KS_IRQHandler,                            /*  109: Key Store                                         */
    TAMPER_IRQHandler,                        /*  110: Tamper detection                                  */
    EWDT_IRQHandler,                          /*  111: Enhanced watchdog timer                           */
    EWWDT_IRQHandler,                         /*  112: Enhanced window watchdog timer                    */
    NS_ISP_IRQHandler,                        /*  113: Non-secure ISP                                    */
    TMR4_IRQHandler,                          /*  114: Timer 4                                           */
    TMR5_IRQHandler,                          /*  115: Timer 5                                           */
};

#if defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif

__attribute__((weak)) void Reset_Handler_PreInit(void)
{
}

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void)
{
    unsigned int pc;

    __asm volatile ("mov %0, pc" : "=r"(pc));

    if (((int)(pc << 3)) >= 0)
    {
        SYS_UnlockReg();

        /* power gating */
        /* M32(0x400001f4) = 0xfffffffful; */
        *(volatile unsigned int *)0x400001F4u = 0xFFFFFFFFu;

        /* M32(0x400000dC) = 0ul; */
        *(volatile unsigned int *)0x400000DCu = 0x00000000u;

        /* Enable GPIO clks, SRAM clks, Trace clk */
        /* CLK->AHBCLK |= (0xffful << 20) | (1ul << 14); */
        *(volatile unsigned int *)0x40000204u |= 0xFFF02000u;
    }

    Reset_Handler_PreInit();
    SystemInit();
    (void)__PROGRAM_START();

    while (1);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
    while (1);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
#endif

static void SPD_Next(void)
{
    __NOP();
    __NOP();
    __NOP();
}

uint32_t __PC(void)
{
    uint32_t pc;

    __asm volatile ("mov %0, pc" : "=r"(pc));

    return pc;
}

void SPD_Return(void)
{
    volatile unsigned int *spd_vtor = (volatile unsigned int *)0x400002C0u;
    volatile unsigned int *new_vtor = (volatile unsigned int *)0x20010000u;

    *spd_vtor = 0x20010000u;
    new_vtor[0] = __get_MSP();
    new_vtor[1] = (unsigned int)SPD_Next;

    __WFI();

    while (1)
    {
        __NOP();
    }
}
