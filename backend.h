#pragma once
#include <bits/stdc++.h>

std::mt19937 rnd(time(nullptr));

int rd();

double get_a();

double get_b();

double get_d();

class Pond {
public:
    Pond(double a = get_a(), double b = get_b(), double d = get_d(), std::string n = "none", std::string p = "no photo");

    Pond(const Pond& other);

    void set_price(int p);

    void set_feed_kf(int qq);

    void set_name(std::string s);

    void set_ny(int n);

    void set_na(int n);

    void reduce(double perc);

    std::string get_name();

    void iterate();

    double cmp_value();

    int get_price();

    int get_ny();

    int get_na();

    void set_ind(int i);

    int get_ind();

    int feed_price();
private:
    int na, ny, price, q, ind;
    std::string name, photo;
    double a, b, d;
};

double gt_perc();

class Accident {
public:
    Accident(double perc = gt_perc());

    void set_name(std::string nm);

    std::string get_name();

    double get_perc();

private:
    double perc;
    std::string name;
};

bool operator < (Pond a, Pond b);

double get_dif();

int get_amount();

int get_col();

int get_fine() ;

int get_price();

int get_feedkf();

void set_k(int k0);

void set_m(int m0);

void set_balance(int s0);

int get_k();

int get_m();

int get_balance();

int get_na(int i);

int get_ny(int i);

std::vector<std::vector<int>> get_contract();

void run();
