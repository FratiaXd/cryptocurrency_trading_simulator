//
//VIRTUAL CRYPTOCURENNCY TRANDING PLATFORM
//

//Libraries
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<limits>
#undef max

//Header files with classes
#include "Coin.h"
#include "User.h"
#include "Portfolio.h"

using namespace std;

//Global variables
string usrnm;
string passw;
string file_usrnm;
string file_portf;
string file_hist;

//Functions
void ask_user3op(string action, string op1, string op2, string op3);
void ask_user4op(string action, string op1, string op2, string op3, string op4);
int input();
void create_user();
void skip_lines(int lines, ifstream& fvar, int chars);
double buy();
double sell();
void display_tr_history(string fname);
void display_pr_his(int i);
void coin_description(int i);


//Class Coin

Coin::Coin(string cName, double cPrice)
{
    name = cName;
    price = cPrice;
    price_change = 0;
}

Coin::Coin()
{
    name = "No data";
    price = 0;
}

int Coin::get_pr()
{
    return price;
}

void Coin::create_fcoin(Coin arr[], int coin_num)       //Checks if the file already exists, if it does not create one
{
    ifstream crypto;
    crypto.open("coins.txt");
    if (crypto.is_open())
    {
        crypto.close();
    }
    else
    {
        ofstream crypto;
        crypto.open("coins.txt");
        for (int i = 0; i < coin_num; i++)
        {
            crypto << setw(11) << arr[i].name;
            crypto << setw(20) << arr[i].price;
            crypto << setw(20) << arr[i].price_change << endl;
        }
        crypto.close();
    }
}

void Coin::load_coins(ifstream& coinF)
{
    coinF >> name >> price >> price_change;
}

void Coin::list_coins(Coin list[], int coin_num, string fname)          //Puts coins from the text file into a new list
{
    ifstream cryptoload("coins.txt");
    if (!cryptoload)
    {
        cout << "File invalid. Restart the program." << endl;
    }
    for (int i = 0; i < coin_num; i++)
    {
        list[i].load_coins(cryptoload);
    }
    cryptoload.close();
}

void Coin::display_coin(Coin list[], int i)         
{
    cout << setw(11) << "NAME" << setw(12) << "PRICE" << endl;
    cout << setw(11) << list[i].name << setw(12) << list[i].price << endl << endl;
}

void Coin::update_price(Coin list[], int coin_num)          //Randomly increases or decreases each coin prices
{
    cout << setw(18) << "NAME" << setw(15) << "PRICE";
    cout << setw(21) << "PRICE CHANGE(1H)" << endl;
    for (int i = 0; i < coin_num; i++)
    {
        double percentage;
        int a = rand() % 2 + 1;
        if (a == 1)                     //Increases
        {
            percentage = rand() % 10;
            list[i].price_change = percentage;
            percentage = percentage / 100;
            list[i].price = list[i].price + (list[i].price * percentage);
            cout << setw(4) << i + 1 << " - ";
            cout << setw(11) << list[i].name << setw(15) << setprecision(5) << list[i].price;       //Displays coins after price update
            cout << setw(17) << "+" << list[i].price_change << "%" << endl;
        }
        if (a == 2)                 //Decreases
        {
            percentage = rand() % 7;
            list[i].price_change = percentage;
            percentage = percentage / 100;
            list[i].price = list[i].price - (list[i].price * percentage);
            cout << setw(4) << i + 1 << " - ";
            cout << setw(11) << list[i].name << setw(15) << setprecision(5) << list[i].price;
            cout << setw(17) << "-" << list[i].price_change << "%" << endl;
        }
    }
    cout << endl;
    cout << "Your choice: ";
}

void Coin::save_coins(Coin list[], int coin_n)          //Saves coin list into the coin text file after price update
{
    ofstream crypto;
    crypto.open("coins.txt");
    for (int i = 0; i < coin_n; i++)
    {
        crypto << setw(11) << list[i].name;
        crypto << setw(20) << list[i].price;
        crypto << setw(20) << list[i].price_change << endl;
    }
    crypto.close();
}

