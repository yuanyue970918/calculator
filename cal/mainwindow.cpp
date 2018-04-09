#include <QtGui>

#include "mainwindow.h"
#include "math.h"

calctool::calctool(QMainWindow *parent)
    : QMainWindow(parent)
{
    codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    A="0";//初始化
    B="0";
    c=' ';//c的初始化符号为空格
    d = 0;
    booltype = true;
    error = true;
    widget = new QWidget(this);
    createActions();
    createMenu();
    createStatus();
    createControl();
    chooseType();
    this->setCentralWidget(widget);

    //���Ӳۺ���
    connect(zero, SIGNAL(clicked()), this, SLOT(b0()));
    connect(one, SIGNAL(clicked()), this, SLOT(b1()));
    connect(two, SIGNAL(clicked()), this, SLOT(b2()));
    connect(three, SIGNAL(clicked()), this, SLOT(b3()));
    connect(four, SIGNAL(clicked()), this, SLOT(b4()));
    connect(five, SIGNAL(clicked()), this, SLOT(b5()));
    connect(six, SIGNAL(clicked()), this, SLOT(b6()));
    connect(seven, SIGNAL(clicked()), this, SLOT(b7()));
    connect(eight, SIGNAL(clicked()), this, SLOT(b8()));
    connect(nine, SIGNAL(clicked()), this, SLOT(b9()));
    connect(addition, SIGNAL(clicked()), this,SLOT(badd()));
    connect(subtraction, SIGNAL(clicked()), this, SLOT(bsub()));
    connect(multiplication, SIGNAL(clicked()), this, SLOT(bmul()));
    connect(division, SIGNAL(clicked()), this, SLOT(bdiv()));
    connect(dot, SIGNAL(clicked()), this, SLOT(bdot()));
    connect(equal, SIGNAL(clicked()), this, SLOT(bequ()));
    connect(anti, SIGNAL(clicked()), this, SLOT(bant()));
    connect(clr, SIGNAL(clicked()), this, SLOT(bclr()));
    connect(ce, SIGNAL(clicked()), this, SLOT(bce()));
    connect(bksp, SIGNAL(clicked()), this, SLOT(bbks()));

    connect(rec, SIGNAL(clicked()), this, SLOT(brec()));
    connect(sqr, SIGNAL(clicked()), this, SLOT(bsqr()));
    connect(per, SIGNAL(clicked()), this, SLOT(bper()));
}

