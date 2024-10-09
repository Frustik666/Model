#include <bits/stdc++.h>
#include "backend.h"

int rd() {
    return abs((int)(rnd()));
}

double get_a() {
    double r = rd() % 2000 + 1000;
    return r / 100.0;
}

double get_b() {
    double r = rd() % 30 + 70;
    return r / 100.0;
}

double get_d() {
    double r = rd() % 20 + 30;
    return r / 100.0;
}

Pond::Pond(double a, double b, double d, std::string n, std::string p) :
a(a), b(b), d(d), name(std::move(n)), photo(std::move(p)) {}

Pond::Pond(const Pond& other) : a(other.a), b(other.b), d(other.b), ind(other.ind), q(other.q), na(other.na), ny(other.ny),
                          price(other.price), name(other.name), photo(other.photo) {}

void Pond::set_price(int p) {
    price = p;
}

void Pond::set_feed_kf(int qq) {
    q = qq;
}

void Pond::set_name(std::string s) {
    name = std::move(s);
}

void Pond::set_ny(int n) {
    ny = n;
}

void Pond::set_na(int n) {
    na = n;
}

void Pond::reduce(double perc) {
    na = na * (1.0 - perc);
    ny = ny * (1.0 - perc);
}

std::string Pond::get_name() {
    return name;
}

void Pond::iterate() {
    int prev = ny;
    ny = a * na;
    na = std::max(0.0, na + b * prev - d * na);
}

double Pond::cmp_value() {
    return (a + b - d) * price / q;
}

int Pond::get_price() {
    return price;
}

int Pond::get_ny() {
    return ny;
}

int Pond::get_na() {
    return na;
}

void Pond::set_ind(int i) {
    ind = i;
}

int Pond::get_ind() {
    return ind;
}

int Pond::feed_price() {
    return q / 2 * ny + q * na;
}


double gt_perc() {
    int p = rd() % 11 + 10;
    return 1.0 * p / 100.0;
}

Accident::Accident(double perc) : perc(perc) {}

void Accident::set_name(std::string nm) {
    name = std::move(nm);
}

std::string Accident::get_name() {
    return name;
}

double Accident::get_perc() {
    perc = gt_perc();
    return perc;
}


bool operator < (Pond a, Pond b) {
    return a.cmp_value() > b.cmp_value();
}

double get_dif() {
    int r = rd() % 41 + 80;
    return r / 100.0;
}

int get_amount() {
    int r = rd() % 41 + 10;
    return r;
}

int get_col() {
    int r = rd() % 8 + 3;
    return r;
}

int get_fine() {
    int r = rd() % 1001 + 1000;
    return r;
}

int get_price() {
    int r = rd() % 501 + 500;
    return r;
}

int get_feedkf() {
    int r = rd() % 201 + 200;
    return r;
}

void set_k(int& k) {
    std::cout << "Enter k: \n";
    std::cin >> k;
}

void set_m(int& m) {
    std::cout << "Enter m: \n";
    std::cin >> m;
}

void set_balance(int& s) {
    std::cout << "Enter the starting balance: \n";
    std::cin >> s;
}

void set_number(int& n, int i) {
    std::cout << "Set the number of fish in the " << i + 1 << " pond: \n";
    std::cin >> n;
}

void set_amount(int& a, int i) {
    std::cout << "Enter the needed amount of fish from pond " << i + 1 << " under contract " << 0 + 1 << ": \n";
    std::cin >> a;
}

void set_fine(int& f, int i) {
    std::cout << "Enter the fine for pond " << i + 1 << " under contract " << 0 + 1 << ": \n";
    std::cin >> f;
}

void set_feed(int& kf, int i) {
    std::cout << "Enter the cost of dry food for fish from pond " << i + 1 << " under contract " << 0 + 1 << ": \n";
    std::cin >> kf;
}

void set_price(int& p, int i) {
    std::cout << "Enter the price of fish from pond " << i + 1 << " under contract " << 0 + 1 << ": \n";
    std::cin >> p;
}

