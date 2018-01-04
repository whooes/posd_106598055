# POSD2017F Homework

## Homework assignment 8

Please use [the files that were used in course](https://github.com/yccheng66/posd2017f) and copy test header to your repository from this project.

In this time, you need to make a `Shell` to wrapper the program that we made before. It should handle user input and put the input into program, then show the corresponding result. And in some situation, you will need to improve your program to handle the exception if wrong expression.


#### Assignment requirement

  1. This assignment doesn't limit how you implement the shell, but you must ensure that your shell conforms to the following requirements.
      * The shell should provide some functions written in `shell.md`.

      * Handle the expressions written in `expression.h`, and show corresponding result.
 
      * Handle the exceptions written in `exception.h`, and show corresponding result.

      * Shell shouldn't crash if something goes wrong.

  2. Design suitable unit test for all implementations that you write for this assignment.

  3. Write the corresponding makefile to generate executable file which named `hw8`. This is for executing the test on CI server.

  4. Write the corresponding makefile to generate executable file which named `shell`. This is for executing the shell.

  5. Make sure your CI job is passed before deadline.s

#### Marks

  There are 29 tests in `expression.h` and `exception.h`, each one is 3 points; 3 functions written in `shell.md`, each one is 4 points.
  For easier calculating, the sum score of assignment is 100 points.

  If Shell crash, total points deducted 10 points.

#### Deadline

  Fri Jan 05 2018 23:59:59

#### Note

  * Try to read building information in console log and fix the hw problem by yourself as possible as you can.