//������������ģ��
void calctool::createActions()
{
    quit = new QAction(tr("Quit(&Quit)"), this);
    quit->setShortcut(QKeySequence::Quit);
    quit->setStatusTip(tr("Quit calculator"));
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
//    copy = new QAction(tr("Copy(&Copy)"), this);
//    copy->setShortcut(QKeySequence::Copy);
//    copy->setStatusTip(tr("Copy selected"));
//    connect(copy, SIGNAL(triggered()), this, SLOT(mcopy()));
//    paste = new QAction(tr("Paste(&Paste)"), this);
//    paste->setShortcut(QKeySequence::Paste);
//    paste->setStatusTip(tr("Paste selected"));
//    connect(paste, SIGNAL(triggered()), this, SLOT(mpaste()));
    undo = new QAction(tr("Undo(&Undo)"), this);
    undo->setShortcut(QKeySequence::Undo);
    undo->setStatusTip(tr("Undo"));
    connect(undo, SIGNAL(triggered()), this, SLOT(mundo()));
    redo = new QAction(tr("Redo(&Redo)"), this);
    redo->setShortcut(QKeySequence::Redo);
    redo->setStatusTip(tr("Redo"));
    connect(redo, SIGNAL(triggered()), this, SLOT(mredo()));
    basic = new QAction(tr("~Basic(&Basic)"), this);
    basic->setStatusTip(tr("Basic"));
    connect(basic, SIGNAL(triggered()), this, SLOT(setTypeBasic()));
    advance = new QAction(tr("Advance(&Advance)"), this);
    advance->setStatusTip(tr("Advance"));
    connect(advance, SIGNAL(triggered()), this, SLOT(setTypeAdvance()));
    content = new QAction(tr("Connect(&Connect)"), this);
    content->setShortcut(QKeySequence::HelpContents);
    content->setStatusTip(tr("Show helping"));
    connect(content, SIGNAL(triggered()), this, SLOT(mcontent()));
    about = new QAction(tr("About(&About)"), this);
    about->setStatusTip(tr("About calctool"));
    connect(about, SIGNAL(triggered()), this, SLOT(mabout()));
}
void calctool::createMenu()
{
    computer = menuBar()->addMenu(tr("Calculator(&C)"));
    computer->addAction(quit);
//    edit = menuBar()->addMenu(tr("Edit(&E)"));
////    edit->addAction(copy);
////    edit->addAction(paste);
//    edit->addAction(undo);
//    edit->addAction(redo);
    view = menuBar()->addMenu(tr("Cheak(&V)"));
    view->addAction(basic);
    view->addAction(advance);
    help = menuBar()->addMenu(tr("Help(&H)"));
    help->addAction(content);
    help->addSeparator();
    help->addAction(about);
}
void calctool::createStatus()
{
    statuslabel = new QLabel();
    statuslabel->setAlignment(Qt::AlignHCenter);
    statuslabel->setMinimumSize(statuslabel->sizeHint());
    statusBar()->addWidget(statuslabel);
}
void calctool::createControl()
{
    editor = new QLineEdit();
    editor->setAlignment(Qt::AlignRight);
    editor->setFixedHeight(60);
    editor->setFont(QFont("Courier 10 Pitch", 18, QFont::Bold));
    QRegExp regExp("[0-9//+//*/////-\\s]{64}");
    editor->setValidator(new QRegExpValidator(regExp, this));
    editor->scroll(256, 0);
    editor->setText("0");
    editor->setEnabled(false);
    layout = new QGridLayout(widget);
    bksp = new QPushButton(tr("AC"));//直接改名字没事
    bksp->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    bksp->setStatusTip(tr("delete right(Backspace)"));
    ce = new QPushButton(tr("CE"));
    ce->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    ce->setStatusTip(tr("clearֵ(Escape)"));
    clr = new QPushButton(tr("Sqrt"));
    clr->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    clr->setStatusTip(tr("Clear all(Shift Delete)"));
    anti = new QPushButton(tr("Rec"));
    anti->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    anti->setStatusTip(tr("Change char(C)"));
    seven = new QPushButton(tr("7"));
    seven->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    eight = new QPushButton(tr("8"));
    eight->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    nine = new QPushButton(tr("9"));
    nine->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    division = new QPushButton(tr("/"));
    division->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    division->setStatusTip(tr("chufa(/)"));
    four = new QPushButton(tr("4"));
    four->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    five = new QPushButton(tr("5"));
    five->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    six = new QPushButton(tr("6"));
    six->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    multiplication = new QPushButton(tr("*"));
    multiplication->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    multiplication->setStatusTip(tr("chengfa(*)"));
    one = new QPushButton(tr("1"));
    one->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    two = new QPushButton(tr("2"));
    two->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    three = new QPushButton(tr("3"));
    three->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    subtraction = new QPushButton(tr("-"));
    subtraction->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    subtraction->setStatusTip(tr("Sub(-)"));
    zero = new QPushButton(tr("0"));
    zero->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    dot = new QPushButton(tr("."));
    dot->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    dot->setStatusTip(tr("Point"));
    equal = new QPushButton(tr("="));
    equal->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    equal->setStatusTip(tr("equal(=)"));
    addition = new QPushButton(tr("+"));
    addition->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    addition->setStatusTip(tr("Add(+)"));

    rec = new QPushButton(tr("Rec"));
    rec->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    rec->setStatusTip(tr("qiudao"));
    sqr = new QPushButton(tr("Sqr"));
    sqr->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    sqr->setStatusTip(tr("Double"));
    per = new QPushButton(tr("Per"));
    per->setSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding);
    per->setStatusTip(tr("percent"));

    input = new QLineEdit;
    input->setAlignment(Qt::AlignRight);
    input->setFixedHeight(60);
    input->setFont(QFont("Courier 10 Pitch", 18, QFont::Bold));




}
//setType()�ۺ���
void calctool::setTypeBasic()
{
    booltype = true;
//    basic->setChecked(true);
    basic->setText(tr("~ ����(&Basic)"));
//    advance->setChecked(false);
    advance->setText(tr("�߼�(&Advance)"));
    chooseType();
}
void calctool::setTypeAdvance()
{
    booltype = false;
//    basic->setChecked(false);
    basic->setText(tr("����(&Basic)"));
//    advance->setChecked(true);
    advance->setText(tr("~ �߼�(&Advance)"));
    chooseType();
}
//λ�ù�ϵ
void calctool::chooseType()
{
    if (booltype)
    {
        rec->hide();
        sqr->hide();
        per->hide();
        input->hide();
        this->setSizeIncrement(350, 375);
        layout->addWidget(editor, 0, 0, 1, 4);
        layout->addWidget(bksp, 1, 0);
        layout->addWidget(ce, 1, 1);
        layout->addWidget(clr, 1, 2);
        layout->addWidget(anti, 1, 3);
        layout->addWidget(seven, 2, 0);
        layout->addWidget(eight, 2, 1);
        layout->addWidget(nine, 2, 2);
        layout->addWidget(division, 2, 3);
        layout->addWidget(four, 3, 0);
        layout->addWidget(five, 3, 1);
        layout->addWidget(six, 3, 2);
        layout->addWidget(multiplication, 3, 3);
        layout->addWidget(one, 4, 0);
        layout->addWidget(two, 4, 1);
        layout->addWidget(three, 4, 2);
        layout->addWidget(subtraction, 4, 3);
        layout->addWidget(zero, 5, 0);
        layout->addWidget(dot, 5, 1);
        layout->addWidget(equal, 5, 2);
        layout->addWidget(addition, 5, 3);
        this->setMinimumSize(350, 375);

        this->setWindowTitle(tr("Calculator"));
    }
    else
    {
        rec->show();
        sqr->show();
        per->show();
        input->show();
        this->setSizeIncrement(650, 350);
        layout->addWidget(editor, 0, 0, 1, 8);

        layout->addWidget(seven, 1, 0);
        layout->addWidget(eight, 1, 1);
        layout->addWidget(nine, 1, 2);
        layout->addWidget(division, 1, 3);
        layout->addWidget(bksp, 1, 5);
        layout->addWidget(ce, 1, 6);
        layout->addWidget(clr, 1, 7);

        layout->addWidget(four, 2, 0);
        layout->addWidget(five, 2, 1);
        layout->addWidget(six, 2, 2);
        layout->addWidget(multiplication, 2, 3);
        layout->addWidget(anti, 2, 5);

        layout->addWidget(one, 3, 0);
        layout->addWidget(two, 3, 1);
        layout->addWidget(three, 3, 2);
        layout->addWidget(subtraction, 3, 3);
        layout->addWidget(rec, 3, 5);
        layout->addWidget(sqr, 3, 6);
        layout->addWidget(per, 3, 7);

        layout->addWidget(zero, 4, 0);
        layout->addWidget(dot, 4, 1);
        layout->addWidget(equal, 4, 2);
        layout->addWidget(addition, 4, 3);
        layout->addWidget(input, 4, 5, 1, 3);
        this->setMinimumSize(650, 350);
        this->setWindowTitle(tr("Calculator Super"));
    }
    widget->setLayout(layout);
}


