#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    filename = "data.csv";
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoginButton_clicked()
{
    QString loginCredentials;
    QString password;
    //Get inserted credentials
    loginCredentials = ui->UserLogin->text();
    password = ui->PasswordLogin->text();
    // qDebug()<<loginCredentials;
    // qDebug()<<password;

    if (isValidCredential(loginCredentials)) {
        if (loginCredentials == "admin@pas.com" && password == "admin") {
            //qDebug()<<"Bentornato, Admin";
            adminLogin();
        }
        else { //Search for the user
            //READ BEGIN
            bool logged = false;

            QFile file(filename);
            if (file.open(QIODevice::ReadOnly)) {
                QTextStream in(&file);
                while (!in.atEnd() && !logged) {
                    QStringList data;
                    QString line = file.readLine();
                    int pos = line.lastIndexOf(QChar('\r'));
                    data.append(line.left(pos).split(','));
                    // qDebug() << data;
                    if (data[4] == loginCredentials) {
                        if (data[5] == password) {
                            qDebug() << "Bentornato" << data[0] << "!";
                            logged = true;
                        }
                        else {
                            qDebug() << "Password errata";
                        }
                    }
                }
                file.close();
            }

            //READ END
            if (logged) {
                QMessageBox dial;
                dial.setText("Successfully logged in!");
                dial.setIcon(QMessageBox::Information);
                dial.setWindowTitle("Success!");
                dial.exec();
                //Open Dialog
            }
        }
    }
    else { //No user found
        QMessageBox dial;
        dial.setText("Login Failed, insert correct credentials");
        dial.setIcon(QMessageBox::Warning);
        dial.setWindowTitle("Failure");
        dial.exec();
    }
}

void MainWindow::adminLogin()
{
    //READ BEGIN

    //Unused/Testing QString userList="Lista utenti attuali: \n \n NOME|COGNOME|NATO|SESSO|USERLOGIN|PASSWORD \n \n";

    QFile file(filename);

    //Creation of  a table Widget to display the CSV file
    QTableWidget* tableWidget = new QTableWidget(0, 6);
    QStringList label;
    label << "Nome"
          << "Cognome"
          << "DataNascita"
          << "Sesso"
          << "Username"
          << "Password";
    tableWidget->setHorizontalHeaderLabels(label);
    tableWidget->resize(450, 300); //A default size which should work in most cases
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //Allows resizing
    tableWidget->setWindowTitle(filename);
    if (file.open(QIODevice::ReadOnly)) {
        //Values to move inside the table
        int row = 0;
        int column = 0;
        QTextStream in(&file);
        while (!in.atEnd()) {
            //QStringList data;
            QString line = file.readLine();
            tableWidget->insertRow(row);
            QStringList data;
            int pos = line.lastIndexOf(QChar('\r'));
            data.append(line.left(pos).split(','));

            for (column = 0; column < 6; ++column) {
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setText(data[column]);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);

                tableWidget->setItem(row, column, item); //Adds User to tableWidget
            }
            ++row;
        }
    }
    file.close();
    tableWidget->show();
}

void MainWindow::on_DatiPersiButton_clicked()
{
    QString loginCredentials = ui->UserLogin->text();
    QString password = ui->UserLogin->text();
    bool logged = false;
    /*
     * Assumiamo che L'admin non perda la password
     * We assume the admin won't ever lose the password
     */
    if (isValidCredential(loginCredentials)) {
        //READ BEGIN

        QFile file(filename);
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream in(&file);
            while (!in.atEnd() && !logged) {
                QStringList data;
                QString line = file.readLine();
                int pos = line.lastIndexOf(QChar('\r'));
                data.append(line.left(pos).split(','));
                //qDebug() << data;
                if (data[4] == loginCredentials) {
                    //Email Sent

                    // qDebug()<<"Email";
                    QMessageBox dial;
                    dial.setText("E-mail di recupero inviata");
                    dial.setIcon(QMessageBox::Information);
                    dial.setWindowTitle("Lost Password");
                    dial.exec();
                    logged = true;
                }
            }
        }

        file.close();
    }
    if (!logged) { //User doesn't exist
        QMessageBox dial;
        dial.setText("Sembra che non sia possibile recuperare informazioni sul tuo account");
        dial.setIcon(QMessageBox::Warning);
        dial.setWindowTitle("Lost Password");
        dial.exec();
    }
}

