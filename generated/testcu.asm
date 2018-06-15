	global main
	extern printf

	section .text

main:
push rbp
mov rbp,rsp
sub rsp,100
mov rax,1
push rax
pop qword[rbp-8]
mov rax,0
push rax
pop qword[rbp-16]
 mov rdi,fmt1
 mov rax,0
 push rbp
 call printf
 pop rbp
L2:
push qword[rbp-8]
mov rax,10
push rax
pop rbx
pop rax
cmp rax,rbx
jl L4
mov rax,0
jmp L5
L4:
mov rax,1
L5:
push rax
pop rax
cmp rax,0
je L3
push qword[rbp-8]
mov rax,1
push rax
mov rax,16
push rax
call add
pop rbx
add rsp,rbx
push rax
pop qword[rbp-8]
push qword[rbp-16]
push qword[rbp-8]
mov rax,16
push rax
call add
pop rbx
add rsp,rbx
push rax
pop qword[rbp-16]
push qword[rbp-8]
push qword[rbp-16]
 mov rdi,fmt2
 pop rdx
 pop rsi
 mov rax,0
 push rbp
 call printf
 pop rbp
jmp L2
L3:
mov rax,0
push rax
pop rax
add rsp,100
pop rbp
ret

add:
push rbp
mov rbp,rsp
sub rsp,100
mov rsi,qword[rbp+32]
mov qword[rbp-8],rsi
mov rsi,qword[rbp+24]
mov qword[rbp-16],rsi
push qword[rbp-16]
push qword[rbp-8]
pop rbx
pop rax
add rax,rbx
push rax
pop qword[rbp-24]
push qword[rbp-24]
pop rax
add rsp,100
pop rbp
ret


 section .data
 fmt1: db `  i   sum\n`, 0
 fmt2: db `  %ld   %ld\n`, 0
