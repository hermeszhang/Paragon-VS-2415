;// TI File $Revision: /main/2 $
;// Checkin $Date: December 7, 2011   18:25:10 $
;//###########################################################################
;//
;// FILE:  F2805x_DBGIER._asm
;//
;// TITLE: Set the DBGIER register
;//
;// DESCRIPTION:
;//  
;//  Function to set the DBGIER register (for realtime emulation).
;//  Function Prototype: void SetDBGIER(Uint16)
;//  Useage: SetDBGIER(value);
;//  Input Parameters: Uint16 value = value to put in DBGIER register. 
;//  Return Value: none          
;//
;//###########################################################################
;// $TI Release: F2805x C/C++ Header Files and Peripheral Examples V100 $
;// $Release Date: November 30, 2011 $
;//###########################################################################	
		.global _SetDBGIER
		.text
		
_SetDBGIER:
		MOV 	*SP++,AL
		POP 	DBGIER
		LRETR
		
