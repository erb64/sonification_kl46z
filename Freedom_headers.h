#ifndef FREEDOM__HEADERS_H
#define FREEDOM__HEADERS_H

#include "mbed.h"

/*
The USB connections are on this end of the board

                                    J2_19   OO  J2_20
                                    J2_17   OO  J2_18
                                    J2_15   OO  J2_16
                                    J2_13   OO  J2_14
J3_2    OO  J3_1                    J2_11   OO  J2_12
J3_4    OO  J3_3                    J2_9    OO  J2_10
J3_6    OO  J3_5                    J2_7    OO  J2_8
J3_8    OO  J3_7                    J2_5    OO  J2_6
J3_10   OO  J3_9                    J2_3    OO  J2_4
J3_12   OO  J3_11                   J2_1    OO  J2_2
J3_14   OO  J3_13                   
J3_16   OO  J3_15                   J1_15   OO  J1_16
                                    J1_13   OO  J1_14
J4_2    OO  J4_1                    J1_11   OO  J1_12
J4_4    OO  J4_3                    J1_9    OO  J1_10
J4_6    OO  J4_5                    J1_7    OO  J1_8
J4_8    OO  J4_7                    J1_5    OO  J1_6
J4_10   OO  J4_9                    J1_3    OO  J1_4
J4_12   OO  J4_11                   J1_1    OO  J1_2

*/

#if   defined (TARGET_KL46Z)
PinName const J1_1 = PTB18 ;
PinName const J1_2 = PTA1 ;
PinName const J1_3 = PTB19 ;
PinName const J1_4 = PTA2 ;
PinName const J1_5 = PTC0 ;
PinName const J1_6 = PTD3 ;
PinName const J1_7 = PTC4 ;
PinName const J1_8 = PTA12 ;
PinName const J1_9 = PTC6 ;
PinName const J1_10 = PTA4 ;
PinName const J1_11 = PTC7 ;
PinName const J1_12 = PTA5 ;
PinName const J1_13 = PTC10 ;
PinName const J1_14 = PTC8 ;
PinName const J1_15 = PTC11 ;
PinName const J1_16 = PTC9 ;

PinName const J2_1 = PTC13 ;
PinName const J2_2 = PTA13 ;
PinName const J2_3 = PTC16 ;
PinName const J2_4 = PTD2 ;
PinName const J2_5 = PTA7 ;
PinName const J2_6 = PTD4 ;
PinName const J2_7 = PTA6 ;
PinName const J2_8 = PTD6 ;
PinName const J2_9 = PTA14 ;
PinName const J2_10 = PTD7 ;
PinName const J2_11 = PTA15 ;
PinName const J2_12 = PTD5 ;
PinName const J2_13 = PTA16 ;
PinName const J2_14 = NC ;  //GND
PinName const J2_15 = PTA17 ;
PinName const J2_16 = NC ;  //AREF
PinName const J2_17 = PTB9 ;
PinName const J2_18 = PTE0 ;
PinName const J2_19 = NC ; //NC
PinName const J2_20 = PTE1 ;

PinName const J3_1 = PTE31 ;
PinName const J3_2 = NC ;  //SDA_PTD5
PinName const J3_3 = PTE19 ;
PinName const J3_4 = NC ;  //3.3V
PinName const J3_5 = PTE18 ;
PinName const J3_6 = PTA20 ;  //RESET
PinName const J3_7 = PTE17 ;
PinName const J3_8 = NC ;  //3.3V
PinName const J3_9 = PTE16 ;
PinName const J3_10 = NC ;  //5V
PinName const J3_11 = PTE6 ;
PinName const J3_12 = NC ;  //GND
PinName const J3_13 = PTE3 ;
PinName const J3_14 = NC ;  //GND
PinName const J3_15 = PTE2 ;
PinName const J3_16 = NC ;  //VIN

