#include "application.h"
#include "mainmenu.h"

#include <QDebug>
#include <QApplication>

int main(int argc, char* argv[]) try {
    QApplication qApplication(argc, argv); // Для корректной работы форм

    MainMenu mainMenu(argv[0]);
    mainMenu.showFullScreen();

//    Application app(argv[0]);
//    app.startingMenu();

    return qApplication.exec(); // Для корректной работы форм
}
catch (int error) {
    switch (error) {
    case 1:
        qDebug()<< "Ошибка открытия файла с персонажем"; break;
    }
}
