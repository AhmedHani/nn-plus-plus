TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    models/LogisticRegression.cpp \
    Activation.cpp \
    CostFunction.cpp \
    Main.cpp \
    Matrix.cpp \
    Operation.cpp

HEADERS += \
    models/LogisticRegression.h \
    Activation.h \
    CostFunction.h \
    Log.h \
    Matrix.h \
    Operation.h
