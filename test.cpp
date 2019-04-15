#include "test.h"

Test::Test(QObject *parent) : QObject(parent)
{

}

void Test::runAll()
{
    std::cout << "Running all test" << std::endl;
    testPixel();
}

void Test::testPixel()
{

}