double Coin::get_price(Coin list[], int i)      //Access coin price outside the class 
{
    double m;
    m = list[i].price;
    return m;
}
                                        
//Class user

User::User(string nm, string pass)
{
    username = nm;
    password = pass;
    balance = 10000;
}

User::User()
{
    username = "No data";
    balance = 0;
}

double User::get_bal()
{
    return balance;
}

void User::display_user()
{
    cout << "Balance (USD): " << balance << endl;
}

void User::create_usfile()      //Creates file for the new user
{
    ofstream account;
    file_usrnm = usrnm + ".txt";
    account.open(file_usrnm.c_str());
    account << "Username: " << usrnm << endl;
    account << "Password: " << passw << endl;
    account << "Balance(USD): " << endl;
    account << balance << endl;
    cout << "Account was created successfully" << endl << endl;
    account.close();
}

void User::create_portfolio()       //Creates portfolio file for the new user
{
    ofstream account;
    file_portf = usrnm + "portfolio.txt";
    account.open(file_portf.c_str());                         //NEW
    account << setw(11) << "NAME" << setw(18) << "QUANTITY" << setw(15) << "BALANCE" << setw(17) << "ENTRY PRICE" << setw(17) << "PROFIT/LOSS" << endl;
    account << setw(11) << "Bitcoin" << setw(18) << 0 << setw(15) << 0 << setw(17) << 0 << setw(17) << 0 << endl;
    account << setw(11) << "Ethereum" << setw(18) << 0 << setw(15) << 0 << setw(17) << 0 << setw(17) << 0 << endl;
    account << setw(11) << "BinanceCoin" << setw(18) << 0 << setw(15) << 0 << setw(17) << 0 << setw(17) << 0 << endl;
    account << setw(11) << "Cardano" << setw(18) << 0 << setw(15) << 0 << setw(17) << 0 << setw(17) << 0 << endl;
    account << setw(11) << "Polkadot" << setw(18) << 0 << setw(15) << 0 << setw(17) << 0 << setw(17) << 0 << endl;
    account << setw(11) << "Ripple" << setw(18) << 0 << setw(15) << 0 << setw(17) << 0 << setw(17) << 0 << endl;
    account << setw(11) << "Uniswap" << setw(18) << 0 << setw(15) << 0 << setw(17) << 0 << setw(17) << 0 << endl;
    account << setw(11) << "Litecoin" << setw(18) << 0 << setw(15) << 0 << setw(17) << 0 << setw(17) << 0 << endl;
    account << setw(11) << "Chainlink" << setw(18) << 0 << setw(15) << 0 << setw(17) << 0 << setw(17) << 0 << endl;
    account << setw(11) << "Theta" << setw(18) << 0 << setw(15) << 0 << setw(17) << 0 << setw(17) << 0 << endl;
    account.close();
}

void User::create_trhis()       //Creates transaction history file for the new user
{
    ofstream account;
    file_hist = usrnm + "history.txt";
    account.open(file_hist.c_str());
    account << setw(16) << "TRANSACTION TYPE" << setw(13) << "NAME" << setw(15) << "QUANTITY" << setw(15) << "PROFIT/LOSS" << endl;
    account.close();
}

bool User::check_user(string filename, string usname, string psword)
{
    string mystring;
    string mystring1;
    int offset;
    int offset1;
    ifstream filecheck;
    filecheck.open(filename);
    if (filecheck.is_open())        //Checks if userfile (user) exists
    {
        while (!filecheck.eof())
        {
            getline(filecheck, mystring);
            if ((offset = mystring.find(usname, 0)) != string::npos)        //Checks if username and password are correct
            {
                getline(filecheck, mystring1);
                if ((offset1 = mystring1.find(psword, 0)) != string::npos)
                {
                    filecheck.close();
                    return true;
                }
            }
            else
            {
                filecheck.close();
                return false;
            }
        }
    }
    else
    {
        cout << "Unable to connect" << endl;
        return false;
    }
}

bool User::check_balance(double a)
{
    if (a > balance)
    {
        cout << endl;
        cout << "Not enough credits. Please try another sum." << endl;
        return false;
    }
    else
    {
        return true;
    }
}

