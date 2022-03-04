#ifndef MENU_H
#define MENU_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/// <readline>
char* readline(const char* str) {
    printf(str);
    char* ans = (char*)malloc(16);
    int ind = 0, buff_size = 16;
    char c;
    scanf("%c", &c);
    while (c != '\n') {
        if (ind >= buff_size - 1) {
            ans = (char*)realloc(ans, buff_size + 16);
            buff_size += 16;
        }
        *(ans + ind) = c;
        scanf("%c", &c);
        ind++;
    }
    *(ans + ind) = '\0';
    return ans;
}
/// </readline>
int start_menu(int greetings) {
    char* ans = NULL;
    size_t fails = 0;
    if (greetings) {
        ans = readline("Hey! How's your nothing?\nRecently Nikita has realized the polymorphism in C. Lol, there's no polymorphism in C, but he did it\nHe did polymorphic rectangular matrix which can work with integer, real and complex numbers. Wanna see?\n");
        for (size_t i = 0; i < strlen(ans); i++) {
            ans[i] = ans[i] | 32;
        }
        while (strcmp(ans, "yes") != 0 && strcmp(ans, "yep") != 0  && strcmp(ans, "no") != 0 && strcmp(ans, "no") != 0 && strcmp(ans, "nope") != 0 && strcmp(ans, "nah") != 0) {
            free(ans);
            ans = readline("I'll assume that I didn't hear it. Enter normally: ");
            for (size_t i = 0; i < strlen(ans); i++) {
                ans[i] = ans[i] | 32;
            }
        }
        if (strcmp(ans, "no") == 0 || strcmp(ans, "nope") == 0 || strcmp(ans, "nah") == 0) {
            free(ans);
            printf("Then, bye!\n");
            return 0;
        }
    }
    if (!greetings || ans != NULL) {
        if (greetings) printf("Alright, see that I can do. I can:");
        if (ans != NULL) free(ans);
        ans = readline("\n1)Data entry\n2)Data output\n3)Data processing\n4)Exit\nChoice is yours: ");
        while (strlen(ans) != 1 || (ans[0] < '1' || ans[0] > '4')) {
            free(ans);
            fails++;
            switch (fails) {
            case 1: ans = readline("Yo, that's not what i wanted to hear from you. Enter it again, only normally (the number from 1 to 3): ");
                break;
            case 2: ans = readline("Do you think I'm going to put up with this? Out with it, enter normally:");
                break;
            case 3: ans = readline("I'm giving you one last chance: ");
                break;
            default: printf("Understood... Over and out\n");
                return 0;
            }
        }
        if (ans[0] == '1') {
            free(ans);
            ans = readline("Alright. How do you wanna enter the data?\n1) Without overwriting\n2) With overwriting\nYour answer: ");
            while (strcmp(ans, "1") != 0 && strcmp(ans, "2") != 0) {
                fails++;
                free(ans);
                switch (fails) {
                case 1: ans = readline("Yo, that's not what i wanted to hear from you. Enter it again, only normally (the number from 1 to 3): ");
                    break;
                case 2: ans = readline("Do you think I'm going to put up with this? Out with it, enter normally:");
                    break;
                case 3: ans = readline("I'm giving you one last chance: ");
                    break;
                default: printf("I have no words... Only quantifiers. Ain't you tired of doing this? When you get tired, call\n");
                    return 0;
                }
            }
            int t = ans[0] - '0';
            free(ans);
            return t;
        }
        else if (ans[0] == '2') {
            free(ans);
            ans = readline("How do you want me to output the data?\n1) Console \n2) SMS\nYour choice: ");
            while (strcmp(ans, "1") != 0) {
                if (strcmp(ans, "2") == 0) {
                    free(ans);
                    printf("Never gonna give you up!\n");
                    printf("Never gonna let you down!\n");
                    printf("Never gonna run around and desert you!\n");
                    printf("\n\nGotcha :) Did you really fall for it? I can't send messages on your phone, sorry :/\n");
                    ans = readline("There's no choice for you, I can output the data only in the console, sry.\n");
                    return 3;
                }
                free(ans);
                fails++;
                switch (fails) {
                case 1: ans = readline("Yo, that's not what i wanted to hear from you. Enter it again, only normally (the number from 1 to 3): ");
                    break;
                case 2: ans = readline("Do you think I'm going to put up with this? Out with it, enter normally:");
                    break;
                case 3: ans = readline("I'm giving you one last chance: ");
                    break;
                default: printf("I have no words... Only quantifiers. Ain't you tired of doing this? When you get tired, call\n");
                    return 0;
                }
            }
            free(ans);
            return 3;
        }
        else if (ans[0] == '3') {
            free(ans);
            ans = readline("I suggest the following:\n1) Matrix addition\n2) Matrix subtraction\n3) Matrix multiplication\n4) Matrix transposition\nYour choice: ");
            while (strlen(ans) != 1 || (ans[0] < '1' && ans[0] > '5')) {
                fails++;
                free(ans);
                switch (fails) {
                case 1: ans = readline("Yo, that's not what i wanted to hear from you. Enter it again, only normally (the number from 1 to 3): ");
                    break;
                case 2: ans = readline("Do you think I'm going to put up with this? Out with it, enter normally:");
                    break;
                case 3: ans = readline("I'm giving you one last chance: ");
                    break;
                default: printf("I have no words... Only quantifiers. Ain't you tired of doing this? When you get tired, call\n");
                    return 0;
                }
            }
            int t = ans[0] - '0';
            free(ans);
            return t + 3;
        }
        else {
            free(ans);
            return 0;
        }
    }
}
#endif 

