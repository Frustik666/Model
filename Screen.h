#pragma once
#include "Window.h"
#include "Label.h"
#include "backend.h"


 class Screen: public QMainWindow {

    Q_OBJECT

 public:
    Screen(int length, int height);
    Screen();
    ~Screen() override;

    void render() {
        now_->show();
    }
private slots:

    void play();
    static void goExit();
    void goToMain();
    void toSettings();
    void toModel();
    void PtoModel();
    void goToPonds();
    void goToTable();
    void next();
    void back();
    void drawFish();
    void dlt();
    void step();

 private:
     int ind_, nowWeek_;
     Window* now_;
     Window* main_;
     Window* start_;
     Window* settings_;
     Window* house_;
     Window* table_;
     Window* pond_;
     std::vector<std::string> fishes_;
     std::vector<std::vector<std::vector<int>>> data_;
    QTimer *timer_, *del_;


};
