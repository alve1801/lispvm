#include<stdio.h>
#define u16 unsigned short
#define MAXMEM 0x4000
u16 mem[MAXMEM];
#define pc mem[0]
#define acc mem[1]
#define opr mem[2]

char debug=0;

void step(){
	if(!pc)return; // machine halted
	u16 op=mem[pc++]; // fetch opcode
	if(debug)printf("% 3i : % 4x ",pc,op);
	if(!(op&0x8000)){acc=op;if(debug)printf("%i\n",acc);return;} // acc mode
	op^=0x8000; // remove operand bit

	const char*cmdnames=
		"jmp cnd get set and ior xor sft "
		"add sub swp out ??a ??b pop psh ";
	if(debug){
		char*t=cmdnames+(op<<2);
		putchar(*t++);
		putchar(*t++);
		putchar(*t++);
		printf(" (%i %i)\n",acc,opr);
	}

	fflush(stdout); // ffs

	switch(op){
		case 0:pc=acc;break; // jmp
		case 1:if(acc)pc+=2;break; // cnd
		case 2:acc=mem[opr];break; // get
		case 3:mem[opr]=acc;break; // set

		case 4:acc&=opr;break; // and
		case 5:acc|=opr;break; // or
		case 6:acc^=opr;break; // xor
		case 7: // bitshift
			acc>>=opr&0xf;
			acc<<=opr>>4;
			break;

		case 8:acc+=opr;break; // add
		case 9:acc-=opr;break; // sub
		case 10: // swp
			acc-=opr;
			opr+=acc;
			acc=opr-acc;
			break;
		case 11: // io
			printf(" < %i '%c'\n",acc,(char)acc);
			//if(debug)printf("< %i '%c'\n",acc,(char)acc);
			//else putchar(acc);
			break;

		case 12:case 13:break;

		case 14: // pop
			if(debug)printf(" > %i %i %i\n",opr,mem[opr],mem[mem[opr]]);
			acc=mem[mem[opr]--];
			break;
		case 15: // push
			if(debug)printf(" > %i %i %i\n",opr,mem[opr]+1,mem[mem[opr]+1]);
			mem[++mem[opr]]=acc;
			break;
	}
}

#include"ack.h"

int main(int argc,char**argv){
	if(argc>1)debug=1;
	for(int i=0;ack[i]!=0xffff;i++)
		mem[i]=ack[i];
	while(pc)step();
	putchar(10);return 0;
}


/*
# vm
'realistic', ie ram, registers, the works. looked around, i think ill just make one from scratch.
shared mem - kind of required by jit/dynamic compilation. what word size? 16?
hack modes, in that we dont use arguments, but commands w/ msb==0 set acc

registers: program counter, accumulator, operand

	0 jmp cnd get set
	4 and ior xor sft
	8 add sub swp out
	c  ?   ?  pop psh

isa primitives:
	goto, cond, get, set,
	and, or, xor, bitshift,
	add, sub, swap, io
	?, ?, pop, push
- bitshift aac right by low nibble then left by high nibble of opr (ala uxn)
- get/set are between acc and mem[opr]
- pop/push are more convoluted versions of get/set. opr tells us where the stack pointer is. also autoinc-/-decrement
- cmp skips over next two commands if acc!=0 (one to set acc, one to jmp)
- jmp is unconditional and absolute - might wanna add a relative version...

sure would be great if we had 8bit words, but larger registers...
- except then wed have to deal with assignment alignment and all that bullshit...
also, pls see if we dont wanna make cmp a bit more complicated, i feel like more varied conditionals are useful
- think through how we'd inplement `cond` w/ this
speaking of, how the hell do we invert a value...
- to be fair, we can also just swap stuff around so it works, but that feels hacky
- ... bro this entire mess is hacky af, how is that supposed to be a genuine problem rn
- tldr ya we wont, shortcircuit that fucker
more registers sure would be convenient. keep acc, have instructions to swap it w/ any register

*/
