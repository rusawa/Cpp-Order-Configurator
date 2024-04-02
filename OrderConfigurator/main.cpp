#include <iostream>
#include <limits> //for 'numeric_limits<streamsize>::max()'
#include <string>
#include <cctype> //for a function 'toupper'
#include <stdlib.h>
#include <array>
#include <fstream> //for working with files
#include <ctime> //for date and time

using namespace std;

void welcome(); //function that prints a welcome screen
int pizzaSize(); //function for choosing the pizza size, returns '-1' when user chooses the exit option
int toppings(); //function for selecting toppings, returns '-1' when user chooses the exit option
int sauces(); //function for sauces selection, returns '-1' when user chooses the exit option
int confirmation(); //function that prints the order and prompts the user about the confirmation, returns '-1' when user chooses the exit option
int print(); //function that prints date, time, ID and the order to a text file
void goodbye(string x); //function that prints a goodbye message. The parameter indicates when the program was stopped and prints a different goodbye message for each step

    time_t now = time(0);
    int order_id = now - 1706545217; //gives the ID a unique value

    string pizza_size;
    string toppings_array[10];
    string sauces_array[3];
    double total = 0;

int main()
{
    welcome();

    if(pizzaSize() == -1) {
        goodbye("EXIT_SIZE");
        return 0;
    }

    if(toppings() == -1) {
        goodbye("EXIT_TOPPINGS");
        return 0;
    }

    if(sauces() == -1){
        goodbye("EXIT_SAUCES");
        return 0;
    }

    if(confirmation() == -1){
        goodbye("EXIT_CONFIRMATION");
        return 0;
    } else {
        welcome();
        cout << "=======================" << endl;
        cout << "THANKS FOR YOUR ORDER!" << endl;
        cout << "=======================" << endl;

        if(print() == -1) {
            cout << "Error" << endl;
            return 0;
        }
    }

    return 0;
}












void welcome(){
    cout << R"(
 ______  ___  ______ _____ ______
|___  / / _ \ | ___ \_   _|___  /
   / / / /_\ \| |_/ / | |    / /
  / /  |  _  ||  __/  | |   / /
./ /___| | | || |    _| |_./ /___
\_____/\_| |_/\_|    \___/\_____/

)";

    cout << endl;
}



int pizzaSize() {
    int number; //an integer input from the user
    bool success = false; //a flag that indicates validity of the user input, it changes to 'true' only when the input is valid
    char confirm; //a char variable that stores an input from the user, when they are prompted about the confirmation of their choice

    do {
        cout << "Choose the pizza size: " << endl;
        cout << "1. L (30cm)(15PLN)" << endl;
        cout << "2. XL (50cm)(20PLN)" << endl;
        cout << "3. XXL (70cm)(30PLN)" << endl;
        cout << "..." << endl;
        cout << "0. Exit" << endl;
        cout << "---------" << endl;
        cout << "Your choice: ";

        try {
            cin >> number;

            if(!cin){ //checking if the 'cin' fails
                throw runtime_error("^^Incorrect input format."); //exception when 'cin' fails
            } else if((number < 0) || (number > 3)){ //checking if the inputed number is within the rage
                throw runtime_error("^^Invalid number. Please select '1', '2', '3' or '0'."); //exception when the number is out of range
            } else {
                cout << "Are you sure you want to choose option: " << number << " (Y/N)";

                try {
                    cin.clear(); //a function that clears the error flag on 'cin'
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
                    cin >> confirm;
                    confirm = toupper(confirm); //makes an input upper case , so 'y', 'Y' and 'n', 'N' are valid

                    if(!cin){ //checking if the 'cin' fails
                        throw runtime_error("^^Incorrect input format."); //exception when 'cin' fails
                    } else if((confirm == 'Y') || (confirm == 'N')){ //checking if the inputed letter is correct
                        if(confirm == 'Y'){
                            success = true; //breaks the 'do... while' loop
                            system("CLS"); //clears the console screen
                        } else {
                            success = false;
                            system("CLS"); //clears the console screen
                            cout << endl;
                        }
                    } else {
                        throw runtime_error("^^Invalid choice."); //exception when the letter is not 'y' or 'n'
                    }
                } catch(runtime_error & e) {
                    system("CLS"); //clears the console screen
                    cout << e.what() << endl; //a message declared in 'throw runtime_error("...")'
                    cout << "=========" << endl;
                    cout << flush; //prints everything between 'system ("CLS")' and 'flush' on a new screen
                    cin.clear(); //a function that clears the error flag on 'cin'
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
                }
            }

        } catch(runtime_error & e){
            system("CLS"); //clears the console screen
            cout << e.what() << endl; //a message declared in 'throw runtime_error("...")'
            cout << "=========" << endl;
            cout << endl;
            cout << flush; //prints everything between 'system ("CLS")' and 'flush' on a new screen
            cin.clear(); //a function that clears the error flag on 'cin'
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it

        }
    } while(success == false); //a loop that ends only if the user input is valid


    switch(number) {
        case 1: {
            pizza_size = "L (40cm)";
            total += 15;
            }
            break;
        case 2: {
            pizza_size = "XL (50cm)";
            total += 20;
            }
            break;
        case 3: {
            pizza_size = "XXL (70cm)";
            total += 30;
            }
            break;
        case 0: return -1;
    }
}



