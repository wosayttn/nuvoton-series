/**************************************************************************//**
 * @file     startup_m480.c
 * @version  V3.00
 * @brief    CMSIS Device Startup File for NuMicro M480
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2023 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include <inttypes.h>
#include <stdio.h>
#include "NuMicro.h"

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void (*VECTOR_TABLE_Type)(void);

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
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

/* External Interrupts */
void BOD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void IRC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void PWRWU_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RAMPE_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CKFAIL_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TAMPER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void WDT_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void WWDT_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EINT0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EINT1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EINT2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EINT3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EINT4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EINT5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void GPA_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void GPB_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void GPC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void GPD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void GPE_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void GPF_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void QSPI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void BRAKE0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EPWM0P0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EPWM0P1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EPWM0P2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void BRAKE1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EPWM1P0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EPWM1P1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EPWM1P2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TMR0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TMR1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TMR2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TMR3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void PDMA_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DAC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EADC00_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EADC01_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ACMP01_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EADC02_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EADC03_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void QSPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USBD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void OHCI_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USBOTG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SC0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SC1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SC2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SDH0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USBD20_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EMAC_TX_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EMAC_RX_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2S0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void OPA0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CRYPTO_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void GPG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EINT6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USCI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USCI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void BPWM0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void BPWM1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPIM_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CCAP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void QEI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void QEI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ECAP0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ECAP1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void GPH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EINT7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SDH1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EHCI_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USBOTG20_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TRNG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EADC10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EADC11_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EADC12_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EADC13_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));

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
    MemManage_Handler,                        /*   -12 MPU Fault Handler                                 */
    BusFault_Handler,                         /*   -11 Bus Fault Handler                                 */
    UsageFault_Handler,                       /*   -10 Usage Fault Handler                               */
    0,                                        /*    -9 Reserved                                          */
    0,                                        /*    -8 Reserved                                          */
    0,                                        /*    -7 Reserved                                          */
    0,                                        /*    -6 Reserved                                          */
    SVC_Handler,                              /*    -5 SVC Handler                                       */
    DebugMon_Handler,                         /*    -4 Debug Monitor Handler                             */
    0,                                        /*    -3 Reserved                                          */
    PendSV_Handler,                           /*    -2 PendSV Handler                                    */
    SysTick_Handler,                          /*    -1 SysTick Handler                                   */

    /* Interrupts */
    BOD_IRQHandler,                           /*    0: Brown Out detection                               */
    IRC_IRQHandler,                           /*    1: Internal RC                                       */
    PWRWU_IRQHandler,                         /*    2: Power down wake up                                */
    RAMPE_IRQHandler,                         /*    3: RAM parity error                                  */
    CKFAIL_IRQHandler,                        /*    4: Clock detection fail                              */
    Default_Handler,                          /*    5: Reserved                                          */
    RTC_IRQHandler,                           /*    6: Real Time Clock                                   */
    TAMPER_IRQHandler,                        /*    7: Tamper detection                                  */
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
    EPWM0P0_IRQHandler,                       /*   25: EPWM0P0                                           */
    EPWM0P1_IRQHandler,                       /*   26: EPWM0P1                                           */
    EPWM0P2_IRQHandler,                       /*   27: EPWM0P2                                           */
    BRAKE1_IRQHandler,                        /*   28: BRAKE1                                            */
    EPWM1P0_IRQHandler,                       /*   29: EPWM1P0                                           */
    EPWM1P1_IRQHandler,                       /*   30: EPWM1P1                                           */
    EPWM1P2_IRQHandler,                       /*   31: EPWM1P2                                           */
    TMR0_IRQHandler,                          /*   32: Timer 0                                           */
    TMR1_IRQHandler,                          /*   33: Timer 1                                           */
    TMR2_IRQHandler,                          /*   34: Timer 2                                           */
    TMR3_IRQHandler,                          /*   35: Timer 3                                           */
    UART0_IRQHandler,                         /*   36: UART0                                             */
    UART1_IRQHandler,                         /*   37: UART1                                             */
    I2C0_IRQHandler,                          /*   38: I2C0                                              */
    I2C1_IRQHandler,                          /*   39: I2C1                                              */
    PDMA_IRQHandler,                          /*   40: Peripheral DMA                                    */
    DAC_IRQHandler,                           /*   41: DAC                                               */
    EADC00_IRQHandler,                        /*   42: EADC0 interrupt source 0                          */
    EADC01_IRQHandler,                        /*   43: EADC0 interrupt source 1                          */
    ACMP01_IRQHandler,                        /*   44: ACMP0 and ACMP1                                   */
    Default_Handler,                          /*   45: Reserved                                          */
    EADC02_IRQHandler,                        /*   46: EADC0 interrupt source 2                          */
    EADC03_IRQHandler,                        /*   47: EADC0 interrupt source 3                          */
    UART2_IRQHandler,                         /*   48: UART2                                             */
    UART3_IRQHandler,                         /*   49: UART3                                             */
    QSPI1_IRQHandler,                         /*   50: QSPI1                                             */
    SPI1_IRQHandler,                          /*   51: SPI1                                              */
    SPI2_IRQHandler,                          /*   52: SPI2                                              */
    USBD_IRQHandler,                          /*   53: USB device                                        */
    OHCI_IRQHandler,                          /*   54: OHCI                                              */
    USBOTG_IRQHandler,                        /*   55: USB OTG                                           */
    CAN0_IRQHandler,                          /*   56: CAN0                                              */
    CAN1_IRQHandler,                          /*   57: CAN1                                              */
    SC0_IRQHandler,                           /*   58: SC0                                               */
    SC1_IRQHandler,                           /*   59: SC1                                               */
    SC2_IRQHandler,                           /*   60: SC2                                               */
    Default_Handler,                          /*   61: Reserved                                          */
    SPI3_IRQHandler,                          /*   62: SPI3                                              */
    Default_Handler,                          /*   63: Reserved                                          */
    SDH0_IRQHandler,                          /*   64: SDH0                                              */
    USBD20_IRQHandler,                        /*   65: USBD20                                            */
    EMAC_TX_IRQHandler,                       /*   66: EMAC_TX                                           */
    EMAC_RX_IRQHandler,                       /*   67: EMAC_RX                                           */
    I2S0_IRQHandler,                          /*   68: I2S0                                              */
    Default_Handler,                          /*   69: Reserved                                          */
    OPA0_IRQHandler,                          /*   70: OPA0                                              */
    CRYPTO_IRQHandler,                        /*   71: CRYPTO                                            */
    GPG_IRQHandler,                           /*   72: GPIO Port G                                       */
    EINT6_IRQHandler,                         /*   73: External Input 6                                  */
    UART4_IRQHandler,                         /*   74: UART4                                             */
    UART5_IRQHandler,                         /*   75: UART5                                             */
    USCI0_IRQHandler,                         /*   76: USCI0                                             */
    USCI1_IRQHandler,                         /*   77: USCI1                                             */
    BPWM0_IRQHandler,                         /*   78: BPWM0                                             */
    BPWM1_IRQHandler,                         /*   79: BPWM1                                             */
    SPIM_IRQHandler,                          /*   80: SPIM                                              */
    CCAP_IRQHandler,                          /*   81: CCAP                                              */
    I2C2_IRQHandler,                          /*   82: I2C2                                              */
    Default_Handler,                          /*   83: Reserved                                          */
    QEI0_IRQHandler,                          /*   84: QEI0                                              */
    QEI1_IRQHandler,                          /*   85: QEI1                                              */
    ECAP0_IRQHandler,                         /*   86: ECAP0                                             */
    ECAP1_IRQHandler,                         /*   87: ECAP1                                             */
    GPH_IRQHandler,                           /*   88: GPIO Port H                                       */
    EINT7_IRQHandler,                         /*   89: External Input 7                                  */
    SDH1_IRQHandler,                          /*   90: SDH1                                              */
    Default_Handler,                          /*   91: Reserved                                          */
    EHCI_IRQHandler,                          /*   92: EHCI                                              */
    USBOTG20_IRQHandler,                      /*   93: USBOTG20                                          */
    Default_Handler,                          /*   94: Reserved                                          */
    Default_Handler,                          /*   95: Reserved                                          */
    Default_Handler,                          /*   96: Reserved                                          */
    Default_Handler,                          /*   97: Reserved                                          */
    Default_Handler,                          /*   98: Reserved                                          */
    Default_Handler,                          /*   99: Reserved                                          */
    Default_Handler,                          /*  100: Reserved                                          */
    TRNG_IRQHandler,                          /*  101: TRNG                                              */
    UART6_IRQHandler,                         /*  102: UART6                                             */
    UART7_IRQHandler,                         /*  103: UART7                                             */
    EADC10_IRQHandler,                        /*  104: EADC1 interrupt source 0                          */
    EADC11_IRQHandler,                        /*  105: EADC1 interrupt source 1                          */
    EADC12_IRQHandler,                        /*  106: EADC1 interrupt source 2                          */
    EADC13_IRQHandler,                        /*  107: EADC1 interrupt source 3                          */
    CAN2_IRQHandler,                          /*  108: CAN2                                              */
};

#if defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif

__WEAK void Reset_Handler_PreInit(void)
{
}

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void)
{
    SYS_UnlockReg();

    Reset_Handler_PreInit();

#if !defined(ENABLE_SPIM_CACHE)
    CLK->AHBCLK |= CLK_AHBCLK_SPIMCKEN_Msk;  //Enable SPIM Clock.
    SPIM_DISABLE_CACHE();
    SPIM_ENABLE_CCM();
#endif	

    SystemInit();

    __PROGRAM_START();
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