PinName const J4_1 = PTE20 ;
PinName const J4_2 = PTB0 ;
PinName const J4_3 = PTE21 ;
PinName const J4_4 = PTB1 ;
PinName const J4_5 = PTE22 ;
PinName const J4_6 = PTB2 ;
PinName const J4_7 = PTE23 ;
PinName const J4_8 = PTB3 ;
PinName const J4_9 = PTB20 ;
PinName const J4_10 = PTC2 ;
PinName const J4_11 = PTE30 ;
PinName const J4_12 = PTC1 ;


#elif   defined (TARGET_KL25Z) 

PinName const J1_1 = PTC7 ;
PinName const J1_2 = PTA1 ; //?
PinName const J1_3 = PTBC0 ;
PinName const J1_4 = PTA2 ; //?
PinName const J1_5 = PTC3 ;
PinName const J1_6 = PTD4 ;
PinName const J1_7 = PTC4 ;
PinName const J1_8 = PTA12 ;
PinName const J1_9 = PTC5 ;
PinName const J1_10 = PTA4 ;
PinName const J1_11 = PTC6 ;
PinName const J1_12 = PTA5 ;
PinName const J1_13 = PTC10 ;
PinName const J1_14 = PTC8 ;
PinName const J1_15 = PTC11 ;
PinName const J1_16 = PTC9 ;

PinName const J2_1 = PTC12 ;
PinName const J2_2 = PTA13 ;
PinName const J2_3 = PTC13 ;
PinName const J2_4 = PTD5 ;
PinName const J2_5 = PTC16 ;
PinName const J2_6 = PTD0 ;
PinName const J2_7 = PTC17 ;
PinName const J2_8 = PTD2 ;
PinName const J2_9 = PTA16 ;
PinName const J2_10 = PTD3 ;
PinName const J2_11 = PTA17 ;
PinName const J2_12 = PTD1 ;
PinName const J2_13 = PTE31 ;
PinName const J2_14 = NC ;  //GND
PinName const J2_15 = NC ; //NC
PinName const J2_16 = NC ;  //AREF
PinName const J2_17 = PTD6 ;
PinName const J2_18 = PTE0 ;
PinName const J2_19 = PTD7 ; 
PinName const J2_20 = PTE1 ;

PinName const J3_1 = PTB8 ;
PinName const J3_2 = NC ;  //SDA_PTD5
PinName const J3_3 = PTB9 ;
PinName const J3_4 = NC ;  //3.3V
PinName const J3_5 = PTB10 ;
PinName const J3_6 = PTA20 ;  //RESET
PinName const J3_7 = PTB11 ;
PinName const J3_8 = NC ;  //3.3V
PinName const J3_9 = PTE2 ;
PinName const J3_10 = NC ;  //5V
PinName const J3_11 = PTE3 ;
PinName const J3_12 = NC ;  //GND
PinName const J3_13 = PTE4 ;
PinName const J3_14 = NC ;  //GND
PinName const J3_15 = PTE5 ;
PinName const J3_16 = NC ;  //VIN

PinName const J4_1 = PTE20 ;
PinName const J4_2 = PTB0 ;
PinName const J4_3 = PTE21 ;
PinName const J4_4 = PTB1 ;
PinName const J4_5 = PTE22 ;
PinName const J4_6 = PTB2 ;
PinName const J4_7 = PTE23 ;
PinName const J4_8 = PTB3 ;
PinName const J4_9 = PTE29 ;
PinName const J4_10 = PTC2 ;
PinName const J4_11 = PTE30 ;
PinName const J4_12 = PTC1 ;

#elif defined (TARGET_KL05Z)

