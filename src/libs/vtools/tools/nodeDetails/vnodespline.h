/************************************************************************
 **
 **  @file   vnodespline.h
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   November 15, 2013
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentina project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2013-2015 Valentina project
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

#ifndef VNODESPLINE_H
#define VNODESPLINE_H

#include <qcompilerdetection.h>
#include <QGraphicsPathItem>
#include <QMetaObject>
#include <QObject>
#include <QString>
#include <QtGlobal>

#include "../ifc/xml/vabstractpattern.h"
#include "../vmisc/def.h"
#include "vabstractnode.h"

/**
 * @brief The VNodeSpline class spline detail node.
 */
class VNodeSpline:public VAbstractNode
{
    Q_OBJECT
public:
    static VNodeSpline *Create(const VAbstractNodeInitData &initData);

    static const QString ToolType;
    virtual QString getTagName() const override;
public slots:
    virtual void FullUpdateFromFile () override {}
    virtual void AllowHover(bool enabled) override;
    virtual void AllowSelecting(bool enabled) override;
protected:
    virtual void AddToFile () override;
    virtual void ShowNode() override {}
    virtual void HideNode() override {}
private:
    Q_DISABLE_COPY(VNodeSpline)

    VNodeSpline(const VAbstractNodeInitData &initData, QObject *qoParent = nullptr);
};

#endif // VNODESPLINE_H
