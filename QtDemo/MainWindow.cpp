#include "MainWindow.h"
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextStream>
#include <QApplication>

MainWindow::MainWindow(int width, int height) : QMainWindow()
{
	QDesktopWidget* desktop = QApplication::desktop();

	int deskW = desktop->width();
	int deskH = desktop->height();

	int maxWidth = width > deskW ? deskW : width;
	int maxHeight = height > deskH ? deskH : height;

	int x = deskW / 2 - (width > deskW ? maxWidth : width) / 2;
	int y = deskH / 2 - (height > deskH ? maxHeight : height) / 2;
	this->setGeometry(x, y, width, height);	

	this->initialize();
}

void MainWindow::initialize()
{
	QFrame* centralFrame = new QFrame(this);
	this->setCentralWidget(centralFrame);

	QVBoxLayout* frameLayout = new QVBoxLayout(centralFrame);
	centralFrame->setLayout(frameLayout);

	QFrame* filePathFrame = new QFrame(centralFrame);	
	QHBoxLayout* filePathLayout = new QHBoxLayout(filePathFrame);
	filePathLayout->setMargin(0);
	filePathFrame->setLayout(filePathLayout);

	filePath = new QLineEdit(filePathFrame);
	filePath->setEnabled(false);
	filePath->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	filePathLayout->addWidget(filePath);

	QPushButton* chooseFileButton = new QPushButton("...", filePathFrame);
	chooseFileButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	chooseFileButton->setMaximumSize(filePath->height(), filePath->height());
	filePathLayout->addWidget(chooseFileButton);
	
	frameLayout->addWidget(filePathFrame);
	
	chooseFileButton->connect(chooseFileButton, SIGNAL(clicked()), this, SLOT(openFile()));

	fileContent = new QTextEdit(centralFrame);
	fileContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	frameLayout->addWidget(fileContent);

	QFrame* dlgButtonsFrame = new QFrame(centralFrame);
	QHBoxLayout* dlgButtonsLayout = new QHBoxLayout(dlgButtonsFrame);
	dlgButtonsLayout->setMargin(0);
	dlgButtonsFrame->setLayout(dlgButtonsLayout);
		
	dlgButtonsLayout->addStretch();

	QPushButton* saveButton = new QPushButton("Save", filePathFrame);
	dlgButtonsLayout->addWidget(saveButton);
	
	saveButton->connect(saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
	
	QPushButton* closeButton = new QPushButton("Close", filePathFrame);
	dlgButtonsLayout->addWidget(closeButton);
	
	closeButton->connect(closeButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
	
	frameLayout->addWidget(dlgButtonsFrame);
}

QString MainWindow::showFileChooseDialog(QFileDialog::AcceptMode acceptMode) {
	QFileDialog chooseFileDialog(this);
	chooseFileDialog.setFileMode(acceptMode == QFileDialog::AcceptSave ? QFileDialog::AnyFile : QFileDialog::ExistingFile);
	chooseFileDialog.setNameFilter("Text Files (*.txt)");
	chooseFileDialog.setViewMode(QFileDialog::Detail);
	chooseFileDialog.setAcceptMode(acceptMode);

	if (chooseFileDialog.exec()) 
	{
		QStringList selectedFiles = chooseFileDialog.selectedFiles();
		if (selectedFiles.size() != 0) 
		{	
			QString selectedFile = selectedFiles.first();
			filePath->setText(selectedFile);

			return selectedFile;
		}
	}

	return "";
}

void MainWindow::openFile() 
{
	QString selectedFile = showFileChooseDialog(QFileDialog::AcceptOpen);

	if (QString::compare("", selectedFile, Qt::CaseInsensitive) != 0)
	{
		QFile file(selectedFile);

		file.open(QFile::ReadOnly | QFile::Text);

		QTextStream fileStream(&file);
		fileContent->setText(fileStream.readAll());

		file.close();
	}
}

void MainWindow::saveFile()
{
	QString selectedFile = showFileChooseDialog(QFileDialog::AcceptSave);

	if (QString::compare("", selectedFile, Qt::CaseInsensitive) != 0)
	{
		QFile file(selectedFile);

		file.open(QFile::WriteOnly | QFile::Text);

		QTextStream fileStream(&file);

		QString newContent = fileContent->toPlainText();
		fileStream << newContent;

		file.close();
	}
}

void MainWindow::closeWindow()
{
	this->close();
}