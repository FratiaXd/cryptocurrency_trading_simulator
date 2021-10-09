
//Class portfolio
#pragma once
#define Portfolio_H
#include "Coin.h"
#include <string>

class Portfolio : public Coin
{
protected:
    double coin_amount;
    double coin_balance;
    double entry_price;
    double profit_loss;
public:
    Portfolio();
    Portfolio(double bal);
    double get_amnt();
    void read_portfolio(std::ifstream& port);
    void list_portf(Portfolio list[], int num, std::string fname);
    void save_portfolio(std::string file, Portfolio list[], int a, Coin lt[]);
    void save_transaction(std::string filen, std::string type, Portfolio list[], int i, double qty);
    bool buy_coin(double sum, double price, Portfolio li[], int i);
    void display_coin_bal(Portfolio list[], int i);
    bool check_coin_balance(double a, Portfolio list[], int i);
    bool sell_coin(double sum, double price, Portfolio list[], int i);
    void display_portfolio();
    void display_fullp(Portfolio list[], int num);
    void after_transaction(Portfolio list[], int id, std::string portf, int coin_num, double sum, double pr, std::string hist, Coin lt[], std::string status);
};