
//Class user
#pragma once

#define User_H
#include <string>

class User
{
protected:
    std::string username;
    std::string password;
    double balance;

public:
    User(std::string nm, std::string pass);
    User();
    double get_bal();
    void display_user();
    void create_usfile();
    void create_portfolio();
    void create_trhis();
    bool check_user(std::string filename, std::string usname, std::string psword);
    bool check_balance(double a);
    double get_balance(std::string fname);
    void upd_balance(double m, std::string fnm, int op);

};