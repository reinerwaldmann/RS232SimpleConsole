#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>

/**
 * @brief The Controller class
 * Класс, от которого наследуются контроллеры. Абстрактен
 */
class Controller
{
public:
    Controller();

    /**
     * @brief wrLine устанавливает напряжение на выходной линии
     * @param numline номер линии
     * @param state состояние (1 - высокий уровень, 0 - низкий уровень)
     */
    virtual void wrLine(int numline, bool state=1)=0;


    /**
     * @brief wrLines устанавливает состояние на группе линий
     * @param line строка, которая устанавливает состояние. Может не наследоваться, тогда ничего не делает
     */
    virtual void wrLines(QString line);
};

#endif // CONTROLLER_H
