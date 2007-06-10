#ifndef DICTIONARYWIDGET_H
#define DICTIONARYWIDGET_H

#include "ui_dictionarywidget.h"


class QSortFilterProxyModel;
class Dictionary;


class DictionaryWidget : public QWidget
{
    Q_OBJECT

public:
    DictionaryWidget();

signals:
    void statusBarMessage(QString, int);

public slots:
    void activateDictionary(Dictionary*);

private slots:
    void slotSearch();
    void slotFiltering(bool);
    void slotFilter();

private:
    Ui::DictionaryWidget ui;

    Dictionary *dict;
    QSortFilterProxyModel *filterModel;
};


#endif
