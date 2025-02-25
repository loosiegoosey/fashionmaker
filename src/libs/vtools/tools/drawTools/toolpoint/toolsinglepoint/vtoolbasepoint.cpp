/************************************************************************
 **
 **  @file   vtoolsinglepoint.cpp
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

#include "vtoolbasepoint.h"

#include <QApplication>
#include <QEvent>
#include <QFlags>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QList>
#include <QMessageBox>
#include <QPen>
#include <QPointF>
#include <QPolygonF>
#include <QRectF>
#include <QSharedPointer>
#include <QStaticStringData>
#include <QStringData>
#include <QStringDataPtr>
#include <QUndoStack>
#include <new>

#include "../../../../dialogs/tools/dialogtool.h"
#include "../../../../dialogs/tools/dialogsinglepoint.h"
#include "../../../../undocommands/addpatternpiece.h"
#include "../../../../undocommands/deletepatternpiece.h"
#include "../../../../undocommands/movespoint.h"
#include "../ifc/exception/vexception.h"
#include "../ifc/ifcdef.h"
#include "../vgeometry/vgobject.h"
#include "../vgeometry/vpointf.h"
#include "../vmisc/vabstractapplication.h"
#include "../vpatterndb/vcontainer.h"
#include "../vwidgets/vgraphicssimpletextitem.h"
#include "../vwidgets/vmaingraphicsscene.h"
#include "../vwidgets/vmaingraphicsview.h"
#include "../../../vabstracttool.h"
#include "../../../vdatatool.h"
#include "../../vdrawtool.h"
#include "vtoolsinglepoint.h"

const QString VToolBasePoint::ToolType = QStringLiteral("single");

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief VToolBasePoint constructor.
 * @param initData init data.
 * @param parent parent object.
 */
