#include <QStylePainter>
#include <QStyleOptionFocusRect>
#include "plotter.h"

Plotter::Plotter(QWidget *parent) : QWidget(parent)
{
    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);
    rubberBandIsShown = false;
    zoomInButton = new QToolButton(this);
    zoomInButton->setIcon(QIcon(":/images/zommin"));
    zoomInButton->adjustSize();
    connect(zoomInButton, &QToolButton::clicked, this, &Plotter::zoomIn);

    zoomOutButton = new QToolButton(this);
    zoomOutButton->setIcon(QIcon(":/images/zoomout"));
    zoomOutButton->adjustSize();
    connect(zoomOutButton, &QToolButton::clicked, this, &Plotter::zoomOut);

    setPlotSettings(PlotSettings());
}

void Plotter::setPlotSettings(const PlotSettings &settings)
{
    zoomStack.clear();
    zoomStack.append(settings);
    curZoom = 0;
    zoomInButton->hide();
    zoomOutButton->hide();
    refresfPixmap();
}

void Plotter::zoomOut()
{
    if (curZoom > 0)
    {
        --curZoom;
        zoomOutButton->setEnabled(curZoom > 0);
        zoomInButton->setEnabled(true);
        zoomInButton->show();
        refresfPixmap();
    }
}

void Plotter::zoomIn()
{
    if (curZoom < zoomStack.count() - 1)
    {
        ++curZoom;
        zoomInButton->setEnabled(curZoom < zoomStack.count() - 1);
        zoomOutButton->setEnabled(true);
        zoomOutButton->show();
        refresfPixmap();
    }
}

void Plotter::setCurveData(int id, const QVector<QPointF> &data)
{
    curveMap[id] = data;
    refresfPixmap();
}

void Plotter::clearCurve(int id)
{
    curveMap.remove(id);
}

QSize Plotter::minimumSizeHint() const
{
    return QSize(6 * Margin, 4 * Margin);
}

QSize Plotter::sizeHint() const
{
    return QSize(12 * Margin, 8 * Margin);
}

void Plotter::paintEvent(QPaintEvent * event)
{
    QStylePainter painter(this);
    painter.drawPixmap(0, 0, pixmap);

    if (rubberBandIsShown)
    {
        painter.setPen(palette().light().color());
        painter.drawRect(rubberBandRect.normalized());
    }
    if (hasFocus())
    {
        QStyleOptionFocusRect option;
        option.initFrom(this);
        option.backgroundColor = (palette().dark().color());
        painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);
    }
}

void Plotter::resizeEvent(QResizeEvent *event)
{
    int x = width() - (zoomInButton->width()) + zoomOutButton->width() + 10;
    zoomInButton->move(x, 5);
    zoomOutButton->move(x + zoomInButton->width() + 5, 5);
    refresfPixmap();
}

void Plotter::mousePressEvent(QMouseEvent *event)
{
    QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
    if (event->button() == Qt::LeftButton)
    {
        if (rect.contains(event->pos()))
        {
            rubberBandIsShown = true;
            rubberBandRect.setTopLeft(event->pos());
            rubberBandRect.setBottomRight(event->pos());
            updateRubberBandRegion();
            setCursor(Qt::CrossCursor);
        }
    }
}

void Plotter::mouseMoveEvent(QMouseEvent *event)
{
    if (rubberBandIsShown)
    {
        updateRubberBandRegion();
        rubberBandRect.setBottomRight(event->pos());
        updateRubberBandRegion();
    }
}

void Plotter::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton) && rubberBandIsShown)
    {
        rubberBandIsShown = false;
        updateRubberBandRegion();
        unsetCursor();

        QRect rect = rubberBandRect.normalized();
        if (rect.width() < 4 || rect.height() < 4)
            return;
        rect.translate(-Margin, -Margin);

        PlotSettings prevSettings = zoomStack[curZoom];
        PlotSettings settings;
        double dx = prevSettings.spanX() / (width() - 2 * Margin);
        double dy = prevSettings.spanY() / (height() - 2 * Margin);
        settings.minX = prevSettings.minX + dx * rect.left();
        settings.maxX = prevSettings.minX + dx * rect.right();
        settings.minY = prevSettings.maxY - dy * rect.bottom();
        settings.maxY = prevSettings.maxY - dy * rect.top();
        settings.adjust();

        zoomStack.resize(curZoom + 1);
        zoomStack.append(settings);
        zoomIn();
    }
}

void Plotter::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Plus:
        zoomIn();
        break;

    case Qt::Key_Minus:
        zoomOut();
        break;

    case Qt::Key_Left:
       zoomStack[curZoom].scroll(-1, 0);
        refresfPixmap();
        break;

    case Qt::Key_Right:
        zoomStack[curZoom].scroll(+1, 0);
        refresfPixmap();
        break;

    case Qt::Key_Down:
        zoomStack[curZoom].scroll(0, -1);
        refresfPixmap();
        break;

    case Qt::Key_Up:
        zoomStack[curZoom].scroll(0, +1);
        refresfPixmap();
        break;

    default:
        QWidget::keyPressEvent(event);
    }
}


void Plotter::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numTicks

}
