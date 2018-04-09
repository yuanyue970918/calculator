#ifndef CALCTOOL_H
#define CALCTOOL_H

#include <QMainWindow>
#include <QString>
//#include <QStack>
#include <QTextCodec>

QT_BEGIN_NAMESPACE
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
QT_END_NAMESPACE

class cal : public QMainWindow
{
    Q_OBJECT
public:
    cal(QMainWindow *parent = 0);
public slots:

    void b0();
    void b1();
    void b2();
    void b3();
    void b4();
    void b5();
    void b6();
    void b7();
    void b8();
    void b9();

    void badd();
    void bsub();
    void bmul();
    void bdiv();
    void bdot();
    void bequ();
    void bant();
    void bce();
    void bclr();
    void bbks();
    void bsqr();
    void brec();
    void bper();

    void mcopy();
    void mpaste();
    void mundo();
    void mredo();
    void setType();
    void mcontent();
    void mabout();

    void setTypeBasic();
    void setTypeAdvance();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    void createActions();
    void createMenu();
    void createStatus();
    void createControl();
    void chooseType();

//    QStack <double> stack;
    QString A,B;
    char c;
    int d;

    QTextCodec *codec;

    QLineEdit *editor;
    QPushButton *bksp;
    QPushButton *ce;
    QPushButton *clr;
    QPushButton *anti;
    QPushButton *seven;
    QPushButton *eight;
    QPushButton *nine;
    QPushButton *division;
    QPushButton *four;
    QPushButton *five;
    QPushButton *six;
    QPushButton *multiplication;
    QPushButton *one;
    QPushButton *two;
    QPushButton *three;
    QPushButton *subtraction;
    QPushButton *zero;
    QPushButton *dot;
    QPushButton *equal;
    QPushButton *addition;

    QPushButton *rec;
    QPushButton *sqr;
    QPushButton *per;

    QWidget *widget;
    QGridLayout *layout;

    QMenu *computer;
    QMenu *edit;
    QMenu *view;
    QMenu *help;
    QAction *quit;
    QAction *copy;
    QAction *paste;
    QAction *undo;
    QAction *redo;
    QAction *basic;
    QAction *advance;
    QAction *content;
    QAction *about;

    QLabel *statuslabel;

    bool booltype;
    bool error;


    QLineEdit *input;
    QString inputmessage;
};

#endif // CALCTOOL_H
