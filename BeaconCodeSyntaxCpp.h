#ifndef BEACONCODESYNTAXCPP_H
#define BEACONCODESYNTAXCPP_H

#include <QObject>
#include <QWidget>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include "BeaconCodeSyntax.h"

class BeaconCodeSyntaxCpp : public BeaconCodeSyntax
{
public:
    BeaconCodeSyntaxCpp(QWidget *parent = nullptr);
};

#endif // BEACONCODESYNTAXCPP_H
