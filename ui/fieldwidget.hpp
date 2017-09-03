#ifndef FIELDWIDGET_HPP
#define FIELDWIDGET_HPP

#include <QWidget>
#include <QPen>
#include <field.hpp>

namespace Ui {
class FieldWidget;
}

class FieldWidget : public QWidget
{
    Q_OBJECT
    double _scale;
    QPoint _pressPos;
    QPoint _screenPos;
    QPoint _offsetPos;
    Field _currentField;
    QPen _gridPen;
public:
    explicit FieldWidget(QWidget *parent = 0);
    ~FieldWidget();
    void paintEvent(QPaintEvent *event);
    void setField(const Field &field);
    void wheelEvent(QWheelEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void scaleChanged(double);
    void requestNewField();
private:
    QPointF getScreenCoords(const glm::vec2 & vec, int w, int h);
    void drawCreature(QPainter &painter, const Creature & creature, int w, int h);
    Ui::FieldWidget *ui;
};

#endif // FIELDWIDGET_HPP
