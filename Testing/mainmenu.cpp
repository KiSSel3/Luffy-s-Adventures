#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(std::string FilePath) : QMainWindow(), ui(new Ui::MainMenu), actionScreenMode(nullptr), mainApplication(nullptr) {
    ui->setupUi(this);

    FilePath.erase(FilePath.find("Testing.exe", 0));
    std::replace(FilePath.begin(), FilePath.end(),'\\','/');
    filePath = FilePath;

    setStyle();

    actionScreenMode = new QAction(this);
    actionScreenMode->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));
    addAction(actionScreenMode);
    connect(actionScreenMode,SIGNAL(triggered()),this,SLOT(onScreenModeTriggered()));
}

void MainMenu::setStyle() { //функция для добавления стилей
    setStyleSheet(StyleForMenu::WidgetStyle(filePath));
    ui->ExitButton->setStyleSheet(StyleForMenu::ButtonsStyle());
    ui->PlayButton->setStyleSheet(StyleForMenu::ButtonsStyle());
    ui->LevelButton->setStyleSheet(StyleForMenu::ButtonsStyle());
    ui->LanguageButton->setStyleSheet(StyleForMenu::LanguageButtonStyle());
    ui->NameOfGame->setStyleSheet(StyleForMenu::LabelStyle());
}

void MainMenu::paintEvent(QPaintEvent *event) { //используется для нормальной отрисовки фона (нашёл на просторах интернета, советуют делать так)
    QStyleOption styleOption;
    styleOption.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget,&styleOption,&painter,this);
    QWidget::paintEvent(event);
}

void MainMenu::on_ExitButton_clicked() { // завершение игры
    //...
    //Логика сохранения
    //...

    close();
}

void MainMenu::on_LanguageButton_clicked() { // замена языка
    if (language == EN) {
        language = RUS;
        ui->LanguageButton->setText("RU");
        ui->PlayButton->setText("ИГРАТЬ");
        ui->ExitButton->setText("ВЫЙТИ");
        ui->LevelButton->setText("УРОВЕНЬ");
    }
    else {
        language = EN;
        ui->LanguageButton->setText("EN");
        ui->PlayButton->setText("PLAY");
        ui->ExitButton->setText("EXIT");
        ui->LevelButton->setText("LEVEL");
    }
}

void MainMenu::onScreenModeTriggered() { //включение\отключение полноэкранного режима
    if (isFullScreen()){
        setWindowState(Qt::WindowNoState);//отключение
    }
    else {
        setWindowState(Qt::WindowFullScreen);//включение
    }
}

void MainMenu::on_PlayButton_clicked() {
    createApplication();

    this->hide(); // Скрывает меню

    mainApplication->startingGame();
    delete mainApplication;
    mainApplication = nullptr;

    this->showFullScreen(); // Показывает меню на весь экран
}

MainMenu::~MainMenu() {
    if(mainApplication != nullptr) {
        delete mainApplication;
    }

    if(actionScreenMode != nullptr) {
        delete actionScreenMode;
    }

    delete ui;
}

void MainMenu::on_LevelButton_clicked() {
    // На данный момент кнопка для тестов функций
}

void MainMenu::createApplication() {
//    if(mainApplication != nullptr) {
//        delete mainApplication;
//        mainApplication = nullptr;
//    }

    mainApplication = new Application(filePath);
}

