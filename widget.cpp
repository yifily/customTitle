#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QIcon>
#include <QPushButton>
#include <QMenu>
#include <QMouseEvent>

CustomTitle::CustomTitle(QWidget *parent) :
    QFrame(parent)
{
    initGuiLayout();
    initGuiStyle();
    bindGuiEvent();
    SearchEditCreate();
}

CustomTitle::~CustomTitle()
{
}

void CustomTitle::setSkinStyle(CustomTitle::SkinStyle style)
{
    QString strStyle;

    switch(style)
    {
    // 黄色
    case Skin_Yellow:
        strStyle = QString("*{background-color: rgba(250,200,0, 200);}");
        break;
        // 渐变
    case Skin_Girl:
        // #fccb90 → #d57eeb
        strStyle = QString("*{background:qlineargradient(spread:pad,x1:1,y1:0,x2:0,y2:0,stop:0 #fccb90,stop:1 #d57eeb)}");
        break;
    case Skin_None:
        // 无风格
        break;
    case Skin_Purple:
        // 紫色风格
        strStyle = QString("*{background-color: rgba(196, 151, 255, 200);}");
        break;
        // 黑色风格
    case Skin_Drak:
        strStyle = "*{background-color: rgba(133, 133, 133, 200);}";
        break;
        // 蓝色风格
    case Skin_Blue:
        strStyle = "*{background-color: rgba(125,184,255, 200);}";
        break;
    }
    // 设置风格
    qApp->setStyleSheet(strStyle);
    return;
}

void CustomTitle::onMenuAction(QAction *pAction)
{
    int tabIndex = pAction->data().toInt();
    setSkinStyle((CustomTitle::SkinStyle)tabIndex);
}
// 设置系统托盘图标

void CustomTitle::SetSystemTrayMenu(QIcon &icon)
{
    m_SysTrayIcon->setIcon(icon);
}
// 获取系统图盘
QSystemTrayIcon *CustomTitle::GetSystemTray()
{
    return m_SysTrayIcon;
}

void CustomTitle::InitSysTrayIcon()
{
    // 初始化化托盘菜单
    m_SystemTrayMenu = new QMenu(this);
    // 添加菜单
    QAction *min = m_SystemTrayMenu->addAction(tr("还原"));
    QAction *quit = m_SystemTrayMenu->addAction(tr("结束"));
    // 还原
    connect(min,&QAction::triggered,[=](){
        this->showNormal();
        m_SysTrayIcon->hide();
    });
    // 退出
    connect(quit,&QAction::triggered,[=](){
        exit(0);
    });

}

void CustomTitle::initGuiLayout()
{



    this->resize(461, 28);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(0);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    la_icon = new QLabel(this);
    la_icon->setObjectName(QString::fromUtf8("la_icon"));

    horizontalLayout_2->addWidget(la_icon);

    la_title = new QLabel(this);
    la_title->setObjectName(QString::fromUtf8("la_title"));
    la_title->setMinimumSize(QSize(100, 0));

    horizontalLayout_2->addWidget(la_title);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer);

    edt_searchText = new QLineEdit(this);
    edt_searchText->setObjectName(QString::fromUtf8("edt_searchText"));

    horizontalLayout_2->addWidget(edt_searchText);

    btn_skin = new QToolButton(this);
    btn_skin->setObjectName(QString::fromUtf8("btn_skin"));

    horizontalLayout_2->addWidget(btn_skin);

    btn_hide = new QToolButton(this);
    btn_hide->setObjectName(QString::fromUtf8("btn_hide"));

    horizontalLayout_2->addWidget(btn_hide);

    btn_exit = new QToolButton(this);
    btn_exit->setObjectName(QString::fromUtf8("btn_exit"));

    horizontalLayout_2->addWidget(btn_exit);
    verticalLayout->addLayout(horizontalLayout_2);
    this->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
    la_icon->setText(QString());
    la_title->setText(QString());
    btn_skin->setText(QString());
    btn_hide->setText(QString());
    btn_exit->setText(QString());

}

