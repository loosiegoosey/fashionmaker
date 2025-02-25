/************************************************************************
 **
 **  @file
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   30 12, 2016
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentina project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2016 Valentina project
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

#ifndef TST_READVAL_H
#define TST_READVAL_H

#include <QtCore/qglobal.h>

#include <QObject>
#include <QLocale>

class TST_ReadVal : public QObject
{
    Q_OBJECT
public:
    explicit TST_ReadVal(QObject *parent = nullptr);
private slots:
    void TestReadVal_data();
    void TestReadVal();
    void TestInvalidData_data();
    void TestInvalidData();
    void cleanupTestCase();
private:
    Q_DISABLE_COPY(TST_ReadVal)
    QLocale m_systemLocale;

    void PrepareVal(qreal val, const QLocale &locale);
    void PrepareString(const QString &str, const QLocale &locale, qreal val=0, int count=-1);

    void TestVal();
};

#endif // TST_READVAL_H
