/********************************************************************************
** Form generated from reading UI file 'setup.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUP_H
#define UI_SETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_setup
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *spinBox_watch;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpinBox *spinBox_buff;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *setup)
    {
        if (setup->objectName().isEmpty())
            setup->setObjectName(QStringLiteral("setup"));
        setup->resize(400, 300);
        setup->setStyleSheet(QString::fromUtf8("\n"
"/***********************\345\205\250\345\261\200*****************************/\n"
"QWidget\n"
"{\n"
"	background-color:rgb(222, 241, 255);\n"
"	font: 12pt \"\346\245\267\344\275\223\";\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	background-color:#F7FBFD;\n"
"	border-radius:5px;\n"
"}\n"
"\n"
"\n"
"QSpinBox {\n"
"	padding-right:20px;\n"
"	border-radius:5px;\n"
"	background:rgb(222, 241, 255);\n"
"	max-height:40px;\n"
"\n"
"	min-height:40px;\n"
"}\n"
"\n"
"/* \345\220\221\344\270\212\346\214\211\351\222\256 */\n"
"QSpinBox::up-button {\n"
"top:6px;\n"
"right:6px;/*\346\216\247\345\210\266\347\256\255\345\244\264\345\267\246\345\217\263\345\201\217\347\247\273*/\n"
"	width:10px;\n"
"	height: 10px;   \n"
"	border-image:url(:/img/up.svg);\n"
"	border-width:1px;\n"
"}\n"
"\n"
"\n"
"/* \345\220\221\344\270\213\346\214\211\351\222\256 */\n"
"QSpinBox::down-button {\n"
"bottom:6px;\n"
"right:6px;/*\346\216\247\345\210\266\347\256\255\345\244\264\345\267\246\345\217\263\345\201\217\347\247\273*/\n"
"	width:10px;\n"
"	heigh"
                        "t: 10px;   \n"
"	border-image:url(:/img/down.svg);\n"
"	border-width:1px;\n"
"	border-top-width:0;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	max-height:40px;\n"
"	border-radius:10px;\n"
"	min-height:40px;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(setup);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(setup);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        spinBox_watch = new QSpinBox(groupBox);
        spinBox_watch->setObjectName(QStringLiteral("spinBox_watch"));

        horizontalLayout_2->addWidget(spinBox_watch);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBox_buff = new QSpinBox(groupBox);
        spinBox_buff->setObjectName(QStringLiteral("spinBox_buff"));

        horizontalLayout->addWidget(spinBox_buff);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(setup);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(setup);
        QObject::connect(buttonBox, SIGNAL(accepted()), setup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), setup, SLOT(reject()));

        QMetaObject::connectSlotsByName(setup);
    } // setupUi

    void retranslateUi(QDialog *setup)
    {
        setup->setWindowTitle(QApplication::translate("setup", "Dialog", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("setup", "\346\263\242\345\275\242\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("setup", "\350\247\206\347\252\227\345\244\247\345\260\217", Q_NULLPTR));
        label_2->setText(QApplication::translate("setup", "\347\274\223\345\255\230\345\244\247\345\260\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class setup: public Ui_setup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUP_H
