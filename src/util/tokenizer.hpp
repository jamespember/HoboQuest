#ifndef HOBO_TOKENIZER
#define HOBO_TOKENIZER

#include <string>

// Source: http://stackoverflow.com/a/1493195
template<class ContainerT>
void tokenize(const std::string &str, ContainerT &tokens,
    const std::string &delims = " ", bool trimEmpty = true) {

  typedef ContainerT Base;
  typedef typename Base::value_type ValueType;
  typedef typename ValueType::size_type SizeType;

  std::string::size_type pos, lastPos = 0;

  while (true) {
    pos = str.find_first_of(delims, lastPos);

    if (pos == std::string::npos) {
      pos = str.length();
      if (pos != lastPos || !trimEmpty)
        tokens.push_back(ValueType(str.data() + lastPos, (SizeType) pos - lastPos));
      break;
    } else {
      if (pos != lastPos || !trimEmpty)
        tokens.push_back(ValueType(str.data() + lastPos, (SizeType) pos - lastPos));
    }

    lastPos = pos + 1;
  }
};

#endif