int toppings() {
    int number; //an integer input from the user
    bool success = false; //a flag that ends the while loop, it changes to 'true' when the user is ready and able to go to the next step
    char confirm; //a char variable that stores an input from the user, when they are prompted about the confirmation of their choice
    int counter = 0; //a variable that stores number of added toppings

    do {
        cout << endl;
        cout << "What toppings would you like? (Choose at least 2, but no more than 10)(3,5PLN each)" << endl;
        cout << "1. Mozzarella (150g)" << endl;
        cout << "2. Cheddar (150g)" << endl;
        cout << "3. Pepperoni (15 slices)" << endl;
        cout << "4. Ham (10 slices)" << endl;
        cout << "5. Mushrooms (100g)" << endl;
        cout << "6. Pineapple (100g)" << endl;
        cout << "7. Spinach (50g)" << endl;
        cout << "8. Anchovy (50g)" << endl;
        cout << "..." << endl;
        cout << "9. Go to the sauce selection" << endl;
        cout << "0. Exit" << endl;
        cout << "---------" << endl;
        cout << "Your choice (" << 10 - counter << " left): ";


        try {
            cin >> number;

            if(!cin) { //checking if the 'cin' fails
                throw runtime_error("^^Incorrect input format."); //exception when 'cin' fails
            } else if((number < 0) || (number > 9)){ //checking if the inputed number is within the rage
                throw runtime_error("^^Selected number out of range."); //exception when the number is out of range
            } else {
                cout << "Are you sure you want to choose option: " << number << " (Y/N)";

                try {
                    cin.clear(); //a function that clears the error flag on 'cin'
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
                    cin >> confirm;
                    confirm = toupper(confirm); //makes an input upper case , so 'y', 'Y' and 'n', 'N' are valid

                    if(!cin) { //checking if the 'cin' fails
                        throw runtime_error("^^Incorrect input format."); //exception when 'cin' fails
                    } else if((confirm == 'Y') || (confirm == 'N')){ //checking if the inputed letter is correct
                        if(confirm == 'Y'){

                            switch(number){
                                case 0: return -1;
                                    break;
                                case 1: {
                                    toppings_array[counter] = "Mozzarella (150g)";
                                    total += 3.5;
                                    counter++;
                                    }
                                    break;
                                case 2: {
                                    toppings_array[counter] = "Cheddar (150g)";
                                    total += 3.5;
                                    counter++;
                                    }
                                    break;
                                case 3: {
                                    toppings_array[counter] = "Pepperoni (15 slices)";
                                    total += 3.5;
                                    counter++;
                                    }
                                    break;
                                case 4: {
                                    toppings_array[counter] = "Ham (10 slices)";
                                    total += 3.5;
                                    counter++;
                                    }
                                    break;
                                case 5: {
                                    toppings_array[counter] = "Mushrooms (100g)";
                                    total += 3.5;
                                    counter++;
                                    }
                                    break;
                                case 6: {
                                    toppings_array[counter] = "Pineapple (100g)";
                                    total += 3.5;
                                    counter++;
                                    }
                                    break;
                                case 7: {
                                    toppings_array[counter] = "Spinach (50g)";
                                    total += 3.5;
                                    counter++;
                                    }
                                    break;
                                case 8: {
                                    toppings_array[counter] = "Anchovy (50g)";
                                    total += 3.5;
                                    counter++;
                                    }
                                    break;
                                case 9: {
                                    if(counter >= 2) {
                                        success = true; //breaks the 'do... while' loop
                                    } else {
                                        throw runtime_error("^^Choose at least 2 options."); //exception when less than 2 options were selected
                                    }
                                    }
                            }
                            system("CLS"); //clears the console screen
                            cin.clear(); //a function that clears the error flag on 'cin'
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
                        } else {
                            system("CLS"); //clears the console screen
                            success = false;
                            cin.clear(); //a function that clears the error flag on 'cin'
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
                        }
                    } else {
                        throw runtime_error("^^Invalid choice."); //exception when the letter is not 'y' or 'n'
                    }
                } catch(runtime_error & e) {
                    system("CLS"); //clears the console screen
                    cout << e.what() << endl; //a message declared in 'throw runtime_error("...")'
                    cout << "=========" << endl;
                    cout << flush; //prints everything between 'system ("CLS")' and 'flush' on a new screen
                    cin.clear(); //a function that clears the error flag on 'cin'
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
                }
            }

        } catch(runtime_error & e) {
            system("CLS"); //clears the console screen
            cout << e.what() << endl; //a message declared in 'throw runtime_error("...")'
            cout << "=========" << endl;
            cout << flush; //prints everything between 'system ("CLS")' and 'flush' on a new screen
            cin.clear(); //a function that clears the error flag on 'cin'
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
        }

        if(counter >= 10){
            success = true;
        }

    } while(success == false);

}



