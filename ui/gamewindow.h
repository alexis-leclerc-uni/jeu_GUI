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
	GameWindow(QWidget* parent = nullptr, QString gameMode = "", int row = 5, int col = 5);
	virtual ~GameWindow();

private:
	int buttonSize = 200;
	int boardRows = 5;
	int boardCols = 5;

protected:
	void debugMessage(int row, int col, QWidget* gridWidget);
	void keyPressEvent(QKeyEvent* event) override;


};

#endif
