#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidget>
#include <QFileDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString filename;

private: /*functions */
    Ui::MainWindow *ui;

private slots: /* Bottoni da schiacciare*/




    void on_LoginButton_clicked();
    void on_DatiPersiButton_clicked();
    void on_IscrivitiButton_clicked();

    bool isValidCredential(QString name);
    bool noDuplicates(QString login);
    void adminLogin();
    void on_CsvChooser_clicked();
};

#endif // MAINWINDOW_H
