#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Saveボタンが押された時のアクション
void MainWindow::on_saveButton_clicked()
{
    // save.jsonという名前のファイルを扱うクラスを生成する
    QFile saveFile(QStringLiteral("save.json"));

    // save.jsonを開くことができなければ警告を出す
    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save.json");
        return;
    }

    // QtでJsonを扱うためのオブジェクトを作製し、キーとそれに対応する値を保存する
    QJsonObject saveObject;
    saveObject["labelKey"] = ui->lineEdit->text();

    // QJsonオブジェクトをテキストの形にして、保存する
    QJsonDocument saveDoc(saveObject);
    saveFile.write(saveDoc.toJson());
}

// Loadボタンが押された時のアクション
void MainWindow::on_loadButton_clicked()
{
    // save.jsonという名前のファイルを扱うクラスを生成する
    QFile loadFile(QStringLiteral("save.json"));

    // save.jsonを開くことができなければ警告を出す
    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save.json");
        return;
    }

    // save.jsonの中身を取得
    QByteArray saveData = loadFile.readAll();

    // 取得したテキストからJsonを扱うためのオブジェクト生成
    QJsonObject json(QJsonDocument::fromJson(saveData).object());

    // Jsonオブジェクトから保存した値を取り出して、labelに表示
    ui->label->setText(json["labelKey"].toString());
}