double User::get_balance(string fname)          //Access user balance outside the class 
{
    double b;
    ifstream acc(fname);
    if (!acc)
    {
        cout << "File invalid. Restart the program." << endl;
    }
    skip_lines(3, acc, 60);
    acc >> balance;
    acc.close();
    b = balance;
    return b;
}

void User::upd_balance(double m, string fnm, int op)        //Updates user balance after transaction and rewrites the file to save it
{
    if (op == 1)
    {
        balance -= m;
    }
    if (op == 2)
    {
        balance += m;
    }
    ofstream account;
    account.open(fnm);
    account << "Username: " << usrnm << endl;
    account << "Password: " << passw << endl;
    account << "Balance(USD): " << endl;
    account << balance << endl;
    account.close();
}

//Class Portfolio

Portfolio::Portfolio()
{
    name = "No data";
    coin_amount = 0;
}

double Portfolio::get_amnt()
{
    return coin_amount;
}

void Portfolio::read_portfolio(ifstream& port)
{
    port >> name >> coin_amount >> coin_balance >> entry_price >> profit_loss;
}

void Portfolio::list_portf(Portfolio list[], int num, string fname)     //Puts coins from the portfolio file into a portfolio list
{
    ifstream portfload(fname);
    if (!portfload)
    {
        cout << "File invalid. Restart the program." << endl;
    }
    skip_lines(1, portfload, 80);
    for (int i = 0; i < num; i++)
    {
        list[i].read_portfolio(portfload);
    }
    portfload.close();
}

void Portfolio::save_portfolio(string file, Portfolio list[], int a, Coin lt[])      //Saves portfolio list into the portfolio text file after the transaction
{
    ofstream portf;
    double price;
    portf.open(file);
    portf << setw(11) << "NAME" << setw(18) << "QUANTITY" << setw(15) << "BALANCE" << setw(17) << "ENTRY PRICE" << setw(17) << "PROFIT/LOSS" << endl;
    for (int i = 0; i < a; i++)
    {
        portf << setw(11) << list[i].name;
        portf << setw(18) << setprecision(6) << list[i].coin_amount;
        price = lt->get_price(lt, i);                               //Gets current price for every coin
        list[i].coin_balance = price * list[i].coin_amount;
        portf << setw(15) << setprecision(5) << list[i].coin_balance;
        portf << setw(17) << list[i].entry_price;
        list[i].profit_loss = (price * list[i].coin_amount) - (list[i].entry_price * list[i].coin_amount);      //Calculates profit or loss
        portf << setw(17) << list[i].profit_loss << endl;
    }
    portf.close();
}

void Portfolio::save_transaction(string filen, string type, Portfolio list[], int i, double qty)        //Saves transaction into the transaction history
{                                                                                                       //text file after the transaction
    ofstream history;
    history.open(filen, ios::app);
    history << setw(16) << type;
    history << setw(13) << list[i].name;
    history << setw(15) << setprecision(6) << qty;
    history << setw(15) << list[i].profit_loss << endl;
    history.close();
}

bool Portfolio::buy_coin(double sum, double price, Portfolio list[], int i)    
{
    float qty;
    int ans;
    qty = sum / price;                                                        //Calculates which coin quantity can be purchased by the current coin price
    cout << endl;
    cout << "You will receive " << setprecision(5) << qty << " coins" << endl;
    cout << "Price per coin is: " << setprecision(5) << price << endl << endl;
    cout << "Please confirm:" << endl << endl;
    cout << "1 - Confirm" << endl;
    cout << "2 - Discard" << endl << endl;
    cout << "Your choice: ";
    cin >> ans;
    if (ans == 1)                           //Changes coin values in the portfolio list after confirmation
    {
        list[i].coin_amount += qty;
        list[i].coin_balance += sum;
        list[i].entry_price = price;
        cout << endl;
        cout << "Transaction processing..." << endl;
        Sleep(700);
        cout << "Transaction success" << endl;
        Sleep(700);
        return true;
    }
    else
    {
        cout << "Transaction discarded" << endl;
        return false;
    }
}

