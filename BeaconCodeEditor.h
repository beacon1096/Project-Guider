#ifndef BEACONCODEEDITOR_H
#define BEACONCODEEDITOR_H

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QPainter>
#include <QTextBlock>
#include <QPlainTextEdit>
#include <QObject>
#include "BeaconCodeSyntaxCpp.h"

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class BeaconCodeEditor;
class BeaconLineNumberArea;

class BeaconCodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    BeaconCodeEditor(QWidget *parent = nullptr);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    BeaconCodeSyntaxCpp *syntaxCpp = nullptr;

public slots:
    QString text();
    void setText(const QString &content);
protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};

class BeaconLineNumberArea : public QWidget
{
public:
    BeaconLineNumberArea(BeaconCodeEditor *editorTarget) : QWidget(editorTarget) {
        editor = editorTarget;
    }

    QSize sizeHint() const override {
        return QSize(editor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        editor->lineNumberAreaPaintEvent(event);
    }

private:
    BeaconCodeEditor *editor;
};
#endif // BEACONCODEEDITOR_H
