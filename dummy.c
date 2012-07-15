#include <stdio.h>
#include <alloca.h>

void test2(int a,int b,int c,int d,int e,int f,int g,int h,int i)
{
	printf("** x = %d, %d, %d, %d, %d, %d, %d, %d, %d\n", a,b,c,d,e,f,g,h,i);
}


void test3()
{
   int x = 100;
   int i;
   long *buffer = alloca(256 * sizeof(long));

   for (i=0; i<256; ++i)
	   buffer[i] = 600 + (i) * 100;

   asm ("movl $x,%edi\n"
        "movq $200,%rsi\n"
        "movq $300,%rdx\n"
        "movq $400,%rcx\n"
        "movq $500,%r8\n"
        "movq $600,%r9\n"
	"callq test2\n"
	);
}


int main()
{
	test3();
}

