//
// Statemachine code from reading SCXML file 'statemachine.scxml'
// Created by: The Qt SCXML Compiler version 1 (Qt 5.15.13)
// WARNING! All changes made in this file will be lost!
//

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QScxmlStateMachine>
#include <QString>
#include <QVariant>

class CalculatorStateMachine: public QScxmlStateMachine
{
    /* qmake ignore Q_OBJECT */
    Q_OBJECT
    Q_PROPERTY(bool wrapper)
    Q_PROPERTY(bool on)
    Q_PROPERTY(bool ready)
    Q_PROPERTY(bool begin)
    Q_PROPERTY(bool result)
    Q_PROPERTY(bool negated1)
    Q_PROPERTY(bool operand1)
    Q_PROPERTY(bool zero1)
    Q_PROPERTY(bool int1)
    Q_PROPERTY(bool frac1)
    Q_PROPERTY(bool opEntered)
    Q_PROPERTY(bool negated2)
    Q_PROPERTY(bool operand2)
    Q_PROPERTY(bool zero2)
    Q_PROPERTY(bool int2)
    Q_PROPERTY(bool frac2)


public:
    Q_INVOKABLE CalculatorStateMachine(QObject *parent = 0);
    ~CalculatorStateMachine();



Q_SIGNALS:


private:
    struct Data;
    friend struct Data;
    struct Data *data;
};

Q_DECLARE_METATYPE(::CalculatorStateMachine*)

#endif // STATEMACHINE_H
