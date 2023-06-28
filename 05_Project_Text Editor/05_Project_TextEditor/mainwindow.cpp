#include "mainwindow.h"
#include "QShortcut"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), font_size(100)

{
    //setWindowTitle("TextEditor");
    setGeometry(250, 250, 600, 400);

    textarea = new QPlainTextEdit();
    setCentralWidget(textarea);
    // calling the function from mainwindow.h
    init_menuBar();
    init_statusBar();
    init_toolBar();

    // connecting the menu functions with menu options
    //new action
    connect(NewAction,&QAction::triggered,this,&MainWindow::New);

    //open action
    connect(OpenAction,&QAction::triggered,this,&MainWindow::Open);

    //save action
    connect(SaveAction,&QAction::triggered,this,&MainWindow::Save);

    //Save AS action
    connect(SaveAsAction,&QAction::triggered,this,&MainWindow::SaveAs);

    //Exit action
    connect(ExitAction,&QAction::triggered,this,&MainWindow::Exit);



    // initialize the current file with << empty >> string
    setCurrentFile(QString());

    // connect on textarea if modified
    // this function's purpose is showing * next to the title of the page if write down any thing
    // (not saved text)
    connect(textarea->document(),&QTextDocument::contentsChanged,this,&MainWindow::documentModified);

    // zoom IN and OUT


}





///////////////////////////// distructor
MainWindow::~MainWindow()
{


}

///////////////////////////////// initialization for the menubar
void MainWindow::init_menuBar(){

    fileMenu = menuBar()->addMenu("File");
    {
        NewAction = new QAction(QIcon(":/icons/new.png"),"New");
        NewAction->setShortcut(QKeySequence::New);
        NewAction->setStatusTip("Create new file");
        fileMenu->addAction(NewAction);

        OpenAction = new QAction(QIcon(":/icons/open.png"), "Open");
        OpenAction->setShortcut(QKeySequence::Open);
        OpenAction->setStatusTip("Open exist file");
        fileMenu->addAction(OpenAction);

        SaveAction = new QAction(QIcon(":/icons/save.png"), "Save");
        SaveAction->setShortcut(QKeySequence::Save);
        SaveAction->setStatusTip("save file");
        fileMenu->addAction(SaveAction);

        SaveAsAction = new QAction(QIcon(":/icons/saveAs.png"), "Save As");
        // SaveAsAction->setShortcut(QKeySequence::SaveAs); // Not-working
        // instead of it we use this method
        SaveAsAction->setShortcut(tr("Ctrl+Shift+S"));
        SaveAsAction->setStatusTip("Save file as ...");
        fileMenu->addAction(SaveAsAction);

        fileMenu->addSeparator();
        ExitAction = new QAction(QIcon(":/icons/exit.png"), "Exit");
        ExitAction->setShortcut(tr("Ctrl+Q"));
        ExitAction->setStatusTip("Exit program");
        fileMenu->addAction(ExitAction);

    }
    //////////// postponed
    editMenu = menuBar()->addMenu("Edit");
    formatmenu = menuBar()->addMenu("Format");
    viewMenu = menuBar()->addMenu("View");

    helpMenu = menuBar()->addMenu("Help");
    {
        AboutAction = new QAction(QIcon(":/icons/about.png"), "help");
        AboutAction->setStatusTip("About Us");
        helpMenu->addAction(AboutAction);
    }

}

//////////////////////////////////// initialization for the statusbar

void MainWindow::init_statusBar(){
    statusBar()->addPermanentWidget(new QLabel(""));
    statusBar()->addPermanentWidget(new QLabel(tr("%1 %").arg(font_size)));
}

/////////////////////// initialization for the toolbar

void MainWindow::init_toolBar(){
    toolbar = new QToolBar();

        // Create actions
        //QAction* newAction = toolbar->addAction(NewAction);
        //QAction* openAction = toolbar->addAction(QIcon(":/icons/open.png"), "Open");
        //QAction* saveAction = toolbar->addAction(QIcon(":/icons/save.png"), "Save");
        //QAction* saveAsAction = toolbar->addAction(QIcon(":/icons/saveAs.png"), "Save As");
        QAction* printAction = toolbar->addAction(QIcon(":/icons/print.png"), "Print");
        QAction* copyAction = toolbar->addAction(QIcon(":/icons/copy.png"), "Copy");
        QAction* cutAction = toolbar->addAction(QIcon(":/icons/cut.png"), "Cut");
        QAction* pasteAction = toolbar->addAction(QIcon(":/icons/paste.png"), "Paste");

        // Apply stylesheet to toolbar items
        QString styleSheet = "QToolButton { color: black; }";
        toolbar->setStyleSheet(styleSheet);

        // Add actions to toolbar
        toolbar->addAction(NewAction);
        toolbar->addAction(OpenAction);
        toolbar->addAction(SaveAction);
        toolbar->addAction(SaveAsAction);
        toolbar->addAction(printAction);
        toolbar->addAction(copyAction);
        toolbar->addAction(cutAction);
        toolbar->addAction(pasteAction);

        addToolBar(toolbar);
}