void calctool::b0()
{
    if(B == "0")
    {
        B = "0";
    }
    else//׷��0
    {
        B = editor->text();
        B.append("0");
    }
    editor->setText(B);
    inputmessage.append("0");
    input->setText(inputmessage);
}

void calctool::b1()
{
    error = false;
    if(B == "0")
    {
        B = "1";
    }
    else
    {
        B = editor->text();
        B.append("1");
    }
    editor->setText(B);
    inputmessage.append("1");
    input->setText(inputmessage);
}

void calctool::b2()
{
    error = false;
    if(B == "0")
    {
        B = "2";
    }
    else
    {
        B = editor->text();
        B.append("2");
    }
    editor->setText(B);
    inputmessage.append("2");
    input->setText(inputmessage);
}

void calctool::b3()
{
    error = false;
    if(B == "0")
    {
        B = "3";
    }
    else
    {
        B = editor->text();
        B.append("3");
    }
    editor->setText(B);
    inputmessage.append("3");
    input->setText(inputmessage);
}

void calctool::b4()
{
    error = false;
    if(B == "0")
    {
        B = "4";
    }
    else
    {
        B = editor->text();
        B.append("4");
    }
    editor->setText(B);
    inputmessage.append("4");
    input->setText(inputmessage);
}

void calctool::b5()
{
    error = false;
    if(B == "0")
    {
        B = "5";
    }
    else
    {
        B = editor->text();
        B.append("5");
    }
    editor->setText(B);
    inputmessage.append("5");
    input->setText(inputmessage);
}

