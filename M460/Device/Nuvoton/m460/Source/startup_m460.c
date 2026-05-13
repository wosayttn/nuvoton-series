/**************************************************************************//**
 * @file     startup_m460.c
 * @version  V3.00
 * @brief    CMSIS Device Startup File for NuMicro M460
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
void BOD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 0: Brown Out detection
void IRC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 1: Internal RC
void PWRWU_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 2: Power down wake up
void RAMPE_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 3: RAM parity error
void CKFAIL_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 4: Clock detection fail
void ISP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 5: ISP
void RTC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 6: Real Time Clock
void TAMPER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 7: TAMPER
void WDT_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 8: Watchdog timer
void WWDT_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 9: Window watchdog timer
void EINT0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 10: External Input 0
void EINT1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 11: External Input 1
void EINT2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 12: External Input 2
void EINT3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 13: External Input 3
void EINT4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 14: External Input 4
void EINT5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 15: External Input 5
void GPA_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 16: GPIO Port A
void GPB_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 17: GPIO Port B
void GPC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 18: GPIO Port C
void GPD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 19: GPIO Port D
void GPE_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 20: GPIO Port E
void GPF_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 21: GPIO Port F
void QSPI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 22: QSPI0
void SPI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 23: SPI0
void BRAKE0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 24: BRAKE0
void EPWM0P0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 25: EPWM0P0
void EPWM0P1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 26: EPWM0P1
void EPWM0P2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 27: EPWM0P2
void BRAKE1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 28: BRAKE1
void EPWM1P0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 29: EPWM1P0
void EPWM1P1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 30: EPWM1P1
void EPWM1P2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 31: EPWM1P2
void TMR0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 32: Timer 0
void TMR1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 33: Timer 1
void TMR2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 34: Timer 2
void TMR3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 35: Timer 3
void UART0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 36: UART0
void UART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 37: UART1
void I2C0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 38: I2C0
void I2C1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 39: I2C1
void PDMA0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 40: Peripheral DMA 0
void DAC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 41: DAC
void EADC00_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 42: EADC0 interrupt source 0
void EADC01_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 43: EADC0 interrupt source 1
void ACMP01_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 44: ACMP0 and ACMP1
void ACMP23_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 45: ACMP2 and ACMP3
void EADC02_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 46: EADC0 interrupt source 2
void EADC03_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 47: EADC0 interrupt source 3
void UART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 48: UART2
void UART3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 49: UART3
void QSPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 50: QSPI1
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 51: SPI1
void SPI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 52: SPI2
void USBD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 53: USBD
void OHCI_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 54: OHCI
void USBOTG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 55: USBOTG
void BMC_Handler(void) __attribute__((weak, alias("Default_Handler")));           // 56: BMC
void SPI5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 57: SPI5
void SC0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 58: SC0
void SC1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 59: SC1
void SC2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 60: SC2
void GPJ_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 61: GPJ
void SPI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 62: SPI3
void SPI4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 63: SPI4
void SDH0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 64: SDH0
void USBD20_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 65: HSUSBD
void EMAC0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 66: EMAC0
void I2S0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 68: I2S0
void I2S1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 69: I2S1
void SPI6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 70: SPI6
void CRPT_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 71: CRPT
void GPG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 72: GPIO Port G
void EINT6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 73: External Input 6
void UART4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 74: UART4
void UART5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 75: UART5
void USCI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 76: USCI0
void SPI7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 77: SPI7
void BPWM0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 78: BPWM0
void BPWM1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 79: BPWM1
void SPIM_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 80: SPIM
void CCAP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 81: CCAP
void I2C2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 82: I2C2
void I2C3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 83: I2C3
void EQEI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 84: EQEI0
void EQEI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 85: EQEI1
void ECAP0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 86: ECAP0
void ECAP1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 87: ECAP1
void GPH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 88: GPIO Port H
void EINT7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 89: External Input 7
void SDH1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 90: SDH1
void PSIO_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 91: PSIO
void EHCI_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 92: EHCI
void USBOTG20_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));   // 93: HSOTG
void ECAP2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 94: ECAP2
void ECAP3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 95: ECAP3
void KPI_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 96: KPI
void HBI_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 97: HBI
void PDMA1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 98: PDMA1
void UART8_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 99: UART8
void UART9_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 100: UART9
void TRNG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 101: TRNG
void UART6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 102: UART6
void UART7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 103: UART7
void EADC10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 104: EADC10
void EADC11_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 105: EADC11
void EADC12_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 106: EADC12
void EADC13_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 107: EADC13
void SPI8_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 108: SPI8
void KS_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));         // 109: KS
void GPI_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));        // 110: GPI
void SPI9_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 111: SPI9
void CANFD00_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 112: CAN FD 00
void CANFD01_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 113: CAN FD 01
void CANFD10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 114: CAN FD 10
void CANFD11_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 115: CAN FD 11
void EQEI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 116: EQEI2
void EQEI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 117: EQEI3
void I2C4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));       // 118: I2C4
void SPI10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));      // 119: SPI10
void CANFD20_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 120: CAN FD 20
void CANFD21_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 121: CAN FD 21
void CANFD30_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 122: CAN FD 30
void CANFD31_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));    // 123: CAN FD 31
void EADC20_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 124: EADC20
void EADC21_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 125: EADC21
void EADC22_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 126: EADC22
void EADC23_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));     // 127: EADC23

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/
#if defined ( __GNUC__ )
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
    PendSV_Handler,                           /*    -2 PendSV Handler Handler                            */
    SysTick_Handler,                          /*    -1 SysTick Handler                                   */

    /* Interrupts */
    BOD_IRQHandler,                           /*    0: BOD                                               */
    IRC_IRQHandler,                           /*    1: IRC                                               */
    PWRWU_IRQHandler,                         /*    2: PWRWU                                             */
    RAMPE_IRQHandler,                         /*    3: RAMPE                                             */
    CKFAIL_IRQHandler,                        /*    4: CKFAIL                                            */
    ISP_IRQHandler,                           /*    5: ISP                                               */
    RTC_IRQHandler,                           /*    6: RTC                                               */
    TAMPER_IRQHandler,                        /*    7: TAMPER                                            */
    WDT_IRQHandler,                           /*    8: WDT                                               */
    WWDT_IRQHandler,                          /*    9: WWDT                                              */
    EINT0_IRQHandler,                         /*   10: EINT0                                             */
    EINT1_IRQHandler,                         /*   11: EINT1                                             */
    EINT2_IRQHandler,                         /*   12: EINT2                                             */
    EINT3_IRQHandler,                         /*   13: EINT3                                             */
    EINT4_IRQHandler,                         /*   14: EINT4                                             */
    EINT5_IRQHandler,                         /*   15: EINT5                                             */
    GPA_IRQHandler,                           /*   16: GPA                                               */
    GPB_IRQHandler,                           /*   17: GPB                                               */
    GPC_IRQHandler,                           /*   18: GPC                                               */
    GPD_IRQHandler,                           /*   19: GPD                                               */
    GPE_IRQHandler,                           /*   20: GPE                                               */
    GPF_IRQHandler,                           /*   21: GPF                                               */
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
    TMR0_IRQHandler,                          /*   32: TIMER0                                            */
    TMR1_IRQHandler,                          /*   33: TIMER1                                            */
    TMR2_IRQHandler,                          /*   34: TIMER2                                            */
    TMR3_IRQHandler,                          /*   35: TIMER3                                            */
    UART0_IRQHandler,                         /*   36: UART0                                             */
    UART1_IRQHandler,                         /*   37: UART1                                             */
    I2C0_IRQHandler,                          /*   38: I2C0                                              */
    I2C1_IRQHandler,                          /*   39: I2C1                                              */
    PDMA0_IRQHandler,                         /*   40: PDMA0                                             */
    DAC_IRQHandler,                           /*   41: DAC                                               */
    EADC00_IRQHandler,                        /*   42: EADC00                                            */
    EADC01_IRQHandler,                        /*   43: EADC01                                            */
    ACMP01_IRQHandler,                        /*   44: ACMP01                                            */
    ACMP23_IRQHandler,                        /*   45: ACMP23                                            */
    EADC02_IRQHandler,                        /*   46: EADC02                                            */
    EADC03_IRQHandler,                        /*   47: EADC03                                            */
    UART2_IRQHandler,                         /*   48: UART2                                             */
    UART3_IRQHandler,                         /*   49: UART3                                             */
    QSPI1_IRQHandler,                         /*   50: QSPI1                                             */
    SPI1_IRQHandler,                          /*   51: SPI1                                              */
    SPI2_IRQHandler,                          /*   52: SPI2                                              */
    USBD_IRQHandler,                          /*   53: USBD                                              */
    OHCI_IRQHandler,                          /*   54: OHCI                                              */
    USBOTG_IRQHandler,                        /*   55: OTG                                               */
    BMC_Handler,                              /*   56: BMC                                               */
    SPI5_IRQHandler,                          /*   57: SPI5                                              */
    SC0_IRQHandler,                           /*   58: SC0                                               */
    SC1_IRQHandler,                           /*   59: SC1                                               */
    SC2_IRQHandler,                           /*   60: SC2                                               */
    GPJ_IRQHandler,                           /*   61: GPJ                                               */
    SPI3_IRQHandler,                          /*   62: SPI3                                              */
    SPI4_IRQHandler,                          /*   63: SPI4                                              */
    SDH0_IRQHandler,                          /*   64: SDH0                                              */
    USBD20_IRQHandler,                        /*   65: HSUSBD                                            */
    EMAC0_IRQHandler,                         /*   66: EMAC0                                             */
    0,                                        /*   67: Reserved                                          */
    I2S0_IRQHandler,                          /*   68: I2S0                                              */
    I2S1_IRQHandler,                          /*   69: I2S1                                              */
    SPI6_IRQHandler,                          /*   70: SPI6                                              */
    CRPT_IRQHandler,                          /*   71: CRPT                                              */
    GPG_IRQHandler,                           /*   72: GPG                                               */
    EINT6_IRQHandler,                         /*   73: EINT6                                             */
    UART4_IRQHandler,                         /*   74: UART4                                             */
    UART5_IRQHandler,                         /*   75: UART5                                             */
    USCI0_IRQHandler,                         /*   76: USCI0                                             */
    SPI7_IRQHandler,                          /*   77: SPI7                                              */
    BPWM0_IRQHandler,                         /*   78: BPWM0                                             */
    BPWM1_IRQHandler,                         /*   79: BPWM1                                             */
    SPIM_IRQHandler,                          /*   80: SPIM                                              */
    CCAP_IRQHandler,                          /*   81: CCAP                                              */
    I2C2_IRQHandler,                          /*   82: I2C2                                              */
    I2C3_IRQHandler,                          /*   83: I2C3                                              */
    EQEI0_IRQHandler,                         /*   84: EQEI0                                             */
    EQEI1_IRQHandler,                         /*   85: EQEI1                                             */
    ECAP0_IRQHandler,                         /*   86: ECAP0                                             */
    ECAP1_IRQHandler,                         /*   87: ECAP1                                             */
    GPH_IRQHandler,                           /*   88: GPH                                               */
    EINT7_IRQHandler,                         /*   89: EINT7                                             */
    SDH1_IRQHandler,                          /*   90: SDH1                                              */
    PSIO_IRQHandler,                          /*   91: PSIO                                              */
    EHCI_IRQHandler,                          /*   92: EHCI                                              */
    USBOTG20_IRQHandler,                      /*   93: HSOTG                                             */
    ECAP2_IRQHandler,                         /*   94: ECAP2                                             */
    ECAP3_IRQHandler,                         /*   95: ECAP3                                             */
    KPI_IRQHandler,                           /*   96: KPI                                               */
    HBI_IRQHandler,                           /*   97: HBI                                               */
    PDMA1_IRQHandler,                         /*   98: PDMA1                                             */
    UART8_IRQHandler,                         /*   99: UART8                                             */
    UART9_IRQHandler,                         /*  100: UART9                                             */
    TRNG_IRQHandler,                          /*  101: TRNG                                              */
    UART6_IRQHandler,                         /*  102: UART6                                             */
    UART7_IRQHandler,                         /*  103: UART7                                             */
    EADC10_IRQHandler,                        /*  104: EADC10                                            */
    EADC11_IRQHandler,                        /*  105: EADC11                                            */
    EADC12_IRQHandler,                        /*  106: EADC12                                            */
    EADC13_IRQHandler,                        /*  107: EADC13                                            */
    SPI8_IRQHandler,                          /*  108: SPI8                                              */
    KS_IRQHandler,                            /*  109: KS                                                */
    GPI_IRQHandler,                           /*  110: GPI                                               */
    SPI9_IRQHandler,                          /*  111: SPI9                                              */
    CANFD00_IRQHandler,                       /*  112: CANFD00                                           */
    CANFD01_IRQHandler,                       /*  113: CANFD01                                           */
    CANFD10_IRQHandler,                       /*  114: CANFD10                                           */
    CANFD11_IRQHandler,                       /*  115: CANFD11                                           */
    EQEI2_IRQHandler,                         /*  116: EQEI2                                             */
    EQEI3_IRQHandler,                         /*  117: EQEI3                                             */
    I2C4_IRQHandler,                          /*  118: I2C4                                              */
    SPI10_IRQHandler,                         /*  119: SPI10                                             */
    CANFD20_IRQHandler,                       /*  120: CANFD20                                           */
    CANFD21_IRQHandler,                       /*  121: CANFD21                                           */
    CANFD30_IRQHandler,                       /*  122: CANFD30                                           */
    CANFD31_IRQHandler,                       /*  123: CANFD31                                           */
    EADC20_IRQHandler,                        /*  124: EADC20                                            */
    EADC21_IRQHandler,                        /*  125: EADC21                                            */
    EADC22_IRQHandler,                        /*  126: EADC22                                            */
    EADC23_IRQHandler,                        /*  127: EADC23                                            */
};

#if defined ( __GNUC__ )
    #pragma GCC diagnostic pop
#endif

__WEAK void Reset_Handler_PreInit(void)
{
    // Empty function
}

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void)
{
    SYS_UnlockReg();

    Reset_Handler_PreInit();

    SystemInit();

    __PROGRAM_START();      // Enter PreMain (C library entry point)
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
