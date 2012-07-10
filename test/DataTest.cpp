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

	Data data4 = map();
	BOOST_CHECK(data4.get<map>() == map());

	Data data5 = "abc123";
	BOOST_CHECK_EQUAL(data5.get<string>(), "abc123");

	Data data6 = string("abc123");
	BOOST_CHECK_EQUAL(data6.get<string>(), "abc123");

	Data data7 = std::vector<Data>();
	BOOST_CHECK(data7.get<std::vector<Data> >() == std::vector<Data>());

	Data data8 = boost::posix_time::time_from_string("2012-07-08");
	BOOST_CHECK_EQUAL(data8.get<boost::posix_time::ptime>(), 
	                  boost::posix_time::time_from_string("2012-07-08"));
}

BOOST_AUTO_TEST_CASE(mustAcceptInitializerList)
{
	Data data = { "array ", "of ", 4, " elements" };

	std::vector<Data> list;
	list.push_back(Data("array "));
	list.push_back(Data("of "));
	list.push_back(Data(4));
	list.push_back(Data(" elements"));

	BOOST_CHECK(data.get<std::vector<Data> >() == list);
}

BOOST_AUTO_TEST_CASE(retrieveUninitializedData)
{
	Data data;
	BOOST_CHECK_THROW(data.get<int>(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(mustImportDataCorrectly)
{
	Data data;
	data.importData("1", [](const string &input) {
			return Data(boost::lexical_cast<int>(input));
		});

	BOOST_CHECK_EQUAL(data.type(), Data::Type::INT);
	BOOST_CHECK_EQUAL(data.get<int>(), 1);
}

BOOST_AUTO_TEST_CASE(mustExportDataCorrectly)
{
	Data data;
	data.importData("1", [](const string &input) {
			return Data(boost::lexical_cast<int>(input));
		});

	string output = data.exportData([](const Data &data) {
			return boost::lexical_cast<string>(data.get<int>());
		});

	BOOST_CHECK_EQUAL(output, "1");
}

BOOST_AUTO_TEST_SUITE_END()
