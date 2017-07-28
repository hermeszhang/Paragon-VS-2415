;// TI File $Revision: /main/2 $
;// Checkin $Date: December 7, 2011   18:16:49 $
;//###########################################################################
;//
;// FILE:  F2805x_Cla._asm
;//
;// TITLE: CLA Assembly Code.
;//
;// This file contains the CLA assembly code.  When building the project
;// containing this file, use C28x codegen V5.2.0 or later with the switch
;// --cla_support=cla0
;//
;//###########################################################################
;// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
;// $Release Date: November 30, 2011 $
;//###########################################################################

;// Include variables and constants that will be shared in the
;// C28x C-code and CLA assembly code.  This is accomplished by
;// using .cdecls to include a C-code header file that contains
;// these variables and constants

      .cdecls   C,LIST,"CLAShared.h"

;// To include an MDEBUGSTOP (CLA breakpoint) as the first instruction
;// of each task, set CLA_DEBUG to 1.  Use any other value to leave out
;// the MDEBUGSTOP instruction.

CLA_DEBUG .set  1

;// CLA code must be within its own assembly section and must be
;// even aligned.  Note: since all CLA instructions are 32-bit
;// this alignment naturally occurs and the .align 2 is most likely
;// redundant

      .sect    "Cla1Prog"
      .align  2


_Cla1Prog_Start:

_Cla1Task1:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T1End:


_Cla1Task2:
    .if CLA_DEBUG == 1
        MDEBUGSTOP
    .endif
;==============================================
; This task logs the last NUM_DATA_POINTS
; ADCRESULT1 values in the array VoltageCLA
;
; When the last element in the array has been
; filled, the task will go back to the
; the first element.
;
; Before starting the ADC conversions, force
; Task 8 to initialize the ConversionCount to zero
;
;==============================================
    MMOVZ16    MR0,  @_ConversionCount        ;1 Current Conversion
    MMOV16     MAR1, MR0, #_VoltageCLA        ;2 Point to VoltageCLA[ConversionCount]
    MUI16TOF32 MR0,  MR0                      ;3 Convert count to float32
    MADDF32    MR0,  MR0, #1.0                ;4 Add 1 to conversion count
    MCMPF32    MR0,  #NUM_DATA_POINTS.0       ;5 Compare count to max
    MF32TOUI16 MR0,  MR0                      ;6 Convert count to Uint16
    MNOP                                      ;7 Wait till I8 to read result
    MMOVZ16    MR2,  @_AdcResult.ADCRESULT1   ;8 Read ADCRESULT1
    MMOV16     *MAR1, MR2                     ;  Store ADCRESULT1
    MBCNDD     _RestartCount, GEQ             ;  If count >= NUM_DATA_POINTS
    MMOVIZ     MR1,  #0.0                     ;  Always executed: load MR1 with 0
    MNOP
    MNOP
    MMOV16      @_ConversionCount, MR0        ;  If branch not taken, store current count
    MSTOP
_RestartCount
    MMOV16      @_ConversionCount, MR1        ;  If branch taken, restart count
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T2End:


_Cla1Task3:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T3End:


_Cla1Task4:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T4End:


_Cla1Task5:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T5End:

_Cla1Task6:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T6End:

_Cla1Task7:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T7End:

_Cla1Task8:
;==============================================
; This task initializes the ConversionCount
; to zero
;==============================================
    MMOVIZ  MR0,  #0.0
    MMOV16  @_ConversionCount, MR0
    MSTOP
_Cla1T8End:



_Cla1Prog_End:


    .end
    .include "CLAShared.h"




