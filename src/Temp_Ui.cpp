#include "Temp_Ui.h"
#include "StlToDatTranslator.h"
#include "StlToObjTranslator.h"
#include "ObjToStlTranslator.h"

#include <QFile>
#include <QTextStream> 
#include <QMessageBox>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), translator(nullptr) {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    translatorComboBox = new QComboBox(this);
    translatorComboBox->addItem("Select Translator");
    translatorComboBox->addItem("STL to DAT");
    translatorComboBox->addItem("STL to OBJ");
    translatorComboBox->addItem("OBJ to STL");
    connect(translatorComboBox, &QComboBox::currentTextChanged, this, &MainWindow::onSelectTranslator);

    fileInput = new QTextEdit(this);
    fileInput->setPlaceholderText("Enter file data here...");

    loadButton = new QPushButton("Load File", this);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadFile);

    translateButton = new QPushButton("Translate", this);
    connect(translateButton, &QPushButton::clicked, this, &MainWindow::onTranslate);

    saveButton = new QPushButton("Save File", this);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveFile);

    layout->addWidget(translatorComboBox);
    layout->addWidget(fileInput);
    layout->addWidget(loadButton);
    layout->addWidget(translateButton);
    layout->addWidget(saveButton);

    setCentralWidget(centralWidget);
    setWindowTitle("File Translator");
}

MainWindow::~MainWindow()
{
}

void MainWindow::onSelectTranslator(const QString& translatorType) {
    if (translator) {
        delete translator;
    }
    if (translatorType == "STL to DAT") {
        translator = new STLToDATTranslator();
    }
    else if (translatorType == "STL to OBJ") {
        translator = new STLToOBJTranslator();
    }
    else if (translatorType == "OBJ to STL") {
        translator = new OBJToSTLTranslator();
    }
    else {
        translator = nullptr;
    }
}

void MainWindow::onLoadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            fileInput->setPlainText(in.readAll());
            file.close();
        }
        else {
            QMessageBox::warning(this, "Error", "Could not open file.");
        }
    }
}

void MainWindow::onTranslate() {
    if (translator) {
        QString inputData = fileInput->toPlainText();
        QString translatedData = translator->translate(inputData);
        fileInput->setPlainText(translatedData);
    }
    else {
        QMessageBox::warning(this, "Error", "Please select a translator.");
    }
}

void MainWindow::onSaveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << fileInput->toPlainText();
            file.close();
        }
        else {
            QMessageBox::warning(this, "Error", "Could not save file.");
        }
    }
}
