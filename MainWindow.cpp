#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString th = MainInfo::theme;
    compiler = new BeaconCompilerBackend;
    instance = new BeaconExternalProgram;
    connect(instance,SIGNAL(programExited(int,QProcess::ExitStatus)),this,SLOT(onInstanceExited()));
//default editor
    editor = new QsciScintilla(this);
    currentEditor = editor;
    textLexer = new QsciLexerCPP(this);
    editor->setLexer(textLexer);
    editor->setMarginType(0,QsciScintilla::NumberMargin);
    editor->setMarginLineNumbers(0,true);
    editor->setMarginWidth(0,35);
    this->ui->editorLayout->addWidget(editor);
//malicious initialization
    this->ui->editorTabWidget->setTabText(0,QString(tr("Untitled ")).append("1"));
    editorList.insert(QString(tr("Untitled ")).append("1"),editor);
    newFileCnt=1;
    fileList.append(BeaconCodeProperty(""));
    fileList.resize(100);
//QTextBrowser-Initialization
    //currentEditor=this->ui->editorTabWidget->findChildren<QTextBrowser*>("defaultBrowser").front();
    connect(currentEditor,SIGNAL(textChanged()),this,SLOT(codeChanged()));
//QTabWidget Initialization
    connect(this->ui->editorTabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabChanged(int)));
//QMenu Initialization
    menuFile=ui->topMenuBar->addMenu("&File");
    menuEdit=ui->topMenuBar->addMenu("&Edit");
    menuView=ui->topMenuBar->addMenu("&View");
    menuBuild=ui->topMenuBar->addMenu("&Build");
    menuDebug=ui->topMenuBar->addMenu("&Debug");
    menuLanguage=ui->topMenuBar->addMenu("&Language");
    menuHelp=ui->topMenuBar->addMenu("&Help");
    menuTest=ui->topMenuBar->addMenu("DEBUGGING");
//QMenu File-QAction Initialization
    actionFileNew = new QAction(tr("New"),this);
    actionFileNew->setShortcut(tr("Ctrl+N"));
    actionFileNew->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/document-new.svg").arg(th)));
    connect(this->actionFileNew,SIGNAL(triggered()),this,SLOT(triggeredNew()));
    menuFile->addAction(actionFileNew);
    actionFileOpen = new QAction(tr("Open"),this);
    actionFileOpen->setShortcut(tr("Ctrl+O"));
    actionFileOpen->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/document-open.svg").arg(th)));
    connect(this->actionFileOpen,SIGNAL(triggered()),this,SLOT(triggeredOpen()));
    menuFile->addAction(actionFileOpen);
    actionFileSave = new QAction(tr("Save"),this);
    actionFileSave->setShortcut(tr("Ctrl+S"));
    actionFileSave->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/document-save.svg").arg(th)));
    connect(this->actionFileSave,SIGNAL(triggered()),this,SLOT(triggeredSave()));
    menuFile->addAction(actionFileSave);
    actionFileSaveAs = new QAction(tr("Save As"),this);
    actionFileSaveAs->setShortcut(tr("Ctrl+Shift+S"));
    actionFileSaveAs->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/document-save-as.svg").arg(th)));
    connect(this->actionFileSaveAs,SIGNAL(triggered()),this,SLOT(triggeredSaveAs()));
    menuFile->addAction(actionFileSaveAs);

    menuFile->addSeparator();

    actionFileCloseFile = new QAction(tr("Close File"),this);
    //actionFileCloseFile->setShortcut(tr(""));
    actionFileCloseFile->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/document-close.svg").arg(th)));
    menuFile->addAction(actionFileCloseFile);
    actionFileCloseAll = new QAction(tr("Close All"),this);
    //actionFileCloseAll->setShortcut(tr(""));
    menuFile->addAction(actionFileCloseAll);
    actionFileCloseOthers = new QAction(tr("Close Others"),this);
    //actionFileCloseOthers->setShortcut(tr(""));
    menuFile->addAction(actionFileCloseOthers);

    menuFile->addSeparator();

    actionFileRecentFiles = new QAction(tr("Recent Files"),this);
    //actionFileRecentFiles->setShortcut(tr(""));
    actionFileRecentFiles->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/document-open-recent.svg").arg(th)));
    menuFile->addAction(actionFileRecentFiles);

    menuFile->addSeparator();

    actionExit = new QAction(tr("Exit"),this);
    actionExit->setShortcut(tr("Ctrl+Q"));
    actionExit->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/application-exit.svg").arg(th)));
    connect(this->actionExit,SIGNAL(triggered()),this,SLOT(triggeredExit()));
    menuFile->addAction(actionExit);

