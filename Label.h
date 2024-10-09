#pragma once
#include "lib.h"

class Label: public QLabel {
    Q_OBJECT

public:
    Label(QWidget* parent = nullptr);

    void mousePressEvent(QMouseEvent *event);

    signals:
    void mousePressedSignal();


};
