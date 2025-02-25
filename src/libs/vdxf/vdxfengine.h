/************************************************************************
 **
 **  @file   vdxfengine.h
 **  @author Valentina Zhuravska <zhuravska19(at)gmail.com>
 **  @date   12 8, 2015
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

#ifndef VDXFENGINE_H
#define VDXFENGINE_H

#include <qcompilerdetection.h>
#include <QMatrix>
#include <QPaintEngine>
#include <QPointF>
#include <QRectF>
#include <QSize>
#include <QString>
#include <QtGlobal>
#include <string>

#include "../vmisc/def.h"
#include "dxfdef.h"
#include "libdxfrw/drw_base.h"

class QTextStream;
class dx_iface;
class DRW_Text;
class VLayoutPiece;
class DRW_Entity;
class dx_ifaceBlock;

class VDxfEngine : public QPaintEngine
{
    friend class VDxfPaintDevice;
public:
    VDxfEngine();
    virtual ~VDxfEngine();

    virtual bool begin(QPaintDevice *pdev) override;
    virtual bool end() override;
    virtual void updateState(const QPaintEngineState &state) override;
    virtual void drawPath(const QPainterPath &path) override;
    virtual void drawLines(const QLineF * lines, int lineCount) override;
    virtual void drawLines(const QLine * lines, int lineCount) override;
    virtual void drawPolygon(const QPointF *points, int pointCount, PolygonDrawMode mode) override;
    virtual void drawPolygon(const QPoint *points, int pointCount, PolygonDrawMode mode) override;
    virtual void drawEllipse(const QRectF & rect) override;
    virtual void drawEllipse(const QRect & rect) override;
    virtual void drawTextItem(const QPointF & p, const QTextItem & textItem) override;
    virtual Type type() const override;
    virtual void drawPixmap(const QRectF &r, const QPixmap &pm, const QRectF &sr) override;

    QSize getSize() const;
    void setSize(const QSize &value);

    double getResolution() const;
    void   setResolution(double value);

    QString getFileName() const;
    void setFileName(const QString &value);

    DRW::Version GetVersion() const;
    void         SetVersion(DRW::Version version);

    void SetBinaryFormat(bool binary);
    bool IsBinaryFormat() const;

    std::string getPenStyle();
    int getPenColor();

    void setMeasurement(const VarMeasurement &var);
    void setInsunits(const VarInsunits &var);

    qreal GetXScale() const;
    void  SetXScale(const qreal &xscale);

    qreal GetYScale() const;
    void  SetYScale(const qreal &yscale);

private:
    Q_DISABLE_COPY(VDxfEngine)
    QSize            size;
    double           resolution;
    QString          fileName;
    DRW::Version     m_version;
    bool             m_binary;
    QTransform       matrix;
    QSharedPointer<dx_iface> input;
    VarMeasurement varMeasurement;
    VarInsunits varInsunits;
    DRW_Text *textBuffer;
    qreal m_xscale{1};
    qreal m_yscale{1};

    Q_REQUIRED_RESULT double FromPixel(double pix, const VarInsunits &unit) const;
    Q_REQUIRED_RESULT double ToPixel(double val, const VarInsunits &unit) const;

    bool ExportToAAMA(const QVector<VLayoutPiece> &details);
    void ExportAAMAOutline(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);
    void ExportAAMADraw(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);
    void ExportAAMAIntcut(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);
    void ExportAAMANotch(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);
    void ExportAAMAGrainline(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);
    void ExportPieceText(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);
    void ExportStyleSystemText(const QSharedPointer<dx_iface> &input, const QVector<VLayoutPiece> &details);
    void ExportAAMADrill(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);

    bool ExportToASTM(const QVector<VLayoutPiece> &details);
    void ExportASTMPieceBoundary(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);
    void ExportASTMSewLine(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);
    void ExportASTMInternalLine(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);
    void ExportASTMInternalCutout(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);
    void ExportASTMAnnotationText(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);
    void ExportASTMDrill(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);
    void ExportASTMNotch(dx_ifaceBlock *detailBlock, const VLayoutPiece &detail);

    Q_REQUIRED_RESULT DRW_Entity *AAMAPolygon(const QVector<QPointF> &polygon, const QString &layer, bool forceClosed);
    Q_REQUIRED_RESULT DRW_Entity *AAMALine(const QLineF &line, const QString &layer);
    Q_REQUIRED_RESULT DRW_Entity *AAMAText(const QPointF &pos, const QString &text, const QString &layer);

    template<class P, class V>
    Q_REQUIRED_RESULT P *CreateAAMAPolygon(const QVector<QPointF> &polygon, const QString &layer, bool forceClosed);

    static std::string FromUnicodeToCodec(const QString &str, QTextCodec *codec);
    std::string getFileNameForLocale() const;
};

#endif // VDXFENGINE_H
