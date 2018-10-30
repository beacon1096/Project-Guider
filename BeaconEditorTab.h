#ifndef BEACONEDITORTAB_H
#define BEACONEDITORTAB_H

#include <QWidget>
#include <QGridLayout>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qsciapis.h>
#include "BeaconEditorInfo.h"

class BeaconEditorTab : public QWidget
{
    Q_OBJECT
public:
    BeaconEditorInfo info;
    QsciScintilla *editor = nullptr;
    QsciLexerCPP *textLexer = nullptr;
    QsciAPIs *apis = nullptr;
    QGridLayout *layout = nullptr;
    QString title;
    explicit BeaconEditorTab(int cnt=0,QWidget *parent = nullptr);
    explicit BeaconEditorTab(QString titleTgt,QWidget *parent = nullptr);
    void setupInfo(QString targetFile);
    void setupInfo(BeaconEditorInfo &targetFile);

signals:

public slots:
private:
    void _setup();
};

#endif // BEACONEDITORTAB_H
