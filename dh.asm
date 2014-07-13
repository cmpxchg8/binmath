
;
; Diffie-Hellman-Merkle Key Exchange
; Copyright (c) 2012, 2014 Kevin Devine
;
; A=EA4484B562D91C7154728389BD132784765824A0217BB013A3878E44F...
; B=E5098C054DD3D42CDC29E026C91DB1AD2CF1E9288E9476C531298C68C...
;
; s1=B02315FB5EBF1EE63A5FF5E221BBD7A908115817C99AFBD1559AAC79...
; s2=B02315FB5EBF1EE63A5FF5E221BBD7A908115817C99AFBD1559AAC79...
;
; Key exchange succeeded
;
.586
.model flat, stdcall

MAX_NUM  equ 128 ; 1024 bits
MAX_BITS equ MAX_NUM*8

option casemap:none
.nolist
.nocref
WIN32_LEAN_AND_MEAN equ 1
include <windows.inc>
include <stdio.inc>
include <stdlib.inc>
includelib <msvcrt.lib>
.list
.cref

CStr macro szText:VARARG
  local dbText
.data
dbText db szText, 0
.code
exitm <offset dbText>
endm

modexp proto C x:DWORD, l:DWORD, b:DWORD, e:DWORD, m:DWORD

.data

; Second Oakley Group
; prime is 2^1024 - 2^960 - 1 + 2^64 * { [2^894 pi] + 129093 }
; https://www.ietf.org/rfc/rfc2409.txt
p_grp db 0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,081h,053h,0E6h,0ECh,051h,066h,028h,049h
      db 0E6h,01Fh,04Bh,07Ch,011h,024h,09Fh,0AEh,0A5h,09Fh,089h,05Ah,0FBh,06Bh,038h,0EEh
      db 0EDh,0B7h,006h,0F4h,0B6h,05Ch,0FFh,00Bh,06Bh,0EDh,037h,0A6h,0E9h,042h,04Ch,0F4h
      db 0C6h,07Eh,05Eh,062h,076h,0B5h,085h,0E4h,045h,0C2h,051h,06Dh,06Dh,035h,0E1h,04Fh
      db 037h,014h,05Fh,0F2h,06Dh,00Ah,02Bh,030h,01Bh,043h,03Ah,0CDh,0B3h,019h,095h,0EFh
      db 0DDh,004h,034h,08Eh,079h,008h,04Ah,051h,022h,09Bh,013h,03Bh,0A6h,0BEh,00Bh,002h
      db 074h,0CCh,067h,08Ah,008h,04Eh,002h,029h,0D1h,01Ch,0DCh,080h,08Bh,062h,0C6h,0C4h
      db 034h,0C2h,068h,021h,0A2h,0DAh,00Fh,0C9h,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh
  
g_grp db 2
      db MAX_NUM dup (0)

; x and y would be random integers chosen by Bob and Alice
; I've predefined them here ONLY for demonstration.
x_alice db 90, 54, 12, 54, 76, 12
        db MAX_NUM dup (0)
        
y_bob   db 12, 43, 54, 65, 23, 12
        db MAX_NUM dup (0)
.code

dump_hex proc uses esi edi ebx txt:DWORD, buf:DWORD, len:DWORD
    mov   esi, [buf]
    mov   ebx, [len]
    invoke printf, txt
    .while ebx > 0
      mov eax, [esi+ebx-4]
      invoke printf, CStr("%04X"), eax
      sub ebx, 4
    .endw
    ret
dump_hex endp

; perform Diffie Hellman Merkle key exchange using oaklay group
; this does both client and server operations to demonstrate
; how it would work in assembly.
;
; x and y should be random integers
;
dhm_key_xchg proc x:dword, y:dword
    local A[MAX_NUM+1]  :byte
    local B[MAX_NUM+1]  :byte
    
    local s1[MAX_NUM+1] :byte
    local s2[MAX_NUM+1] :byte
    
    invoke memset, addr A, 0, MAX_NUM
    invoke memset, addr B, 0, MAX_NUM
    
    ; Alice picks a random integer x and calculates A which is sent to Bob
    invoke modexp, MAX_BITS, addr A, addr g_grp, [x], addr p_grp
    invoke dump_hex, CStr(10, "A="), addr A, MAX_NUM
    
    ; Bob picks a random integer y and calculates B which is sent to Alice
    invoke modexp, MAX_BITS, addr B, addr g_grp, [y], addr p_grp
    invoke dump_hex, CStr(10, "B="), addr B, MAX_NUM
    
    invoke printf, CStr(10)
    
    ; Alice computes secret
    invoke modexp, MAX_BITS, addr s1, addr B, [x], addr p_grp
    invoke dump_hex, CStr(10, "s1="), addr s1, MAX_NUM
    
    ; Bob computes secret
    invoke modexp, MAX_BITS, addr s2, addr A, [y], addr p_grp
    invoke dump_hex, CStr(10, "s2="), addr s2, MAX_NUM
    
    ; s1 + s2 should be equal
    invoke memcmp, addr s1, addr s2, MAX_NUM
    .if eax == 0
      ; use a KDF to generate symmetric key using s1 as input
      invoke puts, CStr(10, 10, "Key exchange succeeded")
    .else
      ; something went wrong..
      invoke puts, CStr(10, 10, "Key exchange failed")
    .endif
    ret
