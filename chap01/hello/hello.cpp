#include <QApplication>
#include <QLabel>
#include <QPushButton>

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	QPushButton * btn = new QPushButton("Quit");
	QObject::connect(btn, SIGNAL(clicked()), &app, SLOT(quit()));
	btn->show();
	return app.exec();
}
