extern vector0_handler, vector32_handler, vector33_handler
global vector0, vector32, vector33

vector0:
	call vector0_handler
	mov al, 0x20
	out 0x20, al
	iret

vector32:
	call vector32_handler
	mov al, 0x20
	out 0x20, al
	iret

vector33:
	call vector33_handler
	mov al, 0x20
	out 0x20, al
	iret