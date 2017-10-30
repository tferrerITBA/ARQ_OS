section .text
global get_sec
global get_min
global get_hr

set_format:
		mov al, 0x0B	; or <reg>, 0x04 --> xxxx xxxx xxxx x0xx
		out 70h, al		;                    0000 0000 0000 0100 == 04
		in al, 71h   	;                    -------------------
		or al, 0x04	    ;                    xxxx xxxx xxxx x1xx
		out 71h, al
		ret

get_sec:
		call set_format
		mov al, 0
		out 70h, al
		in al, 71h
		ret

get_min:
		call set_format
		mov al, 0x02
		out 70h, al
		in al, 71h
		ret

get_hr:
		call set_format
		mov al, 0x04
		out 70h, al
		in al, 71h
		ret