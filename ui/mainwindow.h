#ifndef MAINWINDOW
#define MAINWINDOW

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <QKeyEvent>
#include <QListWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QLabel>
#include <QGridLayout>

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(std::string texteTitre, QWidget* parent = nullptr);
	MainWindow(QWidget* parent = nullptr);
	virtual ~MainWindow();
	void changeSize(int size);

public slots:
	void receiveStart(std::string texteTitre);
	void receiveEnd();
	void receiveChangeSize(int size);

signals:

protected:
	void keyPressEvent(QKeyEvent* event) override;

};

#endif