void Portfolio::display_coin_bal(Portfolio list[], int i)
{
    cout << "Your " << list[i].name << " balance in USD is: ";
    cout << list[i].coin_balance << endl;
}

bool Portfolio::check_coin_balance(double a, Portfolio list[], int i)
{
    if (a > list[i].coin_balance)
    {
        cout << endl;
        cout << "Not enough credits. Please try another sum." << endl;
        return false;
    }
    else
    {
        return true;
    }
}

bool Portfolio::sell_coin(double sum, double price, Portfolio list[], int i)            //Almost the same as buy_coin()
{
    float qty;
    int ans;
    qty = sum / price;  
    cout << endl;
    cout << "You will sell " << setprecision(5) << qty << " coins" << endl;
    cout << "Price per coin is: " << setprecision(5) << price << endl << endl;
    cout << "Please confirm:" << endl << endl;
    cout << "1 - Confirm" << endl;
    cout << "2 - Discard" << endl << endl;
    cout << "Your choice: ";
    cin >> ans;
    if (ans == 1)
    {
        if ((i == 0) || (i == 1))
        {
            if ((list[i].coin_amount >= (qty - 0.0008)) && (list[i].coin_amount <= (qty + 0.0001)))                           //Avoids very small numbers after calculation 
            {                                                                                                                //for BTC and ETH
                list[i].coin_amount = 0;
                list[i].coin_balance = 0;
                list[i].entry_price = 0;
            }
            else
            {
                list[i].coin_amount -= qty;
                list[i].coin_balance -= sum;
            }
        }
        else
        {
            if ((list[i].coin_amount >= (qty - 0.08)) && (list[i].coin_amount <= (qty + 0.01)))                           //Avoids very small numbers after calculation
            {                                                                                                               //For the rest coins
                list[i].coin_amount = 0;
                list[i].coin_balance = 0;
                list[i].entry_price = 0;
            }
            else
            {
                list[i].coin_amount -= qty;
                list[i].coin_balance -= sum;
            }
        }
        cout << endl;
        cout << "Transaction processing..." << endl;
        Sleep(700);
        cout << "Transaction success" << endl;
        Sleep(700);
        return true;
    }
    else
    {
        return false;
    }
}

void Portfolio::display_portfolio()
{
    cout << setw(11) << name << setw(18) << coin_amount;
    cout << setw(15) << coin_balance << setw(17) << profit_loss << endl;
}

void Portfolio::display_fullp(Portfolio list[], int num)
{
    cout << "YOUR ASSETS" << endl << endl;
    cout << setw(11) << "NAME" << setw(18) << "QUANTITY";
    cout << setw(15) << "BALANCE" << setw(17) << "PROFIT/LOSS" << endl;
    for (int i = 0; i < num; i++)
    {
        list[i].display_portfolio();
    }
    cout << endl;
}
               
void Portfolio::after_transaction(Portfolio list[], int id, string portf, int coin_num, double sum, double pr, string hist, Coin lt[], string status)
{
    list->save_transaction(hist, status, list, id, sum / pr);       ////Groups all functions after coin sale
    list->save_portfolio(portf, list, coin_num, lt);
    list->list_portf(list, coin_num, portf);
}

const int MAXCOINS = 10;

