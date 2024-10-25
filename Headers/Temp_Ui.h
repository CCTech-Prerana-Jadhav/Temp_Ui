#pragma once

#include <QtWidgets/QMainWindow>
#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include "Translator.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onTranslate();
    void onSelectTranslator(const QString& translatorType);
    void onLoadFile();
    void onSaveFile();

private:
    QComboBox* translatorComboBox;
    QTextEdit* fileInput;
    QPushButton* loadButton;
    QPushButton* translateButton;
    QPushButton* saveButton;

    Translator* translator;
};