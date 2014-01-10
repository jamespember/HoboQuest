#ifndef HOBO_PARSER
#define HOBO_PARSER

#include <iostream>
#include <string>
#include <unordered_map>

namespace hoboquest {
  class Engine;

  class Parser {
    protected:
      Engine &_engine;
      std::unordered_map<std::string, std::string> _current;
      std::string _token;
      std::istream &_in;
      std::string::size_type _pos = 0;
      bool _in_string = false;
      unsigned _depth = 0;

      void emit();
      bool next();
      void skip_delimeters();

    public:
      Parser(Engine &engine, std::istream &in);
  };
} /* hoboquest */ 

#endif
