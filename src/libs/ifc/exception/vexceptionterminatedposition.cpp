/************************************************************************
 **
 **  @file   vexceptionterminatedposition.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   24 6, 2019
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentina project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2019 Valentina project
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

#include "vexceptionterminatedposition.h"

//---------------------------------------------------------------------------------------------------------------------
VExceptionTerminatedPosition::VExceptionTerminatedPosition(const QString &error) V_NOEXCEPT_EXPR (true)
    :VException(error)
{}

//---------------------------------------------------------------------------------------------------------------------
VExceptionTerminatedPosition::VExceptionTerminatedPosition(const VExceptionTerminatedPosition &e)
V_NOEXCEPT_EXPR (true)
    :VException(e)
{}

//---------------------------------------------------------------------------------------------------------------------
VExceptionTerminatedPosition &VExceptionTerminatedPosition::operator=(const VExceptionTerminatedPosition &e)
V_NOEXCEPT_EXPR (true)
{
    if ( &e == this )
    {
        return *this;
    }
    VException::operator=(e);
    return *this;
}

//---------------------------------------------------------------------------------------------------------------------
VExceptionTerminatedPosition::~VExceptionTerminatedPosition() V_NOEXCEPT_EXPR (true)
{}

//---------------------------------------------------------------------------------------------------------------------
void VExceptionTerminatedPosition::raise() const
{
    throw *this;
}

//---------------------------------------------------------------------------------------------------------------------
VExceptionTerminatedPosition *VExceptionTerminatedPosition::clone() const
{
    return new VExceptionTerminatedPosition(*this);
}
