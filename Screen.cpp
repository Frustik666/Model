#include "Screen.h"

std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());

Screen::Screen(): QMainWindow() {}

std::queue<std::pair<Label*, QMovie*> > del;

Screen::Screen(int length, int height): QMainWindow() {
    nowWeek_ = 0;
    timer_ = new QTimer(this);
    del_ = new QTimer(this);
    connect(del_, SIGNAL(timeout()), this, SLOT(dlt()));
    connect(timer_, SIGNAL(timeout()), this, SLOT(drawFish()));

    int id = QFontDatabase::addApplicationFont("C:/Users/ASUS/Model/resources/RogerScriptC Regular.otf");
    QString font = QFontDatabase::applicationFontFamilies(id).at(0);
    ind_ = 0;
    main_ = new Window(length, height);
    start_ = new Window(length, height);
    settings_ = new Window(length, height);
    house_ = new Window(length, height);
    table_ = new Window(length, height);
    now_ = main_;
    QPixmap back("C:/Users/ASUS/Model/resources/House.png");
    back = back.scaled(main_->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window,back);
    main_->setPalette(palette);

    auto label = new QLabel(main_);
    main_->addItem("START", label);
    label->setGeometry(174, 42, 656, 120);
    label->setFont(QFont(font, 25));
    label->setAlignment(Qt::AlignCenter);
    label->setText("МОДЕЛИРОВАНИЕ РЫБОВОДЧЕСКОГО ХОЗЯЙСТВА");
    label->setStyleSheet("QLabel {"
                         "background-color: rgba(41, 234, 247, 50);"
                         "}");

    auto *sunG = new QMovie("C:/Users/ASUS/Model/resources/sun.gif");
    auto sun = new Label(main_);
    main_->addItem("SUN", sun);
    sun->setGeometry(0, 0, 150, 150);
    sunG->setScaledSize(sun->size());
    sun->setMovie(sunG);
    sunG->start();
    connect(sun, SIGNAL(mousePressedSignal()), this, SLOT(goToMain()));

    auto play = new QPushButton(main_);
    main_->addItem("PLAY", play);
    play->setGeometry(333, 250, 333, 70);
    play->setText("ИГРАТЬ");
    play->setFont({font, 25});
    play->setStyleSheet("QPushButton {"
                        "background-color: rgba(41, 234, 247, 50);"
                        "}");
    connect(play, SIGNAL(clicked()), this, SLOT(play()));

    auto exit = new QPushButton(main_);
    main_->addItem("EXIT", exit);
    exit->setGeometry(333, 350, 333, 70);
    exit->setText("ВЫХОД");
    exit->setFont({font, 25});
    exit->setStyleSheet("QPushButton {"
                        "background-color: rgba(41, 234, 247, 50);"
                        "}");
    connect(exit, SIGNAL(clicked()), this, SLOT(goExit()));


    start_->setPalette(palette);

    auto labelM = new QLabel(start_);
    start_->addItem("PLAY", labelM);
    labelM->setGeometry(174, 42, 656, 120);
    labelM->setFont(QFont(font, 25));
    labelM->setAlignment(Qt::AlignCenter);
    labelM->setText("МОДЕЛИРОВАНИЕ РЫБОВОДЧЕСКОГО ХОЗЯЙСТВА");
    labelM->setStyleSheet("QLabel {"
                         "background-color: rgba(41, 234, 247, 50);"
                         "}");

    auto sunM = new Label(start_);
    start_->addItem("SUN", sunM);
    sunM->setGeometry(0, 0, 150, 150);
    sunM->setMovie(sunG);
    connect(sunM, SIGNAL(mousePressedSignal()), this, SLOT(goToMain()));


    auto getColPonds = new QTextEdit(start_);
    start_->addItem("PONDS", getColPonds);
    getColPonds->setGeometry(333, 200, 333, 70);
    getColPonds->setPlaceholderText("КОЛИЧЕСТВО ПРУДОВ (2-7)");
    getColPonds->setFont({font, 21});
    getColPonds->setStyleSheet("QTextEdit {"
                        "background-color: rgba(41, 234, 247, 50);"
                        "}");

    auto getWeeks = new QTextEdit(start_);
    start_->addItem("WEEKS", getWeeks);
    getWeeks->setGeometry(333, 300, 333, 70);
    getWeeks->setPlaceholderText("КОЛИЧЕСТВО НЕДЕЛЬ (3 - 24)");
    getWeeks->setFont({font, 20});
    getWeeks->setStyleSheet("QTextEdit {"
                           "background-color: rgba(41, 234, 247, 50);"
                           "}");

    auto getCapital = new QTextEdit(start_);
    start_->addItem("CAPITAL", getCapital);
    getCapital->setGeometry(333, 400, 333, 70);
    getCapital->setPlaceholderText("НАЧАЛЬНЫЙ КАПИТАЛ");
    getCapital->setFont({font, 20});
    getCapital->setStyleSheet("QTextEdit {"
                        "background-color: rgba(41, 234, 247, 50);"
                        "}");

    auto toSettings = new QPushButton(start_);
    start_->addItem("SETTINGS", toSettings);
    toSettings->setGeometry(333, 500, 333, 70);
    toSettings->setText("ДАЛЕЕ");
    toSettings->setFont({font, 20});
    toSettings->setStyleSheet("QPushButton {"
                              "background-color: rgba(41, 234, 247, 50);"
                              "}");
    connect(toSettings, SIGNAL(clicked()), this, SLOT(toSettings()));


    settings_->setPalette(palette);

    auto labelS = new QLabel(settings_);
    settings_->addItem("NAME", labelS);
    labelS->setGeometry(174, 42, 656, 120);
    labelS->setFont(QFont(font, 25));
    labelS->setAlignment(Qt::AlignCenter);
    labelS->setText("МОДЕЛИРОВАНИЕ РЫБОВОДЧЕСКОГО ХОЗЯЙСТВА");
    labelS->setStyleSheet("QLabel {"
                          "background-color: rgba(41, 234, 247, 50);"
                          "}");
    auto sunS = new Label(settings_);
    settings_->addItem("SUN", sunS);
    sunS->setGeometry(0, 0, 150, 150);
    sunS->setMovie(sunG);
    connect(sunS, SIGNAL(mousePressedSignal()), this, SLOT(goToMain()));


    QPixmap back2("C:/Users/ASUS/Model/resources/home.jpg");
    back2 = back2.scaled(main_->size(), Qt::IgnoreAspectRatio);
    palette.setBrush(QPalette::Window, back2);
    house_->setPalette(palette);

    auto door = new Label(house_);
    house_->addItem("door", door);
    door->setGeometry(270, 260, 234, 263);
    QPixmap dr("C:/Users/ASUS/Model/resources/door.png");
    dr = dr.scaled(door->size(), Qt::IgnoreAspectRatio);
    door->setPixmap(dr);
    door->setMask(dr.mask());
    connect(door, SIGNAL(mousePressedSignal()), this, SLOT(goToPonds()));

    auto desk = new Label(house_);
    house_->addItem("desk", desk);
    desk->setGeometry(502, 243, 216, 213);
    QPixmap ds("C:/Users/ASUS/Model/resources/desk.png");
    ds = ds.scaled(desk->size(), Qt::IgnoreAspectRatio);
    desk->setPixmap(ds);
    desk->setMask(ds.mask());
    connect(desk, SIGNAL(mousePressedSignal()), this, SLOT(goToTable()));

    auto lamp = new Label(house_);
    house_->addItem("desk", lamp);
    lamp->setGeometry(743, 392, 40, 80);
    connect(lamp, SIGNAL(mousePressedSignal()), this, SLOT(step()));

    pond_ = new Window(main_->size().width(), main_->size().height());
    QPixmap back3("C:/Users/ASUS/Model/resources/pound.png");
    back3 = back3.scaled(main_->size(), Qt::IgnoreAspectRatio);
    palette.setBrush(QPalette::Window, back3);
    pond_->setPalette(palette);

    auto next = new QPushButton(pond_);
    pond_->addItem("NEXT", next);
    next->setGeometry(800, 600, 200, 100);
    next->setText("ДАЛЕЕ");
    next->setFont({font, 20});
    next->setStyleSheet("QPushButton {"
                              "background-color: rgba(41, 234, 247, 50);"
                              "}");
    connect(next, SIGNAL(clicked()), this, SLOT(next()));

    auto goBack = new QPushButton(pond_);
    pond_->addItem("BACK", goBack);
    goBack->setGeometry(0, 600, 200, 100);
    goBack->setText("НАЗАД");
    goBack->setFont({font, 20});
    goBack->setStyleSheet("QPushButton {"
                        "background-color: rgba(41, 234, 247, 50);"
                        "}");
    connect(goBack, SIGNAL(clicked()), this, SLOT(back()));

    auto num = new QLabel(pond_);
    pond_->addItem("NUM", num);
    num->setGeometry(900, 0, 100, 100);
    num->setFont(QFont(font, 40));
    num->setAlignment(Qt::AlignCenter);
    num->setText(QString::number(ind_ + 1));
    num->setStyleSheet("QLabel {"
                          "background-color: rgba(41, 234, 247, 50);"
                          "}");


    ds = ds.scaled(main_->size(), Qt::IgnoreAspectRatio);
    palette.setBrush(QPalette::Window, ds);
    table_->setPalette(palette);
    auto goHome = new Label(table_);
    goHome->setGeometry(621, 572,  160, 70);
    connect(goHome, SIGNAL(mousePressedSignal()), this, SLOT(PtoModel()));


    auto week = new Label(table_);
    table_->addItem("WEEK", week);
    week->setGeometry(174, 42, 656, 120);
    week->setFont(QFont(font, 25));
    week->setAlignment(Qt::AlignCenter);
    week->setText("НЕДЕЛЯ " + QString::number(nowWeek_ + 1));
    week->setStyleSheet("QLabel {"
                        "color: white;"
                        "}");

}

