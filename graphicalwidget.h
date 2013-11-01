#ifndef GRAPHICALWIDGET_H
#define GRAPHICALWIDGET_H

#include <QWidget>

namespace Ui {
class GraphicalWidget;
}

class GraphicalWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit GraphicalWidget(QWidget *parent = 0);
    ~GraphicalWidget();
    
private:
    Ui::GraphicalWidget *ui;
};

#endif // GRAPHICALWIDGET_H
