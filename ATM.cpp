#include <iostream>
#include <cstring>
#include<stdio.h> // to use exit
using namespace std;
static int account_number = 0;
class ATM {
    char Account_name[100];
    char Card_number[11];
    float Amount;

public:
    void check_Input(float &money);
    int find_acc(char cardnumber[]);
    void create_new_acc(char new_acccount_name[], char new_card_number[]);
    void Deposit();
    void Withdrawal();
    void Transfer(ATM&);
    void Print_acc_data();
};
const int accounts_maxnum=100;
ATM accounts [accounts_maxnum];  //global array of objects from type ATM class

void ATM::check_Input(float & money)    // check money to be deposited, withdrawn or transfered
{
    while((cin.peek()!='\n') || (!cin) || money<0 )     // making sure money (contain numbers only and greater than zero)
    {
       cout<<"Input Error \n"<< "please enter a valid number: ";
       cin.clear();
       cin.ignore(1000,'\n');
       cin>>money;
    }
}

           /---------------------------------------------------------------------------------------------------------/

int ATM::find_acc(char cardnumber[])    // return index of the cardnumber sent to it
{
    for (int counter = 0; counter < account_number; counter++)  // looping on created accounts in the system
    {
        if (strcmp(accounts[counter].Card_number, cardnumber) == 0)
            return counter;   // implemented when card number sent to the function exists in the system and return its index
    }

         return -1;     // implemented when card number sent to the function doesn't exist in the system

}

          /---------------------------------------------------------------------------------------------------------/

void ATM::create_new_acc(char new_account_name[], char new_card_number[])
{
    strcpy(Account_name, new_account_name);
    strcpy(Card_number, new_card_number);
    Amount = 0;
    Print_acc_data();
}

         /---------------------------------------------------------------------------------------------------------/

void ATM::Deposit() {
    float deposit_value;
    cout << "Please enter the amount to be deposited (press 0 if you don't want to deposit money anymore): ";
    cin >> deposit_value;
    check_Input(deposit_value);
    Amount += deposit_value + (0.01 * deposit_value);  //add deposit amount to the money + 1% of the deposited amount added
    Print_acc_data();
}
        /---------------------------------------------------------------------------------------------------------/

void  ATM::Withdrawal()
{
    float withdrawn_amount;
      while(1)
        {  cout << "Please enter the amount to be withdrawn (press 0 if you don't want to withdraw money anymore): ";
           cin >> withdrawn_amount;
           check_Input(withdrawn_amount);
            if (Amount < (1.03 * withdrawn_amount))
               {
                cout << "ERROR, The money in your account is not enough, you only have ("<<Amount<<") in your account, please try again\n ";
                continue;

               }
           break;
        }
    Amount -= (1.03 * withdrawn_amount);     // withdraw (withdrawn amount sent by the user + 3% of of the withdrawn amount)
    Print_acc_data();
}
       /---------------------------------------------------------------------------------------------------------/

void ATM::Transfer(ATM &receiving_acc)
{
    float Transfered_amount;
    while(1)
        {  cout << "Please enter the amount to be transfered (press 0 if you don't want to transfer money anymore): ";
           cin >> Transfered_amount;
           check_Input(Transfered_amount);   // check transfered amount is a valid positive float number
            if (Amount < (1.015* Transfered_amount))
           {
            cout << "ERROR, The money in your account is not enough, you only have ("<<Amount<<") in your account, please try again\n ";
            continue;

           }
           break;  // when transfered amount is both valid float number and the money in the sending account is enough
        }

    // sending money from sending account to receiving account and deducing 1.5% (of the transfered amount) from both accounts
    Amount -= 1.015 * Transfered_amount;
    receiving_acc.Amount += 0.985 * Transfered_amount;

    cout << "Sending account: " << endl;
    Print_acc_data();
    cout << "Receiving account : " << endl;
    receiving_acc.Print_acc_data();
}
      /---------------------------------------------------------------------------------------------------------/

void ATM::Print_acc_data() {
    cout << "Name : " << Account_name << endl;
    cout << "Card number : " << Card_number << endl;
    cout << "Amount : " << Amount << endl;
}
      /---------------------------------------------------------------------------------------------------------/

