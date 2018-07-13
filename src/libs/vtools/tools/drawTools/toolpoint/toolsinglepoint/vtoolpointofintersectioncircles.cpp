/************************************************************************
 **
 **  @file   vtoolpointofintersectioncircles.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   29 5, 2015
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentina project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2015 Valentina project
 **  <https://bitbucket.org/dismine/valentina> All Rights Reserved.
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

#include "vtoolpointofintersectioncircles.h"

#include <QSharedPointer>
#include <QStaticStringData>
#include <QStringData>
#include <QStringDataPtr>
#include <new>

#include "../../../../dialogs/tools/dialogpointofintersectioncircles.h"
#include "../../../../dialogs/tools/dialogtool.h"
#include "../../../../visualization/visualization.h"
#include "../../../../visualization/line/vistoolpointofintersectioncircles.h"
#include "../ifc/exception/vexception.h"
#include "../ifc/exception/vexceptionobjecterror.h"
#include "../ifc/xml/vdomdocument.h"
#include "../ifc/ifcdef.h"
#include "../vgeometry/vgobject.h"
#include "../vgeometry/vpointf.h"
#include "../vmisc/vabstractapplication.h"
#include "../vpatterndb/vcontainer.h"
#include "../vpatterndb/vformula.h"
#include "../vwidgets/vmaingraphicsscene.h"
#include "../../../vabstracttool.h"
#include "../../vdrawtool.h"
#include "vtoolsinglepoint.h"

template <class T> class QSharedPointer;

const QString VToolPointOfIntersectionCircles::ToolType = QStringLiteral("pointOfIntersectionCircles");

//---------------------------------------------------------------------------------------------------------------------
VToolPointOfIntersectionCircles::VToolPointOfIntersectionCircles(
        const VToolPointOfIntersectionCirclesInitData &initData, QGraphicsItem *parent)
    :VToolSinglePoint(initData.doc, initData.data, initData.id, parent),
      firstCircleCenterId(initData.firstCircleCenterId),
      secondCircleCenterId(initData.secondCircleCenterId),
      firstCircleRadius(initData.firstCircleRadius),
      secondCircleRadius(initData.secondCircleRadius),
      crossPoint(initData.crossPoint)
{
    ToolCreation(initData.typeCreation);
}

//---------------------------------------------------------------------------------------------------------------------
void VToolPointOfIntersectionCircles::setDialog()
{
    SCASSERT(not m_dialog.isNull())
    QSharedPointer<DialogPointOfIntersectionCircles> dialogTool =
            m_dialog.objectCast<DialogPointOfIntersectionCircles>();
    SCASSERT(not dialogTool.isNull())
    const QSharedPointer<VPointF> p = VAbstractTool::data.GeometricObject<VPointF>(m_id);
    dialogTool->SetFirstCircleCenterId(firstCircleCenterId);
    dialogTool->SetSecondCircleCenterId(secondCircleCenterId);
    dialogTool->SetFirstCircleRadius(firstCircleRadius);
    dialogTool->SetSecondCircleRadius(secondCircleRadius);
    dialogTool->SetCrossCirclesPoint(crossPoint);
    dialogTool->SetPointName(p->name());
}

//---------------------------------------------------------------------------------------------------------------------
VToolPointOfIntersectionCircles *VToolPointOfIntersectionCircles::Create(QSharedPointer<DialogTool> dialog,
                                                                         VMainGraphicsScene *scene,
                                                                         VAbstractPattern *doc, VContainer *data)
{
    SCASSERT(not dialog.isNull())
    QSharedPointer<DialogPointOfIntersectionCircles> dialogTool = dialog.objectCast<DialogPointOfIntersectionCircles>();
    SCASSERT(not dialogTool.isNull())

    VToolPointOfIntersectionCirclesInitData initData;
    initData.firstCircleCenterId = dialogTool->GetFirstCircleCenterId();
    initData.secondCircleCenterId = dialogTool->GetSecondCircleCenterId();
    initData.firstCircleRadius = dialogTool->GetFirstCircleRadius();
    initData.secondCircleRadius = dialogTool->GetSecondCircleRadius();
    initData.crossPoint = dialogTool->GetCrossCirclesPoint();
    initData.name = dialogTool->getPointName();
    initData.scene = scene;
    initData.doc = doc;
    initData.data = data;
    initData.parse = Document::FullParse;
    initData.typeCreation = Source::FromGui;

    VToolPointOfIntersectionCircles *point = Create(initData);
    if (point != nullptr)
    {
        point->m_dialog = dialogTool;
    }
    return point;
}

//---------------------------------------------------------------------------------------------------------------------
VToolPointOfIntersectionCircles *
VToolPointOfIntersectionCircles::Create(VToolPointOfIntersectionCirclesInitData &initData)
{
    const qreal calcC1Radius = qApp->toPixel(CheckFormula(initData.id, initData.firstCircleRadius, initData.data));
    const qreal calcC2Radius = qApp->toPixel(CheckFormula(initData.id, initData.secondCircleRadius, initData.data));

    const VPointF c1Point = *initData.data->GeometricObject<VPointF>(initData.firstCircleCenterId);
    const VPointF c2Point = *initData.data->GeometricObject<VPointF>(initData.secondCircleCenterId);

    QPointF point;
    const bool success = FindPoint(static_cast<QPointF>(c1Point), static_cast<QPointF>(c2Point), calcC1Radius,
                                   calcC2Radius, initData.crossPoint, &point);

    if (not success)
    {
        const QString errorMsg = tr("Error calculating point '%1'. Circles with centers in points '%2' and '%3' have "
                                    "no point of intersection").arg(initData.name, c1Point.name(), c2Point.name());
        qApp->IsPedantic() ? throw VExceptionObjectError(errorMsg) : qWarning() << errorMsg;
    }

    VPointF *p = new VPointF(point, initData.name, initData.mx, initData.my);
    p->SetShowLabel(initData.showLabel);

    if (initData.typeCreation == Source::FromGui)
    {
        initData.id = initData.data->AddGObject(p);
    }
    else
    {
        initData.data->UpdateGObject(initData.id, p);
        if (initData.parse != Document::FullParse)
        {
            initData.doc->UpdateToolData(initData.id, initData.data);
        }
    }

    if (initData.parse == Document::FullParse)
    {
        VAbstractTool::AddRecord(initData.id, Tool::PointOfIntersectionCircles, initData.doc);
        VToolPointOfIntersectionCircles *point = new VToolPointOfIntersectionCircles(initData);
        initData.scene->addItem(point);
        InitToolConnections(initData.scene, point);
        VAbstractPattern::AddTool(initData.id, point);
        initData.doc->IncrementReferens(c1Point.getIdTool());
        initData.doc->IncrementReferens(c2Point.getIdTool());
        return point;
    }
    return nullptr;
}

//---------------------------------------------------------------------------------------------------------------------
bool VToolPointOfIntersectionCircles::FindPoint(const QPointF &c1Point, const QPointF &c2Point, qreal c1Radius,
                                                qreal c2Radius, const CrossCirclesPoint crossPoint,
                                                QPointF *intersectionPoint)
{
    SCASSERT(intersectionPoint != nullptr)

    QPointF p1, p2;
    const int res = VGObject::IntersectionCircles(c1Point, c1Radius, c2Point, c2Radius, p1, p2);

    switch(res)
    {
        case 2:
            if (crossPoint == CrossCirclesPoint::FirstPoint)
            {
                *intersectionPoint = p1;
                return true;
            }
            else
            {
                *intersectionPoint = p2;
                return true;
            }
        case 1:
            *intersectionPoint = p1;
            return true;
        case 3:
        case 0:
        default:
            return false;
    }
}

//---------------------------------------------------------------------------------------------------------------------
QString VToolPointOfIntersectionCircles::FirstCircleCenterPointName() const
{
    return VAbstractTool::data.GetGObject(firstCircleCenterId)->name();
}

//---------------------------------------------------------------------------------------------------------------------
QString VToolPointOfIntersectionCircles::SecondCircleCenterPointName() const
{
    return VAbstractTool::data.GetGObject(secondCircleCenterId)->name();
}

//---------------------------------------------------------------------------------------------------------------------
VFormula VToolPointOfIntersectionCircles::GetFirstCircleRadius() const
{
    VFormula radius(firstCircleRadius, getData());
    radius.setCheckZero(true);
    radius.setToolId(m_id);
    radius.setPostfix(UnitsToStr(qApp->patternUnit()));
    radius.Eval();
    return radius;
}

//---------------------------------------------------------------------------------------------------------------------
void VToolPointOfIntersectionCircles::SetFirstCircleRadius(const VFormula &value)
{
    if (value.error() == false)
    {
        if (value.getDoubleValue() > 0)// Formula don't check this, but radius can't be 0 or negative
        {
            firstCircleRadius = value.GetFormula(FormulaType::FromUser);
            QSharedPointer<VGObject> obj = VAbstractTool::data.GetGObject(m_id);
            SaveOption(obj);
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------
VFormula VToolPointOfIntersectionCircles::GetSecondCircleRadius() const
{
    VFormula radius(secondCircleRadius, getData());
    radius.setCheckZero(true);
    radius.setToolId(m_id);
    radius.setPostfix(UnitsToStr(qApp->patternUnit()));
    radius.Eval();
    return radius;
}

//---------------------------------------------------------------------------------------------------------------------
void VToolPointOfIntersectionCircles::SetSecondCircleRadius(const VFormula &value)
{
    if (value.error() == false)
    {
        if (value.getDoubleValue() > 0)// Formula don't check this, but radius can't be 0 or negative
        {
            secondCircleRadius = value.GetFormula(FormulaType::FromUser);
            QSharedPointer<VGObject> obj = VAbstractTool::data.GetGObject(m_id);
            SaveOption(obj);
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------
CrossCirclesPoint VToolPointOfIntersectionCircles::GetCrossCirclesPoint() const
{
    return crossPoint;
}

//---------------------------------------------------------------------------------------------------------------------
void VToolPointOfIntersectionCircles::SetCrossCirclesPoint(const CrossCirclesPoint &value)
{
    crossPoint = value;

    QSharedPointer<VGObject> obj = VAbstractTool::data.GetGObject(m_id);
    SaveOption(obj);
}

//---------------------------------------------------------------------------------------------------------------------
void VToolPointOfIntersectionCircles::ShowVisualization(bool show)
{
    ShowToolVisualization<VisToolPointOfIntersectionCircles>(show);
}

//---------------------------------------------------------------------------------------------------------------------
void VToolPointOfIntersectionCircles::ShowContextMenu(QGraphicsSceneContextMenuEvent *event, quint32 id)
{
    try
    {
        ContextMenu<DialogPointOfIntersectionCircles>(event, id);
    }
    catch(const VExceptionToolWasDeleted &e)
    {
        Q_UNUSED(e)
        return;//Leave this method immediately!!!
    }
}

//---------------------------------------------------------------------------------------------------------------------
void VToolPointOfIntersectionCircles::RemoveReferens()
{
    const auto firstCircleCenter = VAbstractTool::data.GetGObject(firstCircleCenterId);
    const auto secondCircleCenter = VAbstractTool::data.GetGObject(secondCircleCenterId);

    doc->DecrementReferens(firstCircleCenter->getIdTool());
    doc->DecrementReferens(secondCircleCenter->getIdTool());
}

//---------------------------------------------------------------------------------------------------------------------
void VToolPointOfIntersectionCircles::SaveDialog(QDomElement &domElement, QList<quint32> &oldDependencies,
                                                 QList<quint32> &newDependencies)
{
    SCASSERT(not m_dialog.isNull())
    QSharedPointer<DialogPointOfIntersectionCircles> dialogTool =
            m_dialog.objectCast<DialogPointOfIntersectionCircles>();
    SCASSERT(not dialogTool.isNull())

    AddDependence(oldDependencies, firstCircleCenterId);
    AddDependence(oldDependencies, secondCircleCenterId);
    AddDependence(newDependencies, dialogTool->GetFirstCircleCenterId());
    AddDependence(newDependencies, dialogTool->GetSecondCircleCenterId());

    doc->SetAttribute(domElement, AttrName, dialogTool->getPointName());
    doc->SetAttribute(domElement, AttrC1Center, QString().setNum(dialogTool->GetFirstCircleCenterId()));
    doc->SetAttribute(domElement, AttrC2Center, QString().setNum(dialogTool->GetSecondCircleCenterId()));
    doc->SetAttribute(domElement, AttrC1Radius, dialogTool->GetFirstCircleRadius());
    doc->SetAttribute(domElement, AttrC2Radius, dialogTool->GetSecondCircleRadius());
    doc->SetAttribute(domElement, AttrCrossPoint,
                      QString().setNum(static_cast<int>(dialogTool->GetCrossCirclesPoint())));
}

//---------------------------------------------------------------------------------------------------------------------
void VToolPointOfIntersectionCircles::SaveOptions(QDomElement &tag, QSharedPointer<VGObject> &obj)
{
    VToolSinglePoint::SaveOptions(tag, obj);

    doc->SetAttribute(tag, AttrType, ToolType);
    doc->SetAttribute(tag, AttrC1Center, firstCircleCenterId);
    doc->SetAttribute(tag, AttrC2Center, secondCircleCenterId);
    doc->SetAttribute(tag, AttrC1Radius, firstCircleRadius);
    doc->SetAttribute(tag, AttrC2Radius, secondCircleRadius);
    doc->SetAttribute(tag, AttrCrossPoint, static_cast<int>(crossPoint));
}

//---------------------------------------------------------------------------------------------------------------------
void VToolPointOfIntersectionCircles::ReadToolAttributes(const QDomElement &domElement)
{
    firstCircleCenterId = doc->GetParametrUInt(domElement, AttrC1Center, NULL_ID_STR);
    secondCircleCenterId = doc->GetParametrUInt(domElement, AttrC2Center, NULL_ID_STR);
    firstCircleRadius = doc->GetParametrString(domElement, AttrC1Radius);
    secondCircleRadius = doc->GetParametrString(domElement, AttrC2Radius);
    crossPoint = static_cast<CrossCirclesPoint>(doc->GetParametrUInt(domElement, AttrCrossPoint, QChar('1')));
}

//---------------------------------------------------------------------------------------------------------------------
void VToolPointOfIntersectionCircles::SetVisualization()
{
    if (not vis.isNull())
    {
        VisToolPointOfIntersectionCircles *visual = qobject_cast<VisToolPointOfIntersectionCircles *>(vis);
        SCASSERT(visual != nullptr)

        visual->setObject1Id(firstCircleCenterId);
        visual->setObject2Id(secondCircleCenterId);
        visual->setC1Radius(firstCircleRadius);
        visual->setC2Radius(secondCircleRadius);
        visual->setCrossPoint(crossPoint);
        visual->RefreshGeometry();
    }
}