//QMenu File-QAction Initialization
    actionEditUndo = new QAction(tr("Undo"),this);
    actionEditUndo->setShortcut(tr("Ctrl+Z"));
    actionEditUndo->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/edit-undo.svg").arg(th)));
    connect(this->actionEditUndo,SIGNAL(triggered()),this,SLOT(triggeredUndo()));
    menuEdit->addAction(actionEditUndo);
    actionEditRedo = new QAction(tr("Redo"),this);
    actionEditRedo->setShortcut(tr("Ctrl+Y"));
    actionEditRedo->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/edit-redo.svg").arg(th)));
    connect(this->actionEditRedo,SIGNAL(triggered()),this,SLOT(triggeredRedo()));
    menuEdit->addAction(actionEditRedo);

    menuEdit->addSeparator();

    actionEditSelectAll = new QAction(tr("Select All"),this);
    actionEditSelectAll->setShortcut(tr("Ctrl+A"));
    menuEdit->addAction(actionEditSelectAll);
    connect(this->actionEditSelectAll,SIGNAL(triggered()),this,SLOT(triggeredSelectAll()));
    actionEditCopy = new QAction(tr("Copy"),this);
    actionEditCopy->setShortcut(tr("Ctrl+C"));
    actionEditCopy->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/edit-copy.svg").arg(th)));
    connect(this->actionEditCopy,SIGNAL(triggered()),this,SLOT(triggeredCopy()));
    menuEdit->addAction(actionEditCopy);
    actionEditCut = new QAction(tr("Cut"),this);
    actionEditCut->setShortcut(tr("Ctrl+X"));
    actionEditCut->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/edit-cut.svg").arg(th)));
    connect(this->actionEditCut,SIGNAL(triggered()),this,SLOT(triggeredCut()));
    menuEdit->addAction(actionEditCut);
    actionEditPaste = new QAction(tr("Paste"),this);
    actionEditPaste->setShortcut(tr("Ctrl+V"));
    actionEditPaste->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/edit-paste.svg").arg(th)));
    connect(this->actionEditPaste,SIGNAL(triggered()),this,SLOT(triggeredPaste()));
    menuEdit->addAction(actionEditPaste);

    menuEdit->addSeparator();

    actionEditSearch = new QAction(tr("Search"),this);
    actionEditSearch->setShortcut(tr("Ctrl+F"));
    actionEditSearch->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/edit-find.svg").arg(th)));
    menuEdit->addAction(actionEditSearch);
    actionEditReplace = new QAction(tr("Replace"),this);
    actionEditReplace->setShortcut(tr("Ctrl+R"));
    actionEditReplace->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/edit-find-replace.svg").arg(th)));
    menuEdit->addAction(actionEditReplace);
    actionEditNext = new QAction(tr("Next"),this);
    actionEditNext->setShortcut(tr("F3"));
    actionEditNext->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/go-bottom.svg").arg(th)));
    menuEdit->addAction(actionEditNext);
    actionEditPrevious = new QAction(tr("Previous"),this);
    actionEditPrevious->setShortcut(tr("Shift+F3"));
    actionEditPrevious->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/go-top.svg").arg(th)));
    menuEdit->addAction(actionEditPrevious);
    actionEditGoTo = new QAction(tr("Go To"),this);
    actionEditGoTo->setShortcut(tr("Ctrl+G"));
    actionEditGoTo->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/go-jump.svg").arg(th)));
    menuEdit->addAction(actionEditGoTo);
    actionEditGoToBrace = new QAction(tr("Go To Brace"),this);
    actionEditGoToBrace->setShortcut(tr("Ctrl+J"));
    menuEdit->addAction(actionEditGoToBrace);

    menuEdit->addSeparator();

    actionEditSettings = new QAction(tr("Settings"),this);
    //actionEditSettings->setShortcut(tr(""));
    actionEditSettings->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/configure-shortcuts.svg").arg(th)));
    menuEdit->addAction(actionEditSettings);