void calctool::b6()
{
    error = false;
    if(B == "0")
    {
        B = "6";
    }
    else
    {
        B = editor->text();
        B.append("6");
    }
    editor->setText(B);
    inputmessage.append("6");
    input->setText(inputmessage);
}

void calctool::b7()
{
    error = false;
    if(B == "0")
    {
        B = "7";
    }
    else
    {
        B = editor->text();
        B.append("7");
    }
    editor->setText(B);
    inputmessage.append("7");
    input->setText(inputmessage);
}

void calctool::b8()
{
    error = false;
    if(B == "0")
    {
        B = "8";
    }
    else
    {
        B = editor->text();
        B.append("8");
    }
    editor->setText(B);
    inputmessage.append("8");
    input->setText(inputmessage);
}

void calctool::b9()
{
    error = false;
    if(B == "0")
    {
        B = "9";
    }
    else
    {
        B = editor->text();
        B.append("9");
    }
    editor->setText(B);
    inputmessage.append("9");
    input->setText(inputmessage);
}

void calctool::bdot()
{
    error = false;

    if (!editor->text().contains("."))
    {
        if(B == "0")
            B.append(".");
        else
        {
            B=editor->text();
            B.append(".");
        }
        inputmessage.append(".");
    editor->setText(B);
    }
    input->setText(inputmessage);
}

void calctool::badd()
{
    if (error == true)
    {
        QMessageBox::warning(this, codec->toUnicode("lianxushuru(+-*/)"),
                             codec->toUnicode("illegal！Please try again"));
    }
    else
    {
        inputmessage.append("+");
        error = true;

        if (c != '+')
        {
            B = editor->text();
        }
        double n, m;
        if (c == ' ')
        {
            B = editor->text();
            A = B;
            B = "0";
            c = '+';
        }
        else
        {
            n = A.toDouble();
            m = B.toDouble();
            if (c == '+')
                n = n + m;
            if (c == '-')
                n = n - m;
            if (c == '*')
                n = n * m;
            if (c == '/')
                n = n / m;
            A = QString::number(n, 'f', 4);
            B = "0";
            c = '+';
            editor->setText(A);
         }
        input->setText(inputmessage);
    }
}

