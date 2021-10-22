/***************************************************************************
 **
 **  Copyright (C) 2018-2020 MaMinJie <canpool@163.com>
 **  Contact: https://github.com/canpool
 **           https://gitee.com/icanpool
 **
 **  GNU Lesser General Public License Usage
 **  Alternatively, this file may be used under the terms of the GNU Lesser
 **  General Public License version 3 as published by the Free Software
 **  Foundation and appearing in the file LICENSE.LGPL3 included in the
 **  packaging of this file. Please review the following information to
 **  ensure the GNU Lesser General Public License version 3 requirements
 **  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
 **
 **  GNU General Public License Usage
 **  Alternatively, this file may be used under the terms of the GNU
 **  General Public License version 2.0 or (at your option) the GNU General
 **  Public license version 3 or any later version approved by the KDE Free
 **  Qt Foundation. The licenses are as published by the Free Software
 **  Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
 **  included in the packaging of this file. Please review the following
 **  information to ensure the GNU General Public License requirements will
 **  be met: https://www.gnu.org/licenses/gpl-2.0.html and
 **  https://www.gnu.org/licenses/gpl-3.0.html.
 **
****************************************************************************/
/*******************************************************************************************
 *
 *  TabBar + Center
 *
 *  -------------------------------------------------------------------------|
 *  |   |                               Top                                  |
 *  |   |--------------------------------------------------------------------|
 *  |   |           |                                           |            |
 *  |   |           |                                           |            |
 *  |   |           |                                           |            |
 *  |   |           |                                           |            |
 *  |   |           |                                           |            |
 *  | M |           |                                           |            |
 *  | O |           |                                           |            |
 *  | D |           |                  Stack                    |   Right    |
 *  | E |           |                                           |            |
 *  |   |           |                                           |            |
 *  | B |    Left   |                                           |            |
 *  | A |           |                                           |            |
 *  | R |           |                                           |            |
 *  |   |           |                                           |            |
 *  |   |           |                                           |            |
 *  |   |           |--------------------------------------------------------|
 *  |   |           |                                                        |
 *  |   |           |                  Bottom                                |
 *  |   |           |                                                        |
 *  |   |           |                                                        |
 *  |   |--------------------------------------------------------------------|
 *  |   |                           Status Bar                               |
 *  -------------------------------------------------------------------------|
 *
 *****************************************************************************************
 */
#ifndef FANCYTABWIDGET_H
#define FANCYTABWIDGET_H

#include <QWidget>
#include "qcanpool_global.h"

class QStatusBar;
class QSplitter;

QCANPOOL_BEGIN_NAMESPACE

class FancyTabBar;
class FancyTabWidgetPrivate;
class QCANPOOL_SHARED_EXPORT FancyTabWidget : public QWidget
{
    Q_OBJECT
public:
    enum ActionPosition {Front, Middle, Back };
    enum TabType { Mode, Action };
    enum TabStyle {IconOnly, TextOnly, TextBesideIcon, TextUnderIcon};
    enum CornerPosition {Left, Top, Right, Bottom};

    explicit FancyTabWidget(QWidget *parent = nullptr);
    ~FancyTabWidget();

    int addTab(QWidget *widget, const QString &label, bool hasMenu = false);
    int addTab(QWidget *widget, const QIcon& icon, const QString &label, bool hasMenu = false);

    int insertTab(int index, QWidget *widget, const QString &label, bool hasMenu = false);
    int insertTab(int index, QWidget *widget, const QIcon &icon, const QString &label, bool hasMenu = false);

    void removeTab(int index);

    void setTabEnabled(int index, bool enable);
    bool isTabEnabled(int index) const;

    void setTabVisible(int index, bool visible);
    bool isTabVisible(int index) const;

    void setTabToolTip(int index, QString toolTip);
    QString tabToolTip(int index) const;

    void setTabShortcut(int index, const QString &shortcut);

    enum TabPosition { North, South, West, East };
    Q_ENUM(TabPosition)
    TabPosition tabPosition() const;
    void setTabPosition(TabPosition pos);

    int currentIndex() const;
    QStatusBar* statusBar() const;
    FancyTabBar* tabBar() const;

    void setTabStyle(TabType type, TabStyle style);
    void setTabFont(TabType type, QFont &font);
    void setTabSpace(TabType type, int space);
    void setTabIconSize(QSize size);

    int addAction(QAction *action, ActionPosition position = Back);
    void removeAction(QAction *action);
    void setActionStyle(QAction *action, TabStyle style);

    QSplitter *addCornerWidget(QWidget *widget, CornerPosition position);

    void setHoverColor(const QColor &color);
    QColor hoverColor() const;

    void setPressColor(const QColor &color);
    QColor pressColor() const;

    void setTextColor(const QColor &color);
    void setSelectedTextColor(const QColor &color);

    void setBackgroundColor(const QColor &color);

signals:
    void currentChanged(int index);
    void menuTriggered(int index, QPoint pos);

public slots:
    void setCurrentIndex(int index);
    void hideMenu(int index);

private:
    FancyTabWidgetPrivate *d;
};

QCANPOOL_END_NAMESPACE

#endif // FANCYTABWIDGET_H
