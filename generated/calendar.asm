	global main
	extern printf

	section .text

main:
push rbp
mov rbp,rsp
sub rsp,100
mov rax,5
push rax
pop qword[rbp-8]
mov rax,2017
push rax
pop qword[rbp-16]
push qword[rbp-8]
mov rax,1
push rax
pop rbx
pop rax
cmp rax,rbx
je L50
mov rax,0
jmp L51
L50:
mov rax,1
L51:
push rax
push qword[rbp-8]
mov rax,2
push rax
pop rbx
pop rax
cmp rax,rbx
je L52
mov rax,0
jmp L53
L52:
mov rax,1
L53:
push rax
pop rbx
pop rax
or rax,rbx
push rax
pop rax
cmp rax,0
je L2
push qword[rbp-8]
mov rax,12
push rax
pop rbx
pop rax
add rax,rbx
push rax
pop qword[rbp-8]
push qword[rbp-16]
mov rax,1
push rax
pop rbx
pop rax
sub rax,rbx
push rax
pop qword[rbp-16]
L2:
mov rax,1
push rax
pop qword[rbp-24]
push qword[rbp-24]
push qword[rbp-8]
mov rax,1
push rax
pop rbx
pop rax
add rax,rbx
push rax
mov rax,26
push rax
pop rbx
pop rax
imul rbx
push rax
mov rax,10
push rax
mov rdx,0
pop rbx
pop rax
idiv rbx
push rax
pop rbx
pop rax
add rax,rbx
push rax
push qword[rbp-16]
pop rbx
pop rax
add rax,rbx
push rax
push qword[rbp-16]
mov rax,4
push rax
mov rdx,0
pop rbx
pop rax
idiv rbx
push rax
pop rbx
pop rax
add rax,rbx
push rax
mov rax,6
push rax
push qword[rbp-16]
mov rax,100
push rax
mov rdx,0
pop rbx
pop rax
idiv rbx
push rax
pop rbx
pop rax
imul rbx
push rax
pop rbx
pop rax
add rax,rbx
push rax
push qword[rbp-16]
mov rax,400
push rax
mov rdx,0
pop rbx
pop rax
idiv rbx
push rax
pop rbx
pop rax
add rax,rbx
push rax
pop qword[rbp-32]
push qword[rbp-32]
push qword[rbp-32]
mov rax,7
push rax
mov rdx,0
pop rbx
pop rax
idiv rbx
push rax
mov rax,7
push rax
pop rbx
pop rax
imul rbx
push rax
pop rbx
pop rax
sub rax,rbx
push rax
pop qword[rbp-56]
push qword[rbp-56]
mov rax,0
push rax
pop rbx
pop rax
cmp rax,rbx
je L54
mov rax,0
jmp L55
L54:
mov rax,1
L55:
push rax
pop rax
cmp rax,0
je L4
mov rax,7
push rax
pop qword[rbp-56]
L4:
push qword[rbp-8]
mov rax,12
push rax
pop rbx
pop rax
cmp rax,rbx
jg L56
mov rax,0
jmp L57
L56:
mov rax,1
L57:
push rax
pop rax
cmp rax,0
je L6
push qword[rbp-8]
mov rax,12
push rax
pop rbx
pop rax
sub rax,rbx
push rax
pop qword[rbp-8]
push qword[rbp-16]
mov rax,1
push rax
pop rbx
pop rax
add rax,rbx
push rax
pop qword[rbp-16]
L6:
mov rax,0
push rax
pop qword[rbp-48]
push qword[rbp-8]
mov rax,4
push rax
pop rbx
pop rax
cmp rax,rbx
je L58
mov rax,0
jmp L59
L58:
mov rax,1
L59:
push rax
push qword[rbp-8]
mov rax,6
push rax
pop rbx
pop rax
cmp rax,rbx
je L60
mov rax,0
jmp L61
L60:
mov rax,1
L61:
push rax
pop rbx
pop rax
or rax,rbx
push rax
push qword[rbp-8]
mov rax,9
push rax
pop rbx
pop rax
cmp rax,rbx
je L62
mov rax,0
jmp L63
L62:
mov rax,1
L63:
push rax
pop rbx
pop rax
or rax,rbx
push rax
push qword[rbp-8]
mov rax,11
push rax
pop rbx
pop rax
cmp rax,rbx
je L64
mov rax,0
jmp L65
L64:
mov rax,1
L65:
push rax
pop rbx
pop rax
or rax,rbx
push rax
pop rax
cmp rax,0
je L8
mov rax,30
push rax
pop qword[rbp-48]
jmp L9
L8:
push qword[rbp-8]
mov rax,2
push rax
pop rbx
pop rax
cmp rax,rbx
jne L66
mov rax,0
jmp L67
L66:
mov rax,1
L67:
push rax
pop rax
cmp rax,0
je L10
mov rax,31
push rax
pop qword[rbp-48]
jmp L11
L10:
push qword[rbp-16]
mov rax,8
push rax
call leapyear
pop rbx
add rsp,rbx
push rax
pop rax
cmp rax,0
je L12
mov rax,29
push rax
pop qword[rbp-48]
jmp L13
L12:
mov rax,28
push rax
pop qword[rbp-48]
L13:
L11:
L9:
push qword[rbp-8]
mov rax,8
push rax
call printmonth
pop rbx
add rsp,rbx
push rax
pop qword[rbp-64]
 mov rdi,fmt1
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,2
push rax
push qword[rbp-56]
pop rbx
pop rax
sub rax,rbx
push rax
pop qword[rbp-40]
push qword[rbp-56]
push qword[rbp-48]
pop rbx
pop rax
add rax,rbx
push rax
mov rax,7
push rax
mov rdx,0
pop rbx
pop rax
idiv rbx
push rax
mov rax,1
push rax
pop rbx
pop rax
add rax,rbx
push rax
pop qword[rbp-72]
mov rax,1
push rax
pop qword[rbp-80]
L18:
push qword[rbp-80]
push qword[rbp-72]
pop rbx
pop rax
cmp rax,rbx
jle L68
mov rax,0
jmp L69
L68:
mov rax,1
L69:
push rax
pop rax
cmp rax,0
je L19
mov rax,1
push rax
pop qword[rbp-88]
L16:
push qword[rbp-88]
mov rax,7
push rax
pop rbx
pop rax
cmp rax,rbx
jle L70
mov rax,0
jmp L71
L70:
mov rax,1
L71:
push rax
pop rax
cmp rax,0
je L17
push qword[rbp-40]
mov rax,1
push rax
pop rbx
pop rax
cmp rax,rbx
jl L72
mov rax,0
jmp L73
L72:
mov rax,1
L73:
push rax
push qword[rbp-40]
push qword[rbp-48]
pop rbx
pop rax
cmp rax,rbx
jg L74
mov rax,0
jmp L75
L74:
mov rax,1
L75:
push rax
pop rbx
pop rax
or rax,rbx
push rax
pop rax
cmp rax,0
je L14
 mov rdi,fmt2
 mov rax,0
 push rbp
 call printf
 pop rbp