//Main program
int main()
{
    //Standart coin list which is saved into the text file
    Coin coinList[MAXCOINS] = { Coin("Bitcoin", 56000),
                               Coin("Ethereum", 1700),
                               Coin("BinanceCoin", 460),
                               Coin("Cardano", 1.13),
                               Coin("Polkadot", 35),
                               Coin("Ripple", 1.54),
                               Coin("Uniswap", 30.5),
                               Coin("Litecoin", 193),
                               Coin("Chainlink", 27.2),
                               Coin("Theta", 12.2) };

    //if this file does not exist on a machine
    coinList->create_fcoin(coinList, MAXCOINS);

    //Coin list which used to update price
    Coin newCoinList[MAXCOINS];

    //A portfolio list used to keep track of held coins
    Portfolio portfolioList[MAXCOINS]; 
    
    //Variables
    int answ;
    int answ1;
    double m_amnt;
    bool run = true;
    bool wanttoexit = false;

    //Program loop
    do {
        cout << "Cryptocurrency trading platform" << "\n\n";
        cout << "Create a new account / Log in" << endl << endl;

        //Log in loop
        LOOP:create_user();
             User user1(usrnm, passw);
             file_usrnm = usrnm + ".txt";
             file_portf = usrnm + "portfolio.txt";
             file_hist = usrnm + "history.txt";
        do
        {
            if (user1.check_user(file_usrnm.c_str(), usrnm, passw) == true)     //If the user exists
            {
                cout << "Welcome " << usrnm << endl;
                wanttoexit = true;                                          //goes to the main menu loop
            }
            else
            {
                cout << "User not found" << endl << endl;
                ask_user3op("Do you want to create a new account?", "Exit", "Yes", "No, try to log in again");
                cin >> answ;
                while (cin.fail()) {                //Checks user input
                    answ = input();
                }
                cout << endl;
                cin.ignore();
                switch (answ)
                {
                case 0:
                    run = false; 
                    return 0;                       //Terminates program
                    wanttoexit = true;              
                    break;
                case 1:
                    user1.create_usfile();                      //Creates new user
                    user1.create_portfolio();
                    user1.create_trhis();
                    cout << "Welcome " << usrnm << "!" << endl;
                    wanttoexit = true;
                    break;
                case 2:
                    goto LOOP;                      //Loops again
                    continue;
                    break;
                default:
                    cout << "No choice exists" << endl << endl;
                    goto LOOP;
                }
            }
            cout << endl;
        } while (wanttoexit == false);
        
        cout << endl;
        cout << "Always do your own research...";
        cout << endl;

        //Main menu loop
        do
        {
            cout << endl << endl;
            ask_user3op("MAIN MENU", "Exit", "Go to cryptocurrency market", "Portfolio");
            cin >> answ;
            while (cin.fail()) {
                answ = input();
            }
            cout << endl;
            switch (answ)
            {
            case 0:
                run = false;        //Terminates program
                break;
            case 1:
                //Market loop
                do
                {
                    cout << endl;
                    cout << "CRYPTOCURRENCY MARKET" << endl;
                    cout << "(refresh to see new prices)" << endl << endl;
                    cout << "0 - Go back to main menu" << endl << endl;
                    newCoinList->list_coins(newCoinList, MAXCOINS, "coins.txt");                            //Loads lastest saved coins and their prices into the coin list from the text file 
                    srand(time(0));                                                                 //Randomly update prices every program run    
                    newCoinList->update_price(newCoinList, MAXCOINS);                               //Updates prices
                    newCoinList->save_coins(newCoinList, MAXCOINS);                                         //Saves new data into the text file
                    newCoinList->list_coins(newCoinList, MAXCOINS, "coins.txt");                            //Loads new data into the coin list
                    portfolioList->list_portf(portfolioList, MAXCOINS, file_portf.c_str());                 //Loads lastest saved portfolio data from the text file 
                    portfolioList->save_portfolio(file_portf.c_str(), portfolioList, MAXCOINS, newCoinList);        //Calculates new portfolio worth and saves it
                    portfolioList->list_portf(portfolioList, MAXCOINS, file_portf.c_str());                         //Puts updates portfolio into the list
                    user1.get_balance(file_usrnm.c_str());
                    cin >> answ;
                    while (cin.fail()) {
                        answ = input();
                    }
                    cout << endl << endl;   
                    if (answ == 0)
                    {
                        wanttoexit = true;
                        break;
                    }
                    else if ((answ > 0) || (answ < 11))
                    {
                        newCoinList->display_coin(newCoinList, answ - 1);
                        coin_description(answ);
                        ask_user4op("OPTIONS", "Go back to the main menu", "Buy", "Sell", "Price history");
                        cin >> answ1;
                        while (cin.fail()) {
                            answ1 = input();
                        }
                        cout << endl;
                        if (answ1 == 0)
                        {
                            break;
                        }
                        //Buy coin
                        else if (answ1 == 1) 
                        {
                            double p = newCoinList->get_price(newCoinList, answ - 1); 
                            user1.display_user();
                            m_amnt = buy();
                            if (user1.check_balance(m_amnt) == false)       //Checks if user has enough balance
                            {
                                break;
                            }
                            if (portfolioList->buy_coin(m_amnt, newCoinList->get_price(newCoinList, answ - 1), portfolioList, answ - 1) == false) 
                            {
                                break;
                            }
                            portfolioList->after_transaction(portfolioList, answ - 1, file_portf.c_str(), MAXCOINS, m_amnt, p, file_hist.c_str(), newCoinList, "buy");
                            user1.upd_balance(m_amnt, file_usrnm.c_str(), 1);
                        }
                        //Sell coin
                        else if (answ1 == 2) 
                        {
                            double p = newCoinList->get_price(newCoinList, answ - 1);
                            portfolioList->display_coin_bal(portfolioList, answ - 1);
                            m_amnt = sell();
                            if (portfolioList->check_coin_balance(m_amnt, portfolioList, answ - 1) == false) 
                            {
                                break;
                            }
                            if (portfolioList->sell_coin(m_amnt, newCoinList->get_price(newCoinList, answ - 1), portfolioList, answ - 1) == false) 
                            {
                                break;
                            }
                            portfolioList->after_transaction(portfolioList, answ - 1, file_portf.c_str(), MAXCOINS, m_amnt, p, file_hist.c_str(), newCoinList, "sell");
                            user1.upd_balance(m_amnt, file_usrnm.c_str(), 2);
                        }
                        //Price history
                        else if (answ1 == 3) 
                        {
                            display_pr_his(answ);
                        }

                        else if (answ1 > 3)
                        {
                            cout << "No choice exists" << endl << endl;
                            break;
                        }
                    }

                } while (wanttoexit == false);
                break;
            case 2:
                //Portfolio loop
                do
                {
                    ask_user3op("PORTFOLIO", "Go back to main menu", "Your assets", "Transaction history");
                    cin >> answ;
                    while (cin.fail()) {
                        answ = input();
                    }
                    cout << endl;
                    switch (answ)
                    {
                    case 0:
                        wanttoexit = true;
                        break;
                    case 1:
                        //Assets
                        user1.get_balance(file_usrnm.c_str());
                        user1.display_user();
                        cout << endl;
                        portfolioList->list_portf(portfolioList, MAXCOINS, file_portf.c_str());        
                        portfolioList->display_fullp(portfolioList, MAXCOINS);
                        break;
                    case 2:
                        //Transaction history
                        display_tr_history(file_hist.c_str());
                        break;
                    default:
                        cout << "No choice exists" << endl << endl;
                        break;
                    }

                } while (wanttoexit == false);
                break;
            default:
                cout << "No choice exists" << endl << endl;
                break;
            }

        } while (run == true);
        


    } while (run == true);
    
    return 0;
}

