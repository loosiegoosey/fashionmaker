/************************************************************************
 **
 **  @file   vabstractspline.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   4 3, 2014
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

#include "vabstractspline.h"

#include <QColor>
#include <QFlags>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QLineF>
#include <QPen>
#include <QSharedPointer>
#include <Qt>
#include <new>

#include "../ifc/exception/vexception.h"
#include "../ifc/exception/vexceptionbadid.h"
#include "../ifc/xml/vabstractpattern.h"
#include "../qmuparser/qmutokenparser.h"
#include "../vgeometry/vgobject.h"
#include "../vgeometry/vpointf.h"
#include "../vgeometry/vspline.h"
#include "../vgeometry/vabstractarc.h"
#include "../vpatterndb/vcontainer.h"
#include "../vwidgets/vcontrolpointspline.h"
#include "../../../visualization/line/visline.h"
#include "../../vabstracttool.h"
#include "../vdrawtool.h"

//---------------------------------------------------------------------------------------------------------------------
VAbstractSpline::VAbstractSpline(VAbstractPattern *doc, VContainer *data, quint32 id, QGraphicsItem *parent)
    :VDrawTool(doc, data, id),
      QGraphicsPathItem(parent),
      controlPoints(),
      sceneType(SceneObject::Unknown),
      m_isHovered(false),
      detailsMode(qApp->Settings()->IsShowCurveDetails()),
      m_acceptHoverEvents(true),
      m_parentRefresh(false)
{
    InitDefShape();
    setAcceptHoverEvents(m_acceptHoverEvents);
}

//---------------------------------------------------------------------------------------------------------------------
QPainterPath VAbstractSpline::shape() const
{
    const QSharedPointer<VAbstractCurve> curve = VAbstractTool::data.GeometricObject<VAbstractCurve>(m_id);
    const QVector<QPointF> points = curve->GetPoints();

    QPainterPath path;
    for (qint32 i = 0; i < points.count()-1; ++i)
    {
        path.moveTo(points.at(i));
        path.lineTo(points.at(i+1));
    }

    if (m_isHovered || detailsMode)
    {
        path.addPath(VAbstractCurve::ShowDirection(curve->DirectionArrows(),
                                                   ScaleWidth(VAbstractCurve::LengthCurveDirectionArrow(),
                                                              SceneScale(scene()))));
    }
    path.setFillRule(Qt::WindingFill);
    return ItemShapeFromPath(path, pen());
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const qreal width = ScaleWidth(m_isHovered ? qApp->Settings()->WidthMainLine() : qApp->Settings()->WidthHairLine(),
                                   SceneScale(scene()));

    const QSharedPointer<VAbstractCurve> curve = VAbstractTool::data.GeometricObject<VAbstractCurve>(m_id);
    setPen(QPen(CorrectColor(this, curve->GetColor()), width, LineStyleToPenStyle(curve->GetPenStyle()), Qt::RoundCap));

    auto PaintSpline = [this, curve](QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        if (m_isHovered || detailsMode)
        {
            painter->save();

            QPen arrowPen(pen());
            arrowPen.setStyle(Qt::SolidLine);

            painter->setPen(arrowPen);
            painter->setBrush(brush());

            painter->drawPath(VAbstractCurve::ShowDirection(curve->DirectionArrows(),
                                                            ScaleWidth(VAbstractCurve::LengthCurveDirectionArrow(),
                                                                       SceneScale(scene()))));

            painter->restore();
        }

        PaintWithFixItemHighlightSelected<QGraphicsPathItem>(this, painter, option, widget);
    };

    if (not m_parentRefresh)
    {
        RefreshCtrlPoints();
        m_parentRefresh = true;
        PaintSpline(painter, option, widget);
    }
    else
    {
        m_parentRefresh = false;
        PaintSpline(painter, option, widget);
    }
}

//---------------------------------------------------------------------------------------------------------------------
QString VAbstractSpline::getTagName() const
{
    return VAbstractPattern::TagSpline;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief FullUpdateFromFile update tool data form file.
 */
