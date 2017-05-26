#include "setdatabaseandtabledialog.h"
#include "ui_setdatabaseandtabledialog.h"

#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDate>
#include <QTime>
#include <QHash>
#include <QSettings>
#include <QDir>

SetDatabaseAndTableDialog::SetDatabaseAndTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDatabaseAndTableDialog)
{
    ui->setupUi(this);

    QString path;
    QDir dir;
    path=dir.currentPath();

    qDebug() << path;
    QString temp;
    temp = path + "/debug/ywgroup.ini";
    qDebug() << temp;

    configIniRead = new QSettings(temp, QSettings::IniFormat);


    hostNameOrIpAddress = configIniRead->value("setting/ip").toString();
    port = configIniRead->value("setting/port").toString();
    databaseName = configIniRead->value("setting/database_name").toString();
    tableName = configIniRead->value("setting/table_name").toString();
    username = configIniRead->value("setting/user_name").toString();
    password = configIniRead->value("setting/password").toString();


    ui->hostnameLineEdit->setText(hostNameOrIpAddress);
    ui->portLineEdit->setText(port);
    ui->databaseNameLineEdit->setText(databaseName);
    ui->tableNameLineEdit->setText(tableName);
    ui->userNameLineEdit->setText(username);
    ui->passwordLineEdit->setText(password);

    qDebug() << hostNameOrIpAddress << port << databaseName << tableName << username << password;

    connect(ui->testConnectionPushButton, SIGNAL(clicked(bool)), this, SLOT(testConnetction()));
    connect(ui->loginPushButton, SIGNAL(clicked(bool)), this, SLOT(setParameter()));
    connect(ui->rememberpasswordCheckBox, SIGNAL(clicked(bool)), this, SLOT(saveConfigToFile()));
    //connect(ui->autologinCheckBox,SIGNAL(clicked(bool)),this,SLOT());

    setWhatsThis(tr("Input parameter (hostname or IP username password),"
						 "Test if you can connect with MySQL"));


}

void SetDatabaseAndTableDialog::saveConfigToFile(void)
{
    hostNameOrIpAddress = ui->hostnameLineEdit->text();
    port = ui->portLineEdit->text();
    databaseName = ui->databaseNameLineEdit->text();
    tableName = ui->tableNameLineEdit->text();
    username = ui->userNameLineEdit->text();
    password = ui->passwordLineEdit->text();

    configIniRead->setValue("setting/ip", hostNameOrIpAddress);
    configIniRead->setValue("setting/port", port);
    configIniRead->setValue("setting/database_name", databaseName);
    configIniRead->setValue("setting/table_name", tableName);
    configIniRead->setValue("setting/user_name", username);
    configIniRead->setValue("setting/password", password);

    delete configIniRead;
}

void SetDatabaseAndTableDialog::getParameterOfConnectionFromLineText()
{
    qDebug() << QString("hostname:%1, port:%2, databasename:%3, username:%4, password:%5").\
                arg(hostNameOrIpAddress).arg(port).arg(databaseName).arg(username).arg(password);
}
void SetDatabaseAndTableDialog::setHashMap(QString emptyString,
                                           QHash<QString, QString> &hash,
                                           QString key, QString value)
{
    if(emptyString != value)
    {
        hash[key] = value;
    }
}
void SetDatabaseAndTableDialog::setParameterOfConnection()
{
    QString emptyString = "";

    if(true != hashConnetcion.isEmpty())
    {
        hashConnetcion.clear();
    }

    if(emptyString != hostNameOrIpAddress)
    {
        hashConnetcion["hostnameOrIpAddress"] = hostNameOrIpAddress;
    }
    if(emptyString != port)
    {
        hashConnetcion["port"] = port;
    }
    if(emptyString != databaseName)
    {
        hashConnetcion["databaseName"] = databaseName;
    }
    if(emptyString != tableName)
    {
        hashConnetcion["tableName"] = tableName;
    }
    if(emptyString != username)
    {
        hashConnetcion["username"] = username;
    }
    if(emptyString != password)
    {
        hashConnetcion["password"] = password;
    }
}

void SetDatabaseAndTableDialog::getAndSetParameter(void)
{
    getParameterOfConnectionFromLineText();
    setParameterOfConnection();
}

void SetDatabaseAndTableDialog::testConnetction(void)
{
    getAndSetParameter();
    emit testConnetctionWithSqlSignal(hashConnetcion);

    return;
}

void SetDatabaseAndTableDialog::setParameter(void)
{
    getAndSetParameter();
    emit setDatabaseNameAndTableNameSignal(hashConnetcion);
    this->close();

    return;
}

void SetDatabaseAndTableDialog::okConnectionSlot(bool okConnection)
{
    if(!okConnection)
    {
        QMessageBox::warning(this, tr("Database Error"),
                             database.lastError().text());
    }
    else
    {
        QMessageBox::information(this, tr("connection with sql"),
                             tr("connection test with sql success"),
                             QMessageBox::Ok);
    }
    return;
}

SetDatabaseAndTableDialog::~SetDatabaseAndTableDialog()
{
    delete ui;
}



