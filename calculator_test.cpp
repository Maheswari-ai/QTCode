#include <QTest>
#include "calculator.h" // Include the class you want to test

class CalculatorTest : public QObject {
    Q_OBJECT

private slots:
    // Initialization before tests
    void initTestCase() {
        qDebug() << "Starting Calculator Tests...";
    }

    // Cleanup after tests
    void cleanupTestCase() {
        qDebug() << "All tests finished.";
    }

    // Test case for addition
    void testAddition() {
        Calculator calc;
        QCOMPARE(calc.add(2, 3), 5); // Assert that 2 + 3 == 5
        QCOMPARE(calc.add(-1, -4), -5); // Assert that -1 + (-4) == -5
        QCOMPARE(calc.add(0, 5), 5); // Assert that 0 + 5 == 5
    }

    // Test case for subtraction
    void testSubtraction() {
        Calculator calc;
        QCOMPARE(calc.subtract(7, 4), 3); // Assert that 7 - 4 == 3
        QCOMPARE(calc.subtract(-1, -4), 3); // Assert that -1 - (-4) == 3
        QCOMPARE(calc.subtract(0, 5), -5); // Assert that 0 - 5 == -5
    }
};

QTEST_MAIN(CalculatorTest)
#include "calculator_test.moc"

