#include <iostream>
#include <fstream>

using namespace std;

class credit
{
public:
// different function for each step
    string card_no;
    void type();
    bool isValid();
    void saveToFile(bool isValidCard); // bool to stop termination after this
    void readFromFile();
};

void credit::type()
{  // if card length is 15 and first digit is 3 and 4 or 7 then it  while be American Express card.
    if ((card_no.length() == 15) && (card_no[0] == '3') && (card_no[1] == '4' || card_no[1] == '7'))
    {
        cout << "You are trying to validate an American Express Card." << endl;
    } // if cardlength is 16  and first number is 5 and a second no is 1 to 5 then it is Master Card
    else if ((card_no.length() == 16) && (card_no[0] == '5') && (card_no[1] >= '1' && card_no[1] <= '5'))
    { 
        cout << "You are trying to validate a MasterCard." << endl;
    }// if the card first digit is 4 and length is 13 or 16 then it is Visa Card
    else if ((card_no[0] == '4') && (card_no.length() == 13 || card_no.length() == 16))
    {
        cout << "You are trying to validate a Visa Card." << endl;
    }
    else // if above are not match
    {
        cout << "Card Type Unknown!" << endl;
    }
}

bool credit::isValid()
{
    int len = card_no.length();
    int TotalSum = 0;
    int SumOdd = 0, SumEven = 0;

    // Double the even-placed digits from the end and add all. If it results in a two-digit number, add the digits.
    for (int i = len - 2; i >= 0; i -= 2)
    {
        int twice = (((card_no[i]) - '0') * 2); // Converting character to integer
        if (twice > 9)
        {
            twice = (twice / 10) + (twice % 10);
        }
        SumEven += twice;
    }

    // Add all the odd digits from the end.
    for (int i = len - 1; i >= 0; i -= 2)
    {
        SumOdd += (card_no[i] - '0');
    }

    TotalSum = SumEven + SumOdd;

    // Check if the total sum of odd and even-placed digits is a multiple of 10. If yes, the number is valid.
    bool isValidCard = (TotalSum % 10 == 0);

    return isValidCard;
}

void credit::saveToFile(bool isValidCard)
{
    ofstream outputFile("credit_card_details.txt", ios::app);
    if (outputFile.is_open())
    {
        outputFile << "Card Number: " << card_no << endl;
        outputFile << "Validation Result: " << (isValidCard ? "Valid" : "Invalid") << endl;
        outputFile << "Card Type: ";
        if ((card_no.length() == 15) && (card_no[0] == '3') && (card_no[1] == '4' || card_no[1] == '7'))
        {
            outputFile << "American Express Card" << endl;
        }
        else if ((card_no.length() == 16) && (card_no[0] == '5') && (card_no[1] >= '1' && card_no[1] <= '5'))
        {
            outputFile << "MasterCard" << endl;
        }
        else if ((card_no[0] == '4') && (card_no.length() == 13 || card_no.length() == 16))
        {
            outputFile << "Visa Card" << endl;
        }
        else
        {
            outputFile << "Unknown" << endl;
        }
        outputFile << "--------------------------------------" << endl;
        outputFile.close();
        cout << "Card details saved to file." << endl;
    }
    else
    {
        cout << "Unable to open file for writing." << endl;
    }
}

void credit::readFromFile()
{
    ifstream inputFile("credit_card_details.txt");
    if (inputFile.is_open())
    {
        string line;
        cout << "Contents of the file:" << endl;
        while (getline(inputFile, line))
        {
            cout << line << endl;
        }
        inputFile.close();
    }
    else
    {
        cout << "Unable to open file for reading." << endl;
    }
}

int main()
{
    credit ob1;
    int ans;
    cout << "CREDIT CARD NUMBER VALIDATOR" << endl << endl;

    do
    {
        cout << "Enter the credit card number you want to check: ";
        cin >> ob1.card_no;
        cout << "Your entered number is: " << ob1.card_no << endl;
        ob1.type();
        bool isValidCard = ob1.isValid();
        if (isValidCard)
        {
            cout << "Entered Card Number " << ob1.card_no << " is valid." << endl;
        }
        else
        {
            cout << "Entered Card Number " << ob1.card_no << " is invalid." << endl;
        }
        ob1.saveToFile(isValidCard);
        cout << "Do you want to continue? (1 for yes, 0 for no): ";
        cin >> ans;

        if (ans != 1)
        {
            break;
        }

    } while (true);

    ob1.readFromFile();

    return 0;
}

