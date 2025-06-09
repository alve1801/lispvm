/*
for testing shit, we could try implementing ackerman?
lets do ack(2,2)=7

---

math:
a(0,n)=n+1
a(m+1,0)=a(m,1)
a(m+1,n+1)=a(m,a(m+1,n))

---

stack:
0,n -> n+1
m,0 -> m-1,1
m,n -> m-1,m,n-1

---

pseudocode:
input two args (or in our case, preload)
loop:
	pop a
	if a==0
		pop a
		push --a
		push 1
		goto loop
	pop b
	if b==0
		push ++a
		if stack==1 exit
		goto loop
	push --b
	push ++b
	push --a
	goto loop

---

pseudo-assembly:
.stack[100] .stp=stack .tmp
ack:
	.stp swp pop ; a=pop(stp)
	cnd .zero jmp ; jz zero
	swp .tmp swp set ; tmp=a
	.stp swp pop ; b=pop(stp)
	cnd .less jmp ; jz less
	swp .1 swp dec ; b--
	swp .stp swp psh ; push b
	swp .1 add ; b++
	swp .stp swp psh ; push b
	.tmp swp get swp .1 swp dec ; a--
	swp .stp swp psh ; push a
	.loop jmp ; goto loop

zero:
	pop ; b=pop - stp is still loaded
	swp .1 swp dec ; b--
	swp .stp swp psh ; push(b)
	.1 psh .loop jmp ; push(1), goto loop

less:
	.tmp swp get ; refetch a
	swp .1 add ; a++
	swp .stp swp psh ; push(a)
	; if at end of stack, goto some output function then terminate
	get sub swp .1 sub ; stp-=*stp,stp--
	cnd .print jmp .loop jmp ; if(stp)goto loop;else goto print
	.0 ; padding

print:
	.[stack+1] get swp get out ; print(stack[1])
	.0 jmp ; exit

mnemonics:
	0 jmp cnd get set
	4 and ior xor sft
	8 add sub swp out
	c  ?   ?  pop psh
*/

u16 ack[]={
3,0,0,
// ack 3
87, 0x800a, 0x800e,
0x8001, 47, 0x8000,
0x800a, 86, 0x800a, 0x8003,
87, 0x800a, 0x800e,
0x8001, 60, 0x8000,
0x800a, 1, 0x800a, 0x8009,
0x800a, 87, 0x800a, 0x800f,
0x800a, 1, 0x8008,
0x800a, 87, 0x800a, 0x800f,
86, 0x800a, 0x8002, 0x800a, 1, 0x800a, 0x8009,
0x800a, 87, 0x800a, 0x800f,
3, 0x8000,
// zero 47
0x800e,
0x800a, 1, 0x800a, 0x8009,
0x800a, 87, 0x800a, 0x800f,
1, 0x800f, 3, 0x8000,
// less 60
86, 0x800a, 0x8002,
0x800a, 1, 0x8008,
0x800a, 87, 0x800a, 0x800f,
0x8002, 0x8009, 0x800a, 1, 0x8009,
0x8001, 80, 0x8000, 3, 0x8000,
// print 80
//88,0x800a,0x8002,0x800b,0,0x8000,
110,0x8000,0,0,0,0,
// data 86
0,89,2,3,

// 90 - fuck it, new print function
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // stack *20 - hope it suffices
88,0x800a,0x8002,0x800a,'0',0x8008,0x800b,
0,0x8000,0xffff
};
