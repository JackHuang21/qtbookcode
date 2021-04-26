#include "ticker.h"
#include <QPainter>
#include <QTimerEvent>
#include <QDebug>

Ticker::Ticker(QWidget *parent)
    : QWidget(parent)
{
    offset = 0;
    myTimerId = 0;
}

void Ticker::setText(const QString &newText)
{
    myText = newText;
    update();               // 强制执行重绘
    updateGeometry();       // 通知布局管理器，窗口大小发生了变化
}

QSize Ticker::sizeHint() const
{
    return fontMetrics().size(0, text());
}


void Ticker::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    int textWidth = fontMetrics().width(text());
    if (textWidth < 1)
        return;
    int x = -offset;
    while (x < width())
    {
        painter.drawText(x, 0, textWidth, height(), Qt::AlignLeft | Qt::AlignVCenter, text());
        x += textWidth;
    }
}

void Ticker::showEvent(QShowEvent * /* event */)
{
    qDebug() << "show event trigged.\n";
    myTimerId = startTimer(30);
}

void Ticker::timerEvent(QTimerEvent * event)
{
    if (event->timerId() == myTimerId)
    {
        ++ offset;
        // fontMetrics Returns display (screen) font metrics for the application font.
        if (offset >= fontMetrics().width(text()))
            offset = 0;
        scroll(-1, 0);  // 使用scroll触发paint event事件,scroll仅需要处理一个像素宽度的刷新
    }
    else
    {
        QWidget::timerEvent(event);
    }
}

void Ticker::hideEvent(QHideEvent * /* event */ )
{
    killTimer(myTimerId);
    myTimerId = 0;
}
