/************************************************************************
 **
 **  @file   ifcdef.h
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   10 12, 2014
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2013-2015 Valentina project
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

#ifndef IFCDEF_H
#define IFCDEF_H

#include <QtGlobal>

#ifdef Q_OS_WIN32
    extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;
    #include <windows.h>
#endif /*Q_OS_WIN32*/

enum class Unit : char { Mm, Cm, Inch, Px };

static const quint32 null_id = 0;

#define NULL_ID null_id//use this value for initialization variables that keeps id values. 0 mean uknown id value.
#define NULL_ID_STR "0"

// Detect whether the compiler supports C++11 noexcept exception specifications.
#  if   defined(__clang__)
#    if __has_feature(cxx_noexcept)
#      define V_NOEXCEPT_EXPR(x) noexcept(x) // Clang 3.0 and above have noexcept
#    endif
#  elif defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define V_NOEXCEPT_EXPR(x) noexcept(x) // GCC 4.7 and following have noexcept
#    endif
#  elif defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 180021114
#    define QMUP_NOEXCEPT_EXPR(x) noexcept(x)
#  else
#    define V_NOEXCEPT_EXPR(x)
#  endif

extern const qreal PrintDPI;

qreal WidthMainLine(Unit patternUnit);
qreal WidthHairLine(Unit patternUnit);

double ToPixel(double val, const Unit &unit);
double FromPixel(double pix, const Unit &unit);

qreal UnitConvertor(qreal value, const Unit &from, const Unit &to);

#endif // IFCDEF_H
