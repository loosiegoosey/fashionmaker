/************************************************************************
 **
 **  @file   tst_valentinacommandline.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   4 10, 2015
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

#include "tst_valentinacommandline.h"
#include "../vmisc/vsysexits.h"

#include <QtTest>
#include <QGlobalStatic>

namespace
{
Q_GLOBAL_STATIC_WITH_ARGS(const QString, tmpTestFolder, (QLatin1String("tst_valentina_tmp")))
Q_GLOBAL_STATIC_WITH_ARGS(const QString, tmpTestCollectionFolder, (QLatin1String("tst_valentina_collection_tmp")))
}

TST_ValentinaCommandLine::TST_ValentinaCommandLine(QObject *parent)
    :AbstractTest(parent)
{
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_ValentinaCommandLine::initTestCase()
{
    {// Test files
        QDir tmpDir(*tmpTestFolder);
        if (not tmpDir.removeRecursively())
        {
            QFAIL("Fail to remove test temp directory.");
        }

        if (not CopyRecursively(QCoreApplication::applicationDirPath() + QDir::separator() +
                                QLatin1String("tst_valentina"),
                                QCoreApplication::applicationDirPath() + QDir::separator() + *tmpTestFolder))
        {
            QFAIL("Fail to prepare test files for testing.");
        }
    }

    {// Collection
        QDir tmpDir(*tmpTestCollectionFolder);
        if (not tmpDir.removeRecursively())
        {
            QFAIL("Fail to remove collection temp directory.");
        }

        if (not CopyRecursively(QCoreApplication::applicationDirPath() + QDir::separator() +
                                QLatin1String("tst_valentina_collection"),
                                QCoreApplication::applicationDirPath() + QDir::separator() + *tmpTestCollectionFolder))
        {
            QFAIL("Fail to prepare collection files for testing.");
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_ValentinaCommandLine::OpenPatterns_data() const
{
    QTest::addColumn<QString>("file");
    QTest::addColumn<QString>("arguments");
    QTest::addColumn<int>("exitCode");

    // The file doesn't exist!
    QTest::newRow("Send wrong path to a file")                                     << "wrongPath.val"
                                                                                   << "--test"
                                                                                   << V_EX_NOINPUT;

    QTest::newRow("Measurement independent empty file")                            << "empty.val"
                                                                                   << "--test"
                                                                                   << V_EX_OK;

    QTest::newRow("File with invalid object type")                                 << "wrong_obj_type.val"
                                                                                   << "--test"
                                                                                   << V_EX_NOINPUT;

    QTest::newRow("Empty text VAL file")                                           << "txt.val"
                                                                                   << "--test"
                                                                                   << V_EX_NOINPUT;

    QTest::newRow("Pattern with a warning")                                        << "test_pedantic.val"
                                                                                   << "--test;;--pedantic"
                                                                                   << V_EX_DATAERR;
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_ValentinaCommandLine::OpenPatterns()
{
    QFETCH(QString, file);
    QFETCH(QString, arguments);
    QFETCH(int, exitCode);

    QString error;
    const QString tmp = QCoreApplication::applicationDirPath() + QDir::separator() + *tmpTestFolder;
    const int exit = Run(exitCode, ValentinaPath(), QStringList() << arguments.split(";;")
                         << tmp + QDir::separator() + file, error);

    QVERIFY2(exit == exitCode, qUtf8Printable(error.right(350)));
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_ValentinaCommandLine::ExportMode_data() const
{
    QTest::addColumn<QString>("file");
    QTest::addColumn<QString>("arguments");
    QTest::addColumn<int>("exitCode");

    const QString tmp = QCoreApplication::applicationDirPath() + QDir::separator() + *tmpTestFolder;

    QTest::newRow("Issue #372")<< "issue_372.val"
                               << QString("-p;;0;;-d;;%1;;-b;;output;;--coefficient;;1").arg(tmp)
                               << V_EX_OK;

    QTest::newRow("A file with limited gradation. Multisize measurements. Wrong data.")
            << "glimited_vst.val"
            << QString("-p;;0;;-d;;%1;;--gsize;;46;;--gheight;;164;;-b;;output;;--coefficient;;1").arg(tmp)
            << V_EX_DATAERR;

    QTest::newRow("A file with limited gradation. Multisize measurements. Correct data.")
            << "glimited_vst.val"
            << QString("-p;;0;;-d;;%1;;--gsize;;40;;--gheight;;134;;-b;;output;;--coefficient;;1").arg(tmp)
            << V_EX_OK;

    QTest::newRow("A file with limited gradation. Individual measurements.")
            << "glimited_vit.val"
            << QString("-p;;0;;-d;;%1;;--gsize;;40;;--gheight;;134;;-b;;output;;--coefficient;;1").arg(tmp)
            << V_EX_DATAERR;

    QTest::newRow("A file with limited gradation. No measurements.")
            << "glimited_no_m.val"
            << QString("-p;;0;;-d;;%1;;--gsize;;40;;--gheight;;134;;-b;;output;;--coefficient;;1").arg(tmp)
            << V_EX_DATAERR;
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_ValentinaCommandLine::ExportMode()
{
    QFETCH(QString, file);
    QFETCH(QString, arguments);
    QFETCH(int, exitCode);

    QString error;
    const QString tmp = QCoreApplication::applicationDirPath() + QDir::separator() + *tmpTestFolder;
    const QStringList arg = QStringList() << tmp + QDir::separator() + file
                                          << arguments.split(";;");
    const int exit = Run(exitCode, ValentinaPath(), arg, error);

    QVERIFY2(exit == exitCode, qUtf8Printable(error.right(350)));
}

//---------------------------------------------------------------------------------------------------------------------
void TST_ValentinaCommandLine::TestMode_data() const
{
    QTest::addColumn<QString>("file");
    QTest::addColumn<QString>("arguments");
    QTest::addColumn<int>("exitCode");

    const QString tmp = QCoreApplication::applicationDirPath() + QDir::separator() + *tmpTestFolder;

    QTest::newRow("Issue #256. Correct path.")<< "issue_256.val"
                               << QString("--test")
                               << V_EX_OK;

    QTest::newRow("Issue #256. Wrong path.")<< "issue_256_wrong_path.vit"
                               << QString("--test")
                               << V_EX_NOINPUT;

    QTest::newRow("Issue #256. Correct individual measurements.")<< "issue_256.val"
                               << QString("--test;;-m;;%1").arg(tmp + QDir::separator() +
                                                                QLatin1String("issue_256_correct.vit"))
                               << V_EX_OK;

    QTest::newRow("Issue #256. Wrong individual measurements.")<< "issue_256.val"
                               << QString("--test;;-m;;%1").arg(tmp + QDir::separator() +
                                                                QLatin1String("issue_256_wrong.vit"))
                               << V_EX_NOINPUT;

    QTest::newRow("Issue #256. Correct multisize measurements.")<< "issue_256.val"
                               << QString("--test;;-m;;%1").arg(tmp + QDir::separator() +
                                                                QLatin1String("issue_256_correct.vst"))
                               << V_EX_OK;

    QTest::newRow("Issue #256. Wrong multisize measurements.")<< "issue_256.val"
                               << QString("--test;;-m;;%1").arg(tmp + QDir::separator() +
                                                                QLatin1String("issue_256_wrong.vst"))
                               << V_EX_NOINPUT;

    QTest::newRow("Wrong formula.")<< "wrong_formula.val"
                               << QString("--test")
                               << V_EX_DATAERR;
}

//---------------------------------------------------------------------------------------------------------------------
void TST_ValentinaCommandLine::TestMode()
{
    QFETCH(QString, file);
    QFETCH(QString, arguments);
    QFETCH(int, exitCode);

    QString error;
    const QString tmp = QCoreApplication::applicationDirPath() + QDir::separator() + *tmpTestFolder;
    const QStringList arg = QStringList() << tmp + QDir::separator() + file
                                          << arguments.split(";;");
    const int exit = Run(exitCode, ValentinaPath(), arg, error);

    QVERIFY2(exit == exitCode, qUtf8Printable(error.right(350)));
}

//---------------------------------------------------------------------------------------------------------------------
void TST_ValentinaCommandLine::TestOpenCollection_data() const
{
    QTest::addColumn<QString>("file");
    QTest::addColumn<QString>("arguments");
    QTest::addColumn<int>("exitCode");

    const QString tmp = QCoreApplication::applicationDirPath() + QDir::separator() + *tmpTestCollectionFolder;
    const QString testGOST = QString("--test;;-m;;%1").arg(tmp + QDir::separator() + QLatin1String("GOST_man_ru.vst"));
    const QString keyTest = QStringLiteral("--test");

    QTest::newRow("bra")               << "bra.val"               << keyTest  << V_EX_OK;
#ifdef Q_OS_WIN
    Q_UNUSED(testGOST)
#else
    QTest::newRow("jacketM1_52-176")   << "jacketM1_52-176.val"   << testGOST << V_EX_OK;
    QTest::newRow("jacketM2_40-146")   << "jacketM2_40-146.val"   << testGOST << V_EX_OK;
    QTest::newRow("jacketM3_40-146")   << "jacketM3_40-146.val"   << testGOST << V_EX_OK;
    QTest::newRow("jacketM4_40-146")   << "jacketM4_40-146.val"   << testGOST << V_EX_OK;
    QTest::newRow("jacketM5_30-110")   << "jacketM5_30-110.val"   << testGOST << V_EX_OK;
    QTest::newRow("jacketM6_30-110")   << "jacketM6_30-110.val"   << testGOST << V_EX_OK;
    QTest::newRow("pantsM1_52-176")    << "pantsM1_52-176.val"    << testGOST << V_EX_OK;
    QTest::newRow("pantsM2_40-146")    << "pantsM2_40-146.val"    << testGOST << V_EX_OK;
    QTest::newRow("pantsM7")           << "pantsM7.val"           << testGOST << V_EX_OK;
#endif
    QTest::newRow("TShirt_test")       << "TShirt_test.val"       << keyTest  << V_EX_OK;
    QTest::newRow("TestDart")          << "TestDart.val"          << keyTest  << V_EX_OK;
    QTest::newRow("MaleShirt")         << "MaleShirt.val"         << keyTest  << V_EX_OK;
    QTest::newRow("Trousers")          << "Trousers.val"          << keyTest  << V_EX_OK;
    QTest::newRow("Basic block women")      << "Basic_block_women-2016.val" << keyTest << V_EX_OK;
    QTest::newRow("Gent Jacket with tummy") << "Gent_Jacket_with_tummy.val" << keyTest << V_EX_OK;
    QTest::newRow("Steampunk_trousers")     << "Steampunk_trousers.val"     << keyTest << V_EX_OK;
#ifndef Q_OS_WIN
    QTest::newRow("pattern_blusa")     << "pattern_blusa.val"      << keyTest  << V_EX_OK;
    QTest::newRow("PajamaTopWrap2")    << "PajamaTopWrap2.val"    << keyTest  << V_EX_OK;
    QTest::newRow("Keiko_skirt")       << "Keiko_skirt.val"       << keyTest  << V_EX_OK;
    QTest::newRow("pantalon_base_Eli") << "pantalon_base_Eli.val" << keyTest  << V_EX_OK;
    QTest::newRow("modell_2")          << "modell_2.val"          << keyTest  << V_EX_OK;
    QTest::newRow("IMK_Zhaketa")       << "IMK_Zhaketa_poluprilegayuschego_silueta.val" << keyTest << V_EX_OK;
    QTest::newRow("Moulage_0.5_armhole_neckline") << "Moulage_0.5_armhole_neckline.val" << keyTest << V_EX_OK;
    QTest::newRow("0.7_Armhole_adjustment_0.10")  << "0.7_Armhole_adjustment_0.10.val"  << keyTest << V_EX_OK;
#endif
    // We have a problem with encoding in Windows when we try to open some files in terminal
}

//---------------------------------------------------------------------------------------------------------------------
void TST_ValentinaCommandLine::TestOpenCollection()
{
    QFETCH(QString, file);
    QFETCH(QString, arguments);
    QFETCH(int, exitCode);

    QString error;
    const QString tmp = QCoreApplication::applicationDirPath() + QDir::separator() + *tmpTestCollectionFolder;
    const QStringList arg = QStringList() << tmp + QDir::separator() + file
                                          << arguments.split(";;");
    const int exit = Run(exitCode, ValentinaPath(), arg, error);

    QVERIFY2(exit == exitCode, qUtf8Printable(error.right(350)));
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_ValentinaCommandLine::cleanupTestCase()
{
    {
        QDir tmpDir(*tmpTestFolder);
        if (not tmpDir.removeRecursively())
        {
            QWARN("Fail to remove test temp directory.");
        }
    }

    {
        QDir tmpDir(*tmpTestCollectionFolder);
        if (not tmpDir.removeRecursively())
        {
            QWARN("Fail to remove collection temp directory.");
        }
    }
}
