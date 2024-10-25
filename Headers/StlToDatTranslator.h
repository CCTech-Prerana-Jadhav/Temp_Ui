#pragma once
#include "Translator.h"

class STLToDATTranslator : public Translator {
public:
    QString translate(const QString& inputData) override;
};