void Screen::play() {
    now_->hide();
    now_ = start_;
    render();
}

void Screen::step() {
    house_->hide();
    ++nowWeek_;
    if (get_balance()[nowWeek_] <= 0) {
        goToTable();
        dynamic_cast<Label*>(table_->getItem("WEEK"))->setText("МОДЕЛИРОВАНИЕ ПРОВАЛЕНО");
        table_->show();
        return;
    }
    if (nowWeek_ == get_m() - 1) {
        goToTable();
        dynamic_cast<Label*>(table_->getItem("WEEK"))->setText("МОДЕЛИРОВАНИЕ ПРОШЛО УСПЕШНО");
        table_->show();
        return;
    }
    auto night = new Label(house_);
    night->setGeometry(0, 0, 1000, 1000);
    night->setStyleSheet("QLabel {"
                         "background-color: rgba(0, 0, 0, 90);"
                         "}");
    del.emplace(night, nullptr);
    del_->start(2000);
    night->update();
    house_->show();
}

void Screen::goExit() {
    exit(0);
}

void Screen::goToMain() {
    now_->hide();
    now_ = main_;
    render();
}

void Screen::toModel() {
    int id = QFontDatabase::addApplicationFont("C:/Users/ASUS/Model/resources/RogerScriptC Regular.otf");
    QString font = QFontDatabase::applicationFontFamilies(id).at(0);
    bool f = false;
    std::vector<std::vector<int> > par(7,std::vector<int>(4));
    for (int i = 0; i < get_k(); ++i) {
        QString ncol = dynamic_cast<QTextEdit *>(settings_->getItem("FISH" + std::to_string(i)))->toPlainText();
        if (ncol.size() == 1 && ncol[0] == '0') par[i][0] = 0;
        else if (ncol.split(" ")[0].toInt() == 0) {
            par[i][0] = -1, f = true;
        } else par[i][0] = ncol.split(" ")[0].toInt();
        int col = dynamic_cast<QTextEdit *>(settings_->getItem(
                "COLFISH" + std::to_string(i)))->toPlainText().split(" ")[0].toInt();
        if (col == 0) par[i][1] = -1, f = true;
        else par[i][1] = col;
        int cost = dynamic_cast<QTextEdit *>(settings_->getItem(
                "PRICEFISH" + std::to_string(i)))->toPlainText().split(" ")[0].toInt();
        if (cost == 0) par[i][2] = -1, f = true;
        else par[i][2] = col;
        int food = dynamic_cast<QTextEdit *>(settings_->getItem(
                "FOODFISH" + std::to_string(i)))->toPlainText().split(" ")[0].toInt();
        if (food == 0) par[i][3] = -1, f = true;
        else par[i][3] = col;
    }
    if (f) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, QString::fromUtf8("Сообщение"),
                                      QString::fromUtf8(
                                              "есть некорректно заполненные поля, они будут заданы программой.\n"
                                              "Продолжить?"),
                                              QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::No) return;
        if (reply == QMessageBox::Cancel) return;
    }
    set_contrct(par);
    run();
    data_ = get_data();
    now_->hide();
    now_ = house_;
    now_->show();
}

