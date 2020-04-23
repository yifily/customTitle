#ifndef WIDGET_H
#define WIDGET_H

#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>
#include <qboxlayout.h>



class CustomTitle : public QFrame
{
    Q_OBJECT

public:
    explicit CustomTitle(QWidget *parent = nullptr);
    ~CustomTitle();
signals:
    // 点击搜索文件时显示
   void OnSearchText(QString string);


public:
    /*--------------------窗口风格设置--------------------------*/
    // 风格属性
    enum SkinStyle{
        Skin_None = 0,
        Skin_Drak = 1,
        Skin_Blue = 2,
        Skin_Purple = 3,
        Skin_Yellow = 4,
        Skin_Girl= 5
    };
    const QString m_Skin_Names[6]={"默认","黑色","蓝色","紫色","黄色","少女"};

    // 设置皮肤风格
    void setSkinStyle(SkinStyle style);
public  slots:
    void onMenuAction(QAction* pAction);

//  系统菜单
private:
    // 系统托盘
    QSystemTrayIcon * m_SysTrayIcon;
    // 系统托盘菜单
    QMenu * m_SystemTrayMenu;
public:
    // 设置系统托盘图标
    void SetSystemTrayMenu(QIcon &icon);
    // 获取系统图盘
    QSystemTrayIcon * GetSystemTray();
    // 初始化托盘菜单
    void InitSysTrayIcon();

protected:
    // 鼠标按下
    void mousePressEvent(QMouseEvent *event);
    // 鼠标移动
    void mouseMoveEvent(QMouseEvent *event);
    // 鼠标放开
    void mouseReleaseEvent(QMouseEvent *event);
    // 左键是否按下标志
    bool m_LeftDownFlags;
    // 鼠标点击位置离窗口位置的偏移
    QPoint m_ClickOffset ;


    void initGuiLayout();
    void initGuiStyle();
    void bindGuiEvent();
    void SearchEditCreate();

public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *la_icon;
    QLabel *la_title;
    QSpacerItem *horizontalSpacer;
    QLineEdit *edt_searchText;
    QToolButton *btn_skin;
    QToolButton *btn_hide;
    QToolButton *btn_exit;


};

#endif // WIDGET_H