PinName const J1_1 = NC ;
PinName const J1_2 = PTB2 ; //?
PinName const J1_3 = NC ;
PinName const J1_4 = PTB1 ; //?
PinName const J1_5 = NC ;
PinName const J1_6 = PTA11 ;
PinName const J1_7 = NC ;
PinName const J1_8 = PTB5 ;
PinName const J1_9 = NC ;
PinName const J1_10 = PTA10 ;
PinName const J1_11 = NC ;
PinName const J1_12 = PTA12 ;
PinName const J1_13 = NC ;
PinName const J1_14 = PTB6 ;
PinName const J1_15 = NC ;
PinName const J1_16 = PTB7 ;

PinName const J2_1 = NC ;
PinName const J2_2 = PTB10 ;
PinName const J2_3 = NC ;
PinName const J2_4 = PTB11 ;
PinName const J2_5 = NC ;
PinName const J2_6 = PTA5 ;
PinName const J2_7 = NC ;
PinName const J2_8 = PTA7 ;
PinName const J2_9 = NC ;
PinName const J2_10 = PTA6 ;
PinName const J2_11 = NC ;
PinName const J2_12 = PTB0 ;
PinName const J2_13 = NC ;
PinName const J2_14 = NC ;  //GND
PinName const J2_15 = NC ; //NC
PinName const J2_16 = NC ;  //AREF
PinName const J2_17 = NC ;
PinName const J2_18 = PTB4 ;
PinName const J2_19 = NC ; 
PinName const J2_20 = PTB3 ;

PinName const J3_1 = NC ;
PinName const J3_2 = NC ;  //SDA_PTD5
PinName const J3_3 = NC ;
PinName const J3_4 = NC ;  //3.3V
PinName const J3_5 = NC ;
PinName const J3_6 = NC ;  //RESET
PinName const J3_7 = NC ;
PinName const J3_8 = NC ;  //3.3V
PinName const J3_9 = NC ;
PinName const J3_10 = NC ;  //5V
PinName const J3_11 = NC ;
PinName const J3_12 = NC ;  //GND
PinName const J3_13 = NC ;
PinName const J3_14 = NC ;  //GND
PinName const J3_15 = NC ;
PinName const J3_16 = NC ;  //VIN

PinName const J4_1 = NC ;
PinName const J4_2 = PTB8 ;
PinName const J4_3 = NC ;
PinName const J4_4 = PTB9 ;
PinName const J4_5 = NC ;
PinName const J4_6 = PTA8 ;
PinName const J4_7 = NC ;
PinName const J4_8 = PTA0 ;
PinName const J4_9 = NC ;
PinName const J4_10 = PTA9 ;
PinName const J4_11 = NC ;
PinName const J4_12 = PTB13 ;

#elif defined (TARGET_K22F)

PinName const J1_1 = PTA5 ;
PinName const J1_2 = PTD2 ; //?
PinName const J1_3 = PTA13 ;
PinName const J1_4 = PTD3 ; //?
PinName const J1_5 = PTA12 ;
PinName const J1_6 = PTB16 ;
PinName const J1_7 = PTC8 ;
PinName const J1_8 = PTA2 ;
PinName const J1_9 = PTC9 ;
PinName const J1_10 = PTA4 ;
PinName const J1_11 = PTC7 ;
PinName const J1_12 = PTB10 ;
PinName const J1_13 = PTC10 ;
PinName const J1_14 = PTC3 ;
PinName const J1_15 = PTC5 ;
PinName const J1_16 = PTC6 ;

PinName const J2_1 = NC ;
PinName const J2_2 = PTB19 ;
PinName const J2_3 = NC ;
PinName const J2_4 = PTA1 ;
PinName const J2_5 = PTC0 ;
PinName const J2_6 = PTD4 ;
PinName const J2_7 = PTC11 ;
PinName const J2_8 = PTD6 ;
PinName const J2_9 = NC ;
PinName const J2_10 = PTD7 ;
PinName const J2_11 = NC ;
PinName const J2_12 = PTD5 ;
PinName const J2_13 = NC ;
PinName const J2_14 = NC ;  //GND
PinName const J2_15 = NC ; //NC
PinName const J2_16 = NC ;  //AREF
PinName const J2_17 = NC ;
PinName const J2_18 = PTE0 ;
PinName const J2_19 = NC ; 
PinName const J2_20 = PTE1 ;

