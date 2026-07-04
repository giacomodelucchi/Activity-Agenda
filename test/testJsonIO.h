#ifndef TESTJSONIO_H
#define TESTJSONIO_H

#include "../core/container/memoria.h"
#include "../core/jsonIO/jsonIO.h"

bool runJsonIOTest(const QString& jsonFilePath = QStringLiteral("test_activities.json"));

#endif // TESTJSONIO_H