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

#ifndef __DATAPLUS_DATA_HPP__
#define __DATAPLUS_DATA_HPP__

#include <functional>
#include <string>

#include <boost/any.hpp>

#include "Dataplus.hpp"

using std::string;

DATAPLUS_NS_BEGIN

class Data;
typedef std::function<Data(const string &)> Encoder;
typedef std::function<string(const Data &data)> Decoder;

class Data
{
public:
	class Type {
	public:
		enum Value {
			BOOLEAN,
			DATE,
			DOUBLE,
			INT,
			MAP,
			NONE,
			STRING,
			VECTOR
		};
	};

	Data();

	Data& operator[](const string &key) const;
	Data& operator[](const int &index) const;

	void importData(const string &data, const Encoder &encoder);
	string exportData(const Decoder &decoder);

	void setType(const Type::Value type);
	Type::Value getType() const;

	template<class T>
	void set(const T &data)
	{
		_data = data;
	}

	template<class T>
	T get() const
	{
		return boost::any_cast<T>(_data);
	}

private:
	Type::Value _type;
	boost::any _data;
};

DATAPLUS_NS_END

#endif // __DATAPLUS_DATA_HPP__
