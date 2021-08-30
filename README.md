#### Objectives:
- Gain familiarity with data representation at the level of bits.
- Gain practical knowledge of bit manipulation in C.
- Recognize differences in C datatypes and use C type casting.
- Gain practice using the C compilation worflow.

You will interact with a custom data representation for keeping track of things in a store, implementing functions using bitwise operators, and arrays.

#### Format:
This project uses a custom data represenation of aisles in a store and requires you to perform many bit manipulation operations. **aisle_manager.c** and **store_manager.c** contain skeleton functions for you to complete, each with a comment describing its desired behavior.

As you work through the lab, you are encouraged to test each function one by one as you go (see Checking Your Work for instructions on how to just test one function). **We also encourage you to use previously implemented functions and previously defined macros to help you solve future functions!**  Please post on the message board if you are unsure whether or not it is ok to use something.

#### Aisle Manager:

Start by reading the description of an aisle's data representation at the top of **aisle_manager.c.** Make sure you fully understand the layout of the representation before continuing. If you have any questions, please post on the message board or come to office hours.

Once you understand the data representation, you can begin to implement the skeleton functions in aisle_manager.c. Do not be discouraged by the number of functions! They build gradually in level of difficulty, and many of them are similar to each other. Here's one recommended way of working through the file:

1. Start by filling in the macros at the top of the file with various bitmasks to be used later.
2. Continue by implementing the **get_\*** and **set_\*** functions.
3. Finish by implementing the rest of the functions related to manipulating the items in an aisle.

At this point you should be able to pass all tests in the **aisle_test** executable! Now you can move onto **store_client.c**

#### Store Client
**store_client.c** has some functions for interacting with a group of aisles and a stockroom in the store. It uses a global array with elements of type unsigned long to represent multiple aisles. It uses a global array with elements of type int to represent a stockroom for the store (items stowed away that are not in the aisles). That is, you can use the global variables in any of the functions as though they were local variables, without declaring them as local variables. There are slight differences between global variables in C and Java, but they are not relevant for this assignment.

At this point you should be able to pass all tests in the **store_test** executable! This means you are done with the programming part of the assignment (don't forget about the reflection if you are part of a team!).

#### Functions To Implement
Here is a list of functions that need to be implemented:

**aisle_manager.c**
- get_section
- get_spaces
- get_id
- set_section
- set_spaces
- set_id
- toggle_space
- num_items
- add_items
- remove_items
- rotate_items_left
- rotate_items_right

**store_client.c**
- refill_from_stockroom
- fulfill_order
- empty_section_with_id
- section_with_most_items

#### Checking your Work
We have included a few tools to help you check your work.

- We have included the functions **print_binary_long** and **print_binary_short**, which take an unsigned long and unsigned short, respectively, and output its binary representation. These can be useful in debugging your code, but their use is optional and **all calls to the functions should be commented out in your final submission.** Here is a usage example for print_binary_long (print_binary_short works similarly except it takes an unsigned short as its argument):

```C
void print_binary_example(unsigned long argument) {
  // print out binary view of argument for debugging.
    print_binary_long(argument);
}
```
- You can also use printf to debug your functions, but you'll have to include a line with _#include <stdio.h>_ at the top of your file. Its use is optional, and **all calls to the function should be commented out in your final submission.**

- **aisle_test** and **store_test** are programs that check the functional correctness of the code in **aisle_manager.c** and **store_client.c**, respectively. To build and use them, type the following two commands at your prompt (the $ represents the linux prompt):
```
$ make
$ ./aisle_test
$ ./store_test
```
Notice that you must rebuild **aisle_test** and **store_test** each time you modify your code. (You can rebuild them by typing make.) You may find it helpful to work through the functions one at a time, testing each one as you go. You can use the **-f** flag to instruct **aisle_test** and **store_test** to test only a single function (the $ represents the linux prompt):
```
$ ./aisle_test -f set_id
$ ./store_test -f section_with_most_items
```
- **aisle_test** and **store_test** first test your solution on specific cases, and then on a wide range of inputs. As a manner of limiting the test output, for the range of inputs the testing program will only print out the first input that your solutions are incorrect for (or no input if you pass all cases).
- Each function is tested separately to allow for the opportunity for partial credit should you only complete some of the functions.
- Some test cases used for autograding in gradescope may be hidden.

You can also run the autograding script to verify things before submitting to gradescope (the $ represents the linux prompt):
```
$ python3 hwtest.py ALL
```
#### Submission

- Submit your project on gradescope using the gitlab submission process.

- ***Team specific instructions*** 
  - Teams should only do one submission via group submission.
  - Teams must also edit the file called reflection.txt and include a detailed description of each team members contributions to the project.
