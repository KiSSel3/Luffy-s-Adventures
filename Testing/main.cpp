#include "application.h"

#include <QDebug>

int main(int argc, char* argv[]) try {
    Application app(argv[0]);
    app.start();

    return 0;
}
catch (int error) {
    switch (error) {
    case 1:
        qDebug()<< "Ошибка открытия файла с персонажем"; break;
    }
}
