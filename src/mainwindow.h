#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"


class Dictionary;


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
    void slotNew();
    void slotAbout();
    void slotSetMode(QAction*);

private:
    void setupActions();

    void readSettings();
    void writeSettings();

    Ui::MainWindow ui;
};


#endif
