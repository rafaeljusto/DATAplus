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

#include <boost/lexical_cast.hpp>

#include <dataplus/Data.hpp>

DATAPLUS_NS_BEGIN

string Data::Type::toString(const Value type)
{
	switch(type) {
	case BOOLEAN:
		return "boolean";
	case DATE:
		return "date";
	case DOUBLE:
		return "double";
	case INT:
		return "int";
	case MAP:
		return "map";
	case NONE:
		return "none";
	case STRING:
		return "string";
	case VECTOR:
		return "vector";
	}

	return "";
}

Data::Data() :
	_type(Type::NONE)
{
}

Data::Data(const bool input) :
	_type(Type::BOOLEAN),
	_data(input)
{
}

Data::Data(const boost::posix_time::ptime &input) :
	_type(Type::DATE),
	_data(input)
{
}

Data::Data(const double input) :
	_type(Type::DOUBLE),
	_data(input)
{
}

Data::Data(const int input) :
	_type(Type::INT),
	_data(input)
{
}

Data::Data(const std::map<string, Data> &input) :
	_type(Type::MAP),
	_data(input)
{
}

Data::Data(const char *input) :
	_type(Type::STRING),
	_data(string(input))
{
}

Data::Data(const string &input) :
	_type(Type::STRING),
	_data(input)
{
}

Data::Data(const std::vector<Data> &input) :
	_type(Type::VECTOR),
	_data(input)
{
}

Data::Data(const std::initializer_list<Data> &input) :
	_type(Type::VECTOR)
{
	std::vector<Data> inputTmp;
	inputTmp.insert(inputTmp.end(), input.begin(), input.end());
	_data = inputTmp;
}

bool Data::operator==(const Data &other) const
{
	if (_type != other._type) {
		return false;
	}

	switch(_type) {
	case Data::Type::BOOLEAN:
		return boost::any_cast<bool>(_data) == boost::any_cast<bool>(other._data);

	case Data::Type::DATE:
		return boost::any_cast<boost::posix_time::ptime>(_data) ==
			boost::any_cast<boost::posix_time::ptime>(other._data);

	case Data::Type::DOUBLE:
		return boost::any_cast<double>(_data) ==
			boost::any_cast<double>(other._data);

	case Data::Type::INT:
		return boost::any_cast<int>(_data) == boost::any_cast<int>(other._data);

	case Data::Type::MAP:
		return boost::any_cast<std::map<string, Data> >(_data) ==
			boost::any_cast<std::map<string, Data> >(other._data);

	case Data::Type::NONE:
		return true;

	case Data::Type::STRING:
		return boost::any_cast<string>(_data) ==
			boost::any_cast<string>(other._data);

	case Data::Type::VECTOR:
		return boost::any_cast<std::vector<Data> >(_data) ==
			boost::any_cast<std::vector<Data> >(other._data);
	}

	return false;
}

bool Data::operator!=(const Data &other) const
{
	return !(*this == other);
}

Data& Data::operator[](const string &key) const
{
	if (_data.type() == typeid(std::map<string, Data>)) {
		return boost::any_cast<std::map<string, Data> >(_data)[key];
	}

	throw std::runtime_error("Expected mapped object but found " +
	                         Data::Type::toString(_type) + " object");
}

Data& Data::operator[](const int &index) const
{
	if (_data.type() == typeid(std::vector<Data>)) {
		return boost::any_cast<std::vector<Data> >(_data)[index];
	}

	throw std::runtime_error("Expected vector object but found " +
	                         Data::Type::toString(_type) + " object");
}

void Data::importData(const string &data, const Encoder &encoder)
{
	*this = encoder(data);
}

string Data::exportData(const Decoder &decoder)
{
	return decoder(*this);
}

Data::Type::Value Data::type() const
{
	return _type;
}

std::size_t Data::size() const
{
	switch(_type) {
	case Data::Type::BOOLEAN:
	case Data::Type::DATE:
	case Data::Type::DOUBLE:
	case Data::Type::INT:
		return -1;

	case Data::Type::MAP:
		return boost::any_cast<std::map<string, Data> >(_data).size();

	case Data::Type::NONE:
		return -1;

	case Data::Type::STRING:
		return boost::any_cast<string>(_data).size();

	case Data::Type::VECTOR:
		return boost::any_cast<std::vector<Data> >(_data).size();
	}

	return -1;
}

