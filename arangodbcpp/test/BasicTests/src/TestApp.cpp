////////////////////////////////////////////////////////////////////////////////
/// @brief C++ Library to interface to Arangodb tests.
///
/// DISCLAIMER
///
/// Copyright 2016 ArangoDB GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author John Bufton
/// @author Copyright 2016, ArangoDB GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include <velocypack/Slice.h>

#include "TestApp.h"

std::string TestApp::_ver = "2.8.2";
std::string TestApp::_url = "localhost";
uint16_t TestApp::_port = 8529;

namespace {

void usage() {
  using std::cout;
  using std::endl;
  cout << "BasicTests [Host url] [Host port] [db version] [Test options....]"
       << endl;
  cout << endl << "e.g BasicTests localhost 8529 2.8.2" << endl;
}
}

std::string TestApp::string(Slice& slice) {
  arangodb::velocypack::ValueLength len = slice.getStringLength();
  const char* pData = slice.getString(len);
  return std::string{pData, len};
}

TestApp::TestApp(int argc, char* argv[]) : _argc(argc), _argv(argv) {}

void TestApp::init() {
  _url = std::string{_argv[1]};
  {
    std::istringstream is{_argv[2]};
    is >> _port;
  }
  _ver = std::string{_argv[3]};
  _argc -= 3;
  _argv += 3;
}

int TestApp::run() {
  if (_argc < 4) {
    usage();
    return -1;
  }
  init();
  testing::InitGoogleTest(&_argc, _argv);
  return RUN_ALL_TESTS();
}
