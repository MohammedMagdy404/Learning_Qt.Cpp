#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QTextEdit>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QGuiApplication>
#include <QSaveFile>
#include <QKeyEvent>





class MainWindow : public QMainWindow
{

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    // functions for the menues file, edit, tools, ...etc -> to be connected
    void New();
    void Open();
    void Save();
    void SaveAs();
    void Exit();


    ///////////// Zoom in and Out
protected:
    // Other protected member functions
    void keyPressEvent(QKeyEvent* event) override; // Add this line for declaration

private:

    void init_menuBar();
    void init_toolBar();
    void init_statusBar();


    void setCurrentFile(QString filename);
    void documentModified();
    bool maybeSave();


    int font_size;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* formatmenu;
    QMenu* viewMenu;
    QMenu* helpMenu;

    // to not declare QAction every time
    // file menu actions
    QAction* NewAction;
    QAction* OpenAction;
    QAction* SaveAction;
    QAction* SaveAsAction;
    QAction* ExitAction;

    // about menu actions
    QAction* AboutAction;

    QPlainTextEdit* textarea;

    QToolBar* toolbar;

    ////////// the current file
    QString currentFileName;
};

