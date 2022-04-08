#include<string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>   
#include <stdlib.h> 

#define SIZE 0x100

int main() 
{
    void *code = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE | MAP_JIT, -1, 0);
    
    char *input = malloc(SIZE);
    
    fread(input, SIZE, 1, stdin);
    
    int pagesize = getpagesize();
    void *addrOfThePage = code - ((unsigned int)code % pagesize); 
    
    memccpy(code, input, SIZE, 1);
    
    int (*ret)() = (int(*)())code;
    ret();
}
            