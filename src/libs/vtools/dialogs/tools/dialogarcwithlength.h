/************************************************************************
 **
 **  @file   dialogarcwithlength.h
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   9 6, 2015
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

#ifndef DIALOGARCWITHLENGTH_H
#define DIALOGARCWITHLENGTH_H

#include <qcompilerdetection.h>
#include <QMetaObject>
#include <QObject>
#include <QString>
#include <QtGlobal>

#include "../vmisc/def.h"
#include "dialogtool.h"

namespace Ui
{
    class DialogArcWithLength;
}

class DialogArcWithLength : public DialogTool
{
    Q_OBJECT

public:
    DialogArcWithLength(const VContainer *data, quint32 toolId, QWidget *parent = nullptr);
    ~DialogArcWithLength();

    quint32       GetCenter() const;
    void          SetCenter(const quint32 &value);

    QString       GetRadius() const;
    void          SetRadius(const QString &value);

    QString       GetF1() const;
    void          SetF1(const QString &value);

    QString       GetLength() const;
    void          SetLength(const QString &value);

    QString       GetPenStyle() const;
    void          SetPenStyle(const QString &value);

    QString       GetColor() const;
    void          SetColor(const QString &value);

    qreal         GetApproximationScale() const;
    void          SetApproximationScale(qreal value);
public slots:
    virtual void  ChosenObject(quint32 id, const SceneObject &type) override;
    /**
     * @brief DeployFormulaTextEdit grow or shrink formula input
     */
    void DeployRadiusTextEdit();
    void DeployF1TextEdit();
    void DeployLengthTextEdit();

    void          FXRadius();
    void          FXF1();
    void          FXLength();

protected:
    virtual void  ShowVisualization() override;
    /**
     * @brief SaveData Put dialog data in local variables
     */
    virtual void  SaveData() override;
    virtual void  closeEvent(QCloseEvent *event) override;
    virtual bool  IsValid() const final;

private:
    Q_DISABLE_COPY(DialogArcWithLength)
    Ui::DialogArcWithLength *ui;

    /** @brief flagRadius true if value of radius is correct */
    bool          flagRadius;

    /** @brief flagF1 true if value of first angle is correct */
    bool          flagF1;

    bool          flagLength;

    /** @brief timerRadius timer of check formula of radius */
    QTimer        *timerRadius;

    /** @brief timerF1 timer of check formula of first angle */
    QTimer        *timerF1;

    QTimer        *timerLength;

    /** @brief radius formula of radius */
    QString       radius;

    /** @brief f1 formula of first angle */
    QString       f1;

    QString       length;

    /** @brief formulaBaseHeight base height defined by dialogui */
    int           formulaBaseHeightRadius;
    int           formulaBaseHeightF1;
    int           formulaBaseHeightLength;

    void          Radius();
    void          Length();
    void          EvalF();
};

//---------------------------------------------------------------------------------------------------------------------
inline bool DialogArcWithLength::IsValid() const
{
    return flagRadius && flagF1 && flagLength;
}

#endif // DIALOGARCWITHLENGTH_H
