#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include <time.h>


unsigned char coins = 10;

bool Level1()
{
    // return true;
    fprintf(stdout, "Welcome to my Shop!\nWhat would you like to do?\n");
    fflush(stdout);

    bool run = true;
    int owned_items[3] = {0, 0, 0}; 

    while (run) {
        fprintf(stdout, "1) Buy\n2) Sell\n3) View Your Inventory\n4) Leave Shop\n");
        fflush(stdout);

        char c = getchar();

        // throwaway the newline and confuse people
        getchar();

        switch (c) {
            case '1':
            {
                fprintf(stdout, "What would you like to buy?\n");
                fprintf(stdout, "1) An Apple (2 coins)\n2) An Orange (6 coins)\n3) The Key to the Flag (100 coins)\n");
                fflush(stdout);

                int value = getchar() - 0x31;
                getchar();

                char * items[3] = {"Apples", "Oranges", "Keys to the Flag"};
                int values[3] = {2, 6, 100};
                if (value >= 0 && value < 3) {
                    fprintf(stdout, "How many %s would you like to buy?\n", items[value]);
                    fflush(stdout);
                    int qty = getchar() - 0x30;
                    getchar();

                    if (coins < values[value] * qty) {
                        fprintf(stdout, "You don't have enough money :(\n");
    fflush(stdout);
                    }
                    else {
                        coins -= (values[value] * qty);
                        owned_items[value] += qty;
                    }
                }
                else {
                    fprintf(stdout, "%c is not a valid option\n", value + 0x31);
    fflush(stdout);
                }

                break;
            }
            case '2':
            {
                fprintf(stdout, "What would you like to sell?\n");
                fprintf(stdout, "1) An Apple (1 coins)\n2) An Orange (3 coins)\n");
    fflush(stdout);

                int value = getchar() - 0x31;
                getchar();

                char * items[2] = {"Apples", "Oranges"};
                int values[2] = {1, 3};
                if (value >= 0 && value < 2) {
                    fprintf(stdout, "How many %s would you like to sell?\n", items[value]);
    fflush(stdout);
                    int qty = getchar() - 0x30;
                    getchar();

                    if (owned_items[value] < qty) {
                        fprintf(stdout, "You don't have enough %s :(\n", items[value]);
    fflush(stdout);
                    }
                    else {
                        coins += (values[value] * qty);
                        owned_items[value] -= qty;
                    }
                }
                else {
                    fprintf(stdout, "%c is not a valid option\n", value + 0x31);
    fflush(stdout);
                }
                break;
            }
            case '3':
            {
                fprintf(stdout, "You have %d gold coins!\n", coins);
                fprintf(stdout, "You have %d Apples!\n", owned_items[0]);
                fprintf(stdout, "You have %d Oranges!\n", owned_items[1]);
                fprintf(stdout, "You have %d Keys to the Flag!\n", owned_items[2]);
    fflush(stdout);

                if (owned_items[2] > 0) {
                    fprintf(stdout, "Congrats!! You have the key!\n");
    fflush(stdout);
                    return true;
                }

                break;
            }
            case '4':
                fprintf(stdout, "Goodbye then!\n");
    fflush(stdout);
                run = false;
                break;
            case -1:
                exit(1);
                break;
            default:
                fprintf(stdout, "Do you really think this would be so easy to hack?\n");
    fflush(stdout);
        }
    }

    return false;
}

bool Level2() {

    if (coins != 0x13) {
        fprintf(stdout, "You didn't start all over again!\n");
    fflush(stdout);
        return false;
    }

    time_t t = time(NULL);

    fprintf(stdout, "Time: %zu\n", t);
    srand(t);

    while (coins != 0x37) {
        fprintf(stdout, "How much money do you want to bet?\n");
    fflush(stdout);
        char bet = getchar() - 0x30;

        if (bet > coins || bet < 0) {
            fprintf(stdout, "Don't try cheating!\n");
    fflush(stdout);
            return false;
        }

        fprintf(stdout, "What is the value? (0-9)\n");
    fflush(stdout);
        char guess = getchar() - 0x30;

        int rand_val = rand() % 10;
        if (rand_val == guess) {
            fprintf(stdout, "Correct!\n");
    fflush(stdout);
            coins += bet;
        }
        else {
            fprintf(stdout, "Correct Value was: %d\n", rand_val);
    fflush(stdout);
        }

    }

    return true;
}

bool print_flag_1() {
    if (Level1()) {
        FILE *fp = fopen("flag-1.txt", "r");

        if (fp == NULL)
        {
            printf("Cannot open file \n");
    fflush(stdout);
            exit(0);
        }

        // Read contents from file
        char c = fgetc(fp);
        while (c != EOF)
        {
            printf("%c", c);
            c = fgetc(fp);
        }

        fclose(fp);

        printf("\n");
    fflush(stdout);

        return true;
    }
    return false;
}

bool print_flag_2() {
    if (Level2()) {
        FILE *fp = fopen("flag-2.txt", "r");

        if (fp == NULL)
        {
            printf("Cannot open file \n");
    fflush(stdout);
            exit(0);
        }

        // Read contents from file
        char c = fgetc(fp);
        while (c != EOF)
        {
            printf("%c", c);
            c = fgetc(fp);
        }

        fclose(fp);

        printf("\n");
    fflush(stdout);

        return true;
    }
    return false;
}

int main()
{

    char command[50];
    strcpy(command, "base64 chal");
    
    char * first_flag = "flag{b4s364_1s_s0_c3wl_wh0_kn3w_you_c0u1d_do_th15}";

    if (print_flag_1())
    {
        print_flag_2();
    }
}
