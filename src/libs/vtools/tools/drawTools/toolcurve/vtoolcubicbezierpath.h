/************************************************************************
 **
 **  @file   vtoolcubicbezierpath.h
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   18 3, 2016
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

#ifndef VTOOLCUBICBEZIERPATH_H
#define VTOOLCUBICBEZIERPATH_H

#include <qcompilerdetection.h>
#include <QGraphicsItem>
#include <QMetaObject>
#include <QObject>
#include <QString>
#include <QtGlobal>

#include "../ifc/xml/vabstractpattern.h"
#include "../vmisc/def.h"
#include "vabstractspline.h"

class VCubicBezierPath;
template <class T> class QSharedPointer;

QT_WARNING_PUSH
QT_WARNING_DISABLE_GCC("-Weffc++")

struct VToolCubicBezierPathInitData : VAbstractToolInitData
{
    VToolCubicBezierPathInitData()
        : VAbstractToolInitData(),
          path(nullptr)
    {}

    VCubicBezierPath *path;
};

QT_WARNING_POP

class VToolCubicBezierPath:public VAbstractSpline
{
    Q_OBJECT
public:
    virtual ~VToolCubicBezierPath() Q_DECL_EQ_DEFAULT;
    virtual void setDialog() override;
    static VToolCubicBezierPath *Create(const QPointer<DialogTool> &dialog, VMainGraphicsScene  *scene,
                                        VAbstractPattern *doc, VContainer *data);
    static VToolCubicBezierPath *Create(VToolCubicBezierPathInitData initData);

    static const QString ToolType;
    static void  UpdatePathPoints(VAbstractPattern *doc, QDomElement &element, const VCubicBezierPath &path);
    virtual int  type() const override {return Type;}
    enum { Type = UserType + static_cast<int>(Tool::CubicBezierPath)};

    VCubicBezierPath getSplinePath()const;
    void             setSplinePath(const VCubicBezierPath &splPath);

    virtual void ShowVisualization(bool show) override;
protected slots:
    virtual void ShowContextMenu(QGraphicsSceneContextMenuEvent *event, quint32 id=NULL_ID) override;
protected:
    virtual void  RemoveReferens() override;
    virtual void  SaveDialog(QDomElement &domElement, QList<quint32> &oldDependencies,
                             QList<quint32> &newDependencies) override;
    virtual void  SaveOptions(QDomElement &tag, QSharedPointer<VGObject> &obj) override;
    virtual void  SetVisualization() override;
    virtual void  RefreshGeometry() override;
private:
    Q_DISABLE_COPY(VToolCubicBezierPath)

    VToolCubicBezierPath(const VToolCubicBezierPathInitData &initData, QGraphicsItem * parent = nullptr);

    static void   AddPathPoint(VAbstractPattern *doc, QDomElement &domElement, const VPointF &splPoint);
    void          SetSplinePathAttributes(QDomElement &domElement, const VCubicBezierPath &path);
};

#endif // VTOOLCUBICBEZIERPATH_H
