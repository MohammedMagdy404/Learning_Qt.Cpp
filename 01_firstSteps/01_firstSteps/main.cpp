#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>

// -1- inputs and classes
// -2- Signals and Slots
class Window : public QWidget
{

public:
    Window(QWidget* parent = nullptr):QWidget(parent)
    {
        setFixedSize(500,250);
        // -1- inputs and classes
        name_edit = new QLineEdit(this);
        name_edit->move(100,100);
        name_edit->setStyleSheet("background : cyan; font:bold 15px; color:black");

        // -2- to connect signal with slot
        // Signals and slots are used for communication between objects.
        // connect(sender, &QObject::destroyed, (Resiever)/this, &MyObject::objectDestroyed);
        connect(name_edit, &QLineEdit::returnPressed, this, &Window::EnterPressed);

        name = new QLabel("Name",this);
        name->move(50,100);

        // QPushButton(text,parent)
        button = new QPushButton("Hello Button", this);
        button->move(50,50);
        connect(button, &QPushButton::clicked , this, &Window::ButtonPressed);


    }
    void EnterPressed(){
        QMessageBox msg;
        msg.setText(name_edit->text());
        msg.exec();
        printf("hellooo !");
    }

    void ButtonPressed(){
        QMessageBox msg;
        msg.setText("Holly_Molly u GOT ME! "+name_edit->text());
        msg.exec();
    }
private:
    QLabel* name;
    QLineEdit* name_edit;
    QPushButton* button;
};




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window window;


    window.show();
    return a.exec();
}