void run() {
    std::vector<std::string> names{"Cod", "Carp", "Salmon", "Trout", "Catfish", "Shark", "Clownfish"};
    std::vector<std::string> accs{"fever", "temperature fluctuations", "frosts", "poaching",
                                  "water poisoning", "storm", "zombie apocalypse", "fish tornado"};
    std::shuffle(names.begin(), names.end(), std::random_device());
    std::shuffle(accs.begin(), accs.end(), std::random_device());
    std::vector<Pond> ponds(7);
    for (int i = 0; i < 7; ++i) {
        ponds[i].set_name(names[i]);
        ponds[i].set_ind(i);
    }
    int k, m;
    set_k(k);
    set_m(m);
    while ((int)ponds.size() > k) ponds.pop_back();
    std::vector<int> pos(k);
    std::iota(pos.begin(), pos.end(), 0);
    int s;
    set_balance(s);
    for (int i = 0; i < k; ++i) {
        int l;
        set_number(l, i);
        if (l == -1) {
            l = get_amount();
        }
        ponds[i].set_ny(l);
        ponds[i].set_na(0);
    }
    int n = m / 3;
    std::vector<int> prices(k), amount(k), fine(k), feed_kf(k);
    for (int i = 0; i < k; ++i) {
        set_amount(amount[i], i);
        if (amount[i] == -1) {
            amount[i] = get_col();
        }
        set_fine(fine[i], i);
        if (fine[i] == -1) {
            fine[i] = get_fine();
        }
        set_feed(feed_kf[i], i);
        if (feed_kf[i] == -1) {
            feed_kf[i] = get_feedkf();
        }
        set_price(prices[i], i);
        if (prices[i] == -1) {
            prices[i] = get_price() + feed_kf[i];
        }
    }
    int cns = rd() % n + 1;
    std::vector<std::vector<Accident>> tms(n);
    for (int i = 0; i < cns; ++i) {
        Accident ac;
        ac.set_name(accs[i]);
        tms[rd() % n].push_back(ac);
    }
    std::sort(ponds.begin(), ponds.end());
    for (int j = 0; j < k; ++j) {
        pos[ponds[j].get_ind()] = j;
    }
    for (int i = 0; i < m; ++i) {
        if (i % 3 == 0) {
            if (i) {
                for (int j = 0; j < k; ++j) {
                    prices[j] = prices[j] * 1.0 * get_dif();
                    feed_kf[j] = feed_kf[j] * 1.0 * get_dif();
                    amount[j] = amount[j] * 1.0 * get_dif();
                }
            }
            for (int j = 0; j < k; ++j) {
                ponds[pos[j]].set_price(prices[j]);
                ponds[pos[j]].set_feed_kf(feed_kf[j]);
            }
            for (auto& acc : tms[i / 3]) {
                std::cout << "A " << acc.get_name() << " occured! " << (int)(acc.get_perc() * 100) <<
                " percent of fish died(((\n";
                for (auto& pnd : ponds) {
                    pnd.reduce(acc.get_perc());
                }
            }
            std::sort(ponds.begin(), ponds.end());
            for (int j = 0; j < k; ++j) {
                pos[ponds[j].get_ind()] = j;
            }
        }
        for (int j = 0; j < k; ++j) {
            if (ponds[j].get_na() > amount[ponds[j].get_ind()]) {
                double kf = 1.0 - std::min(1.0, s / 4.0 / k / ponds[j].feed_price());
                ponds[j].reduce(kf);
                s -= std::min(ponds[j].feed_price(), s / 4 / k);
            } else if (ponds[j].feed_price() > s) {
                double kf = 1.0 - s * 1.0 / ponds[j].feed_price();
                ponds[j].reduce(kf);
                s = 0;
            } else {
                s -= ponds[j].feed_price();
            }
            ponds[j].iterate();
        }
        std::sort(ponds.begin(), ponds.end());
        for (int j = 0; j < k; ++j) {
            pos[ponds[j].get_ind()] = j;
        }
        for (int j = 0; j < k; ++j) {
            ponds[j].set_ny(ponds[j].get_ny() + (s / 4.0 / k) / prices[ponds[j].get_ind()]);
        }
        int fn = 0;
        for (int j = 0; j < k; ++j) {
            if (ponds[pos[j]].get_na() < amount[j]) {
                 fn += fine[j];
            } else {
                ponds[pos[j]].set_na(ponds[pos[j]].get_na() - amount[j]);
                s += prices[j] * amount[j];
            }
        }
        s -= fn;
        std::cout << "Your balance after the " << i + 1 << " week is " << std::max(0, s) << "!\n";
        if (s < 0) {
            std::cout << "You're a bankrupt((\n";
            return;
        }
    }
    std::cout << "Your final balance is " << s << "!\n";
}

signed main() {
    run();
}