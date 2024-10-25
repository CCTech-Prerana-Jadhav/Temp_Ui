#pragma once
#include <QString>

class Translator {
public:
    virtual ~Translator() {}
    virtual QString translate(const QString& inputData) = 0;
};