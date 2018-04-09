#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

class calctool : public QMainWindow
{
    Q_OBJECT
public:
    calctool(QMainWindow *parent = 0);
public slots:
    //鎸夐敭鎹曡幏
    void b0();//0鍙烽敭鐨勬Ы鍑芥暟锛屼互涓嬩緷娆＄被鎺?
    void b1();
    void b2();
    void b3();
    void b4();
    void b5();
    void b6();
    void b7();
    void b8();
    void b9();
    //鏁板鍏紡鏂规硶
    void badd();//鍔犲彿閿?
    void bsub();//鍑忓彿閿?
    void bmul();//涔樺彿閿?
    void bdiv();//闄ゅ彿閿?
    void bdot();//鐐瑰彿閿?
    void bequ();//绛夊彿閿?
    void bant();//姝ｈ礋鍙峰垏鎹㈤敭
    void bce();//娓呭睆閿?
    void bclr();//娓呴浂閿?
    void bbks();//鍒犻櫎閿?
    void bsqr();
    void brec();
    void bper();
    //妲藉嚱鏁拌彍鍗曚娇鐢?
    void mcopy();
    void mpaste();
    void mundo();
    void mredo();
    void setType();
    void mcontent();
    void mabout();
    //閫夋嫨妯″紡鐣岄潰鍒囨崲
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
    //璁＄畻浣跨敤
//    QStack <double> stack;
    QString A,B;//瀛樺偍瑕佽绠楃殑鏁?
    char c;//瀛樺偍鏍囩偣绗﹀彿
    int d;//鏍囪寮€鍏崇姸鎬?
    //瀛椾綋鏄剧ず
    QTextCodec *codec;
    //鐣岄潰璁捐浣跨敤
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
    //甯冨眬缃戞牸
    QWidget *widget;
    QGridLayout *layout;
    //鑿滃崟鏍忎娇鐢?
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
    //鐘舵€佹爮浣跨敤
    QLabel *statuslabel;
    //鐣岄潰鍒囨崲
    bool booltype;
    bool error;

    //楂樼骇
    QLineEdit *input;
    QString inputmessage;
};




#endif // MAINWINDOW_H
