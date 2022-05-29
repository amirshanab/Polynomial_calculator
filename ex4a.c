#include <stdio.h>
#include <string.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdlib.h>

int power(int x, int pow);// a function that takes in two numbers and sets one to the power of the 2nd

int x_val(char *userIn);

void get_numbers(char *token, int *num, int *pow);

void split_array(char *userIn);

void execute();

int count_threads(char *userIn);

void *func(void *arg);

int check_legal(char *userIn);

int x = 0;

int check_legal(char *userIn) {// a function that checks the user input to see if there's any space before the ","
    int ret = 0;

    for (int i = 0; i < strlen(userIn); i++) {
        if (userIn[i] == ',' && userIn[i - 1] == ' ')
            ret = 1;
    }
    return ret;
}

int power(int x, int pow) {// a function that takes in two numbers and sets one to the power of the 2nd

    int res = 1;
    while (pow > 0) {
        res *= x;
        pow--;
    }
    return res;
}

int x_val(char *userIn) {//a function that takes in the user input and sets the value of x after ","
    int index = 0;
    char number[strlen(userIn)];
    for (int i = 0; i < strlen(userIn); i++) {
        if (userIn[i] == ',') {
            index = i;
            break;
        }
    }
    if (index != 0) {
        strncpy(number, &userIn[index + 1], strlen(userIn) - index);
        x = atoi(number);

        userIn[index + 1] = '\0';
        userIn[index] = '\n';
    }
    return x;
}

void *func(void *arg) {// the function that does the sum of the array indexes
    char *string = (char *) arg;
    int *res = (int *) malloc(sizeof(int));
    int num = 0;
    int pow = 0;
    get_numbers(string, &num, &pow);
    int x_toThePow;
    x_toThePow = power(x, pow);
    *res = num * x_toThePow;
    pthread_exit((void *) res);// sending the return value to the main

}

void get_numbers(char *input, int *num, int *pow) {// a function that takes in a string input and converts the numbers in it into integers
    int check_pow = 0;

    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == '^') {
            check_pow = 1;
        }
    }
    int check_x = count_threads(input);
    if (check_pow == 0 && check_x == 0) {
        *pow = 0;
        *num = atoi(input);
    } else {
        if (input[0] == 'x') {
            *num = 1;
            char *token = strtok(input, "x");
            if (check_pow != 0)
                *pow = atoi(&token[1]);
            else {
                *pow = 1;
            }
        } else {
            char *token = strtok(input, "x");
            *num = atoi(token);
            token = strtok(NULL, "x");
            if (check_pow != 0)
                *pow = atoi(&token[1]);
            else
                *pow = 1;
        }
    }

}

void split_array(char *userIn) {
    /*
     * a function that takes in the user input and splits it into different strings
     * and then each string is sent off to a function that calculates the mathematical
     * equations in it using threads, and then output is sent to the main thread to sum up the numbers.
     */
    int *res;
    int sum = 0;
    int status;
    x = x_val(userIn);
    int size = count_threads(userIn);
    char *arr[size];
    char *token = strtok(userIn, "+");
    // loop through the string to extract all others tokens
    int i = 0;
    while (token != NULL) {
        arr[i] = calloc(strlen(userIn), sizeof(char));
        strcpy(arr[i], token);
        i++;
        token = strtok(NULL, "+");
    }


    int SIZE = i;
    pthread_t threads[SIZE];
    for (int K = 0; K < SIZE; K++) {
        status = pthread_create(&threads[K], NULL, func, arr[K]);// sending them to execute the function
        if (status != 0) {
            fputs("thread create failed", stderr);// in case of error
            exit(EXIT_FAILURE);
        }
    }

    for (int a = 0; a < SIZE; a++) {// getting the return values from the function
        pthread_join(threads[a], (void **) &res);
        sum += *res;
        free(res);
    }
    printf("the result is : %d\n", sum);

}

int count_threads(char *userIn) {// counting the amount of threads we need.
    int counter = 0;
    for (int i = 0; i < strlen(userIn); i++) {
        if (userIn[i] == 'x') {
            counter++;
        }
    }
    return counter;
}

void execute() {// the main function that creates an infinity loop and checks for the exit command.
    char userIn[510];
    memset(userIn, (int) '\0', 510);


    while (1) {
        printf("please enter :- POLYNOM, VALUE\n");
        fgets(userIn, 510, stdin);// save the user input
        fflush(stdin);

        if (strncmp(userIn, "done", 4) == 0 && strlen(userIn) == 5) {// if the user inputted the word done
            return;
        }

        if (check_legal(userIn) != 0) {
            printf("illegal input space before \",\"\n");
            continue;
        }

        split_array(userIn);

    }
}

int main() {

    execute();

    return 0;
}