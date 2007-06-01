#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"


class QStackedWidget;

class Dictionary;
class DictionaryWidget;


class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow();
	
signals:
	void activateDictionary(Dictionary*);
	
protected:
    void closeEvent(QCloseEvent*);

private slots:
	void slotAbout();
	
private:
	void setupActions();
	
	void readSettings();
	void writeSettings();
	
	Ui::MainWindow ui;

	QStackedWidget *centralWidget;
	
	DictionaryWidget *dictionaryWidget;
};


#endif
