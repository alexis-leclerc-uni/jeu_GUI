#include "menuwindow.h"

MenuWindow::MenuWindow(QWidget* parent)
{
	this->setWindowTitle("Menu du jeu");

	//Modes : normal, rafale, stratégique

	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	// Create a QWidget to hold the grid layout
	QWidget* gridWidget = new QWidget(this);

	// Create the grid layout
	QGridLayout* layout = new QGridLayout(gridWidget);
	gridWidget->setStyleSheet("QPushButton{border-image: url(sprites/menu/bar.png)};"); //pour changer l'image des boutons

	// Set margins for the grid widget
	gridWidget->setContentsMargins(15, 15, 15, 15);

	QFont comics("Comic Sans MS", 16, QFont::Bold);
	comics.setPointSizeF(20);

	QPixmap image("sprites/menu/title.png");

	QPixmap resizedImage = image.scaled(200, 200, Qt::KeepAspectRatio);

	QLabel* lblTitre = new QLabel(gridWidget);
	lblTitre->setAlignment(Qt::AlignCenter);
	lblTitre->setText("Choisir le mode de jeu!!!!!!");
	lblTitre->setFont(comics);

	QLabel* lblImage = new QLabel(gridWidget);
	lblImage->setAlignment(Qt::AlignCenter);
	lblImage->setPixmap(resizedImage);

	QStringList fontFamilies = QFontDatabase::families();

	comics.setPointSizeF(16);

	QPushButton* btnNormal = new QPushButton(gridWidget);
	btnNormal->setText("Normal");
	btnNormal->setObjectName("btnNormal");
	btnNormal->setFont(comics);
	btnNormal->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	btnNormal->setFixedHeight(60);

	QPushButton* btnRafale = new QPushButton(gridWidget);
	btnRafale->setText("Rafale");
	btnRafale->setFont(comics);
	btnRafale->setFixedHeight(60);
	btnRafale->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	QPushButton* btnStrategique = new QPushButton(gridWidget);
	btnStrategique->setText("Stratégique");
	btnStrategique->setFont(comics);
	btnStrategique->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	btnStrategique->setFixedHeight(60);

	layout->addWidget(lblImage, 0, 0, 1, 3);
	layout->addWidget(lblTitre, 1, 0, 1, 3);
	layout->addWidget(btnNormal, 2, 0, 2, 3);
	layout->addWidget(btnRafale, 4, 0, 4, 3);
	layout->addWidget(btnStrategique, 8, 0, 8, 3);

	connect(btnNormal, &QPushButton::clicked, this, [this]() {startGame("Normal"); });
	connect(btnRafale, &QPushButton::clicked, this, [this]() {startGame("Rafale"); });
	connect(btnStrategique, &QPushButton::clicked, this, [this]() {startGame("Strategique"); });

	//ohhhh oui
	// latulippe y'est quand meme beau

	mainLayout->addWidget(gridWidget);

	this->show();
}

MenuWindow::~MenuWindow() {
}

void MenuWindow::startGame(QString gameMode) {
	bool ok;
	int numRows = QInputDialog::getInt(this, tr("Nombre de lignes"), tr("Entrez le nombre de lignes:"), 10, 5, 15, 1, &ok);
	if (!ok)
		return; 

	int numColumns = QInputDialog::getInt(this, tr("Nombre de colonnes"), tr("Entrez le nombre de colonnes:"), 10, 5, 10, 1, &ok);
	if (!ok)
		return; 

	QWidget* gameWindow = new GameWindow(this, gameMode, numRows, numColumns, 100);
	this->close();
}

QWidget* MenuWindow::startGameJeu(QString gameMode, int numRows, int numColumns) {
	bool ok;
	/*
	int numRows = QInputDialog::getInt(this, tr("Nombre de lignes"), tr("Entrez le nombre de lignes:"), 10, 5, 15, 1, &ok);
	if (!ok)
		return;

	int numColumns = QInputDialog::getInt(this, tr("Nombre de colonnes"), tr("Entrez le nombre de colonnes:"), 10, 5, 10, 1, &ok);
	if (!ok)
		return;
	*/
	QWidget* gameWindow = new GameWindow(this, gameMode, numRows, numColumns, 100);
	this->close();
	return gameWindow;
}

void MenuWindow::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Escape) {
		// Exit the application if the Escape key is pressed
		QCoreApplication::quit();
	}
	else {
		// Call the base class implementation for other key events
		QWidget::keyPressEvent(event);
	}
}