void Screen::goToTable() {
    int id = QFontDatabase::addApplicationFont("C:/Users/ASUS/Model/resources/RogerScriptC Regular.otf");
    QString font = QFontDatabase::applicationFontFamilies(id).at(0);
    now_->hide();
    now_ = table_;
    dynamic_cast<Label*>(table_->getItem("WEEK"))->setText("НЕДЕЛЯ " + QString::number(nowWeek_ + 1));
    int last = nowWeek_ - 1;
    if (nowWeek_ == get_m() - 1) last = 0;
    for (int i = 0; i < get_k(); ++i) {
        Label *fish;
        if (table_->getItem("FISH" + std::to_string(i)) == nullptr) fish = new Label(table_);
        else fish = dynamic_cast<Label*>(table_->getItem("FISH" + std::to_string(i)));
        table_->addItem("FISH" + std::to_string(i), fish);
        fish->setGeometry(200 + i * 100, 130, 90, 70);
        fish->setFont(QFont(font, 15));
        fish->setAlignment(Qt::AlignCenter);
        fish->setText(QString::fromStdString(fishes_[i]));
        fish->setStyleSheet("QLabel {"
                            "color: white;"
                            "}");
        Label *col;
        if (table_->getItem("COL" + std::to_string(i)) == nullptr) col = new Label(table_);
        else col = dynamic_cast<Label*>(table_->getItem("COL" + std::to_string(i)));
        table_->addItem("COL" + std::to_string(i), col);
        col->setGeometry(200 + i * 100, 182, 90, 40);
        col->setFont(QFont(font, 13));
        col->setAlignment(Qt::AlignCenter);
        auto s = QString::number(data_[nowWeek_][i][0] + data_[nowWeek_][i][1]);
        if (nowWeek_ != 0) {
            int x = data_[nowWeek_][i][0] + data_[nowWeek_][i][1] - data_[last][i][1] - data_[last][i][0];
            if (x > 0) {
                s += "(+" + QString::number(x) + ")";
            }
            if (x < 0) {
                s += "(" + QString::number(x) + ")";
            }
        }
        col->setText(s);
        col->setStyleSheet("QLabel {"
                            "color: white;"
                            "}");
        Label *coly;
        if (table_->getItem("COLY" + std::to_string(i)) == nullptr) coly = new Label(table_);
        else coly = dynamic_cast<Label*>(table_->getItem("COLY" + std::to_string(i)));
        table_->addItem("COLY" + std::to_string(i), coly);
        coly->setGeometry(200 + i * 100, 242, 90, 40);
        coly->setFont(QFont(font, 13));
        coly->setAlignment(Qt::AlignCenter);
        s = QString::number(data_[nowWeek_][i][0]);
        if (nowWeek_ != 0) {
            int x = data_[nowWeek_][i][0] - data_[last][i][0];
            if (x > 0) {
                s += "(+" + QString::number(x) + ")";
            }
            if (x < 0) {
                s += "(" + QString::number(x) + ")";
            }
        }
        coly->setText(s);
        coly->setStyleSheet("QLabel {"
                           "color: white;"
                           "}");


        Label *cola;
        if (table_->getItem("COLA" + std::to_string(i)) == nullptr) cola = new Label(table_);
        else cola = dynamic_cast<Label*>(table_->getItem("COLA" + std::to_string(i)));
        table_->addItem("COLA" + std::to_string(i), cola);
        cola->setGeometry(200 + i * 100, 300, 90, 40);
        cola->setFont(QFont(font, 13));
        cola->setAlignment(Qt::AlignCenter);
        s = QString::number(data_[nowWeek_][i][1]);
        if (nowWeek_ != 0) {
            int x = data_[nowWeek_][i][1] - data_[last][i][1];
            if (x > 0) {
                s += "(+" + QString::number(x) + ")";
            }
            if (x < 0) {
                s += "(" + QString::number(x) + ")";
            }
        }
        cola->setText(s);
        cola->setStyleSheet("QLabel {"
                            "color: white;"
                            "}");

        Label *quota;
        if (table_->getItem("QUOTA" + std::to_string(i)) == nullptr) quota = new Label(table_);
        else quota = dynamic_cast<Label*>(table_->getItem("QUOTA" + std::to_string(i)));
        table_->addItem("QUOTA" + std::to_string(i), quota);
        quota->setGeometry(200 + i * 100, 360, 90, 40);
        quota->setFont(QFont(font, 13));
        quota->setAlignment(Qt::AlignCenter);
        s = QString::number(data_[nowWeek_][i][2]);
        if (nowWeek_ != 0) {
            int x = data_[nowWeek_][i][2] - data_[last][i][2];
            if (x > 0) {
                s += "(+" + QString::number(x) + ")";
            }
            if (x < 0) {
                s += "(" + QString::number(x) + ")";
            }
        }
        quota->setText(s);
        quota->setStyleSheet("QLabel {"
                            "color: white;"
                            "}");

        Label *cost;
        if (table_->getItem("COST" + std::to_string(i)) == nullptr) cost = new Label(table_);
        else cost = dynamic_cast<Label*>(table_->getItem("COST" + std::to_string(i)));
        table_->addItem("COST" + std::to_string(i), cost);
        cost->setGeometry(200 + i * 100, 420, 90, 40);
        cost->setFont(QFont(font, 13));
        cost->setAlignment(Qt::AlignCenter);
        s = QString::number(data_[nowWeek_][i][3]);
        if (nowWeek_ != 0) {
            int x = data_[nowWeek_][i][3] - data_[last][i][3];
            if (x > 0) {
                s += "(+" + QString::number(x) + ")";
            }
            if (x < 0) {
                s += "(" + QString::number(x) + ")";
            }
        }
        cost->setText(s);
        cost->setStyleSheet("QLabel {"
                             "color: white;"
                             "}");

        Label *food;
        if (table_->getItem("FOOD" + std::to_string(i)) == nullptr) food = new Label(table_);
        else food = dynamic_cast<Label*>(table_->getItem("FOOD" + std::to_string(i)));
        table_->addItem("FOOD" + std::to_string(i), food);
        food->setGeometry(200 + i * 100, 480, 90, 40);
        food->setFont(QFont(font, 13));
        food->setAlignment(Qt::AlignCenter);
        s = QString::number(data_[nowWeek_][i][4]);
        if (nowWeek_ != 0) {
            int x = data_[nowWeek_][i][4] - data_[last][i][4];
            if (x > 0) {
                s += "(+" + QString::number(x) + ")";
            }
            if (x < 0) {
                s += "(" + QString::number(x) + ")";
            }
        }
        food->setText(s);
        food->setStyleSheet("QLabel {"
                            "color: white;"
                            "}");
    }

    Label *col;
    if (table_->getItem("COL") == nullptr) col = new Label(table_);
    else col = dynamic_cast<Label*>(table_->getItem("COL"));
    table_->addItem("COL", col);
    col->setGeometry(80, 182, 160, 40);
    col->setFont(QFont(font, 15));
    //col->setAlignment(Qt::AlignCenter);
    col->setText("КОЛ ВСЕХ(КГ)");
    col->setStyleSheet("QLabel {"
                       "color: white;"
                       "}");

    Label *coly;
    if (table_->getItem("COLY") == nullptr) coly = new Label(table_);
    else coly = dynamic_cast<Label*>(table_->getItem("COLY"));
    table_->addItem("COLY", coly);
    coly->setGeometry(80, 240, 160, 40);
    coly->setFont(QFont(font, 15));
    //col->setAlignment(Qt::AlignCenter);
    coly->setText("КОЛ МАЛЬ(КГ)");
    coly->setStyleSheet("QLabel {"
                       "color: white;"
                       "}");

    Label *cola;
    if (table_->getItem("COLA") == nullptr) cola = new Label(table_);
    else cola = dynamic_cast<Label*>(table_->getItem("COLA"));
    table_->addItem("COLA", cola);
    cola->setGeometry(80, 300, 160, 40);
    cola->setFont(QFont(font, 15));
    //col->setAlignment(Qt::AlignCenter);
    cola->setText("КОЛ ВЗР(КГ)");
    cola->setStyleSheet("QLabel {"
                        "color: white;"
                        "}");

    Label *quota;
    if (table_->getItem("QUOTA") == nullptr) quota = new Label(table_);
    else quota = dynamic_cast<Label*>(table_->getItem("QUOTA"));
    table_->addItem("QUOTA", quota);
    quota->setGeometry(80, 360, 160, 40);
    quota->setFont(QFont(font, 15));
    //col->setAlignment(Qt::AlignCenter);
    quota->setText("КВОТА(КГ)");
    quota->setStyleSheet("QLabel {"
                        "color: white;"
                        "}");

    Label *cost;
    if (table_->getItem("COST") == nullptr) cost = new Label(table_);
    else cost = dynamic_cast<Label*>(table_->getItem("COST"));
    table_->addItem("COST", cost);
    cost->setGeometry(80, 420, 160, 40);
    cost->setFont(QFont(font, 15));
    //col->setAlignment(Qt::AlignCenter);
    cost->setText("ЦЕНА РЫБЫ(РУБ)");
    cost->setStyleSheet("QLabel {"
                         "color: white;"
                         "}");

    Label *food;
    if (table_->getItem("FOOD") == nullptr) food = new Label(table_);
    else food = dynamic_cast<Label*>(table_->getItem("FOOD"));
    table_->addItem("FOOD", food);
    food->setGeometry(80, 480, 160, 40);
    food->setFont(QFont(font, 15));
    //col->setAlignment(Qt::AlignCenter);
    food->setText("ЦЕНА КОРМА(РУБ)");
    food->setStyleSheet("QLabel {"
                        "color: white;"
                        "}");

    Label *capital;
    if (table_->getItem("CAPITAL") == nullptr) capital = new Label(table_);
    else capital = dynamic_cast<Label*>(table_->getItem("CAPITAL"));
    table_->addItem("CAPITAL", capital);
    capital->setGeometry(80, 540, 300, 40);
    capital->setFont(QFont(font, 15));
    //col->setAlignment(Qt::AlignCenter);
    QString s = "КАПИТАЛ(РУБ): " + QString::number(get_balance()[nowWeek_]);
    if (nowWeek_ != 0) {
        int x = get_balance()[nowWeek_] - get_balance()[last];
        if (x > 0) {
            s += "(+" + QString::number(x) + ")";
        }
        if (x < 0) {
            s += "(" + QString::number(x) + ")";
        }
    }
    capital->setText(s);
    capital->setStyleSheet("QLabel {"
                        "color: white;"
                        "}");

    Label *AllCapital;
    if (table_->getItem("ACAPITAL") == nullptr) AllCapital = new Label(table_);
    else AllCapital = dynamic_cast<Label*>(table_->getItem("ACAPITAL"));
    table_->addItem("ACAPITAL", AllCapital);
    AllCapital->setGeometry(80, 600, 300, 40);
    AllCapital->setFont(QFont(font, 15));
    //col->setAlignment(Qt::AlignCenter);
    s = "СОСТОЯНИЕ(РУБ): ";
    int64_t cap = get_balance()[nowWeek_];
    for (const auto& ponds : data_[nowWeek_]) {
        cap += ponds[3] * (ponds[0] + ponds[1]);
     }
    s += QString::number(cap);
    if (nowWeek_ != 0) {
        int64_t capp = get_balance()[last];
        for (const auto& ponds : data_[last]) {
            capp += ponds[3] * (ponds[0] + ponds[1]);
        }
        int64_t x = cap - capp;
        if (x > 0) {
            s += "(+" + QString::number(x) + ")";
        }
        if (x < 0) {
            s += "(" + QString::number(x) + ")";
        }
    }
    AllCapital->setText(s);
    AllCapital->setStyleSheet("QLabel {"
                           "color: white;"
                           "}");


    now_->show();
}

