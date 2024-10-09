#pragma once
#include "lib.h"
class Window: public QMainWindow {

Q_OBJECT

public:
    Window(int length, int height);
    Window();
    ~Window() override;
    void mousePressEvent(QMouseEvent *event) override;
    QWidget* getWidget(QWidget*, const std::string& name) {

    }

    void addItem(const std::string& name, QWidget* item) {
        widgets_.insert({name, item});
    }

    QWidget* getItem(const std::string& name) {
        return widgets_[name];
    }

private:
    std::map<std::string, QWidget*> widgets_;
};
