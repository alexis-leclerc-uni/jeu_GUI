#include "gamewindow.h"

GameWindow::GameWindow(QWidget* parent, QString gameMode, int boardRows, int boardCols, int buttonSize)
{

/*
    explication gab:

        4 cases
			Nuage quand on sait pas
            Eau : quand y'a rien
            Bateau : quand on sait qui en a un    (a cause sonde fucked up)
            Bateau detruit : quand C'est detruit

    TODO:: regler les multiples problemes de coordonnees


*/

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
                genCrosshair(row, col);
                });
        }
    }

    QVBoxLayout* mainLayout = new QVBoxLayout(this); 
    mainLayout->addWidget(gridWidget);

    QLabel* lblElevation = new QLabel(this);
    lblElevation->setObjectName("lblElevation");
    lblElevation->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lblElevation->setFixedHeight(50); 
    lblElevation->setStyleSheet("font-size: 30px;");

    mainLayout->addWidget(lblElevation);

    QLabel* lblAngle = new QLabel(this);
    lblAngle->setObjectName("lblAngle");
    lblAngle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lblAngle->setFixedHeight(50); 
    lblAngle->setStyleSheet("font-size: 30px;");

    mainLayout->addWidget(lblAngle);

    QLabel* lblPuissance = new QLabel(this);
    lblPuissance->setObjectName("lblPuissance");
    lblPuissance->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lblPuissance->setFixedHeight(50); 
    lblPuissance->setStyleSheet("font-size: 30px;");

    mainLayout->addWidget(lblPuissance);

    this->setLayout(mainLayout);

    mainLayout->setContentsMargins(0, 0, 0, 0);

    this->show();
    this->setFocus();
    this->boardCols = boardCols;
    this->boardRows = boardRows;

}

GameWindow::~GameWindow() {
}

void GameWindow::changeElevation(int elevation) {
    QLabel* lblElev = findChild<QLabel*>("lblElevation");
    lblElev->setText(QString("Élevation : %1").arg(elevation));
}

void GameWindow::changeAngle(int angle) {
    QLabel* lblAngle = findChild<QLabel*>("lblAngle");
    lblAngle->setText(QString("Angle : %1").arg(angle));
}

void GameWindow::changePuissance(int puissance) {
    QLabel* lblPuissance = findChild<QLabel*>("lblPuissance");
    lblPuissance->setText(QString("Puissance : %1").arg(puissance));
}

void GameWindow::removeBoats() {
    QRegularExpression exp(".*boat_.*");
    QList<QPushButton*> boatsFound = findChildren<QPushButton*>(exp);
    for (int i = 0; i < boatsFound.length(); i++)
    {
        QPushButton* button = boatsFound[i];
        button->parentWidget()->layout()->removeWidget(button);
        button->deleteLater();
    }
}

void GameWindow::genCrosshair(int row, int col) {
    int pixX = this->buttonSize * row + (this->buttonSize / 2);
    int pixY = this->buttonSize * col + (this->buttonSize / 2);

    int buttonX = 0;
    int buttonY = 0;

    QPushButton* clickedButton = findChild<QPushButton*>(QString("btn_%1_%2").arg(row).arg(col));
    if (!clickedButton) {
        qDebug() << "pas bouton";
        return;
    }
    resetCrosshair(false);

    QPoint buttonPos = clickedButton->mapTo(this->gridWidget, QPoint(0, 0));

    QPushButton* newButton = new QPushButton(this->gridWidget);
    newButton->setFixedSize(buttonSize, buttonSize);
    newButton->move(buttonPos);
    newButton->setObjectName("crosshair");
    QString markerColor;
    if (rotationMode) {
        markerColor = "Blue";
    }
    else {
        markerColor = "Red";
    }
	newButton->setStyleSheet(QString("border-image: url(sprites/%1_marker); border: none;").arg(markerColor));
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
    genCrosshair(this->currentPos[1], this->currentPos[0]);
}

