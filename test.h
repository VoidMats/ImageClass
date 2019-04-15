#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QDebug>
#include "pixel.h"
#include "image.h"

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);
    void runAll();
    void testPixel();

signals:

public slots:

private:

};

#endif // TEST_H
