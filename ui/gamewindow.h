#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

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


class GameWindow : public QWidget
{
	Q_OBJECT

public:
	GameWindow(QWidget* parent = nullptr, QString gameMode = "");
	virtual ~GameWindow();

protected:
	void debugMessage(int row, int col);
	void keyPressEvent(QKeyEvent* event) override;


};

#endif
