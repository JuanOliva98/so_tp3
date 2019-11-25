SECTION .DATA_tp3
	hello:     db 'Hello world!',10
	helloLen:  equ $-hello

SECTION .TEXT_tp3
	GLOBAL say_hi

say_hi:
	mov eax,4            ; write()
	mov ebx,1            ; STDOUT
	mov ecx,hello
	mov edx,helloLen
	int 80h                 ; Interrupt
        ret                        ; Return control

SECTION .bart_section
    GLOBAL say_bye

say_bye:
	mov eax,4            ; write()
	mov ebx,1            ; STDOUT
	mov ecx,hello
	mov edx,helloLen
	int 80h                 ; Interrupt
        ret 