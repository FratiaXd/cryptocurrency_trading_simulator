
//Class coin

#pragma once
#define Coin_H
#include <string>

class Coin
{
private:
    double price;
    double price_change;
protected:
    std::string name;
public:
    Coin(std::string cName, double cPrice);
    Coin();
    int get_pr();
    void create_fcoin(Coin arr[], int coin_num);
    void load_coins(std::ifstream& coinF);
    void list_coins(Coin list[], int coin_num, std::string fname);
    void display_coin(Coin list[], int i);
    void update_price(Coin list[], int coin_num);
    void save_coins(Coin list[], int coin_n);
    double get_price(Coin list[], int i);

};