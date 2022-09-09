#include "pausemenu.h"
#include "ui_pausemenu.h"

PauseMenu::PauseMenu(std::string FilePath) : QMainWindow(), ui(new Ui::PauseMenu), actionScreenMode(nullptr), exitButtonPressed(false) {
    ui->setupUi(this);

    filePath = FilePath;

    setStyle();

    actionScreenMode = new QAction(this);
    actionScreenMode->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));
    addAction(actionScreenMode);
    connect(actionScreenMode,SIGNAL(triggered()),this,SLOT(onScreenModeTriggered()));
}

PauseMenu::~PauseMenu() {
    delete ui;
}

void PauseMenu::setStyle() {
    setStyleSheet(StyleForMenu::WidgetStyle(filePath));
    ui->ExitButton->setStyleSheet(StyleForMenu::ButtonsStyle());
    ui->ContinueButton->setStyleSheet(StyleForMenu::ButtonsStyle());
    ui->LanguageButton->setStyleSheet(StyleForMenu::LanguageButtonStyle());
}

bool PauseMenu::stopGame() {
    return exitButtonPressed;
}

void PauseMenu::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
    QWidget::paintEvent(event);
}

void PauseMenu::on_ExitButton_clicked() {
    exitButtonPressed = true;
}

void PauseMenu::on_LanguageButton_clicked() {
    if (language == EN) {
        language = RUS;
        ui->LanguageButton->setText("RU");
        ui->ContinueButton->setText("ПРОДОЛЖИТЬ");
        ui->ExitButton->setText("ВЫЙТИ");
    }
    else {
        language = EN;
        ui->LanguageButton->setText("EN");
        ui->ContinueButton->setText("CONTINUE");
        ui->ExitButton->setText("EXIT");
    }
}

void PauseMenu::onScreenModeTriggered() {
    if (isFullScreen()){
        setWindowState(Qt::WindowNoState);//отключение
    }
    else {
        setWindowState(Qt::WindowFullScreen);//включение
    }
}

void PauseMenu::on_ContinueButton_clicked() {
    this->hide();
}