int sauces(){
    int number; //an integer input from the user
    bool success = false; //a flag that ends the while loop, it changes to 'true' when the user is ready and able to go to the next step
    char confirm; //a char variable that stores an input from the user, when they are prompted about the confirmation of their choice
    int counter = 0; //a variable that stores number of added toppings

    do {
        cout << endl;
        cout << "What sauces would you like? (Maximum 3)" << endl;
        cout << "1. Garlic Sauce (3PLN)" << endl;
        cout << "2. BBQ Sauce (4PLN)" << endl;
        cout << "3. Nacho Cheese Sauce (5PLN)" << endl;
        cout << "..." << endl;
        cout << "9. Go to the summary" << endl;
        cout << "0. Exit" << endl;
        cout << "---------" << endl;
        cout << "Your choice (" << 3 - counter << " left): ";

        try {
            cin >> number;

            if(!cin) { //checking if the 'cin' fails
                throw runtime_error("^^Incorrect input format."); //exception when 'cin' fails
            } else if(((number < 0) || (number > 3)) && (number != 9)) {
                throw runtime_error("^^Selected number out of range."); //exception when the number is out of range
            } else {
                cout << "Are you sure you want to choose option: " << number << " (Y/N)";

                try {
                    cin.clear(); //a function that clears the error flag on 'cin'
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
                    cin >> confirm;
                    confirm = toupper(confirm); //makes an input upper case , so 'y', 'Y' and 'n', 'N' are valid

                    if(!cin) { //checking if the 'cin' fails
                        throw runtime_error("^^Incorrect input format."); //exception when 'cin' fails
                    } else if((confirm == 'Y') || (confirm == 'N')) { //checking if the inputed letter is correct
                        if(confirm == 'Y') {
                            switch(number) {
                                case 0: return -1;
                                    break;
                                case 1: {
                                    sauces_array[counter] = "Garlic Sauce";
                                    total += 3;
                                    counter++;
                                    }
                                    break;
                                case 2: {
                                    sauces_array[counter] = "BBQ Sauce";
                                    total += 4;
                                    counter++;
                                    }
                                    break;
                                case 3: {
                                    sauces_array[counter] = "Nacho Cheese Sauce";
                                    total += 5;
                                    counter++;
                                    }
                                    break;
                                case 9: {
                                    success = true;
                                }
                            }
                            system("CLS"); //clears the console screen
                            cin.clear(); //a function that clears the error flag on 'cin'
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
                        } else {
                            system("CLS"); //clears the console screen
                            success = false;
                            cin.clear(); //a function that clears the error flag on 'cin'
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
                        }
                    } else {
                        throw runtime_error("^^Invalid choice."); //exception when the letter is not 'y' or 'n'
                    }
                } catch(runtime_error & e) {
                    system("CLS"); //clears the console screen
                    cout << e.what() << endl; //a message declared in 'throw runtime_error("...")'
                    cout << "=========" << endl;
                    cout << flush; //prints everything between 'system ("CLS")' and 'flush' on a new screen
                    cin.clear(); //a function that clears the error flag on 'cin'
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
                }
            }
        } catch(runtime_error & e) {
            system("CLS"); //clears the console screen
            cout << e.what() << endl; //a message declared in 'throw runtime_error("...")'
            cout << "=========" << endl;
            cout << flush; //prints everything between 'system ("CLS")' and 'flush' on a new screen
            cin.clear(); //a function that clears the error flag on 'cin'
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
        }

        if(counter >= 3) {
            success = true;
        }

    } while(success == false);
}



