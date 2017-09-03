#include "fieldwidget.hpp"
#include "ui_fieldwidget.h"

#include <QPainter>
#include <QLine>
#include <QWheelEvent>
#include <QMouseEvent>
#include <glm/glm.hpp>

FieldWidget::FieldWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FieldWidget)
{
    ui->setupUi(this);
    _scale = 0.1;
    _screenPos = QPoint(0,0);
    _offsetPos = QPoint(0,0);
    _pressPos = QPoint(0,0);
    _gridPen = QPen(Qt::gray,1,Qt::DashLine);
}

FieldWidget::~FieldWidget()
{
    delete ui;
}

void FieldWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int w = width();
    int h = height();

    int fieldHalfWidth = _currentField.fieldHalfWidth();
    int fieldHalfHeight = _currentField.fieldHalfHeight();

    painter.fillRect(0,0,w,h,Qt::white);

    const auto & squares = _currentField.squares();
    int curRowIndex = - fieldHalfHeight;
    for(auto & row : squares) {
        int curColIndex = - fieldHalfWidth;
        for(double val : row) {
            QPointF point1 = getScreenCoords(glm::vec2(curColIndex,curRowIndex),w,h);
            QPointF point2 = getScreenCoords(glm::vec2(curColIndex+1.0,curRowIndex+1.0),w,h);

            painter.fillRect(QRectF(point1,point2),QColor((1.0 - val) * 255,val * 255, 0));

            ++curColIndex;
        }
        ++curRowIndex;
    }

    painter.setPen(_gridPen);
    for(int i=-fieldHalfHeight; i<=fieldHalfHeight; ++i) {
        QPointF point1 = getScreenCoords(glm::vec2(-15,i),w,h);
        QPointF point2 = getScreenCoords(glm::vec2(15,i),w,h);
        QLineF line1(point1,point2);
        painter.drawLine(line1);
    }

    for(int i=-fieldHalfWidth; i<=fieldHalfWidth; ++i) {
        QPointF point3 = getScreenCoords(glm::vec2(i,-15),w,h);
        QPointF point4 = getScreenCoords(glm::vec2(i,15),w,h);
        QLineF line2(point3,point4);
        painter.drawLine(line2);
    }

    painter.setBrush(Qt::blue);

    const auto & creatures = _currentField.creatures();
    for(auto & creature : creatures) {
        drawCreature(painter,creature,w,h);
    }

    emit requestNewField();
    update();
}

void FieldWidget::setField(const Field &field)
{
    _currentField = Field(field);
}

void FieldWidget::wheelEvent(QWheelEvent *event)
{
    const double degrees = event->delta() / 10000.0;
    _scale += degrees;
    emit scaleChanged(_scale);
}

void FieldWidget::mouseMoveEvent(QMouseEvent *event)
{
    const QPoint & point = event->pos();
    _screenPos = _pressPos - point;
}

void FieldWidget::mousePressEvent(QMouseEvent *event)
{
    const QPoint & point = event->pos();
    _pressPos = point;
}

void FieldWidget::mouseReleaseEvent(QMouseEvent *event)
{
    const QPoint & point = event->pos();
    _offsetPos += _screenPos;
    _screenPos = QPoint(0,0);
}

QPointF FieldWidget::getScreenCoords(const glm::vec2 &vec, int w, int h)
{
    double aspectRatio = static_cast<double>(w)/static_cast<double>(h);
    QPoint center((w-w/2),(h-h/2));
    double movX =  -(_screenPos.x() + _offsetPos.x());
    double movY =  -(_screenPos.y() + _offsetPos.y());
    return QPoint((vec.x * w/2 *_scale) + movX, (-vec.y * h/2 *_scale)*aspectRatio + movY) + center ;
}

void FieldWidget::drawCreature(QPainter & painter, const Creature &creature, int w, int h)
{
    QPointF start = getScreenCoords(creature.position(),w,h);

    painter.setPen(Qt::white);
    const auto & directions = creature.getDirections();
    for(glm::vec2 direction : directions) {
        painter.drawLine(QLineF(start,getScreenCoords(creature.position() + glm::normalize(direction),w,h)));
    }
    painter.setPen(Qt::black);
    painter.drawEllipse(start,50.0*_scale,50.0*_scale);
    double satisfaction = _currentField.getWeightInPoint(creature.position());
    painter.drawText(start,QString::number(satisfaction));
    painter.drawLine(QLineF(start,getScreenCoords(creature.position() + glm::normalize(creature.direction()),w,h)));

}
