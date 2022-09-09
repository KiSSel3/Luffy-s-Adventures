#include "styleformenu.h"

QString StyleForMenu::WidgetStyle(std::string FilePath) {
    return "QWidget {"
           "   background-image: url(" + QString::fromStdString(FilePath) + "images/forMenu/Background.jpg)"
           "}";
}

QString StyleForMenu::ButtonsStyle() {
    return "QPushButton{"
           "   color:#fff;"
           "   background: none;"
            "   border: none;"
            "   border-radius:50px;"
            "}"
            " "
            "QPushButton:pressed {"
            "   color:#fff;"
            "   border-style: outset;"
            "   font: bold 100px;"
            "   min-width: 10em;"
            "   padding: 6px;"
            "}";
}

QString StyleForMenu::LabelStyle() {
    return  "QLabel{"
            "   color:#fff;"
            "   background: none;"
            "   border: none;"
            "}";
}

QString StyleForMenu::LanguageButtonStyle() {
    return "QPushButton{"
           "   color:#fff;"
           "   background: none;"
            "   border: none;"
            "   border-radius:50px;"
            "}"
            " "
            "QPushButton:pressed {"
            "   color:#fff;"
            "   border-style: outset;"
            "   font: bold 14px;"
            "   min-width: 10em;"
            "   padding: 6px;"
            "}";
}
