//
// Created by ASUS on 07.10.2024.
//
#include "Screen.h"

std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());

Screen::Screen(): QMainWindow() {}

Screen::Screen(int length, int height): QMainWindow() {
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(drawFish()));
    int id = QFontDatabase::addApplicationFont("C:/Users/ASUS/Model/resources/RogerScriptC Regular.otf");
    QString font = QFontDatabase::applicationFontFamilies(id).at(0);
    ind_ = 0;
    main_ = new Window(length, height);
    history_ = new Window(length, height);
    start_ = new Window(length, height);
    settings_ = new Window(length, height);
    house_ = new Window(length, height);
    table_ = new Window(length, height);
    now_ = main_;
    QPixmap back("C:/Users/ASUS/Model/resources/House.png");
    back = back.scaled(main_->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, back);
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
    play->setGeometry(333, 197, 333, 70);
    play->setText("ИГРАТЬ");
    play->setFont({font, 25});
    play->setStyleSheet("QPushButton {"
                        "background-color: rgba(41, 234, 247, 50);"
                        "}");
    connect(play, SIGNAL(clicked()), this, SLOT(play()));

    auto history = new QPushButton(main_);
    main_->addItem("HISTORY", history);
    history->setGeometry(333, 300, 333, 70);
    history->setText("ИСТОРИЯ");
    history->setFont({font, 25});
    history->setStyleSheet("QPushButton {"
                        "background-color: rgba(41, 234, 247, 50);"
                        "}");
    connect(history, SIGNAL(clicked()), this, SLOT(toHistory()));

    auto exit = new QPushButton(main_);
    main_->addItem("EXIT", exit);
    exit->setGeometry(333, 400, 333, 70);
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
    pond_->addItem("NUM", labelS);
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

    //timer_->start(1000);
}

void Screen::play() {
    now_->hide();
    now_ = start_;
    render();
}

void Screen::toHistory() {
    now_->hide();
    now_ = history_;
    render();
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
    now_->hide();
    now_ = house_;
    now_->show();
}

void Screen::goToTable() {
    now_->hide();
    now_ = table_;
    now_->show();
}

void Screen::goToPonds() {
    now_->hide();
    now_ = pond_;
    now_->show();
    timer_->start(1000);
}

void Screen::back() {
    --ind_;
    if (ind_ < 0) {
        toModel();
        return;
    }
    auto lb = dynamic_cast<QLabel*>(pond_->getItem("NUM"));
    lb->setText(QString::number(ind_ + 1));
    lb->update();
        dynamic_cast<QPushButton*>(pond_->getItem("NEXT"))->setEnabled(true);
    now_->hide();
    now_->show();
}

void Screen::next() {
    ++ind_;
    auto lb = dynamic_cast<QLabel*>(pond_->getItem("NUM"));
    lb->setText(QString::number(ind_ + 1));
    lb->update();
    if (ind_ == col_) {
        dynamic_cast<QPushButton*>(pond_->getItem("NEXT"))->setEnabled(false);
    }
    now_->hide();
    now_->show();
}

void Screen::drawFish() {
    now_->hide();
    int y = rnd() % 16;
    bool side = rnd();
    bool isY = rnd();
    auto fish = new Label(pond_);
    fish->setGeometry(1000, y * 50, 100, 50);
    auto *Fish = new QMovie("C:/Users/ASUS/Model/resources/fish" + QString::number(ind_ + 1) + ".gif");
    fish->setMovie(Fish);
    Fish->setScaledSize(fish->size());
    Fish->start();
    auto* an = new QPropertyAnimation(fish, "pos");
    an->setDuration(3000);
    an->setStartValue(fish->pos());
    an->setEndValue(QPoint(-200, y * 50));
    an->start();
    now_->show();
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
        if (reply == QMessageBox::Yes) {
            now_->hide();
            now_ = settings_;
            now_->show();
            colPounds = 3;
            col_ = 3;
            std::vector<int> par(3);
            par[0] = -1;
            par[1] = -1;
            par[2] = -1;
        }
        return;
    }
    std::vector<int> par(3);
    par[0] = colPounds;
    col_ = colPounds;
    par[1] = colWeeks;
    par[2] = capital;
    int id = QFontDatabase::addApplicationFont("C:/Users/ASUS/Model/resources/RogerScriptC Regular.otf");
    QString font = QFontDatabase::applicationFontFamilies(id).at(0);
    fishes_ =  {"ОСЁТР", "ТУНЕЦ", "КАРП", "ДЕКОР", "", "", ""};
    for (int i = 0; i < colPounds; ++i) {

        auto getCapital = new QTextEdit(settings_);
        settings_->addItem("FISH" + std::to_string(i), getCapital);
        getCapital->setGeometry(100, 150 + i * 70, 180, 50);
        getCapital->setPlaceholderText("ИЗНАЧАЛЬНО КОЛ " + QString::fromStdString(fishes_[i]));
        getCapital->setFont({font, 14});
        getCapital->setStyleSheet("QTextEdit {"
                                  "background-color: rgba(41, 234, 247, 50);"
                                  "}");

        auto getCol = new QTextEdit(settings_);
        settings_->addItem("COLFISH" + std::to_string(i), getCol);
        getCol->setGeometry(300, 150 + i * 70, 180, 50);
        getCol->setPlaceholderText("КОЛ В ДОГОВОРЕ " + QString::fromStdString(fishes_[i]));
        getCol->setFont({font, 14});
        getCol->setStyleSheet("QTextEdit {"
                              "background-color: rgba(41, 234, 247, 50);"
                              "}");

        auto getPrice = new QTextEdit(settings_);
        settings_->addItem("PRICEFISH" + std::to_string(i), getPrice);
        getPrice->setGeometry(500, 150 + i * 70, 180, 50);
        getPrice->setPlaceholderText("ЦЕНА " + QString::fromStdString(fishes_[i]));
        getPrice->setFont({font, 16});
        getPrice->setStyleSheet("QTextEdit {"
                                "background-color: rgba(41, 234, 247, 50);"
                                "}");

        auto getFood = new QTextEdit(settings_);
        settings_->addItem("FOODFISH" + std::to_string(i), getFood);
        getFood->setGeometry(700, 150 + i * 70, 180, 50);
        getFood->setPlaceholderText("ЦЕНА КОРМА " + QString::fromStdString(fishes_[i]));
        getFood->setFont({font, 16});
        getFood->setStyleSheet("QTextEdit {"
                               "background-color: rgba(41, 234, 247, 50);"
                               "}");
    }
    auto toModel = new QPushButton(settings_);
    settings_->addItem("TOMODEL", toModel);
    toModel->setGeometry(100, 150 + colPounds * 70, 780, 50);
    toModel->setText("ДАЛЕЕ");
    toModel->setFont({font, 20});
    toModel->setStyleSheet("QPushButton {"
                           "background-color: rgba(41, 234, 247, 50);"
                           "}");
    connect(toModel, SIGNAL(clicked()), this, SLOT(toModel()));
    now_->hide();
    now_ = settings_;
    now_->show();
}


Screen::~Screen() {
    delete main_;
    delete start_;
    delete history_;
    delete house_;
    delete table_;
    delete pond_;
}