int confirmation(){
    int number; //an integer input from the user
    bool success = false; //a flag that ends the while loop, it changes to 'true' when the user is ready and able to go to the next step
    char confirm; //a char variable that stores an input from the user, when they are prompted about the confirmation of their choice

    do {
        cout << "Check your order: " << endl;
        cout << endl;
        cout << "Pizza size: " << pizza_size << endl;
        cout << "Toppings: " << endl;
        for(int i=0; i<10; i++) {
            if(!toppings_array[i].empty()){
                cout << "    " << toppings_array[i] << endl;
            }
        }

        cout << "Sauces: " << endl;
        if(!sauces_array[0].empty()) {
            for(int i=0; i<3; i++) {
                cout << "    " << sauces_array[i] << endl;
            }
        } else {
            cout << "    " << "-----" << endl;
        }
        cout << "=====================" << endl;
        cout << "Your total: " << total << "PLN" << endl;
        cout << "=====================" << endl;
        cout << endl;
        cout << "Would you like to place your order?" << endl;
        cout << "..." << endl;
        cout << "9. Proceed" << endl;
        cout << "0. Cancel and Exit" << endl;
        cout << "---------" << endl;
        cout << "Your choice: ";

        try {
            cin >> number;

            if(!cin) { //checking if the 'cin' fails
                throw runtime_error("^^Incorrect input format."); //exception when 'cin' fails
            } else if((number != 0) && (number != 9)) {
                throw runtime_error("^^Invalid number."); //exception when the number is out of range
            } else {
                cout << "Are you sure you want to choose option: " << number << " (Y/N)";

                try {
                    cin.clear(); //a function that clears the error flag on 'cin'
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
                    cin >> confirm;
                    confirm = toupper(confirm); //makes an input upper case , so 'y', 'Y' and 'n', 'N' are valid

                    if(!cin) { //checking if the 'cin' fails
                        throw runtime_error("^^Incorrect input format."); //exception when 'cin' fails
                    } else if((confirm == 'Y') || (confirm == 'N')) {
                        if(confirm == 'Y') {
                            switch(number) {
                                case 0: return -1;
                                    break;
                                case 9: {
                                    success = true;
                                    system("CLS"); //clears the console screen
                                }
                            }
                        } else {
                            system("CLS"); //clears the console screen
                            success = false;
                            cin.clear(); //a function that clears the error flag on 'cin'
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
                        }
                    } else {
                        throw runtime_error("^^Invalid choice."); //exception when the letter is not 'y' or 'n'
                    }
                } catch(runtime_error & e) {
                    system("CLS"); //clears the console screen
                    cout << e.what() << endl; //a message declared in 'throw runtime_error("...")'
                    cout << "=========" << endl;
                    cout << flush; //prints everything between 'system ("CLS")' and 'flush' on a new screen
                    cin.clear(); //a function that clears the error flag on 'cin'
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
                }
            }
        } catch(runtime_error & e) {
            system("CLS"); //clears the console screen
            cout << e.what() << endl; //a message declared in 'throw runtime_error("...")'
            cout << "=========" << endl;
            cout << flush; //prints everything between 'system ("CLS")' and 'flush' on a new screen
            cin.clear(); //a function that clears the error flag on 'cin'
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes '/n' from the input buffer and everything before it
        }
    } while(success == false);

}



