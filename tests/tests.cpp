#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

#include "../src/transit.h"
#include "../tests/tests.h"

using std::cout;
using std::endl;
using std::ostream;
using std::string;
TEST_CASE("test", "[pls]") {
  const string stop_path = "../dataset/teststop.csv";
  const string trip_path = "../dataset/testtrips.csv";
  Transit t = Transit(trip_path, stop_path);

  for (auto b : t.getBuses()) {
    cout << b.route_id << ", ";
  }
  cout << endl;

  for (auto s : t.getStops()) {
    cout << s.stop_id << ", ";
  }
  cout << endl;
  // for (auto b : t.getBusRoute()) {
  //   cout << b.first.bus_id << ", ";
  // }
  // cout << endl;

  // for (auto s : t.getBusService()) {
  //   cout << s.first.stop_id << ", ";
  // }
  // cout << endl;
  REQUIRE(t.getBusRoute().size() == 8);
  REQUIRE(t.getBusService().size() == 8);
}
