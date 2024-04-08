#include "gamewindow.h"

GameWindow::GameWindow(QWidget* parent, QString gameMode, int boardRows, int boardCols, int buttonSize)
{
    this->buttonSize = buttonSize;

    this->setWindowTitle("Jeu en mode " + gameMode);

    int spacing = 0; // Adjust as needed

    // Create a container widget
    QWidget* gridWidget = new QWidget(this);
    this->gridWidget = gridWidget;
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
                debugMessage(row, col);
                });
        }
    }

    this->show();
    this->setFocus();
    this->boardCols = boardCols;
    this->boardRows = boardRows;
}

GameWindow::~GameWindow() {
}

void GameWindow::debugMessage(int row, int col) {
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

    QPoint buttonPos = clickedButton->mapTo(this->gridWidget, QPoint(0, 0));

    QPushButton* newButton = new QPushButton(this->gridWidget);
    newButton->setFixedSize(buttonSize, buttonSize);
    newButton->move(buttonPos);
    newButton->setObjectName("crosshair");
	newButton->setStyleSheet("border-image: url(sprites/Red_marker); border: none;");
    newButton->show();
}

void GameWindow::changeCoords(int x, int y) {
    if (this->currentPos[0] == -1) {
        this->currentPos[0] = 0;
        this->currentPos[1] = 0;
    }
    // conditions pour pas se rendre dans le vide
    else if((this->currentPos[0] + x >= 0) 
		 && (this->currentPos[1] + y >= 0)
		 && (this->currentPos[0] + x < boardCols) 
		 && (this->currentPos[1] + y < boardRows)) {
        this->currentPos[0] += x;
        this->currentPos[1] += y;
    }
    debugMessage(this->currentPos[1], this->currentPos[0]);
}

void GameWindow::spawnBoat(int y, int x, bool orientation, int size) {
    qDebug() << "spawnin boat";
    if (size == 3) {
        for (int i = 0; i < 3; i++)
        {
		QPushButton* clickedButton = findChild<QPushButton*>(QString("btn_%1_%2").arg(y).arg(x));
			QPoint buttonPos = clickedButton->mapTo(this->gridWidget, QPoint(0, 0));
			QPushButton* newButton = new QPushButton(this->gridWidget);
            int newX = buttonPos.x() + i*buttonSize;
            buttonPos.setX(newX);

			newButton->setFixedSize(buttonSize, buttonSize);
			newButton->move(buttonPos);
			newButton->setObjectName("boatpart");
			newButton->setStyleSheet(QString("border-image: url(sprites/boats/Cuiser/Cruiser%1); border: none;").arg(i+1));
			newButton->show();


        }
    }

}



void GameWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_Escape:
        // Exit the application if the Escape key is pressed
        QCoreApplication::quit();
        break;
    case Qt::Key_Down:
        changeCoords(0, 1);
        break;
    case Qt::Key_Up:
        changeCoords(0, -1);
        break;
    case Qt::Key_Left:
        changeCoords(-1, 0);
        break;
    case Qt::Key_Right:
        changeCoords(1, 0);
        break;
    case Qt::Key_3:
        spawnBoat(this->currentPos[1], this->currentPos[0], 0, 3);
    default:
        // Call the base class implementation for other key events
        QWidget::keyPressEvent(event);
        break;
    }
}