//////////////////////////// helpers
void MainWindow::setCurrentFile(QString filename)
{
    currentFileName = filename;
    textarea->document()->setModified(false);

    setWindowModified(false);
    QString showName = currentFileName;
    if(currentFileName.isEmpty())
        showName = "untitled.txt";

    // #**Alert**# should make sure that the program is not have setWindowTitle() and if have
    // update it
    setWindowFilePath(showName);
    // after i created the documentModified function i realize that we should not make window tilte static.
    // this error will happens -> QWidget::setWindowModified: The window title does not contain a '[*]' placeholder
    //setWindowTitle(showName);
}

void MainWindow::documentModified()
{
    setWindowModified(textarea->document()->isModified());
}

bool MainWindow::maybeSave()
{
    if(!textarea->document()->isModified())
        return true;

    auto ret = QMessageBox::warning(this,"warning","the document is modified \n do u wanna save ?",
                                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);


    switch (ret) {
    case QMessageBox::Save:
        Save();
        break;
    case QMessageBox::Cancel:
        return false;
        break;
    case QMessageBox::Discard:
        break;
    default:
        break;
    }

    return true;
}

//////////////////////////// functions for the menues file, edit, tools, ...etc
void MainWindow::New()
{
    if(maybeSave()){
        textarea->clear();
        setCurrentFile(QString());
    }
}

void MainWindow::Open()
{
    if(maybeSave()){
        currentFileName = QFileDialog::getOpenFileName(this);

        if(!currentFileName.isEmpty()){

            //////////// update the current file
            setCurrentFile(currentFileName);

            QFile file(currentFileName);

            if(!file.open(QFile:: ReadOnly | QFile::Text))
                QMessageBox::warning(this, "Warning","error loading file");

            QTextStream in(&file);

            QGuiApplication::setOverrideCursor(Qt::WaitCursor);
            textarea->document()->setPlainText(in.readAll());
            QGuiApplication::restoreOverrideCursor();


        }
    }
}

void MainWindow::Save()
{
    if(currentFileName.isEmpty()){
        SaveAs();
    }else{
        QGuiApplication::setOverrideCursor(Qt::WaitCursor);

        QSaveFile file(currentFileName);

        if(file.open(QFile::WriteOnly | QFile::Text)){
            QTextStream out(&file);
            out << textarea->document()->toPlainText();
            if(!file.commit()){
                QMessageBox::warning(this, "Warning", "error in saving file");
            }

        }else{
            QMessageBox::warning(this, "Warning", "error in opening file");
        }

        QGuiApplication::restoreOverrideCursor();

        setCurrentFile(currentFileName);
        statusBar()->showMessage("file saved", 2000);

    }
}

void MainWindow::SaveAs()
{
       QFileDialog dialog(this);

       dialog.setWindowModality(Qt::WindowModal);

       dialog.setAcceptMode(QFileDialog::AcceptSave);

       if(dialog.exec() != QDialog::Accepted){
           //error
       }
       else{
           currentFileName = dialog.selectedFiles().first();
           setCurrentFile(currentFileName);
           Save();
       }
}

void MainWindow::Exit()
{

}

//////////////////// Zoom in and out
///

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->modifiers() == Qt::ControlModifier) {
        if (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal) {
            // Zoom in logic
            QFont font = textarea->font();
            qreal newSize = font.pointSizeF() + 1.0;
            font.setPointSizeF(newSize);
            textarea->setFont(font);
        } else if (event->key() == Qt::Key_Minus) {
            // Zoom out logic
            QFont font = textarea->font();
            qreal newSize = font.pointSizeF() - 1.0;
            if (newSize >= 1.0) {
                font.setPointSizeF(newSize);
                textarea->setFont(font);
            }
        }
    }

    QMainWindow::keyPressEvent(event);
}