void valid_account_name(char accountname[])
{
    while(1)
    {   // making sure name doesn't exceed size of account_name array(100 letters)
        if(!cin)
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"ERROR, card number shouln't exceed 100 letters\n"<<"please enter valid account name: ";
            cin.getline(accountname,100);
            continue;
        }

         // making sure name contain letters and spaces only
       bool error= false;
       for(int counter=0; accountname[counter]; counter++)
          { if (!( (accountname[counter]>=65&&accountname[counter]<=90) || (accountname[counter]>=97&&accountname[counter]<=122) || accountname[counter]==32 ))
              {   error=true;
                  cout<<"ERROR, account name must contain letters and spaces only\n"<<"please enter a valid name: ";
                  cin.getline(accountname,100);
                  break;
             }
         }
      if(error)
            continue;    // to start the outer loop from the beginning

        // making sure name doesn't contain double space
        bool double_space= false;
        for(int i=0; i<(strlen(accountname)-1) ;i++)
        {
            if(accountname[i]==' ')
              if(accountname[i+1]==' ')
              {  double_space=true;
                 cout<<"ERROR, name can't contain consecutive spaces\n"<<"please enter valid account name: ";
                 cin.getline(accountname,100);
                 break;
              }
        }
          if(double_space)
           {continue;}  // to start the outer loop from the beginning


            //making sure name doen't start or end with a space
          if (accountname[0]==' ' || accountname[strlen(accountname)-1] == ' ')
            {
            cout<<"ERROR, name can't start or end with space\n"<<"please enter valid account  name: ";
            cin.getline(accountname,100);
            continue;
            }

        // checking name is at least three letters
        if(strlen(accountname)<3)
           {
            cout<<"ERROR, Name is too short\n"<<"please enter valid account name: ";
            cin.getline(accountname,100);
            continue;
           }

        // make sure account name is a realistic one
        int letter_ascii;
        bool unrealistic_input= false;
        for(int k=0 ; k<(strlen(accountname) -3 ) ; k++)
            {   letter_ascii= accountname[k];
                if(letter_ascii==accountname[k+1] && letter_ascii==accountname[k+2]  && letter_ascii==accountname[k+3] )
                {   unrealistic_input= true;
                    cout<<"ERROR, name can't include more than 4 identical consecutive letters\n"<<"please enter valid account name: ";
                    cin.getline(accountname,100);
                    break;
                }
            }
            if(unrealistic_input)
                continue;  // to start outer loop from the beginning


          break; // this statement will be implemented only when account name is valid
    }
}
     /---------------------------------------------------------------------------------------------------------/

void valid_card_number(char cardnumber[])
{
    while (1)
     {  // making sure card number doesn't exceed size of the array (10 digits)
        if (!cin)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input, please try again\n"<<"Please enter valid account number(10 numbers only) : ";
            cin.getline(cardnumber, 11);
            continue;
        }


        // making sure all 10 digits are numbers from 0 to 9
        int error=0;
        for (int i = 0; cardnumber[i]; i++)
            if (!(cardnumber[i] >= 48 && cardnumber[i] <= 57))
            {   error=1;
                cout << "ERROR, only numbers are allowed in the account number, please try again\n"<< "Please enter valid account number(10 numbers only): ";
                cin.getline(cardnumber, 11);
                break;
            }
        if (error==1)
                continue;  // to start the loop from the begining

        if (strlen(cardnumber) < 10)
        {
            cout << "ERROR, card number should contain 10 numbers, not less than that, please try again\n "<<"Please enter valid account number (10 numbers only): ";
            cin.getline(cardnumber, 11);
            continue;
        }


        //checking that card number digits aren't all the same number
        int first = cardnumber[0];
        int x;
        for (int j = 1; cardnumber[j]; j++)
        {
            x = cardnumber[j];
            if (x != first)
                break;
        }
        if (x == first)
        {

            cout << "ERROR, 10 numbers can't all be the same, please try again\n " << "Please enter valid account number (10 numbers only): ";
            cin.getline(cardnumber, 11);
            continue;
        }

        break;   // break out of the loop when checking all the conditions (valid cardnumber)
    }
}
     /---------------------------------------------------------------------------------------------------------/

int  check_operation_number()  // checking operation number is a valid integer from 1 to 5
{   int operation_num;
    cout <<"******************\n"<< "1----Create new account\n" << "2----Deposit\n" << "3----transfer to another account\n" << "4----withdrawal\n" << "5----exit\n" << "Please enter the number of operation: ";
    cin >> operation_num;
    while((cin.peek()!='\n') || (!cin) || operation_num>5 || operation_num<1)
      {
       cout<<"Input Error, please enter number from 1 to 5 only\n "<<"please enter the number of operation: ";
       cin.clear();
       cin.ignore(1000,'\n');
       cin>>operation_num;
      }
    return operation_num;
}
     /---------------------------------------------------------------------------------------------------------/

