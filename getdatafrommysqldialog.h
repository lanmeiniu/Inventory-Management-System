#ifndef GETDATAFROMMYSQLDIALOG_H
#define GETDATAFROMMYSQLDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlRecord>
namespace Ui {
class GetDataFromMysqlDialog;
}

class GetDataFromMysqlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GetDataFromMysqlDialog(QWidget *parent = 0);
    ~GetDataFromMysqlDialog();

signals:
    void getFieldName();
    void searchDataFromMysql(const QString &fieldName, const QString &value);
    void getAlldata();

public slots:
    void fieldNameList(const QList<QString> &list);

private slots:
    void getFieldNameSlots();
    void searchDataSlots();
    void on_pushButton_clicked(bool checked);

private:
    Ui::GetDataFromMysqlDialog *ui;
};

#endif // GETDATAFROMMYSQLDIALOG_H
