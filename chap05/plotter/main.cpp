#include <QApplication>
#include "plotter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Plotter plotter;

    plotter.setWindowTitle(QObject::tr("Jambi Plotter"));
    int numPoints = 100;
    QVector<QPointF> points0;
    QVector<QPointF> points1;

    for (int i = 0; i < numPoints; ++ i)
    {
        points0.append(QPointF(i, uint(qrand()) % 100));
        points1.append(QPointF(i, uint(qrand()) % 100));
    }

    plotter.setCurveData(0, points0);
    plotter.setCurveData(1, points1);

    PlotSettings settings;
    settings.minX = 0.0;
    settings.maxX = 100.0;
    settings.minY = 0.0;
    settings.maxY = 100.0;
    plotter.setPlotSettings(settings);
    plotter.show();
    return a.exec();
}
