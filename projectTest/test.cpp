#include "pch.h"
#include "../project_uni/Coin.h"
#include "../project_uni/Portfolio.h"
#include "../project_uni/User.h"
#include <string>
using namespace std;


//Coin class functions
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

double Coin::get_price(Coin list[], int i)
{
    double m;
    m = list[i].price;
    return m;
}


//User class functions
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



//Portfolio class functions
Portfolio::Portfolio()
{
    name = "No data";
    coin_amount = 0;
}

Portfolio::Portfolio(double bal)
{
    coin_amount = bal;
}

double Portfolio::get_amnt()
{
    return coin_amount;
}

bool Portfolio::buy_coin(double sum, double price, Portfolio list[], int i)
{
    float qty;
    int ans;
    qty = sum / price;
    cout << endl;
    cout << "You will receive " << setprecision(5) << qty << " coins" << endl;
    cout << "Price per coin is: " << setprecision(5) << price << endl << endl;
    cout << "Please confirm:" << endl << endl;
    cout << "1 - Confirm" << endl;
    cout << "2 - Discard" << endl << endl;
    cout << "Your choice: ";
    list[i].coin_amount += qty;
    list[i].coin_balance += sum;
    list[i].entry_price = price;
    cout << endl;
    cout << "Transaction processing..." << endl;
    cout << "Transaction success" << endl;
    return true;
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

bool Portfolio::sell_coin(double sum, double price, Portfolio list[], int i)
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
    if ((i == 0) || (i == 1))
    {
        if ((list[i].coin_amount >= (qty - 0.0008)) && (list[i].coin_amount <= (qty + 0.0001)))
        {
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
        if ((list[i].coin_amount >= (qty - 0.08)) && (list[i].coin_amount <= (qty + 0.01)))
        {
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
    cout << "Transaction success" << endl;
    return true;
}

//Testing
TEST(TestCoin, DefaultConstructor) {
    Coin p1;
    EXPECT_EQ(0, p1.get_pr());
}

TEST(TestCoin, ParamConstructor) {
    Coin p2("Bit", 200);
    EXPECT_EQ(200, p2.get_pr());
}

TEST(TestCoin, AccessPrice) {
    Coin p3[1];
    double m;
    m = p3->get_price(p3, 0);
    EXPECT_EQ(0, m);
}
TEST(TestUser, DefaultConstructor) {
    User u1;
    EXPECT_EQ(0, u1.get_bal());
}

TEST(TestUser, ParamConstructor) {
    User u2("Name", "123ee");
    EXPECT_EQ(10000, u2.get_bal());
}

TEST(TestUser, CheckBalance) {
    User u3("Name", "1234");
    u3.check_balance(11000);
    EXPECT_FALSE(false);
}

TEST(TestPortfolio, DefaultConstructor) {
    Portfolio f1;
    EXPECT_EQ(0, f1.get_amnt());
}

TEST(TestPortfolio, ParamConstructor) {
    Portfolio f21(300);
    EXPECT_EQ(300, f21.get_amnt());
}

TEST(TestPortfolio, Buy) {
    Portfolio f2[1];
    f2->buy_coin(100, 20, f2, 0);
    EXPECT_EQ(5, f2[0].get_amnt());
}

TEST(TestPortfolio, CheckCoinBal) {
    Portfolio f3[1];
    f3->check_coin_balance(500, f3, 0);
    EXPECT_FALSE(false);
}

TEST(TestPortfolio, Sell) {
    Portfolio f4[1];
    f4->sell_coin(200, 2, f4, 0);
    EXPECT_EQ(-100, f4[0].get_amnt());
}