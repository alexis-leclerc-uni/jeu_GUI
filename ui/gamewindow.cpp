#include "gamewindow.h"

GameWindow::GameWindow(QWidget* parent, QString gameMode)
{
	this->setWindowTitle("Jeu en mode " + gameMode);

	this->show();
}

GameWindow::~GameWindow() {
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

