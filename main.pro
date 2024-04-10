TEMPLATE = vcapp
TARGET = jeuGUI
QT += core gui widgets
CONFIG += console

SOURCES +=	ui/menuwindow.cpp \
			ui/gamewindow.cpp \
			main.cpp \
			manette/manette.cpp \
			lib_jeu/Bateau.cpp \
			lib_jeu/Carte.cpp \
			lib_jeu/Joueur.cpp \
			external_libs/serial/SerialPort.cpp \
			lib_jeu/jeu_App.cpp

HEADERS +=	ui/menuwindow.h \
			ui/gamewindow.h \
			manette/manette.h \
			lib_jeu/Bateau.h \
			lib_jeu/Carte.h \
			lib_jeu/Joueur.h \
			lib_jeu/Coordonnee.h \
			external_libs/nlohmann/json.hpp \
			external_libs/serial/SerialPort.hpp \
			external_libs/concurrent_queue.hpp \
			lib_jeu/jeu_App.h