void Screen::goToPonds() {
    now_->hide();
    now_ = pond_;
    now_->show();
    timer_->start(2000);
    del_->start(8000);
}

void Screen::back() {
    timer_->stop();
    del_->stop();
    now_->hide();
    --ind_;
    while (!del.empty()) {
        dlt();
    }
    if (ind_ < 0) {
        now_ = house_;
        now_->show();
        return;
    }
    auto lb = dynamic_cast<QLabel*>(pond_->getItem("NUM"));
    lb->setText(QString::number(ind_ + 1));
    lb->update();
        dynamic_cast<QPushButton*>(pond_->getItem("NEXT"))->setEnabled(true);
    now_->show();
    timer_->start(2000);
    del_->start(8000);
}

void Screen::next() {
    int id = QFontDatabase::addApplicationFont("C:/Users/ASUS/Model/resources/RogerScriptC Regular.otf");
    QString font = QFontDatabase::applicationFontFamilies(id).at(0);
    timer_->stop();
    del_->stop();
    now_->hide();
    ++ind_;
    while (!del.empty()) {
        dlt();
    }
    auto num = dynamic_cast<QLabel*>(pond_->getItem("NUM"));
    auto newNum = new QLabel(pond_);
    newNum->setGeometry(num->geometry());
    newNum->setFont(num->font());
    newNum->setAlignment(Qt::AlignCenter);
    newNum->setText(QString::number(ind_ + 1));
    newNum->setStyleSheet("QLabel {"
                          "background-color: rgba(41, 234, 247, 50);"
                          "}");
    delete num;
    pond_->addItem("NUM", newNum);
    if (ind_ == get_k()) {
        dynamic_cast<QPushButton*>(pond_->getItem("NEXT"))->setEnabled(false);
    }
    now_->show();
    timer_->start(2000);
    del_->stop();
}

