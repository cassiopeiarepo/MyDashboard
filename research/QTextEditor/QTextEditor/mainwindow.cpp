#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    inputText = new InputTextEdit(ui->tab);
    //inputText->
    connect(inputText, &QTextEdit::textChanged, this, &MainWindow::onTextChanged);
    markdownTextEdit = new QTextEdit(ui->tab);
    markdownTextEdit->move(400,0);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTextChanged() {
    //markdownTextEdit->setPlainText(inputText->toMarkdown());
    markdownTextEdit->setMarkdown(inputText->toPlainText());
}