dhm_key_xchg endp

start:
  invoke puts, CStr(10, "Diffie-Hellman-Merkle Key Exchange", 10, "Copyright (c) 2012, 2014 Kevin Devine")
  
  ; just call using the dummy values.
  invoke dhm_key_xchg, addr x_alice, addr y_bob
  invoke ExitProcess, 0
  
; Everything below was written by Z0MBiE/29a
; I've only reformatted it and added description.

; CF:EDI[] = (EDI[] << 1) | CF
RCL_CYCLE macro
    local  __rcl_cycle
__rcl_cycle:            
    rcl    dword ptr [edi], 1
    lea    edi, [edi+4]
    loop   __rcl_cycle
  endm

; EDI[0..ECX-1] vs ESI[0..ECX-1]
CMP_CYCLE macro j_below, j_above
    local  __cmp_cycle
    dec    ecx
__cmp_cycle:
    mov    eax, [edi+ecx*4]
    cmp    eax, [esi+ecx*4]
    jb     j_below
    ja     j_above
    dec    ecx
    jns    __cmp_cycle
; j_equal:
  endm

; CF:EDI[0..ECX-1] -= ESI[0..ECX-1] + CF
SBB_CYCLE macro
    local  __sbb_cycle
__sbb_cycle:
    mov    eax, [esi]
    sbb    [edi], eax
    lea    esi, [esi+4]
    lea    edi, [edi+4]
    loop   __sbb_cycle
  endm

; CF:EDI[0..ECX-1] += ESI[0..ECX-1] + CF
ADC_CYCLE macro
    local  __adc_cycle
__adc_cycle:            
    mov    eax, [esi]
    adc    [edi], eax
    lea    esi, [esi+4]
    lea    edi, [edi+4]
    loop   __adc_cycle
  endm
  

; *****************************
; Modular Exponentiation
;
; l = length in bits
; x = result 
; b = base
; e = exponent
; m = modulus
;
; *****************************
_modexp:
modexp proc c l:DWORD, x:DWORD, b:DWORD, e:DWORD, m:DWORD
    local   l_dd :DWORD
    local   p    :DWORD
    local   t    :DWORD
    
    pushad
    cld
    mov    ecx, l
    shr    ecx, 3          ; in BYTE's
    sub    esp, ecx
    mov    p, esp
    
    sub    esp, ecx
    mov    t, esp
    
    shr    ecx, 2          ; in DWORD's
    mov    l_dd, ecx

    ; x = 1
    mov    edi, x
    xor    eax, eax
    inc    eax
    stosd
    dec    eax
    dec    ecx
    rep    stosd

    ; p = b
    mov    edi, p
    mov    esi, b
    mov    ecx, l_dd
    rep    movsd

    ; ebx = highestbit(e)
    mov    edi, e
    call   @@bitscan

    ; for (edx=0; edx<=ebx; edx++)

    xor    edx, edx
@@pwr_cycle:            
    push   edx
    push   ebx

    ; if (e.bit[edx])
    mov    eax, e
    bt     [eax], edx
    jnc    @@pwr_nobit

    ; x=(x*p) mod m
    mov    edx, x
    call   @@mulmod

@@pwr_nobit:
    ; p=(p*p) mod m
    mov    edx, p
    call   @@mulmod

    ; } // for
    pop    ebx
    pop    edx

    inc    edx
    cmp    edx, ebx
    jbe    @@pwr_cycle

    ;;

    mov    ecx, l
    shr    ecx, 2
    add    esp, ecx

    popad
    ret

; input:  x in EDX
; action: x=(x*p) mod m
; used:   t
@@mulmod:
    ; t = 0
    mov    edi, t
    mov    ecx, l_dd
    xor    eax, eax
    rep    stosd

    ; ebx = highestbit(p)
    mov    edi, p
    call   @@bitscan
    ; while (ebx >= 0)
  ; {

@@mul_cycle:
    ; t *= 2
    mov    edi, t
    mov    ecx, l_dd
    clc
    RCL_CYCLE
    
    ; ecx=0,CF
    call   @@cmpsub

    ; if (p.bit[ebx])
    mov    eax, p
    bt     [eax], ebx
    jnc    @@mul_nobit

    ; t += x
    mov    edi, t
    mov    esi, edx
    mov    ecx, l_dd
    clc
    ADC_CYCLE
    
    ; ecx=0,CF
    call   @@cmpsub
  ; }

@@mul_nobit:            
    dec    ebx
    jns    @@mul_cycle

    ; x = t
    mov    edi, edx
    mov    esi, t
    mov    ecx, l_dd
    rep    movsd
    retn

; input:  EDI=bignumber
; output: EBX=number of highest bit (0-based)

@@bitscan:              
    mov    ebx, l
    dec    ebx
@@bitscan_cycle:        
    bt     [edi], ebx
    jc     @@bitscan_exit
    dec    ebx
    jnz    @@bitscan_cycle
@@bitscan_exit:         
    retn

; if (CF:t >= m) t -= m
@@cmpsub:
    jc     @@ae

    mov    edi, t
    mov    esi, m
    mov    ecx, l_dd
    CMP_CYCLE @@b, @@ae
@@ae:
    mov    edi, t
    mov    esi, m
    mov    ecx, l_dd
    clc
    SBB_CYCLE
@@b:
    retn
modexp endp
                       
    end start
