//
// Created by ASUS on 07.10.2024.
//

#include "Label.h"

Label::Label (QWidget *parent): QLabel(parent) {

}

void Label::mousePressEvent(QMouseEvent *event) {
    emit mousePressedSignal();
    QLabel::mousePressEvent(event);
}