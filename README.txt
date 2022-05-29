Polynomial calculator
authored by Amir Abu Shanab.
208586214
==Description==
ex4a.c :-
this is a program that takes in a string input from the user and goes over it to extract all the numbers in it and
calculate the polynomial equation, by splitting the x problems into x threads and each thread calculates the value of
x multiplied by a number and raised to the power of another number and then the result is sent to the main thread and summed to get the final
sum result.
ex4b.c :-
same as the first part but instead of threads we create x child processes to calculate the values of x, and then we add the results to a shared memory.
== Functions==
8 functions :-
1) power – this function takes in two int values and sets one to the power of the other.
2) x_val - this function takes in the string input and cuts the part after the "," and takes the number after it to set it as the x value.
3) get_numbers – this function takes in 3 variables thr string input and int number and int power, and runes over the string input
   to take the values in it and set the to be the num value and the power value.
4) split_array – this function takes in the user input and splits it up by the delimiter "+", and in case we are using threads in the first part of the exercise
   it creates x threads and uses each thread to run the func function and wait for the result.
   and in case of children process , it creates x children and uses a shared memory to add all the results of the function func.
5) execute - this function is the main function it takes in the input from the user and checks if its a done command and if its not
   it sends the input to a different function.
6) count_threads - this function runs over the user input and count the amount of "x" in it.
7) func - this function calculates the value of x multiplied by the num and raised to the power of pow and send out the result.
8) check_legal _ this function runs over the user's input and checks for a space before ",", if so the program prints out an error message.
==Program Files==
ex4a.c
ex4b.c
==How to compile? ==
gcc ex4a.c -o run -lpthread
run: ./run

gcc ex4b.c -o run
run : ./run
== Input: ==
A string by the user (a polynomial equation).
==Output: ==
the final result of the polynom.