void Screen::PtoModel() {
    now_->hide();
    if (nowWeek_== get_m() - 1 || get_balance()[nowWeek_] <= 0) {
        exit(0);
    }
    now_ = house_;
    now_->show();
}

void Screen::drawFish() {
    now_->hide();
    int y = rnd() % 8;
    bool side = rnd( ) % 2;
    bool isY = rnd() % 2;
    auto fish = new Label(pond_);
    if (side) {
        fish->setGeometry(1200, y * 100, 100 * (1 + isY), 50 * (1 + isY));
        auto *Fish = new QMovie("C:/Users/ASUS/Model/resources/fish" + QString::number(ind_ + 1) + ".gif");
        del.push({fish, Fish});
        fish->setMovie(Fish);
        Fish->setScaledSize(fish->size());
        Fish->start();
        auto *an = new QPropertyAnimation(fish, "pos");
        an->setDuration(3000);
        an->setStartValue(fish->pos());
        an->setEndValue(QPoint(-200, y * 100));
        an->start();
    } else {
        fish->setGeometry(-200, y * 100, 100 * (1 + isY), 50 * (1 + isY));
        auto *Fish = new QMovie("C:/Users/ASUS/Model/resources/fish" + QString::number(ind_ + 1) + "r.gif");
        del.push({fish, Fish});
        fish->setMovie(Fish);
        Fish->setScaledSize(fish->size());
        Fish->start();
        auto *an = new QPropertyAnimation(fish, "pos");
        an->setDuration(3000);
        an->setStartValue(fish->pos());
        an->setEndValue(QPoint(1200, y * 100));
        an->start();
    }
    now_->show();
}