//Function definitions
void ask_user3op(string action, string op1, string op2, string op3)
{
    cout << action << endl << endl;
    cout << "0 - " << op1 << endl;
    cout << "1 - " << op2 << endl;
    cout << "2 - " << op3 << endl << endl;
    cout << "Your choice: ";
}

void ask_user4op(string action, string op1, string op2, string op3, string op4)
{
    cout << action << endl << endl;
    cout << "0 - " << op1 << endl;
    cout << "1 - " << op2 << endl;
    cout << "2 - " << op3 << endl;
    cout << "3 - " << op4 << endl << endl;
    cout << "Your choice: ";
}

int input()             //Checks user input
{
    int x;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
    cout << "Invalid input. Try again: ";
    cin >> x;
    cout << endl;
    return x;
}

void create_user()
{
    cout << "Enter a username: ";
    getline(cin, usrnm);
    cout << "Enter a password: ";
    getline(cin, passw);
    cout << endl;
}

void skip_lines(int lines, ifstream& fvar, int chars)
{
    for (int i = 0; i < lines; i++) {
        fvar.ignore(chars, '\n');
    }
}

double buy()
{
    double mn;
    cout << endl;
    cout << "Enter the money amount (USD) you want to spend: ";
    cin >> mn;
    return mn;
}