bool Data::empty() const
{
	switch(_type) {
	case Data::Type::BOOLEAN:
	case Data::Type::DATE:
	case Data::Type::DOUBLE:
	case Data::Type::INT:
		return false;

	case Data::Type::MAP:
		return boost::any_cast<std::map<string, Data> >(_data).empty();

	case Data::Type::NONE:
		return true;

	case Data::Type::STRING:
		return boost::any_cast<string>(_data).empty();

	case Data::Type::VECTOR:
		return boost::any_cast<std::vector<Data> >(_data).empty();
	}

	return true;
}

bool Data::isBoolean() const
{
	return _type == Type::BOOLEAN;
}

bool Data::isDate() const
{
	return _type == Type::DATE;
}

bool Data::isDouble() const
{
	return _type == Type::DOUBLE;
}

bool Data::isInt() const
{
	return _type == Type::INT;
}

bool Data::isMap() const
{
	return _type == Type::MAP;
}

bool Data::isNone() const
{
	return _type == Type::NONE;
}

bool Data::isString() const
{
	return _type == Type::STRING;
}

bool Data::isVector() const
{
	return _type == Type::VECTOR;
}

bool Data::isNumber() const
{
	return _type == Type::DOUBLE || _type == Type::INT;
}

string Data::asString() const
{
	switch(_type) {
	case Data::Type::BOOLEAN:
		{
			bool value = boost::any_cast<bool>(_data);
			if (value) {
				return "true";
			} else {
				return "false";
			}
		}

	case Data::Type::DATE:
		return boost::posix_time::to_simple_string
			(boost::any_cast<boost::posix_time::ptime>(_data));

	case Data::Type::DOUBLE:
		return boost::lexical_cast<string>(boost::any_cast<double>(_data));

	case Data::Type::INT:
		return boost::lexical_cast<string>(boost::any_cast<int>(_data));

	case Data::Type::MAP:
		{
			string output("{");

			for (const std::pair<string, Data> &data :
				     boost::any_cast<std::map<string, Data> >(_data)) {
				output += data.first + " : " + data.second.asString();
			}

			output += "}";

			return output;
		}

	case Data::Type::NONE:
		return "";

	case Data::Type::STRING:
		return "'" + boost::any_cast<string>(_data) + "'";

	case Data::Type::VECTOR:
		{
			string output("[");

			bool filled = false;
			for (const Data &data : boost::any_cast<std::vector<Data> >(_data)) {
				output += data.asString() + ",";
				filled = true;
			}

			if (filled) {
				output = output.substr(0, output.size() - 1);
			}

			output += "]";

			return output;
		}
	}

	throw std::runtime_error("Cannot convert type " +
	                         Data::Type::toString(_type) + " to string");
}

double Data::asDouble() const
{
	switch(_type) {
	case Data::Type::BOOLEAN:
		return boost::lexical_cast<double>(boost::any_cast<bool>(_data));

	case Data::Type::DATE:
		break;

	case Data::Type::DOUBLE:
		return boost::any_cast<double>(_data);

	case Data::Type::INT:
		return boost::lexical_cast<double>(boost::any_cast<int>(_data));

	case Data::Type::MAP:
		break;

	case Data::Type::NONE:
		break;

	case Data::Type::STRING:
		break;

	case Data::Type::VECTOR:
		break;
	}

	throw std::runtime_error("Cannot convert type " +
	                         Data::Type::toString(_type) + " to double");
}

int Data::asInt() const
{
	switch(_type) {
	case Data::Type::BOOLEAN:
		return boost::lexical_cast<int>(boost::any_cast<bool>(_data));

	case Data::Type::DATE:
		// TODO: epoch?
		break;

	case Data::Type::DOUBLE:
		return boost::lexical_cast<int>(boost::any_cast<double>(_data));

	case Data::Type::INT:
		return boost::any_cast<int>(_data);

	case Data::Type::MAP:
		break;

	case Data::Type::NONE:
		break;

	case Data::Type::STRING:
		break;

	case Data::Type::VECTOR:
		break;
	}

	throw std::runtime_error("Cannot convert type " +
	                         Data::Type::toString(_type) + " to int");
}

bool Data::asBool() const
{
	switch(_type) {
	case Data::Type::BOOLEAN:
		return boost::any_cast<bool>(_data);

	case Data::Type::DATE:
		break;

	case Data::Type::DOUBLE:
		break;

	case Data::Type::INT:
		break;

	case Data::Type::MAP:
		break;

	case Data::Type::NONE:
		break;

	case Data::Type::STRING:
		break;

	case Data::Type::VECTOR:
		break;
	}

	throw std::runtime_error("Cannot convert type " +
	                         Data::Type::toString(_type) + " to boolean");
}

DATAPLUS_NS_END
