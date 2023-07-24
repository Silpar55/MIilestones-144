#pragma once
// Copy the below commented "header" section to all your source code files!

/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 1
Full Name  : Alejandro Silva Juarez
Student ID#: 142655224
Email      : asilva-juarez@myseneca.ca
Section    : NFF

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#include <stdio.h>

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

// Function prototype inputInt
int inputInt(void);

// Function prototype inputIntPositive
int inputIntPositive(void);

// Function prototype inputIntRange
int inputIntRange(int lowerBound, int upperBound);


// Function prototype inputCharOption
char inputCharOption(const char str[]);

// Function prototype inputCString
void inputCString(char* cStr, int minChar, int maxChar);

// Function prototype displayFormattedPhone
void displayFormattedPhone(const char* phoneNum);
