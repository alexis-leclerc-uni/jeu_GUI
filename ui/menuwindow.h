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
	MenuWindow(QWidget* parent = nullptr);
	virtual ~MenuWindow();

private slots:
	void startGame(QString gameMode);
	int calculTaille(int numRows, int numColumns);
	
protected:
	void keyPressEvent(QKeyEvent* event) override;
	int x;
	int y;
	int taille;

};

#endif