//QMenu View-QAction Initialization
    actionViewFileBrowser = new QAction(tr("File Browser"),this);
    //actionViewFileBrowser->setShortcut(tr(""));
    actionViewFileBrowser->setCheckable(true);
    actionViewFileBrowser->setChecked(true);
    menuView->addAction(actionViewFileBrowser);
    actionViewMessage = new QAction(tr("Message"),this);
    actionViewMessage->setCheckable(true);
    actionViewMessage->setChecked(true);
    //actionViewMessage->setShortcut(tr(""));
    menuView->addAction(actionViewMessage);

//QMenu Build-QAction Initialization
    actionBuildCompile = new QAction(tr("Compile"),this);
    actionBuildCompile->setShortcut(tr("F7"));
    actionBuildCompile->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/run-build.svg").arg(th)));
    connect(actionBuildCompile,SIGNAL(triggered()),this,SLOT(triggeredBuild()));
    menuBuild->addAction(actionBuildCompile);
    actionBuildStopCompile = new QAction(tr("Stop Compile"),this);
    actionBuildStopCompile->setShortcut(tr("Ctrl+F7"));
    actionBuildStopCompile->setEnabled(false);
    actionBuildStopCompile->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/process-stop.svg").arg(th)));
    connect(actionBuildStopCompile,SIGNAL(triggered()),this,SLOT(triggeredStopBuild()));
    menuBuild->addAction(actionBuildStopCompile);
    actionBuildExecute = new QAction(tr("Execute"),this);
    actionBuildExecute->setShortcut(tr("Ctrl+F5"));
    actionBuildExecute->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/system-run.svg").arg(th)));
    connect(actionBuildExecute,SIGNAL(triggered()),this,SLOT(triggeredExecute()));
    menuBuild->addAction(actionBuildExecute);
    actionBuildStopExecute = new QAction(tr("Stop Execute"),this);
    //actionBuildStopExecute->setShortcut(tr(""));
    actionBuildStopExecute->setEnabled(false);
    actionBuildStopExecute->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/process-stop.svg").arg(th)));
    connect(actionBuildStopExecute,SIGNAL(triggered()),this,SLOT(triggeredStopExecute()));
    menuBuild->addAction(actionBuildStopExecute);

