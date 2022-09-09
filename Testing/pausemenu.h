#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "styleformenu.h"

#include <QMainWindow>
#include <QPainter>
#include <QStyleOption>
#include <QAction>
#include <QLabel>
#include <QMessageBox>

namespace Ui {
  class PauseMenu;
}

class PauseMenu : public QMainWindow
{
  Q_OBJECT

public:
  explicit PauseMenu(std::string FilePath);
  ~PauseMenu();

  void setStyle();
  bool stopGame();

protected:
  void paintEvent(QPaintEvent *event);

private slots:
  void on_ExitButton_clicked();
  void on_LanguageButton_clicked();
  void onScreenModeTriggered();

  void on_ContinueButton_clicked();

private:
  Ui::PauseMenu *ui;
  enum LanguageEnum {RUS, EN};
  LanguageEnum language;

  QAction* actionScreenMode;

  bool exitButtonPressed;

  std::string filePath;

};

#endif // PAUSEMENU_H