VToolBasePoint::VToolBasePoint (const VToolBasePointInitData &initData, QGraphicsItem * parent )
    :VToolSinglePoint(initData.doc, initData.data, initData.id, parent), namePP(initData.nameActivPP)
{
    m_baseColor = Qt::red;
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    m_namePoint->setBrush(Qt::black);
    ToolCreation(initData.typeCreation);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief setDialog set dialog when user want change tool option.
 */
void VToolBasePoint::setDialog()
{
    SCASSERT(not m_dialog.isNull())
    const QPointer<DialogSinglePoint> dialogTool = qobject_cast<DialogSinglePoint *>(m_dialog);
    SCASSERT(not dialogTool.isNull())
    const QSharedPointer<VPointF> p = VAbstractTool::data.GeometricObject<VPointF>(m_id);
    dialogTool->SetData(p->name(), static_cast<QPointF>(*p));
}

//---------------------------------------------------------------------------------------------------------------------
VToolBasePoint *VToolBasePoint::Create(VToolBasePointInitData initData)
{
    VPointF *point = new VPointF(initData.x, initData.y, initData.name, initData.mx, initData.my);
    point->SetShowLabel(initData.showLabel);

    if (initData.typeCreation == Source::FromGui)
    {
        initData.id = initData.data->AddGObject(point);
    }
    else
    {
        initData.data->UpdateGObject(initData.id, point);
        if (initData.parse != Document::FullParse)
        {
            initData.doc->UpdateToolData(initData.id, initData.data);
        }
    }

    if (initData.parse == Document::FullParse)
    {
        VAbstractTool::AddRecord(initData.id, Tool::BasePoint, initData.doc);
        VToolBasePoint *spoint = new VToolBasePoint(initData);
        initData.scene->addItem(spoint);
        InitToolConnections(initData.scene, spoint);
        VAbstractPattern::AddTool(initData.id, spoint);
        return spoint;
    }
    return nullptr;
}

//---------------------------------------------------------------------------------------------------------------------
void VToolBasePoint::ShowVisualization(bool show)
{
    Q_UNUSED(show) //don't have any visualization for base point yet
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief AddToFile add tag with informations about tool into file.
 */
void VToolBasePoint::AddToFile()
{
    Q_ASSERT_X(not namePP.isEmpty(), Q_FUNC_INFO, "name pattern piece is empty");

    QDomElement sPoint = doc->createElement(getTagName());

    // Create SPoint tag
    QSharedPointer<VGObject> obj = VAbstractTool::data.GetGObject(m_id);
    SaveOptions(sPoint, obj);

    //Create pattern piece structure
    QDomElement patternPiece = doc->createElement(VAbstractPattern::TagDraw);
    doc->SetAttribute(patternPiece, AttrName, namePP);

    QDomElement calcElement = doc->createElement(VAbstractPattern::TagCalculation);
    calcElement.appendChild(sPoint);

    patternPiece.appendChild(calcElement);
    patternPiece.appendChild(doc->createElement(VAbstractPattern::TagModeling));
    patternPiece.appendChild(doc->createElement(VAbstractPattern::TagDetails));

    AddPatternPiece *addPP = new AddPatternPiece(patternPiece, doc, namePP);
    connect(addPP, &AddPatternPiece::ClearScene, doc, &VAbstractPattern::ClearScene);
    connect(addPP, &AddPatternPiece::NeedFullParsing, doc, &VAbstractPattern::NeedFullParsing);
    qApp->getUndoStack()->push(addPP);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief itemChange handle tool change.
 * @param change change.
 * @param value value.
 * @return value.
 */
QVariant VToolBasePoint::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene())
    {
        // Each time we move something we call recalculation scene rect. In some cases this can cause moving
        // objects positions. And this cause infinite redrawing. That's why we wait the finish of saving the last move.
        static bool changeFinished = true;
        if (changeFinished)
        {
            changeFinished = false;
            // value - this is new position.
            QPointF newPos = value.toPointF();

            MoveSPoint *moveSP = new MoveSPoint(doc, newPos.x(), newPos.y(), m_id, this->scene());
            connect(moveSP, &MoveSPoint::NeedLiteParsing, doc, &VAbstractPattern::LiteParseTree);
            qApp->getUndoStack()->push(moveSP);
            const QList<QGraphicsView *> viewList = scene()->views();
            if (not viewList.isEmpty())
            {
                if (VMainGraphicsView *view = qobject_cast<VMainGraphicsView *>(viewList.at(0)))
                {
                    view->EnsureItemVisibleWithDelay(this, VMainGraphicsView::scrollDelay);
                }
            }
            changeFinished = true;
        }
    }
    return VToolSinglePoint::itemChange(change, value);
}

//---------------------------------------------------------------------------------------------------------------------
QPointF VToolBasePoint::GetBasePointPos() const
{
    const QSharedPointer<VPointF> p = VAbstractTool::data.GeometricObject<VPointF>(m_id);
    QPointF pos(qApp->fromPixel(p->x()), qApp->fromPixel(p->y()));
    return pos;
}

//---------------------------------------------------------------------------------------------------------------------
void VToolBasePoint::SetBasePointPos(const QPointF &pos)
{
    QSharedPointer<VPointF> p = VAbstractTool::data.GeometricObject<VPointF>(m_id);
    p->setX(qApp->toPixel(pos.x()));
    p->setY(qApp->toPixel(pos.y()));

    QSharedPointer<VGObject> obj = qSharedPointerCast<VGObject>(p);

    SaveOption(obj);
}

//---------------------------------------------------------------------------------------------------------------------
void VToolBasePoint::DeleteToolWithConfirm(bool ask)
{
    qCDebug(vTool, "Deleting base point.");
    emit qApp->getSceneView()->itemClicked(nullptr);
    if (ask)
    {
        qCDebug(vTool, "Asking.");
        if (ConfirmDeletion() == QMessageBox::No)
        {
            qCDebug(vTool, "User said no.");
            return;
        }
    }

    qCDebug(vTool, "Begin deleting.");
    DeletePatternPiece *deletePP = new DeletePatternPiece(doc, nameActivDraw);
    connect(deletePP, &DeletePatternPiece::NeedFullParsing, doc, &VAbstractPattern::NeedFullParsing);
    qApp->getUndoStack()->push(deletePP);

    // Throw exception, this will help prevent case when we forget to immediately quit function.
    VExceptionToolWasDeleted e("Tool was used after deleting.");
    throw e;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief SaveDialog save options into file after change in dialog.
 */
void VToolBasePoint::SaveDialog(QDomElement &domElement, QList<quint32> &oldDependencies,
                                QList<quint32> &newDependencies)
{
    SCASSERT(not m_dialog.isNull())
    const QPointer<DialogSinglePoint> dialogTool = qobject_cast<DialogSinglePoint *>(m_dialog);
    SCASSERT(not dialogTool.isNull())

    Q_UNUSED(oldDependencies)
    Q_UNUSED(newDependencies)

    const QPointF p = dialogTool->GetPoint();
    const QString name = dialogTool->GetPointName();
    doc->SetAttribute(domElement, AttrName, name);
    doc->SetAttribute(domElement, AttrX, QString().setNum(qApp->fromPixel(p.x())));
    doc->SetAttribute(domElement, AttrY, QString().setNum(qApp->fromPixel(p.y())));
}

//---------------------------------------------------------------------------------------------------------------------
void VToolBasePoint::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    VToolSinglePoint::hoverEnterEvent(event);

    if (flags() & QGraphicsItem::ItemIsMovable)
    {
        SetItemOverrideCursor(this, cursorArrowOpenHand, 1, 1);
    }
}

//---------------------------------------------------------------------------------------------------------------------
void VToolBasePoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (flags() & QGraphicsItem::ItemIsMovable)
    {
        if (event->button() == Qt::LeftButton && event->type() != QEvent::GraphicsSceneMouseDoubleClick)
        {
            SetItemOverrideCursor(this, cursorArrowCloseHand, 1, 1);
            event->accept();
        }
    }
    VToolSinglePoint::mousePressEvent(event);
}

