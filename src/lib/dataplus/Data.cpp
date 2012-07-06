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

#include <map>
#include <vector>

#include <dataplus/Data.hpp>

DATAPLUS_NS_BEGIN

Data::Data() :
	_type(Type::NONE)
{
}

Data& Data::operator[](const string &key) const
{
	if (_data.type() == typeid(std::map<string, Data>)) {
		return boost::any_cast<std::map<string, Data> >(_data)[key];
	}

	throw; // TODO
}

Data& Data::operator[](const int &index) const
{
	if (_data.type() == typeid(std::vector<Data>)) {
		return boost::any_cast<std::vector<Data> >(_data)[index];
	}

	throw; // TODO
}

void Data::importData(const string &data, const Encoder &encoder)
{
	*this = encoder(data);
}

string Data::exportData(const Decoder &decoder)
{
	return decoder(*this);
}

void Data::setType(const Type::Value type)
{
	_type = type;
}

Data::Type::Value Data::getType() const
{
	return _type;
}

DATAPLUS_NS_END
