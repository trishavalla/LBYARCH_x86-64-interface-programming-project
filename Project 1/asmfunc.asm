;*****************************
; x86-to-C interface programming project
; Members:
; SALIC, SHAIMMA 
; VALLADOLID, TRISHA LAINE 
;******************************

section .data
    multiplier dq 255.0

section .text
    bits 64
    default rel
    global imgCvtGrayDoubleToInt

imgCvtGrayDoubleToInt:
    ; Parameters:
    ; RCX: Input array of pointers (double**)
    ; RDX: Output array of pointers (int**)
    ; R8D: Number of rows
    ; R9D: Number of columns

    cmp r8d, 0               ; Check if rows are zero
    jz done                     ; Exit if no rows to process

    mov r14d, 0                  ; Initialize row index to 0

L1_ROW:
    ; Load pointers to the current row
    mov r10, [rcx + r14 * 8]    
    mov r11, [rdx + r14 * 8]    

    mov r15d, 0                 ; Reset column index to 0

L2_COL:
    ; Check if all columns processed
    cmp r15d, r9d           
    je L3_ROW      
    movsd xmm0, [r10 + r15 * 8] 
   
   ; Multiply double by multiplier
    movsd xmm1, [multiplier]   
    mulsd xmm0, xmm1            
    roundsd xmm0, xmm0, 0       ; Round to nearest integer
    cvttsd2si eax, xmm0         ; Convert to integer
    mov [r11 + r15 * 4], eax   

    inc r15d                   
    jmp L2_COL                

L3_ROW:
    inc r14d                   
    cmp r14d, r8d               
    jne L1_ROW              

done:
    ret                         ; Exit function