void Screen::dlt() {
    if (del.empty()) {
        del_->stop();
        return;
    }
    delete del.front().first;
    delete del.front().second;
    del.pop();
}

void Screen::toSettings() {
    bool f = true;
    int colPounds = dynamic_cast<QTextEdit*>(now_->getItem("PONDS"))->toPlainText().split(" ")[0].toInt();
    int colWeeks = dynamic_cast<QTextEdit*>(now_->getItem("WEEKS"))->toPlainText().split(" ")[0].toInt();
    int capital = dynamic_cast<QTextEdit*>(now_->getItem("CAPITAL"))->toPlainText().split(" ")[0].toInt();
    if (colPounds < 2 || colPounds > 7 || colWeeks < 3 || colWeeks > 24 || capital < 10000 ) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, QString::fromUtf8("Сообщение"),
                                      QString::fromUtf8(
                                              "есть некорректно заполненные поля, они будут заданы программой.\n"
                                              "Продолжить?"),
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::No) {
            f = 0;
        } else if (reply == QMessageBox::Cancel) {
            f = 0;
        }
    }
        if (colPounds < 2 || colPounds > 7) {
            colPounds = rnd() % 6 + 2;
        }
        set_k(colPounds);
        if ( colWeeks < 3 || colWeeks > 24) {
            colWeeks = rnd() % 21 + 3;
        }
        set_m(colWeeks);
        if (capital < 10000) {
            capital = rnd() % (int)(1e7) + 10000;
        }
        set_balance(capital);

        int id = QFontDatabase::addApplicationFont("C:/Users/ASUS/Model/resources/RogerScriptC Regular.otf");
        QString font = QFontDatabase::applicationFontFamilies(id).at(0);
        fishes_ = {"ОСЁТР", "ДЕКОР", "КАРП", "ТУНЕЦ", "АКУЛА", "КАРАСЬ", "ФОРЕЛЬ"};
        for (int i = 0; i < colPounds; ++i) {
            QTextEdit *getCapital;
            if (settings_->getItem("FISH" + std::to_string(i)) == nullptr) getCapital = new QTextEdit(settings_);
            else getCapital = dynamic_cast<QTextEdit*>(settings_->getItem("FISH" + std::to_string(i)));
            settings_->addItem("FISH" + std::to_string(i), getCapital);
            getCapital->setGeometry(100, 150 + i * 70, 180, 50);
            getCapital->setPlaceholderText("ИЗН КОЛ " + QString::fromStdString(fishes_[i]));
            getCapital->setFont({font, 14});
            getCapital->setStyleSheet("QTextEdit {"
                                      "background-color: rgba(41, 234, 247, 50);"
                                      "}");

            QTextEdit *getCol;
            if (settings_->getItem("COLFISH" + std::to_string(i)) == nullptr) getCol = new QTextEdit(settings_);
            else getCol = dynamic_cast<QTextEdit*>(settings_->getItem("COLFISH" + std::to_string(i)));
            settings_->addItem("COLFISH" + std::to_string(i), getCol);
            getCol->setGeometry(300, 150 + i * 70, 180, 50);
            getCol->setPlaceholderText("КВОТА " + QString::fromStdString(fishes_[i]));
            getCol->setFont({font, 14});
            getCol->setStyleSheet("QTextEdit {"
                                  "background-color: rgba(41, 234, 247, 50);"
                                  "}");

            QTextEdit *getPrice;
            if (settings_->getItem("PRICEFISH" + std::to_string(i)) == nullptr) getPrice = new QTextEdit(settings_);
            else getPrice = dynamic_cast<QTextEdit*>(settings_->getItem("PRICEFISH" + std::to_string(i)));
            settings_->addItem("PRICEFISH" + std::to_string(i), getPrice);
            getPrice->setGeometry(500, 150 + i * 70, 180, 50);
            getPrice->setPlaceholderText("ЦЕНА " + QString::fromStdString(fishes_[i]));
            getPrice->setFont({font, 16});
            getPrice->setStyleSheet("QTextEdit {"
                                    "background-color: rgba(41, 234, 247, 50);"
                                    "}");

            QTextEdit *getFood;
            if (settings_->getItem("FOODFISH" + std::to_string(i)) == nullptr) getFood = new QTextEdit(settings_);
            else getFood = dynamic_cast<QTextEdit*>(settings_->getItem("FOODFISH" + std::to_string(i)));
            settings_->addItem("FOODFISH" + std::to_string(i), getFood);
            getFood->setGeometry(700, 150 + i * 70, 180, 50);
            getFood->setPlaceholderText("ЦЕНА КОРМА " + QString::fromStdString(fishes_[i]));
            getFood->setFont({font, 15});
            getFood->setStyleSheet("QTextEdit {"
                                   "background-color: rgba(41, 234, 247, 50);"
                                   "}");
        }
        for (int i = colPounds; i < 7; ++i) {
            delete settings_->getItem("FISH" + std::to_string(i));
            settings_->getItem("FISH" + std::to_string(i)) = nullptr;
            delete settings_->getItem("COLFISH" + std::to_string(i));
            settings_->getItem("COLFISH" + std::to_string(i)) = nullptr;
            delete settings_->getItem("PRICEFISH" + std::to_string(i));
            settings_->getItem("PRICEFISH" + std::to_string(i)) = nullptr;
            delete settings_->getItem("FOODFISH" + std::to_string(i));
            settings_->getItem("FOODFISH" + std::to_string(i)) = nullptr;
        }

        QPushButton* toModel;
        if (settings_->getItem("TOMODEL") == nullptr) {
            toModel = new QPushButton(settings_);
            connect(toModel, SIGNAL(clicked()), this, SLOT(toModel()));
        }
        else toModel = dynamic_cast<QPushButton*>(settings_->getItem("TOMODEL"));
        settings_->addItem("TOMODEL", toModel);
        toModel->setGeometry(100, 150 + colPounds * 70, 780, 50);
        toModel->setText("ДАЛЕЕ");
        toModel->setFont({font, 20});
        toModel->setStyleSheet("QPushButton {"
                               "background-color: rgba(41, 234, 247, 50);"
                               "}");
        if (f) {
            now_->hide();
            now_ = settings_;
            now_->show();
        }
}


Screen::~Screen() {
    delete main_;
    delete start_;
    delete settings_;
    delete house_;
    delete table_;
    delete pond_;
    delete timer_;
    delete del_;
}
