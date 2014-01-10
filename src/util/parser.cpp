#include "parser.hpp"
#include "../engine.hpp"

#include <iostream>
#include <string>
#include <unordered_map>

namespace hoboquest {
  Parser::Parser(Engine &engine, std::istream &in) :
  _engine(engine), _in(in) {
    while (next());
  }

  void Parser::emit() {
    _engine.import_entity(_current);
    _current.clear();
    // in_string = false;
    // --depth;
  }

  bool Parser::next() {
    _token.clear();
    return false;
  }

  // unsigned Parser::indendation() {

  // }

  // void Parser::skip_delimeters() {
    // char c;
    // while (_in.good() && _in.get)
  // }
} /* hoboquest */ 
