cmake_minimum_required(VERSION 3.10)
project(calculator LANGUAGES CXX)

# Set install directory for examples
if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/scxml/calculator")

# Find Qt5 components
find_package(Qt5 REQUIRED COMPONENTS Core Gui Qml Scxml Test)

# Enable Qt's automatic MOC
set(CMAKE_AUTOMOC ON)

# Define the source directory for QML
set(QML_DIR "${CMAKE_SOURCE_DIR}/qml")

# Add executable target for the application
add_executable(calculatorscxml
    calculator.cpp        # Main application logic
    calculator_logic.cpp  # Ensure this file exists in the source directory
    calculator-qml.h
)

# Link Qt5 libraries for the application
target_link_libraries(calculatorscxml PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Scxml
)

# Add Statecharts (if applicable)
qt5_add_statecharts(calculatorscxml
    statemachine.scxml
)

# Add QML resources
qt5_add_resources(QML_RESOURCES qmake_qml_resources.qrc)
target_sources(calculatorscxml PRIVATE ${QML_RESOURCES})

# Installation for QML files
install(FILES ${QML_DIR}/MainWindow.qml ${QML_DIR}/Button.qml DESTINATION "${INSTALL_EXAMPLEDIR}/qml")

# Define test sources
set(CALCULATOR_TEST_SOURCES
    calculator_test.cpp  # Test file for Calculator class
    calculator_logic.cpp  # Include logic file used in tests
    calculator.h          # Include the header for the Calculator class
)

# Add executable for the test
add_executable(calculator_test
    ${CALCULATOR_TEST_SOURCES}
)

# Link the test executable with Qt Test, Core, Gui, Qml
target_link_libraries(calculator_test PRIVATE
    Qt5::Test
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
)

# Enable testing
enable_testing()

# Register the test with CTest
add_test(NAME CalculatorTests COMMAND calculator_test)

# Set target properties for the main application
set_target_properties(calculatorscxml PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