//QMenu Debug-QAction Initialization
    actionDebugStart = new QAction(tr("Start"),this);    
    actionDebugStart->setShortcut(tr("F5"));
    actionDebugStart->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/debug-run.svg").arg(th)));
    menuDebug->addAction(actionDebugStart);
    actionDebugStop = new QAction(tr("Stop"),this);
    actionDebugStop->setShortcut(tr("Shift+F5"));
    actionDebugStop->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/media-playback-stop.svg").arg(th)));
    actionDebugStop->setEnabled(false);
    menuDebug->addAction(actionDebugStop);
    actionDebugPause = new QAction(tr("Pause"),this);
    //actionDebugPause->setShortcut(tr(""));
    actionDebugPause->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/media-playback-pause.svg").arg(th)));
    actionDebugPause->setEnabled(false);
    menuDebug->addAction(actionDebugPause);

    menuDebug->addSeparator();

    actionDebugStepOver = new QAction(tr("Step Over"),this);
    actionDebugStepOver->setShortcut(tr("F10"));
    actionDebugStepOver->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/debug-step-over.svg").arg(th)));
    actionDebugStepOver->setEnabled(false);
    menuDebug->addAction(actionDebugStepOver);
    actionDebugStepInto = new QAction(tr("Step Into"),this);
    actionDebugStepInto->setShortcut(tr("F11"));
    actionDebugStepInto->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/debug-step-into.svg").arg(th)));
    actionDebugStepInto->setEnabled(false);
    menuDebug->addAction(actionDebugStepInto);
    actionDebugStepOut = new QAction(tr("Step Out"),this);
    actionDebugStepOut->setShortcut(tr("Shift+F11"));
    actionDebugStepOut->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/debug-step-out.svg").arg(th)));
    actionDebugStepOut->setEnabled(false);
    menuDebug->addAction(actionDebugStepOut);
    actionDebugRunToCursor = new QAction(tr("Run To Cursor"),this);
    actionDebugRunToCursor->setShortcut(tr("Ctrl+F10"));
    actionDebugRunToCursor->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/debug-execute-to-cursor.svg").arg(th)));
    actionDebugRunToCursor->setEnabled(false);
    menuDebug->addAction(actionDebugRunToCursor);

    menuDebug->addSeparator();

    actionDebugToggleBreakpoint = new QAction(tr("Toggle Breakpoint"),this);
    actionDebugToggleBreakpoint->setShortcut(tr("F9"));
    menuDebug->addAction(actionDebugToggleBreakpoint);

//QMenu Language-QAction Initialization
    actionLanguageChinese = new QAction(tr("中文"),this);
    actionLanguageChinese->setCheckable(true);
    //actionLanguageChinese->setShortcut("");
    menuLanguage->addAction(actionLanguageChinese);
    actionLanguageEnglish = new QAction(tr("English"),this);
    actionLanguageEnglish->setCheckable(true);
    actionLanguageEnglish->setChecked(true);
    //actionLanguageEnglish->setShortcut("");
    menuLanguage->addAction(actionLanguageEnglish);

//QMenu Help-QAction Initialization
    actionHelpHelp = new QAction(tr("Help..."),this);
    //actionHelpHelp->setShortcut("");
    menuHelp->addAction(actionHelpHelp);

    menuHelp->addSeparator();

    actionHelpAboutProgram = new QAction(tr("About CppCreator"),this);
    //actionHelpAboutProgram->setShortcut("");
    actionHelpAboutProgram->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/help-about.svg").arg(th)));
    connect(this->actionHelpAboutProgram,SIGNAL(triggered()),this,SLOT(showAboutProgram()));
    menuHelp->addAction(actionHelpAboutProgram);
    actionHelpAboutFramework = new QAction(tr("About BeaconFramwork"),this);
    //actionHelpAboutFramework->setShortcut("");
    actionHelpAboutFramework->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/help-about.svg").arg(th)));
    connect(this->actionHelpAboutFramework,SIGNAL(triggered()),this,SLOT(showAboutBF()));
    menuHelp->addAction(actionHelpAboutFramework);
    actionHelpAboutQt = new QAction(tr("About Qt"),this);
    //actionHelpAboutQt->setShortcut("");
    actionHelpAboutQt->setIcon(QIcon(QString(":/Resources/Icons/Actions/%1/help-about.svg").arg(th)));
    connect(this->actionHelpAboutQt,SIGNAL(triggered()),this,SLOT(showAboutQt()));
    menuHelp->addAction(actionHelpAboutQt);

