#include "mainwindow.h"

MainWindow::MainWindow(std::string texteTitre, QWidget* parent)
{
	this->setWindowTitle(QString::fromStdString(texteTitre));


	QHBoxLayout* layout = new QHBoxLayout(this);

	QLabel* labelLeftArrow = new QLabel(this);
	labelLeftArrow->setText("←");

	QLabel* labelRightArrow = new QLabel(this);
	labelRightArrow->setText("  →");

	QLabel* labelMiddle = new QLabel(this);
	labelMiddle->setText("Taille");
	labelMiddle->setObjectName("labelMiddle");

	layout->setSpacing(0);
	layout->addWidget(labelLeftArrow);
	layout->addWidget(labelMiddle);
	layout->addWidget(labelRightArrow);
	this->setStyleSheet("QLabel{font-size: 20px}");

	this->show();
}

MainWindow::~MainWindow() {
}


void MainWindow::changeSize(int size) {
	QLabel* label = findChild<QLabel*>(QString("labelMiddle"));

	label->setText(QString("%1").arg(size));


}

void MainWindow::receiveChaneSize(int size) {
	changeSize(size);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Escape) {
		// Exit the application if the Escape key is pressed
		QCoreApplication::quit();
	}
	else {
		// Call the base class implementation for other key events
		QWidget::keyPressEvent(event);
	}
}

void MainWindow::receiveStart(std::string texteTitre) {

	this->setWindowTitle(QString::fromStdString(texteTitre));


	QHBoxLayout* layout = new QHBoxLayout(this);

	QLabel* labelLeftArrow = new QLabel(this);
	labelLeftArrow->setText("←");

	QLabel* labelRightArrow = new QLabel(this);
	labelRightArrow->setText("  →");

	QLabel* labelMiddle = new QLabel(this);
	labelMiddle->setText("Taille");
	labelMiddle->setObjectName("labelMiddle");

	layout->setSpacing(0);
	layout->addWidget(labelLeftArrow);
	layout->addWidget(labelMiddle);
	layout->addWidget(labelRightArrow);
	this->setStyleSheet("QLabel{font-size: 20px}");

	this->show();
}

void MainWindow::receiveEnd() {
	this->close();
}
