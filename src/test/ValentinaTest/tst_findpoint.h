/************************************************************************
 **
 **  @file   tst_findpoint.h
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   25 1, 2016
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

#ifndef TST_FINDPOINT_H
#define TST_FINDPOINT_H

#include "../vtest/abstracttest.h"

class TST_FindPoint : public AbstractTest
{
    Q_OBJECT
public:
    explicit TST_FindPoint(QObject *parent = nullptr);

private slots:
    void TestPointOfIntersectionCurves_data();
    void TestPointOfIntersectionCurves();

    void TestTrueDarts_data();
    void TestTrueDarts();

    void TestLineIntersectAxis_data();
    void TestLineIntersectAxis();

    void TestTriangle_data();
    void TestTriangle();

    void TestShoulderPoint_data();
    void TestShoulderPoint();

    void TestCurveIntersectAxis_data();
    void TestCurveIntersectAxis();
};

#endif // TST_FINDPOINT_H
