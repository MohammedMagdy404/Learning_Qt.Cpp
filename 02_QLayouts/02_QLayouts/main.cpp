#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
// -1- QLayout()
#include <QHBoxLayout>
#include <QVBoxLayout>

// -2- Hello, world ;)
#include <QDebug>

class Window : public QWidget // ':' for inheretance
{
private:
    QVBoxLayout* mainlayout;
    QHBoxLayout* row1layout;
    QHBoxLayout* row2layout;
    QHBoxLayout* row3layout;
    QLabel* username_label;
    QLabel* password_label;

    QLineEdit* username_box;
    QLineEdit* password_box;

    QPushButton* login;
    QPushButton* cancel;


public:
    /*
    - (QWidget* parent = nullptr) is the constructor declaration with a single parameter named parent of type QWidget*. This parameter is optional, and if no argument is provided when creating an instance of Window, it will default to nullptr.
    - ':' introduces the constructor initializer list.
    - QWidget(parent) in the initializer list ensures proper initialization of the base class.
    */
    Window(QWidget* parent = nullptr):QWidget(parent)
    {
        setWindowTitle("Login");
        setFixedSize(300,200);

        // -1- window layout --Vertical--
        mainlayout = new QVBoxLayout();
        //this->setLayout(mainlayout);
        setLayout(mainlayout);

        // -2- row_1 layout
        row1layout = new QHBoxLayout();
        row1layout->setSpacing(50);
        username_label = new QLabel("username: ");
        username_box = new QLineEdit();
        // add label and box to row layout
        row1layout->addWidget(username_label);
        row1layout->addWidget(username_box);
        // add row1layout to mainlayout
        mainlayout->addLayout(row1layout);


        // -3- row_2 layout
        row2layout = new QHBoxLayout();
        row2layout->setSpacing(50);
        password_label = new QLabel("Password: ");
        password_box = new QLineEdit();
        // QLineEdit::EchoMode::Password
        // class: QlineEdit
        // '::' scope resolution operator is used to access elements within a class or namespace.
        // EchoMode: This is the name of the enum class within QLineEdit that defines different modes for displaying text input.
        password_box->setEchoMode(QLineEdit::EchoMode::Password);
        // add label and box to row layout
        row2layout->addWidget(password_label);
        row2layout->addWidget(password_box);
        // add row2layout to mainlayout
        mainlayout->addLayout(row2layout);


        // -4- row_3 layout
        row3layout = new QHBoxLayout();
        row3layout->addStretch();
        login = new QPushButton("Login");
        cancel = new QPushButton("Cancel");
        // add label and box to row layout
        row3layout->addWidget(login);
        row3layout->addWidget(cancel);
        // add row3layout to mainlayout
        mainlayout->addLayout(row3layout);


        // -- Connections --

        connect(login, &QPushButton::clicked , this, &Window::login_pressed);
        connect(cancel, &QPushButton::clicked , this, &Window::cancel_pressed);







    }

    void login_pressed(){
        //c_str() : character array
        printf("Logged in: %s\n", username_box->text().toStdString().c_str());
        printf("Password in: %s\n", password_box->text().toStdString().c_str());

    }

    void cancel_pressed(){
        printf("canceled \n");

    }


};



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window window;




    // hello, world
    qInfo() << "Hello, world";
    window.show();
    return a.exec();
}
