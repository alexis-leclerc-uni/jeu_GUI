#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QObject>
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
#include <QPointer>

#include "ui/gamewindow.h"
#include "ui/threadSignal.h"

#include "external_libs/concurrent_queue.hpp"
using lime62::concurrent_queue;

class MenuWindow : public QWidget
{
	Q_OBJECT

public:
	MenuWindow(QWidget* parent = nullptr);
	virtual ~MenuWindow();


public slots:
	void receiveStartGameJeu();
	void receiveMode(std::string resultat);
	void receiveTailleX(int resultat);
	void receiveTailleY(int resultat);
	

private slots:
	void startGame(QString gamemode);

signals:
	void sendStartGame(int numRows, int numCols, QString gameMode);

private:
	QString gameMode;
	int numRows;
	int numCols;

protected:
	void keyPressEvent(QKeyEvent* event) override;


};

#endif
