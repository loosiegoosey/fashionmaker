/************************************************************************
 **
 **  @file   vapplication.h
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

#ifndef VAPPLICATION_H
#define VAPPLICATION_H

#include "../vmisc/vabstractapplication.h"
#include "../vwidgets/vmaingraphicsview.h"
#include "../vpatterndb/vtranslatevars.h"
#include "vsettings.h"
#include "vcmdexport.h"

class VApplication;// use in define

#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<VApplication*>(VAbstractApplication::instance()))

/**
 * @brief The VApplication class reimplamentation QApplication class.
 */
class VApplication : public VAbstractApplication
{
    Q_OBJECT
public:

    VApplication(int &argc, char ** argv);
    virtual ~VApplication() override;
    static void        NewValentina(const QString &fileName = QString());
    virtual bool       notify(QObject * receiver, QEvent * event) override;

    void               InitOptions();

    QString            TapeFilePath() const;

    QTimer             *getAutoSaveTimer() const;
    void               setAutoSaveTimer(QTimer *value);

    static QStringList LabelLanguages();

    void               StartLogging();
    void               ActivateDarkMode();
    QTextStream       *LogFile();

    virtual const VTranslateVars *TrVars() override;

    bool static IsGUIMode();
    virtual bool IsAppInGUIMode() const override;
    virtual bool IsPedantic() const override;

    virtual void OpenSettings() override;
    VSettings *ValentinaSettings();

protected:
    virtual void       InitTrVars() override;
    virtual bool	   event(QEvent *e) override;

protected slots:
    virtual void AboutToQuit() override;

private:
    Q_DISABLE_COPY(VApplication)
    VTranslateVars     *trVars;
    QTimer             *autoSaveTimer;

    QSharedPointer<VLockGuard<QFile>> lockLog;
    std::shared_ptr<QTextStream> out;

    QString            LogDirPath()const;
    QString            LogPath()const;
    bool               CreateLogDir()const;
    void               BeginLogging();
    void               ClearOldLogs()const;

public:
    //moved to the end of class so merge should go
    const VCommandLinePtr     CommandLine() const;
};

//---------------------------------------------------------------------------------------------------------------------
inline QTimer *VApplication::getAutoSaveTimer() const
{
    return autoSaveTimer;
}

//---------------------------------------------------------------------------------------------------------------------
inline void VApplication::setAutoSaveTimer(QTimer *value)
{
    autoSaveTimer = value;
}
//---------------------------------------------------------------------------------------------------------------------


#endif // VAPPLICATION_H