void calctool::bsub()
{
    if (error == true)
    {
        QMessageBox::warning(this, codec->toUnicode("lianxushuru(+-*/)"),
                             codec->toUnicode("illegal！Please try again"));
    }
    else
    {
        inputmessage.append("-");
        error = true;
        if (c != '-')
        {
            B = editor->text();
        }
        double n, m;
        if ( c == ' ')
        {
            A = B;
            B = "0";
            c = '-';
        }
        else
        {
            n = A.toDouble();
            m = B.toDouble();
            if (c == '+')
                n = n + m;
            if (c == '-')
                n = n - m;
            if (c == '*')
                n = n * m;
            if (c == '/')
                n = n / m;
            A = QString::number(n, 'f', 4);
            B = "0";
            c = '-';
            editor->setText(A);
        }
        input->setText(inputmessage);
    }
}

void calctool::bdiv()
{
    if (error == true)
    {
        QMessageBox::warning(this, codec->toUnicode("lianxushuru(+-*/)"),
                             codec->toUnicode("illegal！Please try again"));
    }
    else
    {
        inputmessage.append("/");
        error = true;
        if (c != '/')
        {
            B = editor->text();
        }
        double n, m;
        if (c == ' ')
        {
            A = B;
            B = "0";
            c = '/';
        }
        else
        {
            n = A.toDouble();
            m = B.toDouble();
            if (c == '+')
                n = n + m;
            if (c == '-')
                n = n - m;
            if (c == '*')
            n = n * m;
            if (c == '/')
                n = n / m;
            A = QString::number(n, 'f', 4);
            B = "0";
            c = '/';
            editor->setText(A);
        }
        input->setText(inputmessage);
    }
}


void calctool::bmul()
{
    if (error == true)
    {
        QMessageBox::warning(this, codec->toUnicode("lianxushuru(+-*/)"),
                             codec->toUnicode("illegal！Please try again"));
    }
    else
    {
        inputmessage.append("*");
        error = true;
        if(c != '*')
        {
            B = editor->text();
        }
        double n, m;
        if (c == ' ')
        {
            A = B;
            B = "0";
            c = '*';
        }
        else
        {
            n = A.toDouble();
            m = B.toDouble();
            if (c == '+')
                n = n + m;
            if (c == '-')
                n = n - m;
            if (c == '*')
                n = n * m;
            if (c == '/')
                n = n / m;
            A = QString::number(n, 'f', 4);
            B = "0";
            c = '*';
            editor->setText(A);
        }
        input->setText(inputmessage);
    }
}

void calctool::bequ()
{
    if (error == true)
    {
        QMessageBox::warning(this, codec->toUnicode("lianxushuru(+-*/)"),
                             codec->toUnicode("illegal！Please try again"));
    }
    else
    {
        inputmessage.append("=");
        error = false;
        if (c != '=')
        {
            B = editor->text();
        }
        double n, m;
        if (c == ' ')
        {
            A = B;
            B = "0";
            c = '=';
        }
        else
        {
            n = A.toDouble();
            m = B.toDouble();
            if (c == '+')
                n = n + m;
            if (c == '-')
                n = n - m;
            if (c == '*')
                n = n * m;
            if (c == '/')
                n = n / m;
            A = QString::number(n, 'f', 4);
            inputmessage = A;
            B = "0";
            c = ' ';
            editor->setText(A);
        }
        input->setText(inputmessage);
    }
}

void calctool::bant()
{
    if (error == true)
    {
        QMessageBox::warning(this, codec->toUnicode("lianxushuru(+-*/)"),
                             codec->toUnicode("illegal！Please try again"));
    }
    else
    {
      //  error = true;

        if (c != '^')
        {
            B = editor->text();
        }
        double n, m;
        if (c == ' ')
        {
            B = editor->text();
            A = B;
            n = A.toDouble();

            A = QString::number(1/n, 'f', 4);
            B = "0";
            editor->setText(A);
        }
        else
        {
            B = editor->text();
            n = A.toDouble();
            m = B.toDouble();
            if (c == '+')
                n = n + m;
            if (c == '-')
                n = n - m;
            if (c == '*')
                n = n * m;
            if (c == '/')
                n = n / m;
            A = QString::number(n, 'f', 4);
            B = "0";
            c = '^';
            editor->setText(A);
         }
        input->setText(inputmessage);
    }
}

