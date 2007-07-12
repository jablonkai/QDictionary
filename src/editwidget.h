#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include "ui_editwidget.h"


class QStandardItemModel;

class Dictionary;


class EditWidget : public QWidget
{
    Q_OBJECT

public:
    EditWidget();

public slots:
	void activateDictionary(Dictionary*);

private slots:
    void slotAdd();
    void slotReset();

private:
	void updateList();

	Ui::EditWidget ui;

    Dictionary *dict;

    QStandardItemModel *model;
};


#endif