/*The given code is a C++ program that implements a credit card number validator. Let's go through the code step by step:

1. The code begins with the inclusion of two header files: `<iostream>` and `<fstream>`. `<iostream>` provides input and output stream operations, while `<fstream>` is used for file input and output operations.

2. The `using namespace std;` statement allows the use of standard C++ library functions and objects without explicitly specifying the namespace.

3. Next, a class called `credit` is defined. This class represents a credit card and contains member functions and variables to perform operations on credit card objects.

   - `card_no` is a public string variable that represents the credit card number.

   - The member functions of the `credit` class include:
     - `type()`: This function determines the type of the credit card based on its number.
     - `isValid()`: This function checks whether the credit card number is valid according to the Luhn algorithm.
     - `saveToFile()`: This function saves the credit card details, including the number, validation result, and card type, to a file named "credit_card_details.txt".
     - `readFromFile()`: This function reads the contents of the "credit_card_details.txt" file and prints them to the console.

4. The `type()` function checks the length and initial digits of the credit card number to determine its type. It uses conditional statements (`if` and `else if`) to match the conditions for each card type and outputs the corresponding message.

5. The `isValid()` function implements the Luhn algorithm to validate the credit card number. It calculates the sum of the even-placed and odd-placed digits in the number, doubles the even-placed digits (if necessary), and adds them together. Finally, it checks if the total sum is a multiple of 10, which indicates a valid credit card number. The function returns a boolean value indicating the validity of the card.

6. The `saveToFile()` function opens the "credit_card_details.txt" file in append mode (`ios::app`), writes the credit card number, validation result, and card type to the file, and then closes it. The function also provides appropriate messages if the file cannot be opened.

7. The `readFromFile()` function opens the "credit_card_details.txt" file, reads its contents line by line, and prints them to the console. If the file cannot be opened, an appropriate message is displayed.

8. The `main()` function is the entry point of the program. It creates an instance of the `credit` class (`ob1`), prompts the user to enter a credit card number, and performs the following steps in a loop:

   - Calls the `type()` function to determine the card type.
   - Calls the `isValid()` function to check the validity of the credit card number.
   - Displays the validation result to the user.
   - Calls the `saveToFile()` function to save the credit card details to the file.
   - Asks the user if they want to continue entering credit card numbers.

   The loop continues until the user enters a value other than 1 (indicating they don't want to continue).

9. After the loop ends, the `readFromFile()` function is called to display the contents of the "credit_card_details.txt" file to the user.

10. The program ends by returning 0 from the `main()` function, indicating successful execution.

Overall, this program allows users to enter credit card numbers, validates them, saves the details to a file, and provides an option to view the saved credit card details.

*/
/*

The Luhn algorithm, also known as the modulus 10 algorithm, is a checksum formula used to validate a variety of identification numbers, including credit card numbers. The `isValid()` function in the given code implements the Luhn algorithm to check the validity of a credit card number.

Here's a detailed explanation of the Luhn algorithm as implemented in the code:

1. The function begins by initializing variables:
   - `len` stores the length of the credit card number.
   - `TotalSum` holds the sum of the digits.
   - `SumOdd` and `SumEven` represent the sums of odd-placed and even-placed digits, respectively.

2. The algorithm processes the credit card number from right to left (starting with the second-to-last digit) and performs the following steps:

   - The even-placed digits (starting from the right) are doubled and added to `SumEven`. If the result is a two-digit number, the digits are added individually. For example, if the digit is 6, it becomes 12 (6 * 2), and the sum increases by 1 + 2 = 3.
   - The odd-placed digits are added to `SumOdd`.

   Note: The code uses ASCII values to perform arithmetic operations on characters. Subtracting the character '0' from a digit character gives its corresponding integer value.

3. After processing all the digits, the sums of odd and even digits are added together, and the result is stored in `TotalSum`.

4. The algorithm checks if `TotalSum` is divisible by 10 without a remainder. If the remainder is 0, the credit card number is considered valid, and the function returns `true`. Otherwise, it returns `false` to indicate an invalid card number.

To summarize, the Luhn algorithm calculates the sum of the odd and even digits of a credit card number and checks if the total sum is divisible by 10. If it is divisible by 10, the credit card number is considered valid.

The `isValid()` function in the code implements these steps and returns `true` or `false` based on the result of the Luhn algorithm. This allows the program to determine the validity of a credit card number entered by the user.

*/
/*
Certainly! Let's delve into more details about the variables `SumOdd` and `SumEven` in the `isValid()` function.

1. `SumOdd`:
   - This variable represents the sum of the digits at odd positions in the credit card number. In the Luhn algorithm, odd positions start counting from the rightmost digit.
   - The algorithm iterates through the credit card number from right to left, considering each digit at an odd position.
   - For example, if the credit card number is "123456789", the digits at odd positions are 9, 7, 5, 3, and 1.
   - The algorithm adds these digits to the `SumOdd` variable.

2. `SumEven`:
   - This variable represents the sum of the digits at even positions in the credit card number. In the Luhn algorithm, even positions start counting from the second-to-last digit.
   - The algorithm iterates through the credit card number from right to left, considering each digit at an even position.
   - For example, if the credit card number is "123456789", the digits at even positions are 8, 6, 4, and 2.
   - The algorithm doubles these digits, and if the result is a two-digit number, it adds the individual digits to the `SumEven` variable.
     - For example, doubling 8 results in 16, so the sum increases by 1 + 6 = 7.
     - Doubling 6 results in 12, so the sum increases by 1 + 2 = 3.
     - Doubling 4 results in 8, so the sum increases by 8.
     - Doubling 2 results in 4, so the sum increases by 4.

At the end of the iteration, the variables `SumOdd` and `SumEven` contain the sums of the odd and even digits, respectively, from the credit card number. These sums are then used in further calculations to determine the validity of the credit card number according to the Luhn algorithm.

It's important to note that the algorithm accounts for credit card numbers of different lengths. It works correctly for both 13-digit and 16-digit credit card numbers, as specified in the code. The length of the credit card number affects which digits are considered odd or even in the algorithm.




*/