jmp L15
L14:
push qword[rbp-40]
 mov rdi,fmt3
 pop rsi
 mov rax,0
 push rbp
 call printf
 pop rbp
L15:
push qword[rbp-88]
mov rax,1
push rax
pop rbx
pop rax
add rax,rbx
push rax
pop qword[rbp-88]
push qword[rbp-40]
mov rax,1
push rax
pop rbx
pop rax
add rax,rbx
push rax
pop qword[rbp-40]
jmp L16
L17:
 mov rdi,fmt4
 mov rax,0
 push rbp
 call printf
 pop rbp
push qword[rbp-80]
mov rax,1
push rax
pop rbx
pop rax
add rax,rbx
push rax
pop qword[rbp-80]
jmp L18
L19:
 mov rdi,fmt5
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

leapyear:
push rbp
mov rbp,rsp
sub rsp,100
mov rsi,qword[rbp+24]
mov qword[rbp-8],rsi
push qword[rbp-8]
mov rax,4
push rax
mov rdx,0
pop rbx
pop rax
idiv rbx
push rax
mov rax,4
push rax
pop rbx
pop rax
imul rbx
push rax
push qword[rbp-8]
pop rbx
pop rax
cmp rax,rbx
jne L76
mov rax,0
jmp L77
L76:
mov rax,1
L77:
push rax
pop rax
cmp rax,0
je L20
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

L20:
push qword[rbp-8]
mov rax,100
push rax
mov rdx,0
pop rbx
pop rax
idiv rbx
push rax
mov rax,100
push rax
pop rbx
pop rax
imul rbx
push rax
push qword[rbp-8]
pop rbx
pop rax
cmp rax,rbx
jne L78
mov rax,0
jmp L79
L78:
mov rax,1
L79:
push rax
pop rax
cmp rax,0
je L22
mov rax,1
push rax
pop rax
add rsp,100
pop rbp
ret

L22:
push qword[rbp-8]
mov rax,400
push rax
mov rdx,0
pop rbx
pop rax
idiv rbx
push rax
mov rax,400
push rax
pop rbx
pop rax
imul rbx
push rax
push qword[rbp-8]
pop rbx
pop rax
cmp rax,rbx
je L80
mov rax,0
jmp L81
L80:
mov rax,1
L81:
push rax
pop rax
cmp rax,0
je L24
mov rax,1
push rax
pop rax
add rsp,100
pop rbp
ret

