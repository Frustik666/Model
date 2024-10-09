#pragma once
#include "Window.h"
#include "Label.h"
#include "lib.h"


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
    void toHistory();
    static void goExit();
    void goToMain();
    void toSettings();
    void toModel();
    void goToPonds();
    void goToTable();
    void next();
    void back();
    void drawFish();

 private:
     int ind_, col_;
     Window* now_;
     Window* main_;
     Window* start_;
     Window* history_;
     Window* settings_;
     Window* house_;
     Window* table_;
     Window* pond_;
     std::vector<std::string> fishes_;
    QTimer* timer_;


};