double sell()
{
    double mn;
    cout << endl;
    cout << "Enter the money amount (USD) you want to receive: ";
    cin >> mn;
    return mn;
}

void display_tr_history(string fname)
{
    ifstream hist(fname);

    if (!hist)
    {
        cout << "File invalid" << endl;
    }
    char str[255];
    while (hist) {
        hist.getline(str, 255);
        if (hist) cout << str << endl;
    }
    hist.close();
}

void display_pr_his(int i)
{
    cout << "Price history: " << endl << endl;
    switch (i)
    {
    case 1:
        cout << "1 day ago - 50230$" << endl;
        cout << "1 week ago - 46410$" << endl;
        cout << "1 month ago- 39870$" << endl;
        cout << "1 year ago - 2400$" << endl;
        Sleep(900);
        break;
    case 2:
        cout << "1 day ago - 1600$" << endl;
        cout << "1 week ago - 1798$" << endl;
        cout << "1 month ago - 1215$" << endl;
        cout << "1 year ago - 348$" << endl;
        Sleep(900);
        break;
    case 3:
        cout << "1 day ago - 445$" << endl;
        cout << "1 week ago - 672$" << endl;
        cout << "1 month ago - 253$" << endl;
        cout << "1 year ago - 5$" << endl;
        Sleep(900);
        break;
    case 4:
        cout << "1 day ago - 1.23$" << endl;
        cout << "1 week ago - 1.65$" << endl;
        cout << "1 month ago - 0.84$" << endl;
        cout << "1 year ago - 0.05$" << endl;
        Sleep(900);
        break;
    case 5:
        cout << "1 day ago - 38.77$" << endl;
        cout << "1 week ago - 38.23$" << endl;
        cout << "1 month ago - 24$" << endl;
        cout << "1 year ago - 2.15$" << endl;
        Sleep(900);
        break;
    case 6:
        cout << "1 day ago - 1.74$" << endl;
        cout << "1 week ago - 0.74$" << endl;
        cout << "1 month ago - 0.45$" << endl;
        cout << "1 year ago - 0.38$" << endl;
        Sleep(900);
        break;
    case 7:
        cout << "1 day ago - 36.13$" << endl;
        cout << "1 week ago - 30.75$" << endl;
        cout << "1 month ago - 42.97$" << endl;
        cout << "1 year ago - 9.38$" << endl;
        Sleep(900);
        break;
    case 8:
        cout << "1 day ago - 241.14$" << endl;
        cout << "1 week ago - 252.71$" << endl;
        cout << "1 month ago - 173$" << endl;
        cout << "1 year ago - 94.42$" << endl;
        Sleep(900);
        break;
    case 9:
        cout << "1 day ago - 36.88$" << endl;
        cout << "1 week ago - 32.70$" << endl;
        cout << "1 month ago - 27.69$" << endl;
        cout << "1 year ago - 8.55$" << endl;
        Sleep(900);
        break;
    case 10:
        cout << "1 day ago - 12.40$" << endl;
        cout << "1 week ago - 13.15$" << endl;
        cout << "1 month ago - 2.64$" << endl;
        cout << "1 year ago - 0.31$" << endl;
        Sleep(900);
        break;
    default:
        break;
    }
}