//---------------------------------------------------------------------------------------------------------------------
void VToolBasePoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (flags() & QGraphicsItem::ItemIsMovable)
    {
        if (event->button() == Qt::LeftButton && event->type() != QEvent::GraphicsSceneMouseDoubleClick)
        {
            SetItemOverrideCursor(this, cursorArrowOpenHand, 1, 1);
        }
    }
    VToolSinglePoint::mouseReleaseEvent(event);
}

//---------------------------------------------------------------------------------------------------------------------
void VToolBasePoint::SaveOptions(QDomElement &tag, QSharedPointer<VGObject> &obj)
{
    VToolSinglePoint::SaveOptions(tag, obj);

    QSharedPointer<VPointF> point = qSharedPointerDynamicCast<VPointF>(obj);
    SCASSERT(point.isNull() == false)

    doc->SetAttribute(tag, AttrType, ToolType);
    doc->SetAttribute(tag, AttrX, qApp->fromPixel(point->x()));
    doc->SetAttribute(tag, AttrY, qApp->fromPixel(point->y()));
}

//---------------------------------------------------------------------------------------------------------------------
void VToolBasePoint::ReadToolAttributes(const QDomElement &domElement)
{
    Q_UNUSED(domElement)
    // This tool doesn't need read attributes from file.
}

//---------------------------------------------------------------------------------------------------------------------
QString VToolBasePoint::MakeToolTip() const
{
    const QSharedPointer<VPointF> point = VAbstractTool::data.GeometricObject<VPointF>(m_id);

    const QString toolTip = QString("<table>"
                                    "<tr> <td><b>%1:</b> %2</td> </tr>"
                                    "</table>")
            .arg(tr("Label"), point->name());
    return toolTip;
}

//---------------------------------------------------------------------------------------------------------------------
void VToolBasePoint::ShowContextMenu(QGraphicsSceneContextMenuEvent *event, quint32 id)
{
    qCDebug(vTool, "Context menu base point");
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
    qCDebug(vTool, "Restored overriden cursor");
#endif

    try
    {
        if (doc->CountPP() > 1)
        {
            qCDebug(vTool, "PP count > 1");
            ContextMenu<DialogSinglePoint>(event, id, RemoveOption::Enable, Referens::Ignore);
        }
        else
        {
            qCDebug(vTool, "PP count = 1");
            ContextMenu<DialogSinglePoint>(event, id, RemoveOption::Disable);
        }
    }
    catch(const VExceptionToolWasDeleted &e)
    {
        qCDebug(vTool, "Tool was deleted. Immediately leave method.");
        Q_UNUSED(e)
        return;//Leave this method immediately!!!
    }
    qCDebug(vTool, "Context menu closed. Tool was not deleted.");
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief FullUpdateFromFile update tool data form file.
 */
void  VToolBasePoint::FullUpdateFromFile()
{
    RefreshPointGeometry(*VAbstractTool::data.GeometricObject<VPointF>(m_id));
}

//---------------------------------------------------------------------------------------------------------------------
void VToolBasePoint::EnableToolMove(bool move)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, move);
    VToolSinglePoint::EnableToolMove(move);
}
