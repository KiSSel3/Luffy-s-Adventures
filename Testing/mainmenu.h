#ifndef MAINMENU_H
#define MAINMENU_H

#include "application.h"
#include "styleformenu.h"

#include <QMainWindow>
#include <QPainter>
#include <QStyleOption>
#include <QAction>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QMainWindow {
    Q_OBJECT
public:
    MainMenu(std::string FilePath);
    ~MainMenu();

private slots:
    void on_ExitButton_clicked();
    void on_LanguageButton_clicked();
    void onScreenModeTriggered();
    void on_PlayButton_clicked();

private:
    enum LanguageEnum {RUS, EN} language;

    Ui::MainMenu* ui;
    QAction* actionScreenMode;

    Application* mainApplication;
    std::string filePath;


    void createApplication();
    void paintEvent(QPaintEvent *event);
    void setStyle();
};
#endif // MAINMENU_H