void MainWindow::on_IscrivitiButton_clicked()
{

    ui->dateEdit->setMaximumDate(QDate::currentDate());

    QString nome, cognome, dataNascita, sesso, loginCredentials, password;

    nome = ui->NomeEdit->text();
    cognome = ui->CognomeEdit->text();
    loginCredentials = ui->TelefonoEdit->text();
    password = ui->PasswordRegisterEdit->text();
    dataNascita = ui->dateEdit->text();
    if (ui->UomoButton->isChecked()) {
        sesso = "M";
    }
    else {
        sesso = "F";
    }

    /* Debugging values
    qDebug()<< nome;
    qDebug()<< cognome;
    qDebug()<< dataNascita;
    qDebug()<< sesso;
    qDebug()<< loginCredentials;
    qDebug()<< password;
*/
    //Defines a file with filename path
    QFile file(filename);

    bool validNome = true;
    bool validCognome = true;
    bool validLogin = true;
    bool validPassword = true;
    bool canWrite = true;

    if (nome.isEmpty())
        validNome = false;
    if (cognome.isEmpty())
        validCognome = false;
    if (loginCredentials.isEmpty())
        validLogin = false;
    if (password.isEmpty())
        validPassword = false;

    if (!(validNome | validCognome | validLogin | validPassword)) {
        QString missing = "Something is missing: \n";
        if (!validNome)
            missing.append("Nome \n");
        if (!validCognome)
            missing.append("Cognome \n");
        if (!validLogin)
            missing.append("Credenziali \n");
        if (!validPassword)
            missing.append("Password\n");
        QMessageBox dial;
        dial.setText(missing);
        dial.setIcon(QMessageBox::Warning);
        dial.setWindowTitle("Missing Data");
        dial.exec();
        canWrite = false;
    }

    if (canWrite) {
        //The only duplicates we check for are Usernames
        canWrite = noDuplicates(loginCredentials);
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text) & isValidCredential(loginCredentials) & canWrite) {
        QTextStream stream(&file);

        stream << nome << ",";
        stream << cognome << ",";
        stream << dataNascita << ",";
        stream << sesso << ",";
        stream << loginCredentials << ",";
        stream << password << ",";
        stream << "\n";

        //Ugly, but the data should be short enough to be displayed correctly
        QString dati = "Iscrizione effettuata con successo \n Dati: \n Nome: ";
        dati.append(nome);
        dati.append("\n Cognome:");
        dati.append(cognome);
        dati.append("\n Data di nascita:");
        dati.append(dataNascita);
        dati.append("\n Sesso:");
        dati.append(sesso);
        dati.append("\n Login:");
        dati.append(loginCredentials);
        dati.append("\n Password:");
        dati.append(password);
        QMessageBox dial;
        dial.setText(dati);
        dial.setIcon(QMessageBox::Information);
        dial.setWindowTitle("Iscrizione completata");
        dial.exec();

        file.close();
    }
    else {
        // qDebug()<<"There has been an error";
        //We just don't do anything
        file.close();
    }
}

bool MainWindow::noDuplicates(QString login)
{
    //Quite self explanatory, we check for duplicate Username values
    bool returnValue = true;
    //READ BEGIN

    bool logged = false;

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd() && !logged) {
            QStringList data;
            QString line = file.readLine();
            int pos = line.lastIndexOf(QChar('\r'));
            data.append(line.left(pos).split(','));
            // qDebug() << data;
            if (data[4] == login) {
                qDebug() << "We have a dobule!";
                returnValue = false;
            }
        }
        file.close();
    }

    //READ END
    return returnValue;
}

bool MainWindow::isValidCredential(QString login)
{

    /* The regex works for any string in the form:
     *
     * <Text>(dots included)(numbers included> @ <Text>.<Text>
     *
     * The numerical Regex works for any 10 combinations of numbers
     *
     * */

    bool retVal = false;

    // Email ([0-9]*[a-zA-Z]*)+@([0-9]*[a-zA-Z]*)+\\.([0-9]*[a-zA-Z]*)+
    QRegularExpression regex("^([0-9]*[a-zA-Z]*[.]*)+@([0-9]*[a-zA-Z]*)+\\.([0-9]*[a-zA-Z][.]*)+$");
    /* Used For Regex Validation
     qDebug()<<"Is regex valid:"<< regex.isValid();

    if (!regex.isValid()) {
      QString errorString = regex.errorString(); // errorString == "missing )"
      int errorOffset = regex.patternErrorOffset(); // errorOffset == 22
          qDebug()<< errorString;
    }
     */

    QRegularExpressionMatch match = regex.match(login);
    if (match.hasMatch()) { //Valid Email
        //qDebug()<<"We're in";
        retVal = true;
    }
    else { //Invalid Email
        QRegularExpression regex2("^[0-9]{10}$");
        match = regex2.match(login);
        if (match.hasMatch()) { //Valid Phone Number
            //qDebug()<<"It's a phone number!";
            retVal = true;
        }
        else { //Invalid Login Credentials
            // qDebug()<<"We're out";
        }
    }

    return retVal;
}

void MainWindow::on_CsvChooser_clicked()
{
    QString loginCredentials = ui->UserLogin->text();
    QString password = ui->PasswordLogin->text();
    if (loginCredentials == "admin@pas.com" & password == "admin")
        filename = QFileDialog::getOpenFileName();
    else {
        QMessageBox dial;
        dial.setText("Only admin users can change the csv file");
        dial.setIcon(QMessageBox::Critical);
        dial.setWindowTitle("Unable to choose CSV");
        dial.exec();
    }
}
