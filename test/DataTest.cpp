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
#include <string>
#include <vector>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>

#include <dataplus/Data.hpp>

using std::string;
using dataplus::Data;

// When you need to run only one test, compile only this file with the
// STAND_ALONE flag.
#ifdef STAND_ALONE
#define BOOST_TEST_MODULE DATAplus
#endif

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(dataplusTests)

BOOST_AUTO_TEST_CASE(implicitConstructorMustWork)
{
	Data data1 = true;
	BOOST_CHECK_EQUAL(data1.get<bool>(), true);

	Data data2 = 1.1;
	BOOST_CHECK_EQUAL(data2.get<double>(), 1.1);

	Data data3 = 1;
	BOOST_CHECK_EQUAL(data3.get<int>(), 1);

	typedef std::map<string, Data> map;

	map input4;
	Data data4 = input4;
	//BOOST_CHECK_EQUAL(data4.get<map>(), input4);

	Data data5 = "abc123";
	BOOST_CHECK_EQUAL(data5.get<string>(), "abc123");

	Data data6 = string("abc123");
	BOOST_CHECK_EQUAL(data6.get<string>(), "abc123");

	std::vector<Data> input7;
	Data data7 = input7;
	//BOOST_CHECK_EQUAL(data7.get<std::vector<Data> >(), input7);

	Data data8 = { "array ", "of ", 4, " elements" };

	Data data9 = boost::posix_time::time_from_string("2012-07-08");
	BOOST_CHECK_EQUAL(data9.get<boost::posix_time::ptime>(), 
	                  boost::posix_time::time_from_string("2012-07-08"));
}

BOOST_AUTO_TEST_CASE(mustImportDataCorrectly)
{
	Data data;
	data.importData("1", [](const string &input) {
			Data data;
			data.setType(Data::Type::INT);
			data.set<int>(boost::lexical_cast<int>(input));
			return data;
		});

	BOOST_CHECK_EQUAL(data.getType(), Data::Type::INT);
	BOOST_CHECK_EQUAL(data.get<int>(), 1);
}

BOOST_AUTO_TEST_CASE(mustExportDataCorrectly)
{
	Data data;
	data.importData("1", [](const string &input) {
			Data data;
			data.setType(Data::Type::INT);
			data.set<int>(boost::lexical_cast<int>(input));
			return data;
		});

	string output = data.exportData([](const Data &data) {
			int output = data.get<int>();
			return boost::lexical_cast<string>(output);
		});

	BOOST_CHECK_EQUAL(output, "1");
}

BOOST_AUTO_TEST_SUITE_END()
