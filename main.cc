//
// Created by Steve Atkins on 27/08/2024.
//
#include <QApplication>
#include <QPushButton>
#include <QWebEngineView>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QWebEngineView button(nullptr);
    button.setHtml("<p>Hello World");
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