PinName const J3_1 = NC ;
PinName const J3_2 = NC ;  //SDA_PTD5
PinName const J3_3 = NC ;
PinName const J3_4 = NC ;  //3.3V
PinName const J3_5 = NC ;
PinName const J3_6 = NC ;  //RESET
PinName const J3_7 = NC ;
PinName const J3_8 = NC ;  //3.3V
PinName const J3_9 = NC ;
PinName const J3_10 = NC ;  //5V
PinName const J3_11 = NC ;
PinName const J3_12 = NC ;  //GND
PinName const J3_13 = NC ;
PinName const J3_14 = NC ;  //GND
PinName const J3_15 = NC ;
PinName const J3_16 = NC ;  //VIN

PinName const J4_1 = NC ; //ADC0_DP0
PinName const J4_2 = PTB0 ;
PinName const J4_3 = NC ; //ADC0_DM0
PinName const J4_4 = PTB1 ;
PinName const J4_5 = NC ; //ADC0_DP3
PinName const J4_6 = PTC1 ;
PinName const J4_7 = NC ; //ADC0_DM3
PinName const J4_8 = PTC2 ;
PinName const J4_9 = PTC4 ;
PinName const J4_10 = PTB3 ;
PinName const J4_11 = NC ; //DAC0_OUT
PinName const J4_12 = PTB2 ;

#elif defined (TARGET_K20D50M)

PinName const J1_1 = PTD0 ;
PinName const J1_2 = PTE1 ; //?
PinName const J1_3 = PTC11 ;
PinName const J1_4 = PTE0 ; //?
PinName const J1_5 = PTC5 ;
PinName const J1_6 = PTA5 ;
PinName const J1_7 = PTC6 ;
PinName const J1_8 = PTD4 ;
PinName const J1_9 = PTC7 ;
PinName const J1_10 = PTC8 ;
PinName const J1_11 = PTA4 ;
PinName const J1_12 = PTA1 ;
PinName const J1_13 = PTD7 ;
PinName const J1_14 = PTC3 ;
PinName const J1_15 = PTC9 ;
PinName const J1_16 = PTC4 ;

PinName const J2_1 = PTC13 ;
PinName const J2_2 = PTA12 ;
PinName const J2_3 = PTC10 ;
PinName const J2_4 = PTA2 ;
PinName const J2_5 = NC ;
PinName const J2_6 = PTC2 ;
PinName const J2_7 = NC ;
PinName const J2_8 = PTD2 ;
PinName const J2_9 = NC ;
PinName const J2_10 = PTD3 ;
PinName const J2_11 = NC ;
PinName const J2_12 = PTD1 ;
PinName const J2_13 = NC ;
PinName const J2_14 = NC ;  //GND
PinName const J2_15 = NC ; //NC
PinName const J2_16 = NC ;  //AREF
PinName const J2_17 = NC ;
PinName const J2_18 = PTB3 ;
PinName const J2_19 = NC ; 
PinName const J2_20 = PTB2 ;

PinName const J3_1 = NC ;
PinName const J3_2 = NC ;  //SDA_PTD5
PinName const J3_3 = NC ;
PinName const J3_4 = NC ;  //3.3V
PinName const J3_5 = NC ;
PinName const J3_6 = NC ;  //RESET
PinName const J3_7 = NC ;
PinName const J3_8 = NC ;  //3.3V
PinName const J3_9 = NC ;
PinName const J3_10 = NC ;  //5V
PinName const J3_11 = NC ;
PinName const J3_12 = NC ;  //GND
PinName const J3_13 = NC ;
PinName const J3_14 = NC ;  //GND
PinName const J3_15 = NC ;
PinName const J3_16 = NC ;  //VIN

