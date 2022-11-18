#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

#include "../src/transit.h"
#include "../tests/tests.h"

using std::ostream;
using std::string;

TEST_CASE("test", "[pls]") {
  string stop_path = "../dataset/teststop.csv";
  string trip_path = "../dataset/testtrip.csv";
  Transit t = Transit(stop_path, trip_path);
  REQUIRE(t.getBusRoute().size() == 8);
  REQUIRE(t.getBusService().size() == 8);
}
