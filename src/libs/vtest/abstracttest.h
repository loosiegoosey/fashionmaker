/************************************************************************
 **
 **  @file   abstracttest.h
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   7 5, 2015
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentina project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2015 Valentina project
 **  <https://gitlab.com/smart-pattern/valentina> All Rights Reserved.
 **
 **  Valentina is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Valentina is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Valentina.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#ifndef ABSTRACTTEST_H
#define ABSTRACTTEST_H

#include <QMetaObject>
#include <QObject>
#include <QString>

template <class T> class QVector;
class VSAPoint;

#include <ciso646>

#ifdef __GNUC__
#define V_UNUSED __attribute__ ((unused))
#else
#define V_UNUSED
#endif

// Return codes for testing run application
static const auto V_UNUSED TST_EX_BIN = -1;      // Can't find binary.
static const auto V_UNUSED TST_EX_FINISH_TIME_OUT = -2; // The operation timed out or an error occurred.
static const auto V_UNUSED TST_EX_START_TIME_OUT = -3; // The operation timed out or an error occurred.
static const auto V_UNUSED TST_EX_CRASH = -4;    // Program crashed.

#undef V_UNUSED

enum ErrorState {ErrorLoad = 0, ErrorInstall, ErrorSize, NoError};

class VPiece;
class VContainer;
class VPointF;
class VSplinePoint;
class VPieceNode;
enum class GOType : qint8;
struct VPiecePassmarkData;

class AbstractTest : public QObject
{
    Q_OBJECT
public:
    explicit AbstractTest(QObject *parent = nullptr);

    void VectorFromJson(const QString &json, QVector<QPointF>& vector);
    void VectorFromJson(const QString &json, QVector<VSAPoint>& vector);

    void PieceFromJson(const QString &json, VPiece &piece, QSharedPointer<VContainer> &data);

    void PassmarkDataFromJson(const QString &json, VPiecePassmarkData& data);
    void PassmarkShapeFromJson(const QString &json, QVector<QLineF> &shape);

protected:
    void Comparison(const QVector<QPointF> &ekv, const QVector<QPointF> &ekvOrig) const;
    void Comparison(const QPointF &result, const QPointF &expected) const;
    void Comparison(const QVector<QLineF> &result, const QVector<QLineF> &expected) const;

    QString ValentinaPath() const;
    QString TapePath() const;
    QString TranslationsPath() const;

    int Run(int exit, const QString &program, const QStringList &arguments, QString &error, int msecs = 120000);
    bool CopyRecursively(const QString &srcFilePath, const QString &tgtFilePath) const;

    void PrepareDocument(const QString &json, QByteArray &data) const;
    void TestRoot(const QJsonObject &root, const QString &attribute, const QString &file);

    template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
    void ReadDoubleValue(const QJsonObject &itemObject, const QString &attribute, T &value,
                         const QString &defaultValue = QString());
    template <typename T, typename std::enable_if<std::is_enum<T>::value>::type* = nullptr>
    void ReadDoubleValue(const QJsonObject &itemObject, const QString &attribute, T &value,
                         const QString &defaultValue = QString());
    template <typename T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
    void ReadDoubleValue(const QJsonObject &itemObject, const QString &attribute, T &value,
                         const QString &defaultValue = QString());
    void ReadStringValue(const QJsonObject &itemObject, const QString &attribute, QString &value,
                         const QString &defaultValue = QString());
    void ReadBooleanValue(const QJsonObject &itemObject, const QString &attribute, bool &value,
                          const QString &defaultValue = QString());
    void ReadPointValue(const QJsonObject &itemObject, const QString &attribute, VPointF &value);
    void ReadSplinePointValues(const QJsonObject &itemObject, const QString &attribute, QVector<VSplinePoint> &points);
    void ReadSplinePointValue(const QJsonObject &itemObject, VSplinePoint &point);
    void ReadPieceNodeValue(const QJsonObject &itemObject, VPieceNode &node);

    void QPointFromJson(const QJsonObject &itemObject, QPointF &point);
    void VPointFromJson(const QJsonObject &itemObject, VPointF &point);
    void QLineFromJson(const QJsonObject &itemObject, QLineF &line);
    void SAPointFromJson(const QJsonObject &itemObject, VSAPoint &point);
    void SplineFromJson(const QJsonObject &itemObject, QSharedPointer<VContainer> &data);
    void SplinePathFromJson(const QJsonObject &itemObject, QSharedPointer<VContainer> &data);

    void DBFromJson(const QJsonObject &dbObject, QSharedPointer<VContainer> &data);
    void MainPathFromJson(const QJsonObject &pieceObject, VPiece &piece);
};

#endif // ABSTRACTTEST_H
