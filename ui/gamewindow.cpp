#include "gamewindow.h"

GameWindow::GameWindow(QWidget* parent, QString gameMode, int boardRows, int boardCols, int buttonSize)
{
    this->buttonSize = buttonSize;

    this->setWindowTitle("Jeu en mode " + gameMode);

    int spacing = 0; // Adjust as needed

    // Create a container widget
    QWidget* gridWidget = new QWidget(this);
    gridWidget->setObjectName("gridWidget");
    gridWidget->setStyleSheet("QWidget#gridWidget { background-color: white; }");

    // Calculate the total width and height needed for the buttons and spacing
    int totalWidth = boardCols * (buttonSize + spacing) - spacing;
    int totalHeight = boardRows * (buttonSize + spacing) - spacing;

    // Set the size of the container widget
    gridWidget->setFixedSize(totalWidth, totalHeight);

    // Create buttons and position them manually
    for (int row = 0; row < boardRows; ++row) {
        for (int col = 0; col < boardCols; ++col) {
            QPushButton* button = new QPushButton(gridWidget);
            button->setFixedSize(buttonSize, buttonSize);
            button->setObjectName(QString("btn_%1_%2").arg(row).arg(col));
            button->setGeometry(col * (this->buttonSize + spacing), row * (this->buttonSize + spacing), this->buttonSize, this->buttonSize);
            button->setStyleSheet("border-image: url(sprites/water/tile.png); color: blue; border: none;");
            connect(button, &QPushButton::clicked, this, [row, col, this, gridWidget]() {
                debugMessage(row, col, gridWidget);
                });
        }
    }
    this->move(0, 0);
    this->show();
}

GameWindow::~GameWindow() {
}

void GameWindow::debugMessage(int row, int col, QWidget* gridWidget) {
    int pixX = this->buttonSize * row + (this->buttonSize / 2);
    int pixY = this->buttonSize * col + (this->buttonSize / 2);

    int buttonX = 0;
    int buttonY = 0;


    QPushButton* clickedButton = findChild<QPushButton*>(QString("btn_%1_%2").arg(row).arg(col));
    if (!clickedButton) {
        qDebug() << "pas bouton";
        return;
    }
    QPushButton* crosshairButton = findChild<QPushButton*>(QString("crosshair").arg(row).arg(col));
    if (crosshairButton) {
        crosshairButton->deleteLater();
    }

    QPoint buttonPos = clickedButton->mapTo(gridWidget, QPoint(0, 0));

    QPushButton* newButton = new QPushButton(gridWidget);
    newButton->setFixedSize(buttonSize, buttonSize);
    newButton->move(buttonPos);
    newButton->setObjectName("crosshair");
	newButton->setStyleSheet("border-image: url(sprites/Red_marker); border: none;");
    newButton->show();
}



void GameWindow::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Escape) {
		// Exit the application if the Escape key is pressed
		QCoreApplication::quit();
	}
	else {
		// Call the base class implementation for other key events
		QWidget::keyPressEvent(event);
	}
}

