#ifndef GRAPHICALWINDOW_H
#define GRAPHICALWINDOW_H

#include <QWidget>

namespace Ui {
class GraphicalWindow;
}

class GraphicalWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit GraphicalWindow(QWidget *parent = 0);
    ~GraphicalWindow();
    
private:
    Ui::GraphicalWindow *ui;
};

#endif // GRAPHICALWINDOW_H
