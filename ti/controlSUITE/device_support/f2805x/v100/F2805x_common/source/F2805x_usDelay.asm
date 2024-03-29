;// TI File $Revision: /main/2 $
;// Checkin $Date: December 7, 2011   18:25:03 $
;//###########################################################################
;//
;// FILE:  F2805x_usDelay._asm
;//
;// TITLE: Simple delay function
;//
;// DESCRIPTION:
;//  
;// This is a simple delay function that can be used to insert a specified
;// delay into code.  
;// 
;// This function is only accurate if executed from internal zero-waitstate
;// SARAM. If it is executed from waitstate memory then the delay will be
;// longer then specified.
;//
;//  *IMPORTANT*
;//  IF RUNNING FROM FLASH, PLEASE COPY OVER THE SECTION "ramfuncs"  FROM FLASH
;//  TO RAM PRIOR TO CALLING InitSysCtrl() OR InitAdc(). THIS PREVENTS THE MCU FROM THROWING
;//  AN EXCEPTION WHEN A CALL TO DELAY_US() IS MADE. 
;// 
;// To use this function:
;//
;//  1 - update the CPU clock speed in the F2805x_Examples.h
;//    file. For example:
;//    #define CPU_RATE 16.667L // for a 60MHz CPU clock speed
;//
;//  2 - Call this function by using the DELAY_US(A) macro
;//    that is defined in the F2805x_Examples.h file.  This macro
;//    will convert the number of microseconds specified
;//    into a loop count for use with this function.  
;//    This count will be based on the CPU frequency you specify.
;//
;//  3 - For the most accurate delay 
;//    - Execute this function in 0 waitstate RAM.  
;//    - Disable interrupts before calling the function
;//      If you do not disable interrupts, then think of
;//      this as an "at least" delay function as the actual
;//      delay may be longer. 
;//
;//  The C assembly call from the DELAY_US(time) macro will
;//  look as follows: 
;//
;//  extern void Delay(long LoopCount);                
;//
;//        MOV   AL,#LowLoopCount
;//        MOV   AH,#HighLoopCount
;//        LCR   _Delay
;//
;//  Or as follows (if count is less then 16-bits):
;//
;//        MOV   ACC,#LoopCount
;//        LCR   _Delay
;//
;//
;//###########################################################################
;// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
;// $Release Date: November 30, 2011 $
;//###########################################################################	



       .def _DSP28x_usDelay
       .sect "ramfuncs"

        .global  __DSP28x_usDelay
_DSP28x_usDelay:
        SUB    ACC,#1
        BF     _DSP28x_usDelay,GEQ    ;; Loop if ACC >= 0
        LRETR 

;There is a 9/10 cycle overhead and each loop
;takes five cycles. The LoopCount is given by
;the following formula:
;  DELAY_CPU_CYCLES = 9 + 5*LoopCount
; LoopCount = (DELAY_CPU_CYCLES - 9) / 5
; The macro DELAY_US(A) performs this calculation for you
;
;//===========================================================================
;// End of file.
;//===========================================================================