//fileToolBar
    ui->fileToolBar->addAction(actionFileNew);
    ui->fileToolBar->addAction(actionFileOpen);
    ui->fileToolBar->addAction(actionFileSave);
    ui->fileToolBar->addAction(actionFileCloseFile);

    ui->editToolBar->addAction(actionEditCopy);
    ui->editToolBar->addAction(actionEditCut);
    ui->editToolBar->addAction(actionEditPaste);
    ui->editToolBar->addAction(actionEditUndo);
    ui->editToolBar->addAction(actionEditRedo);
    ui->editToolBar->addAction(actionEditSettings);

    ui->buildToolBar->addAction(actionBuildCompile);
    ui->buildToolBar->addAction(actionBuildStopCompile);
    ui->buildToolBar->addAction(actionBuildExecute);
    ui->buildToolBar->addAction(actionBuildStopExecute);

    ui->debugToolBar->addAction(actionDebugStart);
    ui->debugToolBar->addAction(actionDebugStop);
    ui->debugToolBar->addAction(actionDebugPause);
    ui->debugToolBar->addAction(actionDebugStepOver);
    ui->debugToolBar->addAction(actionDebugStepInto);
    ui->debugToolBar->addAction(actionDebugStepOut);
    ui->debugToolBar->addAction(actionDebugRunToCursor);

//About Interface
    abI = new BeaconAboutInterface;