L24:
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

printmonth:
push rbp
mov rbp,rsp
sub rsp,100
mov rsi,qword[rbp+24]
mov qword[rbp-8],rsi
push qword[rbp-8]
mov rax,1
push rax
pop rbx
pop rax
cmp rax,rbx
je L82
mov rax,0
jmp L83
L82:
mov rax,1
L83:
push rax
pop rax
cmp rax,0
je L26
 mov rdi,fmt6
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

L26:
push qword[rbp-8]
mov rax,2
push rax
pop rbx
pop rax
cmp rax,rbx
je L84
mov rax,0
jmp L85
L84:
mov rax,1
L85:
push rax
pop rax
cmp rax,0
je L28
 mov rdi,fmt7
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

L28:
push qword[rbp-8]
mov rax,3
push rax
pop rbx
pop rax
cmp rax,rbx
je L86
mov rax,0
jmp L87
L86:
mov rax,1
L87:
push rax
pop rax
cmp rax,0
je L30
 mov rdi,fmt8
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

L30:
push qword[rbp-8]
mov rax,4
push rax
pop rbx
pop rax
cmp rax,rbx
je L88
mov rax,0
jmp L89
L88:
mov rax,1
L89:
push rax
pop rax
cmp rax,0
je L32
 mov rdi,fmt9
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

L32:
push qword[rbp-8]
mov rax,5
push rax
pop rbx
pop rax
cmp rax,rbx
je L90
mov rax,0
jmp L91
L90:
mov rax,1
L91:
push rax
pop rax
cmp rax,0
je L34
 mov rdi,fmt10
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

L34:
push qword[rbp-8]
mov rax,6
push rax
pop rbx
pop rax
cmp rax,rbx
je L92
mov rax,0
jmp L93
L92:
mov rax,1
L93:
push rax
pop rax
cmp rax,0
je L36
 mov rdi,fmt11
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

L36:
push qword[rbp-8]
mov rax,7
push rax
pop rbx
pop rax
cmp rax,rbx
je L94
mov rax,0
jmp L95
L94:
mov rax,1
L95:
push rax
pop rax
cmp rax,0
je L38
 mov rdi,fmt12
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

L38:
push qword[rbp-8]
mov rax,8
push rax
pop rbx
pop rax
cmp rax,rbx
je L96
mov rax,0
jmp L97
L96:
mov rax,1
L97:
push rax
pop rax
cmp rax,0
je L40
 mov rdi,fmt13
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

L40:
push qword[rbp-8]
mov rax,9
push rax
pop rbx
pop rax
cmp rax,rbx
je L98
mov rax,0
jmp L99
L98:
mov rax,1
L99:
push rax
pop rax
cmp rax,0
je L42
 mov rdi,fmt14
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

L42:
push qword[rbp-8]
mov rax,10
push rax
pop rbx
pop rax
cmp rax,rbx
je L100
mov rax,0
jmp L101
L100:
mov rax,1
L101:
push rax
pop rax
cmp rax,0
je L44
 mov rdi,fmt15
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

L44:
push qword[rbp-8]
mov rax,11
push rax
pop rbx
pop rax
cmp rax,rbx
je L102
mov rax,0
jmp L103
L102:
mov rax,1
L103:
push rax
pop rax
cmp rax,0
je L46
 mov rdi,fmt16
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

L46:
push qword[rbp-8]
mov rax,12
push rax
pop rbx
pop rax
cmp rax,rbx
je L104
mov rax,0
jmp L105
L104:
mov rax,1
L105:
push rax
pop rax
cmp rax,0
je L48
 mov rdi,fmt17
 mov rax,0
 push rbp
 call printf
 pop rbp
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

L48:
mov rax,1
push rax
pop rax
add rsp,100
pop rbp
ret


 section .data
 fmt1: db `Su Mo Tu We Th Fr Sa\n`, 0
 fmt2: db `   `, 0
 fmt3: db `%2d `, 0
 fmt4: db `\n`, 0
 fmt5: db `\n`, 0
 fmt6: db `       January\n`, 0
 fmt7: db `      February\n`, 0
 fmt8: db `        March\n`, 0
 fmt9: db `        April\n`, 0
 fmt10: db `         May\n`, 0
 fmt11: db `        June\n`, 0
 fmt12: db `        July\n`, 0
 fmt13: db `       August\n`, 0
 fmt14: db `      September\n`, 0
 fmt15: db `       October\n`, 0
 fmt16: db `      November\n`, 0
 fmt17: db `      December\n`, 0