PinName const J4_1 = NC ; //CMP1_IN5
PinName const J4_2 = PTC0 ;
PinName const J4_3 = NC ; //CMP1_IN3
PinName const J4_4 = PTC1 ;
PinName const J4_5 = NC ; //ADC0_DP3
PinName const J4_6 = PTD6 ;
PinName const J4_7 = NC ; //ADC0_DM3
PinName const J4_8 = PTD5 ;
PinName const J4_9 = NC ; //ADC0_DP0
PinName const J4_10 = PTB1 ;
PinName const J4_11 = NC ; //ADC0_DM0;
PinName const J4_12 = PTB0 ;

#elif defined (TARGET_K64F)

PinName const J1_1 = PTB10 ;
PinName const J1_2 = PTC16 ; //?
PinName const J1_3 = PTB19 ;
PinName const J1_4 = PTC17 ; //?
PinName const J1_5 = PTC1 ;
PinName const J1_6 = PTB9 ;
PinName const J1_7 = PTC8 ;
PinName const J1_8 = PTA1 ;
PinName const J1_9 = PTC9 ;
PinName const J1_10 = PTB23 ;
PinName const J1_11 = PTC0 ;
PinName const J1_12 = PTA2 ;
PinName const J1_13 = PTC7 ;
PinName const J1_14 = PTC2 ;
PinName const J1_15 = PTC5 ;
PinName const J1_16 = PTC3 ;

PinName const J2_1 = PTE26 ;
PinName const J2_2 = PTA0 ;
PinName const J2_3 = NC ;
PinName const J2_4 = PTC4 ;
PinName const J2_5 = NC ; //ADC0_DP0
PinName const J2_6 = PTD0 ;
PinName const J2_7 = NC ; //ADC0_DM0
PinName const J2_8 = PTD2 ;
PinName const J2_9 = NC ;
PinName const J2_10 = PTD3 ;
PinName const J2_11 = NC ; //ADC1_DP0
PinName const J2_12 = PTD1 ;
PinName const J2_13 = NC ; //ADC1_DM0
PinName const J2_14 = NC ;  //GND
PinName const J2_15 = NC ; //NC
PinName const J2_16 = NC ;  //AREF
PinName const J2_17 = NC ; //ADC1_SE18
PinName const J2_18 = PTE25 ;
PinName const J2_19 = NC ; 
PinName const J2_20 = PTE24 ;

PinName const J3_1 = NC ;
PinName const J3_2 = NC ;  //SDA_PTD5
PinName const J3_3 = NC ;
PinName const J3_4 = NC ;  //3.3V
PinName const J3_5 = NC ;
PinName const J3_6 = NC ;  //RESET
PinName const J3_7 = NC ;
PinName const J3_8 = NC ;  //3.3V
PinName const J3_9 = NC ;
PinName const J3_10 = NC ;  //5V
PinName const J3_11 = NC ;
PinName const J3_12 = NC ;  //GND
PinName const J3_13 = NC ;
PinName const J3_14 = NC ;  //GND
PinName const J3_15 = NC ;
PinName const J3_16 = NC ;  //VIN

PinName const J4_1 = NC ; //ADC0_DP1
PinName const J4_2 = PTB2 ;
PinName const J4_3 = NC ; //ADCO_DM1
PinName const J4_4 = PTB3 ;
PinName const J4_5 = NC ; //ADC1_DP1
PinName const J4_6 = PTB10 ;
PinName const J4_7 = NC ; //ADC1_DM1
PinName const J4_8 = PTB11 ;
PinName const J4_9 = PTB20 ;
PinName const J4_10 = PTC11 ;
PinName const J4_11 = NC ; //DAC0_OUT
PinName const J4_12 = PTC10 ;

#else
  #error TARGET NOT DEFINED
#endif


#endif // FREEDOM__HEADERS_H