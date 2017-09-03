#include "playgroundwidget.hpp"
#include "ui_playgroundwidget.h"

PlaygroundWidget::PlaygroundWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaygroundWidget)
{
    ui->setupUi(this);
    connect(ui->fieldWidget,&FieldWidget::scaleChanged,this,&PlaygroundWidget::scaleChanged);
    connect(ui->fieldWidget,&FieldWidget::requestNewField,this,&PlaygroundWidget::onFieldRequested);
}

PlaygroundWidget::~PlaygroundWidget()
{
    delete ui;
}

void PlaygroundWidget::scaleChanged(double scale)
{
    ui->scaleLabel->setText(QString::number(scale));
}

void PlaygroundWidget::onFieldRequested()
{
    const Field & field = _playground.requestField();
    ui->fieldWidget->setField(field);
}

void PlaygroundWidget::on_startButton_released()
{
    _playground.start();
}

void PlaygroundWidget::on_stopButton_released()
{
    _playground.stop();
}

void PlaygroundWidget::on_initButton_released()
{
    _playground.init();
}

void PlaygroundWidget::on_resetButton_released()
{
    _playground.reset();
}
