#include "BeaconEditorTab.h"

BeaconEditorTab::BeaconEditorTab(QString titleTgt, QWidget *parent) : QWidget(parent)
{
    _setup();
    title=titleTgt;
}
BeaconEditorTab::BeaconEditorTab(int cnt, QWidget *parent) : QWidget(parent)
{
    _setup();
    title=QString(tr("Untitled")).append(" ").append(QString::number(cnt));
}
void BeaconEditorTab::_setup(){
    layout = new QGridLayout(this);
    editor = new QsciScintilla(this);
    //Lexer
    textLexer = new QsciLexerCPP(this);
    editor->setLexer(textLexer);
    //Margin Line Number
    editor->setMarginType(0,QsciScintilla::NumberMargin);
    editor->setMarginLineNumbers(0,true);
    editor->setMarginWidth(0,30);
    //Margin Breakpoint
    editor->setMarginType(1,QsciScintilla::SymbolMargin);
    editor->setMarginWidth(1,10);
    editor->setMarginSensitivity(1,true);
    editor->setMarginMarkerMask(1, 0x02);
    editor->markerDefine(QsciScintilla::Circle, 1);
    editor->setMarkerBackgroundColor(QColor("#ee1111"), 1);
    //Margin Step in
    editor->setMarginType(2, QsciScintilla::SymbolMargin);
    editor->setMarginLineNumbers(2, false);
    editor->setMarginWidth(2, 10);
    editor->setMarginSensitivity(2, false);
    editor->setMarginMarkerMask(2, 0x04);
    editor->markerDefine(QsciScintilla::RightArrow, 2);
    editor->setMarkerBackgroundColor(QColor("#eaf593"), 2);
    //Margin Folder
    editor->setMarginType(3, QsciScintilla::SymbolMargin);
    editor->setMarginLineNumbers(3, false);
    editor->setMarginWidth(3, 10);
    editor->setMarginSensitivity(3, true);
    //Auto Completion-API
    apis = new QsciAPIs(textLexer);
    apis->load(":/Resources/Qsci/Apis/cpp.api");
    apis->prepare();
    editor->setAutoCompletionSource(QsciScintilla::AcsAll);
    editor->setAutoCompletionCaseSensitivity(true);
    editor->setAutoCompletionThreshold(2);
    //others
    editor->setUnmatchedBraceForegroundColor(Qt::blue);
    editor->setIndentationGuides(true);
    editor->setMarginsBackgroundColor(Qt::lightGray);
    editor->setCaretLineVisible(true);
    editor->setCaretLineBackgroundColor(Qt::lightGray);
    editor->setAutoIndent(true);
    editor->SendScintilla(QsciScintilla::SCI_SETCODEPAGE,QsciScintilla::SC_CP_UTF8);

    layout->addWidget(editor);
    this->setLayout(layout);
}
void BeaconEditorTab::setupInfo(QString targetFile){
    this->info.setProperty(targetFile);
    this->title=info.fileName;
}
void BeaconEditorTab::setupInfo(BeaconEditorInfo &targetFile){
    this->info.setProperty(targetFile);
    this->title=info.fileName;
}