int print(){
    time_t now = time(0);
    tm *ltm = localtime(&now);

    fstream recipe; //file type variable
    recipe.open("recipe.txt", ios::out); //opens or creates a file 'recipe.txt', a list for the chef
    try {
        if(!recipe) {
            throw runtime_error("Something went wrong. Cannot create a file.");
            return -1;
        }
    } catch(runtime_error & e) {
        cout << e.what() << endl;
        cout << endl;
    }


    recipe << "Order ID: " << order_id << endl; //prints 'order_id' to the text file
    recipe << endl;

    recipe << "Date: " << ltm->tm_mday << "." << 1 + ltm->tm_mon  << "." << 1900 + ltm->tm_year <<endl; //prints date to the text file
    recipe << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl; //prints time to the text file
    recipe << endl;

    recipe << "Pizza size: " << pizza_size << endl; //prints 'pizza_size' to the text file
    recipe << endl;
    recipe << "Toppings: " << endl;
    for(int i=0; i<10; i++) { //loop that prints all of the topping to the text file
        if(!toppings_array[i].empty()){ //checks if the string is empty or not
            recipe << "    " << toppings_array[i] << endl; //prints current position in the array
        }
    }

    recipe << "Sauces: " << endl;
    if(!sauces_array[0].empty()) { //checks if the string in position [0] is empty or not
        for(int i=0; i<3; i++) { //loop that prints all of the topping to the text file
            if(!sauces_array[i].empty()){ //checks if the string is empty or not
                recipe << "    " << sauces_array[i] << endl; //prints current position in the array
            }
        }
    } else {
        recipe << "    " << "-----" << endl;
    }

    recipe.close(); //closes the 'recipe.txt' file



    fstream bill;
    bill.open("bill.txt", ios::out); //opens or creates a file 'bill.txt', a receipt for the customer

    try {
        if(!bill) {
            throw runtime_error("Something went wrong. Cannot create a file.");
            return -1;
        }
    } catch(runtime_error & e) {
        cout << e.what() << endl;
        cout << endl;
    }


    bill << R"(
 ______  ___  ______ _____ ______
|___  / / _ \ | ___ \_   _|___  /
   / / / /_\ \| |_/ / | |    / /
  / /  |  _  ||  __/  | |   / /
./ /___| | | || |    _| |_./ /___
\_____/\_| |_/\_|    \___/\_____/

)";

    bill << endl;

    bill << "Order ID: " << order_id << endl; //prints 'order_id' to the text file
    bill << endl;

    bill << "Date: " << ltm->tm_mday << "." << 1 + ltm->tm_mon  << "." << 1900 + ltm->tm_year <<endl; //prints date to the text file
    bill << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl; //prints time to the text file
    bill << endl;

    bill << "Pizza size: " << pizza_size << endl; //prints 'pizza_size' to the text file
    bill << endl;
    bill << "Toppings: " << endl;
    for(int i=0; i<10; i++) { //loop that prints all of the topping to the text file
        if(!toppings_array[i].empty()){ //checks if the string is empty or not
            bill << "    " << toppings_array[i] << endl; //prints current position in the array
        }
    }

    bill << "Sauces: " << endl;
    if(!sauces_array[0].empty()) { //checks if the string in position [0] is empty or not
        for(int i=0; i<3; i++) { //loop that prints all of the topping to the text file
            if(!sauces_array[i].empty()){ //checks if the string is empty or not
                bill << "    " << sauces_array[i] << endl; //prints current position in the array
            }
        }
    } else {
        bill << "    " << "-----" << endl;
    }
    bill << endl;
    bill << "Total: " << total << "PLN" << endl;


    bill.close(); //closes the 'recipe.txt' file

}



void goodbye(string x) {
    if(x == "EXIT_SIZE") {
        cout << endl;
        cout << "==========================================" << endl;
        cout << "   Maybe next time... Have a nice day!" << endl;
        cout << "==========================================" << endl;
    }

    if(x == "EXIT_TOPPINGS") {
        cout << endl;
        cout << "===========================================" << endl;
        cout << " So close... Maybe later? Have a nice day!" << endl;
        cout << "===========================================" << endl;
    }

    if(x == "EXIT_SAUCES") {
        cout << endl;
        cout << "============================================" << endl;
        cout << " Only one step left... Try again next time!" << endl;
        cout << "============================================" << endl;
    }

    if(x == "EXIT_CONFIRMATION") {
        cout << endl;
        cout << "===========================================" << endl;
        cout << " You were almost there... Maybe next time!" << endl;
        cout << "===========================================" << endl;
    }

}


