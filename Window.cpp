#include "Window.h"

Window::Window(): QMainWindow() {}

Window::Window(int length, int height) {
    setMinimumSize(length, height);
    setMaximumSize(length, height);
}

Window::~Window() {
    for (auto& to : widgets_) {
        delete to.second;
    }
}

void Window::mousePressEvent(QMouseEvent *event) {
    std::cout << event->pos().rx() << ' ' << event->pos().ry() << '\n';
}