int main()
{   int operation_number;
    while(1)  // will be terminated when the user chooses to terminate the program
    {operation_number=check_operation_number();
    switch (operation_number) {
case 1:
   {
        if(account_number==accounts_maxnum) // checking if more accounts can be created or not
          {
            cout<<"Sorry, No more accounts can be created, you can only create ("<<accounts_maxnum<<") accounts \n";
            break; // to break out of case 1
          }


         cout << "please enter the account name: ";
         char accountname[100];
         cin.ignore();
         cin.getline(accountname, 100);
         valid_account_name(accountname);

         char new_cardnumber[11];

      while(1)
       {   cout << "please enter the card number(10 digits): ";
           cin.getline(new_cardnumber, 11);
           valid_card_number(new_cardnumber);

          int acc_found = accounts[0].find_acc(new_cardnumber);
          if (acc_found == -1)   //true when card number is not found in the system
            {
            accounts[account_number].create_new_acc(accountname,new_cardnumber);
            account_number++;
            break;   //break when account number is valid and not taken(doesn't exist in the system)
            }
          else
              cout<<"ERROR, this card number isn't available, please try another one\n";

      }
   }
    break;
case 2:
   {
        char cardnumber[11];
        cin.ignore(1000,'\n');
        while(1)
        {    cout << "please enter the card number(10 digits): ";
             //cin.ignore;
             cin.getline(cardnumber, 11);
             valid_card_number(cardnumber);   // first make sure cardnumber is valid
             int acc_found = accounts[0].find_acc(cardnumber);
             if (acc_found != -1)  //true when account number is found in the system
                {
                       accounts[acc_found].Deposit();
                       break;   //break when card number is both valid and found in the system
                }
            else
                       cout<<"Sorry, this card number doesn't exist in the system, please try again\n";  //will start the loop again
        }
    }

    break;
case 3:
    {
      char sending_cardnumber[11];
      char receiving_cardnumber[11];
      int receiving_acc_found;
      int sending_acc_found;
      cin.ignore();
    while(1)
      {
             while(1)
              { cout << "please enter the number of the sending account (10 digits): ";
                cin.getline(sending_cardnumber, 11);
                valid_card_number(sending_cardnumber);  // first make sure sending card number is valid

                sending_acc_found = accounts[0].find_acc(sending_cardnumber);
                if (sending_acc_found != -1)
                    {
                       break;  // break when sending card number is both valid and found in the system
                    }
                else
                      cout<<"Sorry, this card number doesn't exist in the system, please try again\n";  // repeat the loop agian
              }


             while(1)
              { cout << "please enter the number of the receiving account (10 digits): ";
                cin.getline(receiving_cardnumber, 11);
                valid_card_number(receiving_cardnumber);   // first make sure receiving card number is valid

                receiving_acc_found = accounts[0].find_acc(receiving_cardnumber);
               if (receiving_acc_found != -1)
                   {
                      break;     // break when receiving card number is both valid and found in the system
                   }
              else
                     cout<<"Sorry, this card number doesn't exist in the system, please try again\n";   // repeat the loop agian

             }

        if (sending_acc_found!=receiving_acc_found)  //making sure receiving and sending accounts aren't the same
           {
               accounts[sending_acc_found].Transfer(accounts[receiving_acc_found]);
               break;
           }
        else
        {
            cout<<"Sending and Receiving accounts can't be the same\n";
        }
    }

    }
    break;
case 4:
    {   char withdraw_cardnumber[11];
        cin.ignore(1000,'\n');
        while(1)
        {    cout << "please enter the card number(10 numbers only): ";
             cin.getline(withdraw_cardnumber, 11);
             valid_card_number(withdraw_cardnumber);  // first make sure withdraw cardnumber is valid

            int acc_found = accounts[0].find_acc(withdraw_cardnumber);
            if (acc_found != -1)
                {
                   accounts[acc_found].Withdrawal();
                   break;  // break when withdraw cardnumber is both valid and found in the system
                }
            else
                   cout<<"Sorry, this card number doesn't exist in the system, please try again\n";  // repeat the loop again
        }

    }
    break;
case 5:
        {   cout<<"\nThe program has terminated successfully \n";
            exit(0);}   //terminate the program
        break;
    }
    }
    return 0;
}