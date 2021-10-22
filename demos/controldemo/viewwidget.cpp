#include "viewwidget.h"

#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFile>
#include <QButtonGroup>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include "QtNavListView.h"
#include "QtNavTreeView.h"

ViewWidget::ViewWidget(QWidget *parent)
    : QWidget(parent)
{
    createWindow();
}

void ViewWidget::createWindow()
{
    m_pTabWidget = new QTabWidget();

    createNavButtonView();
    createNavTreeView();
    createNavTreeView();
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_pTabWidget);
    setLayout(mainLayout);
}
void ViewWidget::createNavButtonView()
{
   //IO口状态
    QHBoxLayout *hboxLayout_input = new QHBoxLayout();
    QHBoxLayout *hboxLayout_output = new QHBoxLayout();
    QGroupBox *groupBox_input = new QGroupBox("开关量输入状态");
    QGroupBox *groupBox_output = new QGroupBox("开关量输出状态");
    for(int i=0;i<8;i++)
    {
        inputCB[i]=new QCheckBox(this);
        inputCB[i]->setText((QString().sprintf("%d", i+1)));
        inputCB[i]->setFont(QFont(tr("Consolas"),12));
        hboxLayout_input->addWidget(inputCB[i]);
     }
    for(int i=0;i<8;i++)
    {
        outputCB[i]=new QCheckBox(this);
        outputCB[i]->setText((QString().sprintf("%d", i+1)));
        outputCB[i]->setFont(QFont(tr("Consolas"),12));
        hboxLayout_output->addWidget(outputCB[i]);
     }
    groupBox_input->setLayout(hboxLayout_input);
    groupBox_output->setLayout(hboxLayout_output);
    //读取按钮
    QHBoxLayout *hboxLayout_Handle = new QHBoxLayout();
    QPushButton *refreshDataBtn = new QPushButton("读出");
    refreshDataBtn->setFont(QFont(tr("Consolas"),14));
    refreshDataBtn->resize(100,100);
    connect(refreshDataBtn, SIGNAL(clicked()), this, SLOT(readMcp23017()));
    hboxLayout_Handle->addWidget(refreshDataBtn);
    QPushButton *writeDataBtn = new QPushButton("写入");
    writeDataBtn->setFont(QFont(tr("Consolas"),14));
    connect(writeDataBtn, SIGNAL(clicked()), this, SLOT(writeMcp23017()));
    hboxLayout_Handle->addWidget(writeDataBtn);
    QPushButton *clearLogBtn = new QPushButton("清除日志");
    writeDataBtn->setFont(QFont(tr("Consolas"),14));
    connect(clearLogBtn, SIGNAL(clicked()), this, SLOT(clearLog()));
    hboxLayout_Handle->addWidget(clearLogBtn);
    hboxLayout_Handle->setGeometry(QRect(200, 200, 300, 300));
    QVBoxLayout *vboxLayout_Left = new QVBoxLayout();
    vboxLayout_Left->addWidget(groupBox_input);
    vboxLayout_Left->addWidget(groupBox_output);
    vboxLayout_Left->addLayout(hboxLayout_Handle);


    m_logView= new QListView();
    logModel=new QStringListModel();
    m_logView->setModel(logModel);
    m_logView->setFixedSize(300,600);

    QWidget *w = new QWidget();
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    hboxLayout->addItem(vboxLayout_Left);
    hboxLayout->addWidget(m_logView);

    w->setLayout(hboxLayout);

    m_pTabWidget->addTab(w, tr("MCP23017 测试"));
}
void ViewWidget::createNavListView()
{
    QtNavListView *listView1 = new QtNavListView(this);

    QtNavListView *listView2 = new QtNavListView(this);
    listView2->setIconBgcVisible(false);
    listView2->setLineColor(QColor(255, 255, 255));
    listView2->setBackColor(QColor(238, 238, 238), QColor(255, 69, 0), QColor(255, 160, 122));
    listView2->setTextColor(QColor(10, 10, 10), QColor(254, 255, 239), QColor(10, 10, 10));

    QtNavListView *listView3 = new QtNavListView(this);
    listView3->setIconBgcVisible(false);
    listView3->setLineColor(QColor(32, 53, 74));
    listView3->setBackColor(QColor(52, 73, 94), QColor(24, 189, 155), QColor(24, 189, 155, 150));
    listView3->setTextColor(QColor(254, 255, 255), QColor(252, 252, 252), QColor(0, 0, 0));

    listView1->setInfoVisible(false);
    listView2->setInfoVisible(false);
    listView3->setInfoVisible(true);

    listView3->setLineVisible(false);
    listView3->setIconStyle(QtNavListView::Triangle);

    listView1->readData(":/view/config.xml");
    listView2->readData(":/view/config.xml");
    listView3->readData(":/view/config.xml");

    QWidget *w = new QWidget();
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    hboxLayout->addWidget(listView1);
    hboxLayout->addWidget(listView2);
    hboxLayout->addWidget(listView3);
    w->setLayout(hboxLayout);

    m_pTabWidget->addTab(w, tr("ListView"));
}

