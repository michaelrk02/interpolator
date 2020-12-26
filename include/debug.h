#pragma once

#include <iostream>

#ifndef NDEBUG
#define DUMP(_X) ::std::cout << #_X << ": " << (_X) << ::std::endl
#else
#define DUMP(_X)
#endif

#ifndef NDEBUG
#define TRACE(_X) ::std::cout << (_X) << ::std::endl
#else
#define TRACE(_X)
#endif

