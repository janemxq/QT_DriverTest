#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QListView>
#include <QStringListModel>
#include "qtextedit.h"
#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "sys/ioctl.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"
#include <poll.h>
#include <sys/select.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
class QTabWidget;

class ViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewWidget(QWidget *parent = nullptr);

private:
    void createWindow();
    void createNavListView();
    void createNavTreeView();
    void createNavButtonView();

private:
    QTabWidget *m_pTabWidget;
    QListView *m_logView;
    //信息模型
     QStringListModel *logModel;
    //开关量输入
    QCheckBox *inputCB[8];
    //开关量输出
    QCheckBox *outputCB[8];
private slots:
    void clearLog();
    void readMcp23017();
    void writeMcp23017();
    void updateLeds(char * buf,bool isRead=false);
    void log(QString info);
};

#endif // VIEWWIDGET_H
