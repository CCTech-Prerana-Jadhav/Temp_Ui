#pragma once
#include "Translator.h"

class OBJToSTLTranslator : public Translator {
public:
    QString translate(const QString& inputData) override;
};