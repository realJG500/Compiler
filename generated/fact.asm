	global main
	extern printf

	section .text

main:
push rbp
mov rbp,rsp
sub rsp,100
mov rax,4
push rax
mov rax,8
push rax
call fact
pop rbx
add rsp,rbx
push rax
 mov rdi,fmt1
 pop rsi
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

fact:
push rbp
mov rbp,rsp
sub rsp,100
mov rsi,qword[rbp+24]
mov qword[rbp-8],rsi
push qword[rbp-8]
mov rax,0
push rax
pop rbx
pop rax
cmp rax,rbx
je L4
mov rax,0
jmp L5
L4:
mov rax,1
L5:
push rax
pop rax
cmp rax,0
je L2
mov rax,1
push rax
pop rax
add rsp,100
pop rbp
ret

jmp L3
L2:
push qword[rbp-8]
push qword[rbp-8]
mov rax,1
push rax
pop rbx
pop rax
sub rax,rbx
push rax
mov rax,8
push rax
call fact
pop rbx
add rsp,rbx
push rax
pop rbx
pop rax
imul rbx
push rax
pop rax
add rsp,100
pop rbp
ret

L3:

 section .data
 fmt1: db `%d\n`, 0