void GameWindow::spawnBoat(int x, int y, bool orientation, int size) {
    QString boatType;
    qDebug() << "spawnin boat";


    switch (size)
    {
		case(2):
			boatType = QString("Destroyer");
			break;
		case(3):
			boatType = QString("Cruiser");
			break;
		case(4):
			boatType = QString("Battleship");
			break;
		case(5):
			boatType = QString("Carrier");
			break;
		default:
			break;
    }

	QRegularExpression exp(QString(".*%1.*").arg(boatType));
	QList<QPushButton*> buttonsFound = findChildren<QPushButton*>(exp);
    if (!buttonsFound.isEmpty()) {
        if (boatType == "Cruiser") {
            boatType = "Submarine";
			QRegularExpression exp(QString(".*%1.*").arg(boatType));
			QList<QPushButton*> buttonsFound = findChildren<QPushButton*>(exp);
            if (!buttonsFound.isEmpty()) {
				QMessageBox::warning(this, "Attention", QString("Le %1 a déjà été placé").arg(boatType));
				return;
            }
        }
        else {
            QMessageBox::warning(this, "Attention", QString("Le %1 a déjà été placé").arg(boatType));
            return;
        }
    }


	QPushButton* clickedButton = findChild<QPushButton*>(QString("btn_%1_%2").arg(y).arg(x));
	if (!clickedButton) {
		qDebug() << "bouton non trouvé";
		return;
	}
	for (int i = 0; i < size; i++)
	{
        if (!gridWidget)
        {
            qDebug() << "widget pas bin bon";
            return;
        }
		QPoint buttonPos = clickedButton->mapTo(this->gridWidget, QPoint(0, 0));
		QPushButton* newButton = new QPushButton(this->gridWidget);

        int newX;
        int newY;
        QString rotation;
        if (orientation) {
			int newX = buttonPos.x() + i*buttonSize;
			buttonPos.setX(newX);
            int newY = buttonPos.y();
            rotation = "_rotated";

        }
        else {
			int newY = buttonPos.y() + i*buttonSize;
			buttonPos.setY(newY);
            int newX = buttonPos.x();
        }

		newButton->setFixedSize(buttonSize, buttonSize);
		newButton->move(buttonPos);
		newButton->setObjectName(QString("%1_boat_%2_%3").arg(boatType).arg(buttonPos.x()/100).arg(buttonPos.y()/100));
		newButton->setStyleSheet(QString("border-image: url(sprites/boats/%1/%1_%2%3); border: none;").arg(boatType).arg(i + 1).arg(rotation));

		newButton->show();


	}
    resetCrosshair(true);

}

/// <summary>
/// if bool is true, then itll also reset the coords
/// </summary>
void GameWindow::resetCrosshair(bool clear) {
    QPushButton* crosshairButton = findChild<QPushButton*>(QString("crosshair"));
    if (crosshairButton) {
        crosshairButton->deleteLater();
    }
    if (clear) {
		this->currentPos[0] = -1;
		this->currentPos[1] = -1;
    }
}

bool GameWindow::allBoatsPlaced() {
	QRegularExpression exp(QString(".*_boat_.*"));
	QList<QPushButton*> boatsFound = findChildren<QPushButton*>(exp);
    return boatsFound.length() == 17;
    
}

bool GameWindow::checkIfHit(int x, int y) {
	QRegularExpression exp(QString(".*boat_%1_%2.*").arg(x).arg(y));
	QList<QPushButton*> boatsFound = findChildren<QPushButton*>(exp);
    return boatsFound.length() != 0;
}



void GameWindow::changeGamemode(int mode) {
    if (mode == 1) {
		QRegularExpression exp(QString(".*btn_.*"));
		QList<QPushButton*> backgroundFound = findChildren<QPushButton*>(exp);

        for (int i = 0; i < backgroundFound.length(); i++)
        {
            backgroundFound[i]->setStyleSheet("border-image: url(sprites/water/cloud.png); color: blue; border: none;");

        }
        
		QRegularExpression exp2(QString(".*_boat_.*"));
		QList<QPushButton*> boatsFound = findChildren<QPushButton*>(exp2);

        for (int i = 0; i < boatsFound.length(); i++)
        {
            boatsFound[i]->setVisible(false);

        }
    }
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
    if (mode == 0) {
        switch (event->key()) {
			case Qt::Key_2:
				spawnBoat(this->currentPos[0], this->currentPos[1], rotationMode, 2);
				break;
			case Qt::Key_3:
				spawnBoat(this->currentPos[0], this->currentPos[1], rotationMode, 3);
				break;
			case Qt::Key_4:
				spawnBoat(this->currentPos[0], this->currentPos[1], rotationMode, 4);
				break;
			case Qt::Key_5:
				spawnBoat(this->currentPos[0], this->currentPos[1], rotationMode, 5);
				break;
			case Qt::Key_Space:
				rotationMode = !rotationMode;
				//regens the crosshair to change its color
				changeCoords(0, 0);
				break;
            case Qt::Key_7:
                changeAngle(69);
                break;
            case Qt::Key_8:
                changePuissance(69);
                break;
            case Qt::Key_9:
                changeElevation(69);
				break;
			case Qt::Key_Return:
				if (allBoatsPlaced()) {
					//chepo
					QMessageBox::information(this, "Bateau", "Tout les bateaux ont été placés ");
					changeGamemode(1);
                    this->mode = 1;
				}
				else {
					QMessageBox::information(this, "Bateau", "Veuillez placer tout les bateaux avant de commencer la partie.");

				}
				break;
        }
    }
    else {
        switch (event->key()) {
        case Qt::Key_Return:
			if (checkIfHit(this->currentPos[0], this->currentPos[1])) {
				//chepo
				QMessageBox::information(this, "Bateau", "HIT!!!! ");
			}
			else {
				QMessageBox::information(this, "Bateau", "pas de hit");
			}
        }
    }

    switch (event->key()) {
    case Qt::Key_Escape:
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
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