void coin_description(int i)        
{
    cout << "Coin description: " << endl << endl;
    switch (i)
    {
    case 1:
        cout << "Bitcoin is a decentralized cryptocurrency launched in January 2009." << endl;
        cout << "Bitcoin is a peer-to-peer online currency, meaning that" << endl;
        cout << "all transactions happen directly between equal, independent network participants," << endl;
        cout << "without the need for any intermediary to permit or facilitate them." << endl << endl;
        break;
    case 2:
        cout << "Ethereum is a decentralized open-source blockchain system that features its own cryptocurrency, Ether." << endl;
        cout << "ETH works as a platform for numerous other cryptocurrencies," << endl;
        cout << "as well as for the execution of decentralized smart contracts." << endl;
        cout << "ETH officially launched the blockchain on July 30, 2015." << endl << endl;
        cout << "Learn more on our website: https://ethereum.org/en/" << endl << endl;
        break;
    case 3:
        cout << "BNB was launched through an initial coin offering in 2017." << endl;
        cout << "It was originally issued as an ERC-20 token running on the Ethereum network," << endl;
        cout << "with a total supply capped at 200 million coins." << endl;
        cout << "BNB coins were swapped with BEP2 BNB in 2019 with the launch of" << endl;
        cout << "the Binance Chain mainnet, and are now no longer hosted on Ethereum." << endl << endl;
        cout << "Learn more on our website: https://www.binance.com/en" << endl << endl;
        break;
    case 4:
        cout << "Cardano is a proof-of-stake blockchain platform." << endl;
        cout << "Cardano was founded back in 2017, and the ADA token is designed to" << endl;
        cout << "ensure that owners can participate in the operation of the network." << endl;
        cout << "Because of this, those who hold the cryptocurrency" << endl;
        cout << "have the right to vote on any proposed changes to the software." << endl << endl;
        cout << "Learn more on our website: https://cardano.org/" << endl << endl;
        break;
    case 5:
        cout << "Polkadot is an open-source sharding multichain protocol that facilitates" << endl;
        cout << "the cross - chain transfer of any data or asset types. The Polkadot protocol" << endl;
        cout << "connects public and private chains, permissionless networks, oracles and future technologies," << endl;
        cout << "allowing these independent blockchains to trustlessly share information" << endl;
        cout << "and transactions through the Polkadot relay chain." << endl << endl;
        cout << "Learn more on our website: https://polkadot.network/" << endl << endl;
        break;
    case 6:
        cout << "XRP is the currency that runs on a digital payment platform called RippleNet." << endl;
        cout << "The RippleNet payment platform is a real-time gross settlement system" << endl;
        cout << "that aims to enable instant monetary transactions globally." << endl;
        cout << "While XRP is the cryptocurrency native to the XRP Ledger," << endl;
        cout << "you can actually use any currency to transact on the platform." << endl << endl;
        cout << "Learn more on our website: https://xrpl.org/" << endl << endl;
        break;
    case 7:
        cout << "Uniswap launched in November 2018." << endl;
        cout << "Uniswap aims to keep token trading automated and completely open to anyone who holds tokens." << endl;
        cout << "Uniswap creates more efficiency by solving liquidity issues with automated solutions," << endl;
        cout << "avoiding the problems which plagued the first decentralized exchanges." << endl << endl;
        cout << "Learn more on our website: https://uniswap.org/blog/uni/" << endl << endl;
        break;
    case 8:
        cout << "Litecoin (LTC) is a cryptocurrency that was designed to provide fast," << endl;
        cout << "secure and low-cost payments by leveraging the unique properties of blockchain technology." << endl;
        cout << "The cryptocurrency was created based on the Bitcoin (BTC) protocol," << endl;
        cout << "but it differs in terms of the hashing algorithm used." << endl << endl;
        cout << "Learn more on our website: https://litecoin.org/" << endl << endl;
        break;
    case 9:
        cout << "Chainlink (LINK) is a decentralized oracle network which aims to" << endl;
        cout << "connect smart contracts with data from the real world. LINK, the cryptocurrency" << endl;
        cout << "native to the Chainlink decentralized oracle network, is used to pay node operators." << endl;
        cout << "LINK has a 'transfer and call' functionality of transfer," << endl;
        cout << "allowing tokens to be receivedand processed by contracts within a single transaction." << endl << endl;
        cout << "Learn more on our website: https://chain.link/" << endl << endl;
        break;
    case 10:
        cout << "Theta (THETA) is a blockchain powered network purpose-built for video streaming." << endl;
        cout << "Launched in March 2019, the Theta mainnet operates as a decentralized network in which users" << endl;
        cout << "share bandwidth and computing resources on a peer-to-peer (P2P) basis." << endl << endl;
        cout << "Learn more on our website: https://www.thetatoken.org/" << endl << endl;
        break;
    default:
        break;
    }
}     



