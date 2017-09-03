#ifndef PLAYGROUNDWIDGET_HPP
#define PLAYGROUNDWIDGET_HPP

#include <QWidget>
#include <playground.hpp>

namespace Ui {
class PlaygroundWidget;
}

class PlaygroundWidget : public QWidget
{
    Q_OBJECT

    Playground _playground;
public:
    explicit PlaygroundWidget(QWidget *parent = 0);
    ~PlaygroundWidget();

private slots:
    void scaleChanged(double scale);
    void onFieldRequested();
    void on_startButton_released();
    void on_stopButton_released();
    void on_initButton_released();

    void on_resetButton_released();

private:
    Ui::PlaygroundWidget *ui;
};

#endif // PLAYGROUNDWIDGET_HPP
