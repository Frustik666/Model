#include <bits/stdc++.h>

#include <utility>

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

    Pond(const Pond& other) : a(other.a), b(other.b), d(other.b), q(other.q), na(other.na), ny(other.ny),
                              price(other.price), name(other.name), photo(other.photo) {}

    void set_price(int p) {
        price = p;
    }

    void set_feed_kf(double qq) {
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
        int prev = ny;
        ny = a * na;
        na = b * prev - d * na;
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

    int set_ind(int i) {
        ind = i;
    }

    int get_ind() {
        return ind;
    }

    int feed_price() const {
        return q / 2 * ny + q * na;
    }
private:
    int na, ny, price;
    std::string name, photo;
    double a, b, d, q, ind;
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
        ponds[i].set_ny(l);
        ponds[i].set_na(0);
    }
    int n = m / 3;
    std::vector<std::vector<int>> prices(k, std::vector<int>(n)), amount(k, std::vector<int>(n)),
                                                                  fine(k, std::vector<int>(n));
    std::vector<std::vector<double>> feed_kf(k, std::vector<double>(n));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << "Enter the needed amount of fish from pond " << i + 1 << " under contract " << j + 1 << ": \n";
            std::cin >> amount[i][j];
            std::cout << "Enter the fine for pond " << i + 1 << " under contract " << j + 1 << ": \n";
            std::cin >> fine[i][j];
            std::cout << "Enter the price of fish from pond " << i + 1 << " under contract " << j + 1 << ": \n";
            std::cin >> prices[i][j];
        }
    }
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << "Enter the cost of dry food for fish from pond " << i + 1 << " under contract " << j + 1 << ": \n";
            std::cin >> feed_kf[i][j];
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
            for (int j = 0; j < k; ++j) {
                ponds[pos[j]].set_price(prices[j][i / 3]);
                ponds[pos[j]].set_feed_kf(feed_kf[j][i / 3]);
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
            if (ponds[j].feed_price() > s) {
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
            ponds[j].set_ny(ponds[j].get_ny() + (s / 4.0 / k) / ponds[j].get_price());
        }
        std::cout << s << "\n";
        int fn = 0;
        for (int j = 0; j < k; ++j) {
            if (ponds[pos[j]].get_na() < amount[j][i / 3]) {
                 fn += fine[j][i / 3];
            } else {
                ponds[pos[j]].set_na(ponds[pos[j]].get_na() - amount[j][i / 3]);
                s += prices[j][i / 3] * amount[j][i / 3];
            }
        }
        s -= fn;
        std::cout << s << "\n";
        if (s < 0) {
            std::cout << "You're a bankrupt((\n";
            return 0;
        }
    }
}
