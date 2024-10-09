#include "Screen.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Screen scr(1000, 700);
    scr.render();
    return QApplication::exec();
}
