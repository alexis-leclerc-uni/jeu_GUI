#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

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

#include "ui/threadSignal.h"


class GameWindow : public QWidget
{
	Q_OBJECT
		
public:
	GameWindow(QWidget* parent = nullptr);
	GameWindow(QWidget* parent, QString gamemode, int numRows, int numCols, int TailleButton);
	virtual ~GameWindow();

public slots:
	void receiveStartGame(int numRows, int numCols, QString gameMode);
	void ChangeCoordsSlot(std::string s);
	void receiveTailleBateau(int resultat);
	void receivePlaceBateau();
	void receiveRotateBateau();
	void receiveJoueur1Fini();
	void receiveJoueur2Fini();
	void receiveJoueur(std::string resultat);
	void receiveCarte(std::string resultat);
	void receiveElevation(int resultat);
	void receiveElevationConfirmation();
	void receiveAngle(int resultat);
	void receiveAngleConfirmation();
	void receivePuissance(int resultat);
	void receivePuissanceConfirmation();
	

private:
	int buttonSize = 60;
	int boardRows = 5;
	int boardCols = 5;
	int mode = 0;
	int tailleBateau = -1;

	bool joueur1Joue = true;
	bool elevationConfirmation = false;
	bool angleConfirmation = false;
	bool puissanceConfirmation = false;

	int elevation = 0;
	int angle = 0;
	int puissance = 0;

	int currentPos[2] = {-1, -1};
    QWidget* gridWidget;
	bool rotationMode = false;

protected:
	void genCrosshair(int row, int col);
	void keyPressEvent(QKeyEvent* event) override;
	void changeCoords(int x, int y);
	void spawnBoat(int x, int y, bool orientation, int size);
	void resetCrosshair(bool clear);
	bool allBoatsPlaced();
	void changeGamemode(int mode);
	bool checkIfHit(int x, int y);
	void removeBoats();

	void changeElevation(int elevation);
	void changePuissance(int puissance);
	void changeAngle(int angle);
	void changeContent(int x, int y, int state);


};

#endif
