#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Initialize GameManager
    gameManager = new GameManager(this);
    
    // Create the stacked widget to hold different views
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    
    // Create the main menu widget and add it to the stack
    QWidget* menuWidget = new QWidget();
    QVBoxLayout* menuLayout = new QVBoxLayout(menuWidget);
    
    // Add the main menu components to the layout
    menuLayout->addWidget(ui->titleLabel);
    menuLayout->addWidget(ui->line);
    menuLayout->addWidget(ui->label_3);
    
    // Create new layouts for map size and coins instead of reusing ui layouts
    QHBoxLayout* newMapSizeLayout = new QHBoxLayout();
    newMapSizeLayout->addWidget(ui->label_4);
    newMapSizeLayout->addWidget(ui->xmap);
    newMapSizeLayout->addWidget(ui->label_5);
    newMapSizeLayout->addWidget(ui->ymap);
    menuLayout->addLayout(newMapSizeLayout);
    
    QHBoxLayout* newCoinLayout = new QHBoxLayout();
    newCoinLayout->addWidget(ui->label_6);
    newCoinLayout->addWidget(ui->StartCoin);
    menuLayout->addLayout(newCoinLayout);
    
    menuLayout->addWidget(ui->pushButton);
    menuLayout->addWidget(ui->settingsButton);
    menuLayout->addWidget(ui->helpButton);
    menuLayout->addWidget(ui->exitButton);
    
    stackedWidget->addWidget(menuWidget);
    
    // Create the game view and add it to the stack
    gameView = new GameView(this);
    gameView->setGameManager(gameManager);
    stackedWidget->addWidget(gameView);
    
    // Connect the returnToMenu signal
    connect(gameView, &GameView::returnToMenu, this, &MainWindow::switchToMainMenu);
    
    // Start with the main menu
    stackedWidget->setCurrentIndex(0);
    
    // Connect GameManager signals
    connect(gameManager, &GameManager::gameStarted, this, &MainWindow::switchToGameView);

    // Connect new buttons
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::showSettings);
    connect(ui->helpButton, &QPushButton::clicked, this, &MainWindow::showHelp);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::exitGame);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameManager;
}

// Button to start the game
void MainWindow::on_pushButton_clicked()
{
    // Get values from UI elements
    int x = ui->xmap->value();
    int y = ui->ymap->value();
    QString coinText = ui->StartCoin->text();
    bool ok;
    int coins = coinText.toInt(&ok);

    if (!ok) {
        // Display an error message box
        QMessageBox::critical(this, "Input Error", "Invalid coin input! Please enter a valid number.");
        return; // Don't start the game
    }

    // Set values in GameManager
    gameManager->setMapSize(x, y);
    gameManager->setStartingCoins(coins);

    // Start the game
    gameManager->startGame();
    std::cout << "Game Started" << std::endl;
    
    // Switch to the game view (this will also happen via the signal connection)
    switchToGameView();
}

void MainWindow::switchToGameView()
{
    // Switch to the game view
    stackedWidget->setCurrentIndex(1);
    
    // Set focus to the game view
    gameView->setFocus();
}

void MainWindow::switchToMainMenu()
{
    // Reset game state
    if (gameManager) {
        gameManager->resetGame();
    }
    
    // Switch back to the main menu
    stackedWidget->setCurrentIndex(0);
}

// Show settings dialog
void MainWindow::showSettings()
{
    QMessageBox::information(this, "Settings", "Settings dialog not implemented yet.");
}

// Show help dialog
void MainWindow::showHelp()
{
    QMessageBox::information(this, "Help", "Help dialog not implemented yet.");
}

// Exit the game
void MainWindow::exitGame()
{
    close();
}

// Rest of the methods remain unchanged

// Starting coin amount
void MainWindow::on_StartCoin_textChanged(const QString &arg1)
{
    // No need to do anything here, the value is retrieved when the button is clicked
    std::cout << arg1.toStdString() << std::endl;
}

// Y value map size
void MainWindow::on_ymap_valueChanged(int arg1)
{
    // No need to do anything here, the value is retrieved when the button is clicked
}

// X value map size
void MainWindow::on_xmap_valueChanged(int arg1)
{
    // No need to do anything here, the value is retrieved when the button is clicked
}