#ifndef ASCII_H
#define ASCII_H

#ifndef NULL
#define NULL 0
#endif
#ifndef NUL
#define NUL 0
#endif

#if NULL != 0
#error "unexpected value for NULL"
#endif
#if NUL != 0
#error "unexpected value for NUL"
#endif

#ifndef SOH //start of header
#define SOH 1
#endif

#if SOH != 1
#error "unexpected value for SOH"
#endif

#ifndef STX    //start of text block/end of header block
#define STX 2
#endif
#ifndef STXT    //start of text block/end of header block
#define STXT 2
#endif

#if STX != 2
#error "unexpected value for STX"
#endif
#if STXT != 2
#error "unexpected value for STXT"
#endif

#ifndef ETX        //end of text block
#define ETX 3
#endif
#ifndef ETXT        //end of text block
#define ETXT 3
#endif

#if ETX != 3
#error "unexpected value for ETX"
#endif
#if ETXT != 3
#error "unexpected value for ETXT"
#endif

#ifndef EOT //end of transmission 
#define EOT 4
#endif

#if EOT != 4
#error "unexpected value for EOT"
#endif

#ifndef ENQ //enquire
#define ENQ 5
#endif

#if ENQ != 5
#error "unexpected value for ENQ"
#endif

#ifndef ACK //acknowledge
#define ACK 6
#endif

#if ACK != 6
#error "unexpected value for ACK"
#endif

#ifndef BELL    //bell
#define BELL 7
#endif
#ifndef BEL   //bell
#define BEL 7
#endif

#if BELL != 7
#error "unexpected value for BELL"
#endif
#if BEL != 7
#error "unexpected value for BEL"
#endif

#ifndef BKSP    //backspace
#define BKSP 8
#endif
#ifndef BS    //backspace
#define BS 8
#endif

#if BKSP != 8
#error "unexpected value for BKSP"
#endif
#if BS != 8
#error "unexpected value for BS"
#endif

#ifndef HTAB    //horizontal tab
#define HTAB 9
#endif
#ifndef HT    //horizontal tab
#define HT 9
#endif

#if HTAB != 9
#error "unexpected value for HTAB"
#endif
#if HT != 9
#error "unexpected value for HT"
#endif

#ifndef LF  //line feed
#define LF 10
#endif

#if LF != 10
#error "unexpected value for LF"
#endif

#ifndef VTAB  //vertical tab
#define VTAB 11
#endif
#ifndef VT  //vertical tab
#define VT 11

#if VTAB != 11
#error "unexpected value for VTAB"
#endif
#if VT != 11
#error "unexpected value for VT"
#endif
#endif

#ifndef FF  //form feed
#define FF 12
#endif

#if FF != 12
#error "unexpected value for FF"
#endif

#ifndef CR  //carriage return
#define CR 13
#endif

#if CR != 13
#error "unexpected value for CR"
#endif

#ifndef SO  //shift out (switch to extended character set)
#define SO 14
#endif

#if SO != 14
#error "unexpected value for SO"
#endif

#ifndef SI  //shift in (switch to standard character set)
#define SI 15
#endif

#if SI != 15
#error "unexpected value for SI"
#endif

#ifndef DLE //data link escape (supplemental control character)
#define DLE 16
#endif

#if DLE != 16
#error "unexpected value for DLE"
#endif

#ifndef DC0 //device control 0 (data link escape is alternate mnemonic)
#define DC0 16
#endif

#if DC0 != 16
#error "unexpected value for DC0"
#endif

#ifndef DC1 //device control 1
#define DC1 17
#endif

#if DC1 != 17
#error "unexpected value for DC1"
#endif

#ifndef DC2 //device control 2
#define DC2 18
#endif

#if DC2 != 18
#error "unexpected value for DC2"
#endif

#ifndef DC3 //device control 3
#define DC3 19
#endif

#if DC3 != 19
#error "unexpected value for DC3"
#endif

#ifndef DC4 //;device control 4
#define DC4 20
#endif

#if DC4 != 20
#error "unexpected value for DC4"
#endif

#ifndef NAK //;negative acknowledge
#define NAK 21
#endif

#if NAK != 21
#error "unexpected value for NAK"
#endif

#ifndef SYN //;synchronous idle
#define SYN 22
#endif

#if SYN != 22
#error "unexpected value for SYN"
#endif

#ifndef ETB //;end of transmission block
#define ETB 23
#endif

#if ETB != 23
#error "unexpected value for ETB"
#endif

#ifndef CAN //;cancel
#define CAN 24
#endif

#if CAN != 24
#error "unexpected value for CAN"
#endif

#ifndef EM  //;end of medium
#define EM 25
#endif

#if EM != 25
#error "unexpected value for EM"
#endif

#ifndef SUB //;substitute
#define SUB 26
#endif

#if SUB != 26
#error "unexpected value for SUB"
#endif

#ifndef ESC //;escape
#define ESC 27
#endif

#if ESC != 27
#error "unexpected value for ESC"
#endif

#ifndef FS  //;file separator
#define FS 28
#endif

#if FS != 28
#error "unexpected value for FS"
#endif

#ifndef GS  //;group separator
#define GS 29
#endif

#if GS != 29
#error "unexpected value for GS"
#endif

#ifndef RS  //;record separator
#define RS 30
#endif

#if RS != 30
#error "unexpected value for RS"
#endif

#ifndef US  //;unit separator
#define US 31
#endif

#if US != 31
#error "unexpected value for US"
#endif

#ifndef SPACE   //;space character
#define SPACE   32
#endif

#if SPACE != 32
#error "unexpected value for SPACE"
#endif

#ifndef DOUBLE_QUOTE    
#define DOUBLE_QUOTE  0x22  //34
#endif

#if DOUBLE_QUOTE != 0X22
#error "unexpected value for DOUBLE_QUOTE"
#endif

#ifndef SINGLE_QUOTE    
#define SINGLE_QUOTE  0x27  //39
#endif

#if SINGLE_QUOTE != 0X27
#error "unexpected value for SINGLE_QUOTE"
#endif

#ifndef COMMA   
#define COMMA  0x2C //44
#endif

#if COMMA != 0X2C
#error "unexpected value for COMMA"
#endif

#ifndef DELETE  
#define DELETE  0x7F    //127
#endif
#ifndef DEL  
#define DEL  0x7F   //127
#endif

#if DELETE != 0X7F
#error "unexpected value for DELETE"
#endif
#if DEL != 0X7F
#error "unexpected value for DEL"
#endif

#endif      //ASCII_H