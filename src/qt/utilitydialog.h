// Copyright (c) 2011-2017 The SteepCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef STEEPCOIN_QT_UTILITYDIALOG_H
#define STEEPCOIN_QT_UTILITYDIALOG_H

#include <QDialog>
#include <QObject>

class SteepCoinGUI;

namespace Ui {
    class HelpMessageDialog;
}

/** "Help message" dialog box */
class HelpMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpMessageDialog(QWidget *parent, bool about);
    ~HelpMessageDialog();

    void printToConsole();
    void showOrPrint();

private:
    Ui::HelpMessageDialog *ui;
    QString text;

private Q_SLOTS:
    void on_okButton_accepted();
};


/** "Shutdown" window */
class ShutdownWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ShutdownWindow(QWidget *parent=0, Qt::WindowFlags f=0);
    static QWidget *showShutdownWindow(SteepCoinGUI *window);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // STEEPCOIN_QT_UTILITYDIALOG_H
