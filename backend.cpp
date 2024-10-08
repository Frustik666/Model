#include <bits/stdc++.h>

std::mt19937 rnd(time(nullptr));

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

class Pond {
public:
    Pond(double a = get_a(), double b = get_b(), double d = get_d(), std::string n = "none", std::string p = "no photo") :
    a(a), b(b), d(d), name(std::move(n)), photo(std::move(p)) {}

    Pond(const Pond& other) : a(other.a), b(other.b), d(other.b), ind(other.ind), q(other.q), na(other.na), ny(other.ny),
                              price(other.price), name(other.name), photo(other.photo) {}

    void set_price(int p) {
        price = p;
    }

    void set_feed_kf(int qq) {
        q = qq;
    }

    void set_name(std::string s) {
        name = std::move(s);
    }

    void set_ny(int n) {
        ny = n;
    }

    void set_na(int n) {
        na = n;
    }

    void reduce(double perc) {
        na = na * (1.0 - perc);
        ny = ny * (1.0 - perc);
    }

    std::string get_name() {
        return name;
    }

    void iterate() {
//        std::cout << "it " << na << " "<< ny << " " << a << " " << b << " " << d << "\n";
        int prev = ny;
        ny = a * na;
        na = std::max(0.0, na + b * prev - d * na);
//        std::cout << "ti " << na << " "<< ny << "\n";
    }

    double cmp_value() {
        return (a + b - d) * price / q;
    }

    int get_price() {
        return price;
    }

    int get_ny() {
        return ny;
    }

    int get_na() {
        return na;
    }

    void set_ind(int i) {
        ind = i;
    }

    int get_ind() {
        return ind;
    }

    int feed_price() {
        return q / 2 * ny + q * na;
    }
private:
    int na, ny, price, q, ind;
    std::string name, photo;
    double a, b, d;
};

double gt_perc() {
    int p = rd() % 11 + 10;
    return 1.0 * p / 100.0;
}

class Accident {
public:
    Accident(double perc = gt_perc()) : perc(perc) {}

    void set_name(std::string nm) {
        name = std::move(nm);
    }

    std::string get_name() {
        return name;
    }

    double get_perc() {
        perc = gt_perc();
        return perc;
    }

private:
    double perc;
    std::string name;
};

bool operator < (Pond a, Pond b) {
    return a.cmp_value() > b.cmp_value();
}

std::vector<std::string> names{"Cod", "Carp", "Salmon", "Trout", "Catfish", "Shark", "Clownfish"};
std::vector<std::string> accs{"fever", "temperature fluctuations", "frosts", "poaching",
                              "water poisoning", "storm", "zombie apocalypse", "fish tornado"};

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

signed main() {
    std::shuffle(names.begin(), names.end(), std::random_device());
    std::shuffle(accs.begin(), accs.end(), std::random_device());
    std::vector<Pond> ponds(7);
    for (int i = 0; i < 7; ++i) {
        ponds[i].set_name(names[i]);
        ponds[i].set_ind(i);
    }
    int k, m;
    std::cout << "Enter k && m: \n";
    std::cin >> k >> m;
    while ((int)ponds.size() > k) ponds.pop_back();
    std::vector<int> pos(k);
    std::iota(pos.begin(), pos.end(), 0);
    std::cout << "Enter the starting balance: \n";
    int s;
    std::cin >> s;
    for (int i = 0; i < k; ++i) {
        std::cout << "Set the number of fish in the " << i + 1 << " pond: \n";
        int l;
        std::cin >> l;
        if (l == -1) {
            l = get_amount();
        }
        ponds[i].set_ny(l);
        ponds[i].set_na(0);
    }
    int n = m / 3;
    std::vector<int> prices(k), amount(k), fine(k), feed_kf(k);
    for (int i = 0; i < k; ++i) {
        std::cout << "Enter the needed amount of fish from pond " << i + 1 << " under contract " << 0 + 1 << ": \n";
        std::cin >> amount[i];
        if (amount[i] == -1) {
            amount[i] = get_col();
        }
        std::cout << "Enter the fine for pond " << i + 1 << " under contract " << 0 + 1 << ": \n";
        std::cin >> fine[i];
        if (fine[i] == -1) {
            fine[i] = get_fine();
        }
        std::cout << "Enter the cost of dry food for fish from pond " << i + 1 << " under contract " << 0 + 1 << ": \n";
        std::cin >> feed_kf[i];
        if (feed_kf[i] == -1) {
            feed_kf[i] = get_feedkf();
        }
        std::cout << "Enter the price of fish from pond " << i + 1 << " under contract " << 0 + 1 << ": \n";
        std::cin >> prices[i];
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
//                std::cout << 0 << "\n";
                double kf = 1.0 - std::min(1.0, s / 4.0 / k / ponds[j].feed_price());
                ponds[j].reduce(kf);
                s -= std::min(ponds[j].feed_price(), s / 4 / k);
            } else if (ponds[j].feed_price() > s) {
//                std::cout << ponds[j].feed_price() << " " << ponds[j].get_na() << " " << ponds[j].get_ny() << " " << feed_kf[ponds[j].get_ind()] << " " << s << "\n";
//                std::cout << 1 << "\n";
                double kf = 1.0 - s * 1.0 / ponds[j].feed_price();
                ponds[j].reduce(kf);
                s = 0;
            } else {
//                std::cout << 2 << "\n";
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
//            std::cout << j << " " << ponds[j].get_na() << " " << ponds[j].get_ny() << "\n";
            if (ponds[pos[j]].get_na() < amount[j]) {
                 fn += fine[j];
            } else {
                ponds[pos[j]].set_na(ponds[pos[j]].get_na() - amount[j]);
                s += prices[j] * amount[j];
            }
//            std::cout << j << " " << ponds[j].get_na() << " " << ponds[j].get_ny() << "\n";
        }
        s -= fn;
        if (s < 0) {
            std::cout << "You're a bankrupt((\n";
            return 0;
        }
        std::cout << "Your balance after the " << i + 1 << " week is " << s << "!\n";
    }
    std::cout << "Your final balance is " << s << "!\n";
}