void VAbstractSpline::FullUpdateFromFile()
{
    ReadAttributes();
    RefreshGeometry();
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::Disable(bool disable, const QString &namePP)
{
    const bool enabled = !CorrectDisable(disable, namePP);
    this->setEnabled(enabled);
    emit setEnabledPoint(enabled);
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::DetailsMode(bool mode)
{
    detailsMode = mode;
    RefreshGeometry();
    ShowHandles(detailsMode);
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::AllowHover(bool enabled)
{
    // Manually handle hover events. Need for setting cursor for not selectable paths.
    m_acceptHoverEvents = enabled;

    for (auto point : qAsConst(controlPoints))
    {
        point->setAcceptHoverEvents(enabled);
    }
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::AllowSelecting(bool enabled)
{
    setFlag(QGraphicsItem::ItemIsSelectable, enabled);

    for (auto point : qAsConst(controlPoints))
    {
        point->setFlag(QGraphicsItem::ItemIsSelectable, enabled);
    }
}

//---------------------------------------------------------------------------------------------------------------------
QString VAbstractSpline::MakeToolTip() const
{
    const QSharedPointer<VAbstractCurve> curve = VAbstractTool::data.GeometricObject<VAbstractCurve>(m_id);

    const QString toolTip = QString("<table>"
                                    "<tr> <td><b>%4:</b> %5</td> </tr>"
                                    "<tr> <td><b>%1:</b> %2 %3</td> </tr>"
                                    "</table>")
            .arg(tr("Length"))
            .arg(qApp->fromPixel(curve->GetLength()))
            .arg(UnitsToStr(qApp->patternUnit(), true), tr("Label"), curve->name());
    return toolTip;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief ShowTool highlight tool.
 * @param id object id in container
 * @param enable enable or disable highlight.
 */
void VAbstractSpline::ShowTool(quint32 id, bool enable)
{
    ShowItem(this, id, enable);
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::RefreshGeometry()
{
    InitDefShape();
    RefreshCtrlPoints();
    SetVisualization();
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief hoverEnterEvent handle hover enter events.
 * @param event hover enter event.
 */
// cppcheck-suppress unusedFunction
void VAbstractSpline::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_isHovered = true;
    setToolTip(MakeToolTip());
    QGraphicsPathItem::hoverEnterEvent(event);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief hoverLeaveEvent handle hover leave events.
 * @param event hover leave event.
 */
// cppcheck-suppress unusedFunction
void VAbstractSpline::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_isHovered = false;
    QGraphicsPathItem::hoverLeaveEvent(event);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief itemChange hadle item change.
 * @param change change.
 * @param value value.
 * @return value.
 */
QVariant VAbstractSpline::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        emit ChangedToolSelection(value.toBool(), m_id, m_id);
    }

    return QGraphicsPathItem::itemChange(change, value);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief keyReleaseEvent handle key release events.
 * @param event key release event.
 */
void VAbstractSpline::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Delete:
            try
            {
                DeleteToolWithConfirm();
            }
            catch(const VExceptionToolWasDeleted &e)
            {
                Q_UNUSED(e)
                return;//Leave this method immediately!!!
            }
            break;
        default:
            break;
    }
    QGraphicsPathItem::keyReleaseEvent ( event );
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Special for not selectable item first need to call standard mousePressEvent then accept event
    QGraphicsPathItem::mousePressEvent(event);

    // Somehow clicking on notselectable object do not clean previous selections.
    if (not (flags() & ItemIsSelectable) && scene())
    {
        scene()->clearSelection();
    }

    event->accept();// Special for not selectable item first need to call standard mousePressEvent then accept event
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief mouseReleaseEvent  handle mouse release events.
 * @param event mouse release event.
 */
void VAbstractSpline::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (IsSelectedByReleaseEvent(this, event))
    {
        emit ChoosedTool(m_id, sceneType);
    }
    QGraphicsPathItem::mouseReleaseEvent(event);
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::ReadToolAttributes(const QDomElement &domElement)
{
    Q_UNUSED(domElement)
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::SaveOptions(QDomElement &tag, QSharedPointer<VGObject> &obj)
{
    VDrawTool::SaveOptions(tag, obj);

    const QSharedPointer<VAbstractCurve> curve = qSharedPointerCast<VAbstractCurve>(obj);
    doc->SetAttribute(tag, AttrColor, curve->GetColor());
    doc->SetAttribute(tag, AttrPenStyle, curve->GetPenStyle());
    doc->SetAttribute(tag, AttrAScale, curve->GetApproximationScale());
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::RefreshCtrlPoints()
{
    // do nothing
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    ShowContextMenu(event);
}

//---------------------------------------------------------------------------------------------------------------------
VSpline VAbstractSpline::CorrectedSpline(const VSpline &spline, const SplinePointPosition &position,
                                         const QPointF &pos) const
{
    VSpline spl;
    if (position == SplinePointPosition::FirstPoint)
    {
        QLineF line(static_cast<QPointF>(spline.GetP1()), pos);
        if (QGuiApplication::keyboardModifiers() == Qt::ShiftModifier)
        {
            line.setAngle(VisLine::CorrectAngle(line.angle()));
        }

        qreal newAngle1 = line.angle();
        QString newAngle1F = QString().setNum(newAngle1);

        qreal newLength1 = line.length();
        QString newLength1F = QString().setNum(qApp->fromPixel(newLength1));

        if (not qmu::QmuTokenParser::IsSingle(spline.GetStartAngleFormula()))
        {
            newAngle1 = spline.GetStartAngle();
            newAngle1F = spline.GetStartAngleFormula();
        }

        if (not qmu::QmuTokenParser::IsSingle(spline.GetC1LengthFormula()))
        {
            newLength1 = spline.GetC1Length();
            newLength1F = spline.GetC1LengthFormula();
        }

        spl = VSpline(spline.GetP1(), spline.GetP4(), newAngle1, newAngle1F, spline.GetEndAngle(),
                      spline.GetEndAngleFormula(), newLength1, newLength1F, spline.GetC2Length(),
                      spline.GetC2LengthFormula());
    }
    else
    {
        QLineF line(static_cast<QPointF>(spline.GetP4()), pos);
        if (QGuiApplication::keyboardModifiers() == Qt::ShiftModifier)
        {
            line.setAngle(VisLine::CorrectAngle(line.angle()));
        }

        qreal newAngle2 = line.angle();
        QString newAngle2F = QString().setNum(newAngle2);

        qreal newLength2 = line.length();
        QString newLength2F = QString().setNum(qApp->fromPixel(newLength2));

        if (not qmu::QmuTokenParser::IsSingle(spline.GetEndAngleFormula()))
        {
            newAngle2 = spline.GetEndAngle();
            newAngle2F = spline.GetEndAngleFormula();
        }

        if (not qmu::QmuTokenParser::IsSingle(spline.GetC2LengthFormula()))
        {
            newLength2 = spline.GetC2Length();
            newLength2F = spline.GetC2LengthFormula();
        }
        spl = VSpline(spline.GetP1(), spline.GetP4(), spline.GetStartAngle(), spline.GetStartAngleFormula(),
                      newAngle2, newAngle2F, spline.GetC1Length(), spline.GetC1LengthFormula(),
                      newLength2, newLength2F);
    }

    return spl;
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::CurveSelected(bool selected)
{
    setSelected(selected);

    for (auto point : qAsConst(controlPoints))
    {
        point->blockSignals(true);
        point->setSelected(selected);
        point->blockSignals(false);
    }
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::InitDefShape()
{
    const QSharedPointer<VAbstractCurve> curve = VAbstractTool::data.GeometricObject<VAbstractCurve>(m_id);
    this->setPath(curve->GetPath());
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::ShowHandles(bool show)
{
    for (auto point : qAsConst(controlPoints))
    {
        point->setVisible(show);
    }
    update();// Show direction
}

//---------------------------------------------------------------------------------------------------------------------
QString VAbstractSpline::GetLineColor() const
{
    const QSharedPointer<VAbstractCurve> curve = VAbstractTool::data.GeometricObject<VAbstractCurve>(m_id);
    return curve->GetColor();
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::SetLineColor(const QString &value)
{
    QSharedPointer<VAbstractCurve> curve = VAbstractTool::data.GeometricObject<VAbstractCurve>(m_id);
    curve->SetColor(value);
    QSharedPointer<VGObject> obj = qSharedPointerCast<VGObject>(curve);
    SaveOption(obj);
}

//---------------------------------------------------------------------------------------------------------------------
QString VAbstractSpline::GetPenStyle() const
{
    const QSharedPointer<VAbstractCurve> curve = VAbstractTool::data.GeometricObject<VAbstractCurve>(m_id);
    return curve->GetPenStyle();
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::SetPenStyle(const QString &value)
{
    QSharedPointer<VAbstractCurve> curve = VAbstractTool::data.GeometricObject<VAbstractCurve>(m_id);
    curve->SetPenStyle(value);
    QSharedPointer<VGObject> obj = qSharedPointerCast<VGObject>(curve);
    SaveOption(obj);
}

//---------------------------------------------------------------------------------------------------------------------
QString VAbstractSpline::name() const
{
    return ObjectName<VAbstractCurve>(m_id);
}

//---------------------------------------------------------------------------------------------------------------------
qreal VAbstractSpline::GetApproximationScale() const
{
    return VAbstractTool::data.GeometricObject<VAbstractCurve>(m_id)->GetApproximationScale();
}

//---------------------------------------------------------------------------------------------------------------------
quint32 VAbstractSpline::GetDuplicate() const
{
    return VAbstractTool::data.GeometricObject<VAbstractCurve>(m_id)->GetDuplicate();
}

//---------------------------------------------------------------------------------------------------------------------
void VAbstractSpline::GroupVisibility(quint32 object, bool visible)
{
    Q_UNUSED(object)
    setVisible(visible);
}

// VToolAbstractArc
//---------------------------------------------------------------------------------------------------------------------
VToolAbstractArc::VToolAbstractArc(VAbstractPattern *doc, VContainer *data, quint32 id, QGraphicsItem *parent)
    : VAbstractSpline(doc, data, id, parent)
{}

//---------------------------------------------------------------------------------------------------------------------
QString VToolAbstractArc::CenterPointName() const
{
    QSharedPointer<VAbstractArc> arc = VAbstractTool::data.GeometricObject<VAbstractArc>(m_id);
    SCASSERT(arc.isNull() == false)

    return VAbstractTool::data.GetGObject(arc->GetCenter().id())->name();
}
