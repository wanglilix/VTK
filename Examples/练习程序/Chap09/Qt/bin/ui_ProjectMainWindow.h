/********************************************************************************
** Form generated from reading UI file 'ProjectMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTMAINWINDOW_H
#define UI_PROJECTMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_ProjectMainWindow
{
public:
    QAction *actionLoadImage;
    QAction *m_OpenAction;
    QWidget *m_CentralWidget;
    QVBoxLayout *verticalLayout;
    QVTKWidget *m_QVTKWidget;
    QMenuBar *menubar;
    QMenu *m_MenuFile;
    QStatusBar *m_StatusBar;

    void setupUi(QMainWindow *ProjectMainWindow)
    {
        if (ProjectMainWindow->objectName().isEmpty())
            ProjectMainWindow->setObjectName(QString::fromUtf8("ProjectMainWindow"));
        ProjectMainWindow->resize(595, 482);
        actionLoadImage = new QAction(ProjectMainWindow);
        actionLoadImage->setObjectName(QString::fromUtf8("actionLoadImage"));
        m_OpenAction = new QAction(ProjectMainWindow);
        m_OpenAction->setObjectName(QString::fromUtf8("m_OpenAction"));
        m_CentralWidget = new QWidget(ProjectMainWindow);
        m_CentralWidget->setObjectName(QString::fromUtf8("m_CentralWidget"));
        verticalLayout = new QVBoxLayout(m_CentralWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_QVTKWidget = new QVTKWidget(m_CentralWidget);
        m_QVTKWidget->setObjectName(QString::fromUtf8("m_QVTKWidget"));

        verticalLayout->addWidget(m_QVTKWidget);

        ProjectMainWindow->setCentralWidget(m_CentralWidget);
        menubar = new QMenuBar(ProjectMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 595, 23));
        m_MenuFile = new QMenu(menubar);
        m_MenuFile->setObjectName(QString::fromUtf8("m_MenuFile"));
        ProjectMainWindow->setMenuBar(menubar);
        m_StatusBar = new QStatusBar(ProjectMainWindow);
        m_StatusBar->setObjectName(QString::fromUtf8("m_StatusBar"));
        ProjectMainWindow->setStatusBar(m_StatusBar);

        menubar->addAction(m_MenuFile->menuAction());
        m_MenuFile->addAction(m_OpenAction);

        retranslateUi(ProjectMainWindow);

        QMetaObject::connectSlotsByName(ProjectMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ProjectMainWindow)
    {
        ProjectMainWindow->setWindowTitle(QApplication::translate("ProjectMainWindow", "9-1 \350\257\273\345\217\226JPG\345\233\276\345\203\217", 0, QApplication::UnicodeUTF8));
        actionLoadImage->setText(QApplication::translate("ProjectMainWindow", "\346\211\223\345\274\200\345\233\276\345\203\217", 0, QApplication::UnicodeUTF8));
        m_OpenAction->setText(QApplication::translate("ProjectMainWindow", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        m_MenuFile->setTitle(QApplication::translate("ProjectMainWindow", "\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProjectMainWindow: public Ui_ProjectMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTMAINWINDOW_H
