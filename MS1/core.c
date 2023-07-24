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
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


// TEST 01 Function inputInt 

int inputInt(void)
{
    char character = ' ';
    int value;

    do
    {
        scanf("%d%c", &value, &character);

        if (character != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (character != '\n');

    // If the character after the integer is a new line character that means an appropriate value was entered
    return value;
}

// TEST 02 Function inputIntPositive

int inputIntPositive(void)
{
    char character = ' ';
    int value;

    do
    {
        scanf("%d%c", &value, &character);

        if (character != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        if (value <= 0)
        {
            printf("ERROR! Value must be > 0: ");
        }

    } while (character != '\n' || value <= 0);


    // If the character after the integer is a new line character that means an appropriate value was entered
    return value;

}


// TEST 03 & 04 Function inputIntRange
int inputIntRange(int lowerBound, int upperBound)
{
    int value;

    do
    {
        value = inputInt();

        if (value < lowerBound || value >  upperBound)
            {
                printf("ERROR! Value must be between -3 and 11 inclusive: ");
            }

    } while (value < lowerBound || value >  upperBound);

    return value;
}

// Test 05 Function inputCharOption
char inputCharOption(const char str[])
{
    char letter;
    int i, validateChar = 0;
    

    do
    {
        // qwErty\0
        // 0123456
        // a
        // get character
        scanf(" %c", &letter);

    // Verify each possible option
        for ( i = 0; str[i] != '\0'; i++)
        {

            // if letter is equal to one of them means that the input is correct
            if (letter == str[i])
            {
                validateChar++;
            }
        }


        // no char match with the letter ingresed
        if (validateChar == 0)
        {
            printf("ERROR: Character must be one of [qwErty]: ");
        }



    } while (validateChar == 0);

    clearInputBuffer();

    return letter;
}

// TEST 06 & 07 & 08 Function inputCstring
void inputCString(char* cStr, int minChar, int maxChar)
{

    // EXAMPLE 
    // maxChar = 6
    // minChar = 4
    
    // flag
    int done = 1;
    // get char
    char ch = 'x';

    do
    {
        int len = 0;

        // while the char is not a new line AND length is not more that the max length...
        while (ch != '\n' && len <= maxChar)
        {
            ch = getchar();
            // I know that:
            // char* cStr => char[LENGTH]
            // so:
            cStr[len] = ch;
            len++;
        }
        
        
        // We need to add '\0' in the array, so we need to add it OR REPLACE the last char if it is full 
        // check if there is space 
        if (ch == '\n' && len <= (maxChar + 1))
        {
            len--;
            cStr[len] = '\0';
        }
        else
        {
            // if not, replace the last char to '\0' and we remove the extra char clearing the buffer 
            cStr[maxChar] = '\0';
            clearInputBuffer();
        }


        
        /*
        with the above logic we get:
        -The lenght of the string ingresed: len;
        -The string to return it;

        NOW VALIDATE
        */

        
        // check if is exactly
        if (minChar == maxChar && len != minChar)
        {
            printf("ERROR: String length must be exactly %d chars: ", minChar);
            ch = 'x';

        }
        // check if is more than maxChar
        else if (len > maxChar)
        {
            printf("ERROR: String length must be no more than %d chars: ", maxChar);
            ch = 'x';
        }
        // check if is between the range
        else if (len < minChar || len > maxChar)
        {
            printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
            ch = 'x';
        }
        else
        {
            done = 0;
        }


    } while (done);
}

// TEST 09 Function displayFormattedPhone
void displayFormattedPhone(const char* phoneNum)
{
    int i, numbers = 0, isNotNumber = 0;

    if (phoneNum != NULL)
    {
        // Get every char and indentify if is number
        for (i = 0; phoneNum[i] != '\0'; i++)
        {

            if (phoneNum[i] >= '0' && phoneNum[i] <= '9')
            {
                numbers++;
            }
            else
            {
                isNotNumber++;
            }
        }
        if (numbers == 10 && isNotNumber == 0)
        {
            printf("(");
            for (i = 0; i < 3; i++)
            {
                printf("%c", phoneNum[i]);
            }
            printf(")");
            for (i = 3; i < 6; i++)
            {
                printf("%c", phoneNum[i]);
            }
            printf("-");
            for (i = 6; i < 10; i++)
            {
                printf("%c", phoneNum[i]);
            }
        }
        else
        {
            printf("(___)___-____");

        }

    }else{
        printf("(___)___-____");
      
    }
  
}
