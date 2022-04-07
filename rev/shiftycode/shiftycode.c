#include <stdio.h>
#include <stdlib.h>

#define MAX_PROGRAM_LENGTH 1000

#define ADD 0 
#define SUB 1
#define MUL 2
#define DIV 3
#define PRINT 4
#define JMP 5
#define INPT 6
#define CMP 7
#define HALT 8

unsigned char commands[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

int main(int argc, char * argv[]) {

    if (argc != 2) {
        printf("Usage: ./shiftycode <filename>\n");
        exit(0);
    }

    printf("Processing: %s\n", argv[1]);

    FILE * fp = fopen(argv[1], "r");

    unsigned char program[MAX_PROGRAM_LENGTH];

    if (fp == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    size_t newLen = fread(program, sizeof(char), MAX_PROGRAM_LENGTH, fp);
    if ( ferror( fp ) != 0 ) {
        fputs("Error reading file", stderr);
    } else {
        program[newLen++] = '\0';
    }

    fclose(fp);

    printf("Program Data:\n");

    for (int i = 0; i < MAX_PROGRAM_LENGTH / 16; i++) {
        for (int j = 0; j < 16; j++) {
            printf("%02x ", (unsigned char)0xFF & (program[(i * 16) + j]));
        }
        printf("\n");
    }

    int ip = 0;

    unsigned char op = program[ip++];
    unsigned short registers[255];

    for (int i = 0; i < 255; i++) {
        registers[i] = 0;
    }

    unsigned char flag;

    while (1) {
        if (op == commands[ADD]) {
            commands[ADD]++;

            switch (program[ip++]) {
                case 1:
                    {
                        char reg_val = program[ip++];
                        registers[reg_val] = registers[reg_val] + program[ip++];
                        break;
                    }
                case 2:
                    {
                        char reg_val = program[ip++];
                        registers[reg_val] = registers[reg_val] + registers[program[ip++]];
                        break;
                    }
                default:
                    exit(1);
            }

        }
        else if (op == commands[SUB]) {
            commands[SUB]++;

            switch (program[ip++]) {
                case 1:
                    {
                        char reg_val = program[ip++];
                        registers[reg_val] = registers[reg_val] - program[ip++];
                        break;
                    }
                case 2:
                    {
                        char reg_val = program[ip++];
                        registers[reg_val] = registers[reg_val] - registers[program[ip++]];
                        break;
                    }
                default:
                    exit(1);
            }

        }
        else if (op == commands[MUL]) {
            commands[MUL]++;

            switch (program[ip++]) {
                case 1:
                    {
                        char reg_val = program[ip++];
                        registers[reg_val] = registers[reg_val] * program[ip++];
                        break;
                    }
                case 2:
                    {
                        char reg_val = program[ip++];
                        registers[reg_val] = registers[reg_val] * registers[program[ip++]];
                        break;
                    }
                default:
                    exit(1);
            }

        }
        else if (op == commands[DIV]) {
            commands[DIV]++;

            switch (program[ip++]) {
                case 1:
                    {
                        char reg_val = program[ip++];
                        registers[reg_val] = registers[reg_val] / program[ip++];
                        break;
                    }
                case 2:
                    {
                        char reg_val = program[ip++];
                        registers[reg_val] = registers[reg_val] / registers[program[ip++]];
                        break;
                    }
                default:
                    exit(1);
            }

        }
        else if (op == commands[PRINT]) {

            char reg_val = program[ip++];

            printf("%c", 0xFF & registers[reg_val]);

        }
        else if (op == commands[JMP]) {
            commands[JMP]++;

            switch (program[ip++]) {
                case 1:
                    {
                        char val = program[ip++];
                        if (flag) {
                            ip += val;
                        }
                        break;
                    }
                case 2:
                    {
                        char val = program[ip++];
                        if (!flag) {
                            ip += val;
                        }
                        break;
                    }
                default:
                    exit(1);
            }

        }
        else if (op == commands[INPT]) {
            commands[INPT]++;

            char reg_val = program[ip++];
            registers[reg_val] = getchar();

        }
        else if (op == commands[CMP]) {
            commands[CMP]++;

            switch (program[ip++]) {
                case 1:
                    {
                        char reg_val = program[ip++];
                        if (registers[reg_val] == program[ip++]) {
                            flag = 0;
                        }
                        else {
                            flag = 1;
                        }
                        break;
                    }
                case 2:
                    {
                        char reg_val = program[ip++];
                        char reg_val_2 = program[ip++];
                        if (registers[reg_val] == registers[reg_val_2]) {
                            flag = 0;
                        }
                        else {
                            flag = 1;
                        }
                        break;
                    }
                case 3:
                    {
                        if (registers[program[ip++]] < program[ip++]) {
                            flag = 0;
                        }
                        else {
                            flag = 1;
                        }
                        break;
                    }
                case 4:
                    {
                        if (registers[program[ip++]] > program[ip++]) {
                            flag = 0;
                        }
                        else {
                            flag = 1;
                        }
                        break;
                    }
                case 5:
                    {
                        if (registers[program[ip++]] < registers[program[ip++]]) {
                            flag = 0;
                        }
                        else {
                            flag = 1;
                        }
                        break;
                    }
                case 6:
                    {
                        if (registers[program[ip++]] > registers[program[ip++]]) {
                            flag = 0;
                        }
                        else {
                            flag = 1;
                        }
                        break;
                    }
                default:
                    exit(1);
            }

        }
        else if (op == commands[HALT]) {
            break;
        }
        op = program[ip++];
    }

    printf("\nProgram Exited\n");

}