void ViewWidget::createNavTreeView()
{
    QtNavTreeView *treeView = new QtNavTreeView(this);

    QString parentText(tr("QtCanpool"));
    treeView->addItem(parentText);
    treeView->setItemInfo(parentText, tr("Qt"));
    parentText = QString(tr("demos"));
    treeView->addItem(parentText);
    treeView->addItem(parentText, tr("controldemo"));
    treeView->addItem(parentText, tr("fancydemo"));
    treeView->addItem(parentText, tr("litedemo"));
    treeView->addItem(parentText, tr("qtitanribbon"));
    treeView->addItem(parentText, tr("qtoffice"));
    treeView->addItem(parentText, tr("qtqrcode"));
    parentText = QString(tr("doc"));
    treeView->addItem(parentText);
    treeView->addItem(parentText, tr("pics"));
    treeView->addItem(parentText, tr("help"));
    parentText = QString(tr("projects"));
    treeView->addItem(parentText);
    treeView->addItem(parentText, tr("template"));
    treeView->addItem(parentText, tr("qtcreator"));
    parentText = QString(tr("share"));
    treeView->addItem(parentText);
    parentText = QString(tr("src"));
    treeView->addItem(parentText);
    treeView->addItem(parentText, tr("libs"));
    treeView->addItem(parentText, tr("modules"));
    treeView->addItem(parentText, tr("plugins"));
    treeView->addItem(parentText, tr("shared"));
    treeView->addItem(parentText, tr("tools"));

    QWidget *w = new QWidget();
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    hboxLayout->addWidget(treeView);
    w->setLayout(hboxLayout);

    m_pTabWidget->addTab(w, tr("TreeView"));
}
void ViewWidget::clearLog()
{
    logModel->removeRows(0,logModel->rowCount());
}
void ViewWidget::readMcp23017()
{
    //打开驱动设备
    int fd;
        char *filename;
        char databuf[2];
         int ret = 0;
        fd = open("/dev/mcp23017", O_RDWR);
        if(fd < 0) {

            log(QString().sprintf("驱动打开失败 %s", "/dev/mcp23017"));
            return ;
        }else{
//            log(QString().sprintf("驱动打开成功 %s", "/dev/mcp23017"));
        }

            ret = read(fd, databuf, sizeof(databuf));

            if(ret == 0) { 			/* 数据读取成功 */
                updateLeds(databuf);
                log("数据读取成功 ");
            }
        ::close(fd);	/* 关闭文件 */
}
void ViewWidget::log(QString info)
{
    int row=m_logView->currentIndex().row();
    row=(row == -1?0:row);
    logModel->insertRows(row, 1);
    logModel->setData(logModel->index(row), info);

}
void ViewWidget::writeMcp23017()
{
    //打开驱动设备
    int fd;
        char *filename;
        char databuf[2];
         int ret = 0;
        fd = open("/dev/mcp23017", O_RDWR);
        if(fd < 0) {
            log(QString().sprintf("驱动打开失败 %s", "/dev/mcp23017"));
            return ;
        }else{
//            log(QString().sprintf("驱动打开成功 %s", "/dev/mcp23017"));
        }
            updateLeds(databuf,true);
            ret = write(fd, databuf, 1);

            if(ret == 0) {
                log(QString().sprintf("数据 0X%02x 写入成功", databuf[0]));
            }
        ::close(fd);	/* 关闭文件 */
}
void ViewWidget::updateLeds(char * buf,bool isRead)
{

    if(isRead)
    {
        buf[0]=0;
       for(int i=0;i<8;i++)
        {
            if(outputCB[i]->isChecked()==true)
            {
                buf[0]|=(1<<i);
            }
            else
            {
                buf[0]&=~(1<<i);
            }

        }
    }else
    {
        log(QString().sprintf("IOA = %x IOB = %x",  buf[0], buf[1]));
        for(int i=0;i<8;i++)
        {
            inputCB[i]->setChecked((buf[0]>>i&0x01) == 1?true:false);
        }
        for(int i=0;i<8;i++)
        {
            outputCB[i]->setChecked((buf[1]>>i&0x01) == 1?true:false);
        }
    }

}
