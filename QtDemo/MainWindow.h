#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QFileDialog>

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	QLineEdit* filePath;
	QTextEdit* fileContent;

	void initialize();
	QString showFileChooseDialog(QFileDialog::AcceptMode acceptMode);

private slots:
	void openFile();
	void saveFile();
	void closeWindow();

public:
	MainWindow(int width, int height);	
};
