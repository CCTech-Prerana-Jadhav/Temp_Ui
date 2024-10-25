#pragma once
#include "Translator.h"

class STLToOBJTranslator : public Translator {
public:
    QString translate(const QString& inputData) override;
};