#include "gamewindow.h"

GameWindow::GameWindow(QWidget* parent, QString gameMode)
{
	this->setWindowTitle("Jeu en mode " + gameMode);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	QWidget* gridWidget = new QWidget(this);

	QGridLayout* layout = new QGridLayout(gridWidget);
	layout->setSpacing(0);
	layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

	int buttonSize = 200;

	// Create a grid of QPushButton items
	for (int row = 0; row < 5; ++row) {
		for (int col = 0; col < 5; ++col) {
			QPushButton* button = new QPushButton(QString("%1,%2").arg(row).arg(col), this);
			button->setFixedSize(buttonSize, buttonSize);
			button->setFixedSize(buttonSize, buttonSize);
			button->setContentsMargins(0, 0, 0, 0); // Set margins of the button to zero
			button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
			connect(button, &QPushButton::clicked, this, [row, col, this]() {
				debugMessage(row, col);
				// You can add your logic here to change the properties of the clicked button
				});
			layout->addWidget(button, row, col);
		}
	}

	mainLayout->addWidget(gridWidget);

	this->show();
}

GameWindow::~GameWindow() {
}

void GameWindow::debugMessage(int row, int col) {
	QMessageBox::information(this, "Message", "Button clicked on row " + QString::number(row) + " and col "  + QString::number(col));

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

