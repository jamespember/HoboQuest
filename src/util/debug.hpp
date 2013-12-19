#ifdef DEBUGGING
  #include "iostream"
  #define DEBUG(x) do { std::cerr << x << std::endl; } while (0)
#else
  #define DEBUG(x) do {} while (0)
#endif
