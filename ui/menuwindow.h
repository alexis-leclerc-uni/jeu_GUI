#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QPixmap>
#include <QFontDatabase>
#include <QIcon>
#include <QLabel>
#include <QKeyEvent>
#include <QListWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QGridLayout>

#include "ui/gamewindow.h"


class MenuWindow : public QWidget
{
	Q_OBJECT

public:
	MenuWindow(Controller* c, QWidget* parent = nullptr);
	virtual ~MenuWindow();

public slots:
	void receiveStartGameJeu();
	void receiveMode(std::string resultat);
	void receiveTailleX(int resultat);
	void receiveTailleY(int resultat);
	

private slots:
	void startGame(QString gameMode);

private:
	Controller* controller;
	QString gameMode;
	int numRows;
	int numCols;

protected:
	void keyPressEvent(QKeyEvent* event) override;


};

#endif
