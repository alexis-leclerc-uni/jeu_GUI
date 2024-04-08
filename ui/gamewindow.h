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
	GameWindow(QWidget* parent = nullptr, QString gameMode = "", int row = 5, int col = 5, int buttonSize = 200);
	virtual ~GameWindow();

private:
	int buttonSize = 200;
	int boardRows = 5;
	int boardCols = 5;

	int currentPos[2] = {-1, -1};
    QWidget* gridWidget;

protected:
	void debugMessage(int row, int col);
	void keyPressEvent(QKeyEvent* event) override;
	void changeCoords(int x, int y);


};

#endif
