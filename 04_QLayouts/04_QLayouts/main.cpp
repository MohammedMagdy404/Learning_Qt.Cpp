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
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>

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
        formGroub = new QGroupBox();
        formGroub->setTitle("form layout");

        formLayout = new QFormLayout();
        formGroub->setLayout(formLayout);
        mainLayout->addWidget(formGroub);


        for (int i = 0; i < 3; ++i)
            formLabel[i] = new QLabel(tr("Line %1").arg(i+1));

        formLineEdit = new QLineEdit();
        formLayout->addRow(formLabel[0],formLineEdit);


        compoBox = new QComboBox();
        compoBox->addItem("the 1st");
        compoBox->addItem("the 2nd");
        compoBox->addItem("the 3rd");
        formLayout->addRow(formLabel[1],compoBox);

        spinBox = new QSpinBox();
        formLayout->addRow(formLabel[2],spinBox);

        // The syntax --> QObject::connect(sender, SIGNAL(mySignal()), receiver, SLOT(mySlot()));
        // For OverLoaded Functions -*-*-*> connect(compoBox,QOverload<int>(&QComboBox::currentIndexChanged),this,&Window::onIndexChanged);
        connect(compoBox,&QComboBox::currentIndexChanged,this,&Window::onIndexChanged);
        connect(spinBox,&QSpinBox::valueChanged,this,&Window::onValueChanged);


    }
    // currentIndexChanged(int index) the slot function should be as signal function in arrgument
    void onIndexChanged(int index){
        auto txt = compoBox->itemText(index);
        // c_str => character array
        printf("%s \n", txt.toStdString().c_str());
    }

    void onValueChanged(int val){
        printf("%d \n", val);
    }

private:
    QVBoxLayout* mainLayout;
    QGridLayout* gridLayout;
    QFormLayout* formLayout;

    // Groub_Box
    QGroupBox* gridGroub;
    QGroupBox* formGroub;

    // labels
    QLabel* gridLabel[3];
    QLabel* formLabel[3];

    // lineEdit
    QLineEdit* gridLineEdit[3];
    QLineEdit* formLineEdit;

    // rich text box
    QTextEdit* gridTextEdit;

    // compobox
    QComboBox* compoBox;
    // spinBox
    QSpinBox* spinBox;



};
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;



    window.show();
    return app.exec();
}
