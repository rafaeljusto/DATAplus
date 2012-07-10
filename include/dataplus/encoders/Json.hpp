/*
  DATAplus Copyright (C) 2012 Rafael Dantas Justo

  This file is part of DATAplus.

  DATAplus is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  DATAplus is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with DATAplus.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __DATAPLUS_ENCODERS_JSON_HPP__
#define __DATAPLUS_ENCODERS_JSON_HPP__

#include <dataplus/Data.hpp>
#include <dataplus/Dataplus.hpp>

DATAPLUS_ENCODER_NS_BEGIN

dataplus::Data encode(const string &input);

DATAPLUS_ENCODER_NS_END

#endif // __DATAPLUS_ENCODERS_JSON_HPP__