void CustomTitle::initGuiStyle()
{
    this->setStyleSheet("CustomTitle {border-width:2px;border-style:solid;border-color:#ff5500}");
    setWindowFlags(windowFlags()| Qt::FramelessWindowHint);
    la_icon->setStyleSheet("QLabel {background:transparent;}");
    la_title->setStyleSheet("QLabel {background:transparent;}");
    la_icon->setPixmap(QPixmap(":/image/logoko2.png").scaled(22,22));
    la_title->setText("KiteQuit");
    btn_skin->setStyleSheet(""
                                "QToolButton{border-image:url(:/image/shirt2.ico); background:transparent;}"
                                "QToolButton:hover{border-image:url(:/image/shirt1.ico)}"
                                "QToolButton:pressed{border-image:url(:/image/shirt3.ico)}"
                                "QToolButton{border-color:#ff5500}");
    btn_hide->setStyleSheet(""
                                "QToolButton{border-image:url(:/image/hide1.png); background:transparent;}"
                                "QToolButton:hover{border-image:url(:/image/hide2.png)}"
                                "QToolButton:pressed{border-image:url(:/image/hide3.png)}"
                                "QToolButton{border-color:#ff5500}");

    btn_exit->setStyleSheet(""
                                "QToolButton{border-image:url(:/image/close1.png); background:transparent;}"
                                "QToolButton:hover{border-image:url(:/image/close2.png)}"
                                "QToolButton:pressed{border-image:url(:/image/close3.png)}"
                                "QToolButton{border-color:#ff5500}");

}

void CustomTitle::bindGuiEvent()
{
    // - 事件
    // 1.搜索事件

    // 2.换皮肤
    // 2.1 加入菜单
    btn_skin->setMenu(new QMenu(btn_skin));
    btn_skin->menu()->setStyleSheet("QMenu { menu-scrollable: 1; }"); //Makes the Menu scrollable instead of multi-columns
    connect( btn_skin, &QPushButton::clicked,[=](){

        QMenu* pMenu = btn_skin->menu();
        QList<QAction*> lActions;
        pMenu->clear();

        for( int i = 0; i < 6; ++i )
        {
            QAction* pAct = new QAction(QString("%1").arg(m_Skin_Names[i]), pMenu);
            pAct->setData(i);

            lActions.append(pAct);
        }

        pMenu->addActions(lActions);
        connect(pMenu, SIGNAL(triggered(QAction*)), this, SLOT(onMenuAction(QAction*)));

        if( !pMenu->isEmpty() ) {
            btn_skin->showMenu();
        }
    });

    // 3.隐藏托盘
    InitSysTrayIcon();
    // 隐藏
    connect(btn_hide,&QToolButton::clicked,[=](){
        this->hide();
        //新建QSystemTrayIcon对象
        m_SysTrayIcon = new QSystemTrayIcon(this);
        // 添加系统图标
        m_SysTrayIcon->setIcon(QIcon(":/image/logoko2.png"));
        // 提示
        m_SysTrayIcon->setToolTip(tr("KiteQuit"));
        m_SysTrayIcon->setContextMenu(m_SystemTrayMenu);
        // 显示菜单
        m_SysTrayIcon->show();

    });

    // 4. 结束进程
    connect(btn_exit,&QToolButton::clicked,[=](){
            exit(0);
    });
}

void CustomTitle::SearchEditCreate()
{
    // 搜索框
    QPushButton *btn_search = new QPushButton(this);
    btn_search->setCursor(Qt::PointingHandCursor);
    btn_search->setFixedSize(22, 22);
    btn_search->setToolTip("搜索");
    btn_search->setStyleSheet(
                "QPushButton{border-image:url(:/image/search_1.png); background:transparent;}"
                "QPushButton:hover{border-image:url(:/image/search_2.png)}"
                "QPushButton:pressed{border-image:url(:/image/search_3.png)}");
    QHBoxLayout *pSearchLayout = new QHBoxLayout();
    pSearchLayout->addStretch();
    pSearchLayout->addWidget(btn_search);
    pSearchLayout->setSpacing(0);
    pSearchLayout->setContentsMargins(0, 0, 0, 0);
    edt_searchText->setLayout(pSearchLayout);

    // 点击按钮时发送搜索信号
    connect( btn_search, &QPushButton::clicked,[=](){
        QString SearchStr = edt_searchText->text();
        emit OnSearchText(SearchStr);
    });
}


void CustomTitle::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_LeftDownFlags = true;
        m_ClickOffset = event->pos();
    }
}

void CustomTitle::mouseReleaseEvent(QMouseEvent *)
{
    if(m_LeftDownFlags == true)
    {
        m_LeftDownFlags = false;
    }


}


void CustomTitle::mouseMoveEvent(QMouseEvent *event)
{
    // 无边框移动窗口
    if(m_LeftDownFlags == true)
    {
        int x = event->globalX() - m_ClickOffset.x();
        int y = event->globalY()- m_ClickOffset.y() ;
        if(this->topLevelWidget())
        {
            // 跟这窗口移动
            this->move(x, y);
        }
        else{
            QWidget *Par = this->parentWidget();
            Par->move(x, y);
        }

    }
}


