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
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <boost/any.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

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

		static string toString(const Value type);
	};

	Data();
	Data(const bool input);
	Data(const boost::posix_time::ptime &input);
	Data(const double input);
	Data(const int input);
	Data(const std::map<string, Data> &input);
	Data(const char *input);
	Data(const string &input);
	Data(const std::vector<Data> &input);
	Data(const std::initializer_list<Data> &input);

	bool operator==(const Data &other) const;
	bool operator!=(const Data &other) const;
	Data& operator[](const string &key) const;
	Data& operator[](const int &index) const;

	friend std::ostream& operator<<(std::ostream &os, const Data &data)
	{
		os << data.asString();
		return os;
	}

	void importData(const string &data, const Encoder &encoder);
	string exportData(const Decoder &decoder);

	Type::Value type() const;
	std::size_t size() const;
	bool empty() const;

	bool isBoolean() const;
	bool isDate() const;
	bool isDouble() const;
	bool isInt() const;
	bool isMap() const;
	bool isNone() const;
	bool isString() const;
	bool isVector() const;
	bool isNumber() const;

	string asString() const;
	double asDouble() const;
	int asInt() const;
	bool asBool() const;

	template<class T>
	void set(const T &data)
	{
		_data = data;
	}

	template<class T>
	T get() const
	{
		if (_data.empty() || _type == Type::NONE) {
			throw std::runtime_error("No data");
		}

		return boost::any_cast<T>(_data);
	}

private:
	Type::Value _type;
	boost::any _data;
};

DATAPLUS_NS_END

#endif // __DATAPLUS_DATA_HPP__