void calctool::bclr()
{
    if (error == true)
    {
        QMessageBox::warning(this, codec->toUnicode("lianxushuru(+-*/)"),
                             codec->toUnicode("illegal！Please try again"));
    }
    else
    {
  //      error = true;

        if (c != '^')
        {
            B = editor->text();
        }
        double n, m;
        if (c == ' ')
        {
            B = editor->text();
            A = B;
            n = A.toDouble();
            m = sqrt(n);
            A = QString::number(m, 'f', 4);
            B = "0";
            editor->setText(A);
            c == '^';
        }
        else
        {
            n = A.toDouble();
            m = B.toDouble();
            if (c == '+')
                n = n + m;
            if (c == '-')
                n = n - m;
            if (c == '*')
                n = n * m;
            if (c == '/')
                n = n / m;
            A = QString::number(n, 'f', 4);
            B = "0";
            c = '^';
            editor->setText(A);
         }
        input->setText(inputmessage);
    }
}

void calctool::bce()
{
    A="0";
    B="0";
    c=' ';
    editor->setText(B);
    inputmessage = "";
    input->setText(inputmessage);
}

void calctool::bbks()
{
    editor->backspace();
}

void calctool::bsqr()
{
    double m;
    B = editor->text();
    m = B.toDouble();
    m = m * m;
    A = QString::number(m, 'f', 4);
    B = A;
    editor->setText(B);
    inputmessage.append("sqr)");
    input->setText(inputmessage);
}

void calctool::brec()
{
    double m;
    B = editor->text();
    m = B.toDouble();
    m = 1 / m;
    A = QString::number(m, 'f', 4);
    B = A;
    editor->setText(B);
    inputmessage.append("rec)");
    input->setText(inputmessage);
}

void calctool::bper()
{
    double m;
    B = editor->text();
    m = B.toDouble();
    m = m / 100;
    A = QString::number(m, 'f', 4);
    B = A;
    editor->setText(B);
    inputmessage.append("per)");
    input->setText(inputmessage);
}

//�˵�ʹ�òۺ���
void calctool::mcopy()
{

}

void calctool::mpaste()
{

}

void calctool::mundo()
{

}

void calctool::mredo()
{

}

void calctool::setType()
{

}

void calctool::mcontent()
{
    QTextBrowser *helpbrowser = new QTextBrowser(0);
    helpbrowser->setSource(QUrl::fromLocalFile(":/source/assistant.html"));
    helpbrowser->showFullScreen();
}

void calctool::mabout()
{
    QMessageBox::about(this, tr("About Calctool"),
            tr("<h2>Calctool V5.30.2</h2>"
               "<p>Copyright &copy; 2010 Software Inc."
               "<p>Just a tool"));
}

void calctool::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Backspace:
        bbks();
        break;
    case Qt::Key_0:
        b0();
        break;
    case Qt::Key_1:
        b1();
        break;
    case Qt::Key_2:
        b2();
        break;
    case Qt::Key_3:
        b3();
        break;
    case Qt::Key_4:
        b4();
        break;
    case Qt::Key_5:
        b5();
        break;
    case Qt::Key_6:
        b6();
        break;
    case Qt::Key_7:
        b7();
        break;
    case Qt::Key_8:
        b8();
        break;
    case Qt::Key_9:
        b9();
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Equal:
        bequ();
        break;
    case Qt::Key_Minus:
        bsub();
        break;
    case Qt::Key_Plus:
        badd();
        break;
    case Qt::Key_Asterisk:
        bmul();
        break;
    case Qt::Key_Slash:
        bdiv();
        break;
    case Qt::Key_Period:
        bdot();
        break;
    }
}