//QMenu DEBUGGING-QAction Initialization
    actionBCPDExternalProgram = new QAction(tr("Test:BFExternalProgram"));
    //actionBCPDExternalProgram->setShortcut("");
    connect(actionBCPDExternalProgram,SIGNAL(triggered()),this,SLOT(executeExternalProgram()));
    menuTest->addAction(actionBCPDExternalProgram);
}
//Statement updates
void MainWindow::tabChanged(int target){
    qDebug() << "tabChanged triggered: by" << target;
    currentEditor=editorList.value(this->ui->editorTabWidget->tabText(target));
    qDebug() << "with content: [" << currentEditor->text() << "]";
}
//@TODO
void MainWindow::codeChanged(){

}
//QActions-File
void MainWindow::triggeredNew(){
    newFileCnt++;
    QWidget *newWidget = new QWidget;
    QsciScintilla *newEditor = new QsciScintilla;
    QGridLayout *newLayout = new QGridLayout;
    currentEditor = newEditor;
    textLexer = new QsciLexerCPP(this);
    newEditor->setLexer(textLexer);
    newEditor->setMarginType(0,QsciScintilla::NumberMargin);
    newEditor->setMarginLineNumbers(0,true);
    newEditor->setMarginWidth(0,35);
    newLayout->addWidget(newEditor);
    newLayout->setSpacing(0);
    newLayout->setMargin(0);
    newWidget->setLayout(newLayout);
    qDebug() << "Till pnt 2";
    this->ui->editorTabWidget->addTab(newWidget,QString(tr("Untitled ")).append(QString::number(newFileCnt)));
    qDebug() << "To " << this->ui->editorTabWidget->count()-1;
    editorList.insert(QString(tr("Untitled ")).append(QString::number(newFileCnt)),newEditor);
    this->ui->editorTabWidget->setCurrentIndex(this->ui->editorTabWidget->count()-1);
    qDebug () << "Till pnt 1";
    qDebug() << "[ActionDBG]Tab Inserted @ " << this->ui->editorTabWidget->indexOf(newWidget);
}
void MainWindow::triggeredNew(QString fileName){
    newFileCnt++;
    QWidget *newWidget = new QWidget;
    QsciScintilla *newEditor = new QsciScintilla;
    QGridLayout *newLayout = new QGridLayout;
    currentEditor = newEditor;
    textLexer = new QsciLexerCPP(this);
    newEditor->setLexer(textLexer);
    newEditor->setMarginType(0,QsciScintilla::NumberMargin);
    newEditor->setMarginLineNumbers(0,true);
    newEditor->setMarginWidth(0,35);
    newLayout->addWidget(newEditor);
    newLayout->setSpacing(0);
    newLayout->setMargin(0);
    newWidget->setLayout(newLayout);
    qDebug() << "Till pnt 2";
    this->ui->editorTabWidget->addTab(newWidget,QString(tr("Untitled ")).append(QString::number(newFileCnt)));
    qDebug() << "To " << this->ui->editorTabWidget->count()-1;
    editorList.insert(fileName,newEditor);
    this->ui->editorTabWidget->setCurrentIndex(this->ui->editorTabWidget->count()-1);
    qDebug () << "Till pnt 1";
    qDebug() << "[ActionDBG]Tab Inserted @ " << this->ui->editorTabWidget->indexOf(newWidget);
}
void MainWindow::triggeredOpen(){
    QString target = QFileDialog::getOpenFileName(this, tr("Open File"), ".",tr("C++(*.cpp *.h)"));
    if(target.isEmpty())return;
    BeaconCodeProperty targetFile(target);
    qDebug() << "[ActionDBG]OpenFile:targetFileP=[" << targetFile.filePath << "],N=[" << targetFile.fileName << "]";
    if(!this->currentEditor->text().isEmpty() && !this->fileList.at(this->ui->editorTabWidget->currentIndex()).filePath.isEmpty()){
        qDebug() << "[ActionDBG]Open triggered:newPageCreated";
        this->triggeredNew(targetFile.fileName);
    }
    qDebug() << "[ActionDBG]Open triggered:listPos=" << this->ui->editorTabWidget->currentIndex();
    fileList[this->ui->editorTabWidget->currentIndex()]=targetFile;
    qDebug() << QString("[ActionDBG]Open finished,targetFile:path=[%1],name=[%2]").arg(fileList[this->ui->editorTabWidget->currentIndex()].filePath).arg(fileList[this->ui->editorTabWidget->currentIndex()].fileName);
    this->currentEditor->setText(BeaconFileIO::readFileContent(target));
    this->ui->editorTabWidget->setTabText(this->ui->editorTabWidget->currentIndex(),targetFile.fileName);
}
void MainWindow::triggeredSave(){
    QString target=this->fileList.at(this->ui->editorTabWidget->currentIndex()).filePath;
    qDebug() << "[ActionDBG]Save triggered, target filePath:[" << target <<"],fileName:[" << this->fileList.at(this->ui->editorTabWidget->currentIndex()).fileName << ']';
    if(target.isEmpty()){
        target = QFileDialog::getSaveFileName(this, tr("Save.."), ".",tr("C++(*.cpp *.h)"));
        if(target.isEmpty())return;
        this->fileList[this->ui->editorTabWidget->currentIndex()].setProperty(target);
        editorList.insert(this->fileList.at(this->ui->editorTabWidget->currentIndex()).fileName,this->editorList.value(this->fileList[this->ui->editorTabWidget->currentIndex()].fileName));
    }
    BeaconFileIO::saveFileContent(target,this->currentEditor->text());
    this->ui->editorTabWidget->setTabText(this->ui->editorTabWidget->currentIndex(),this->fileList.at(this->ui->editorTabWidget->currentIndex()).fileName);
}
void MainWindow::triggeredSaveAs(){
    QString target=QFileDialog::getSaveFileName(this, tr("Save.."), ".",tr("C++(*.cpp *.h)"));
    if(!BeaconFileIO::saveFileContent(target,this->currentEditor->text()))
        qDebug() << "[ActionDBG]Save failed: Plasma Genereal File Exception";
    editorList.insert(this->fileList.at(this->ui->editorTabWidget->currentIndex()).fileName,this->editorList.value(this->fileList[this->ui->editorTabWidget->currentIndex()].fileName));
    this->fileList[this->ui->editorTabWidget->currentIndex()].setProperty(target);
    this->ui->editorTabWidget->setTabText(this->ui->editorTabWidget->currentIndex(),this->fileList.at(this->ui->editorTabWidget->currentIndex()).fileName);
}
void MainWindow::triggeredExit(){
    this->close();
}
//QAction-Edit
void MainWindow::triggeredUndo(){
    currentEditor->undo();
}
void MainWindow::triggeredRedo(){
    currentEditor->redo();
}
void MainWindow::triggeredSelectAll(){
    currentEditor->selectAll();
}
void MainWindow::triggeredCopy(){
    currentEditor->copy();
}
void MainWindow::triggeredCut(){
    currentEditor->cut();
}
void MainWindow::triggeredPaste(){
    currentEditor->paste();
}
//QAction-Build
void MainWindow::triggeredBuild(){
    int index=this->ui->editorTabWidget->currentIndex();
    QStringList arg,pathS;
    arg.append(this->fileList[index].filePath);
    arg.append("-o");
    pathS=this->fileList[index].filePath.split(".");
    pathS.removeLast();
    if(BeaconPlatformInfo::isWindows)pathS.append("exe");
    arg.append(pathS.join("."));
    this->actionBuildCompile->setEnabled(false);
    this->actionBuildStopCompile->setEnabled(true);
    this->actionBuildExecute->setEnabled(false);
    this->actionBuildStopExecute->setEnabled(false);
    this->fileList[index].executablePath=pathS.join(".");
    qDebug() << "sourcefile: " << this->fileList[index].filePath;
    qDebug() << "executable: " << pathS.join(".");
    compiler->compileStart(this->fileList[index].filePath,pathS.join("."));
    this->actionBuildCompile->setEnabled(true);
    this->actionBuildStopCompile->setEnabled(false);
    this->actionBuildExecute->setEnabled(true);
    this->actionBuildStopExecute->setEnabled(false);
    this->ui->buildBrowser->append(compiler->latestCompileLog);
}
void MainWindow::triggeredStopBuild(){
    if(compiler->gcc.program.state()==QProcess::Running)
        compiler->gcc.program.kill();
    if(compiler->gpp.program.state()==QProcess::Running)
        compiler->gpp.program.kill();
    this->actionBuildCompile->setEnabled(true);
    this->actionBuildStopCompile->setEnabled(false);
    this->actionBuildExecute->setEnabled(true);
    this->actionBuildStopExecute->setEnabled(false);
}
void MainWindow::triggeredExecute(){
    if(this->fileList[this->ui->editorTabWidget->currentIndex()].executablePath.isEmpty())triggeredBuild();
    QStringList arg;
    arg.append("/k");
    arg.append(QStringList(this->fileList[this->ui->editorTabWidget->currentIndex()].executablePath));
    instance->setProgram("cmd.exe",arg);
    instance->startProgram();
    this->actionBuildCompile->setEnabled(false);
    this->actionBuildStopCompile->setEnabled(false);
    this->actionBuildExecute->setEnabled(false);
    this->actionBuildStopExecute->setEnabled(true);
    qDebug() << "Instance started";
}
void MainWindow::triggeredStopExecute(){
    if(instance->program.state() == QProcess::Running)
        instance->program.terminate();
    this->actionBuildCompile->setEnabled(true);
    this->actionBuildStopCompile->setEnabled(false);
    this->actionBuildExecute->setEnabled(true);
    this->actionBuildStopExecute->setEnabled(false);
}
//QActions-Help 1/4
void MainWindow::showAboutQt(){
    QMessageBox::aboutQt(this,"GUIDER");
}
void MainWindow::showAboutBF(){

}
void MainWindow::showAboutProgram(){
    abI->show();
}
//Helper
void MainWindow::onInstanceExited(){
    qDebug() << "Instance ended";
    this->actionBuildCompile->setEnabled(true);
    this->actionBuildStopCompile->setEnabled(false);
    this->actionBuildExecute->setEnabled(true);
    this->actionBuildStopExecute->setEnabled(false);
}
//QActions-Test
void MainWindow::executeExternalProgram(){
    //QString target=QFileDialog::getOpenFileName(this, tr("Execute.."), ".",tr("Executable(*.*)"));
    QSettings settings;
    QString target=settings.value("gppPath").toString();
    BeaconExternalProgram app;
    QStringList arg;arg.append("-v");
    app.setProgram(target,arg);
    app.startProgram();
    app.program.waitForFinished();
    QMessageBox::information(nullptr, "Finished", app.logOut, QMessageBox::Yes, QMessageBox::Yes);
}
MainWindow::~MainWindow(){
    delete ui;
}
