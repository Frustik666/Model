#include "Window.h"

Window::Window(): QMainWindow() {}

Window::Window(int length, int height) {
    setMinimumSize(length, height);
    setMaximumSize(length, height);
}

Window::~Window() = default;

void Window::mousePressEvent(QMouseEvent *event) {
    std::cout << event->pos().rx() << ' ' << event->pos().ry() << '\n';
}
