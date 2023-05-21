#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QTextEdit>

// -1- GridLayout

class Window : public QWidget
{

public:
    Window(QWidget* parent = nullptr):QWidget(parent)
    {
        setWindowTitle("grid Layout");
        setGeometry(250,250,500,500);

        // declare the layout
        mainLayout = new QVBoxLayout();
        this->setLayout(mainLayout);

        gridGroub = new QGroupBox();
        gridGroub->setTitle("GridLayout");

        // declare the layout
        gridLayout = new QGridLayout();
        gridGroub->setLayout(gridLayout);

        // adding the element to the mainlayout
        mainLayout->addWidget(gridGroub);

        // adding to the groub Box
        for (int i = 0; i < 3; ++i) {
            // tr() function is likely a translation function used in the context of internationalization (i18n) or localization (l10n) of software applications. It stands for "translate" and is commonly used in frameworks like Qt.
            // tr() function is used to mark text strings for translation.
            // -- The %1 -- syntax is a placeholder syntax used in Qt's translation mechanism to handle the substitution of values into translated strings. The %1 indicates that the first value to be substituted will be inserted at that position. The arg() function is then used to provide the actual value that will replace the %1 placeholder.
            gridLabel[i] = new QLabel(tr("Line %1").arg(i+1));
            gridLineEdit[i] = new QLineEdit();
            //addWidget(gridLabel[i], i(the row number) , 0 (column number in the grid));
            gridLayout->addWidget(gridLabel[i], i , 0);
            gridLayout->addWidget(gridLineEdit[i],i , 1);
        }


        gridTextEdit = new QTextEdit();
        // addWidget(gridTextEdit, 0(row num), 2(column num), 3(Span in rows), 1(span in columns);
        gridLayout->addWidget(gridTextEdit, 0, 2, 3, 1);


        // the second group
        groub2 = new QGroupBox();
        groub2->setTitle("the 2nd Groub");
        mainLayout->addWidget(groub2);

    }

private:
    QVBoxLayout* mainLayout;
    QGridLayout* gridLayout;

    // Groub_Box
    QGroupBox* gridGroub;
    QGroupBox* groub2;

    // labels
    QLabel* gridLabel[3];

    // lineEdit
    QLineEdit* gridLineEdit[3];

    // rich text box
    QTextEdit* gridTextEdit;



};
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;



    window.show();
    return app.exec();
}
