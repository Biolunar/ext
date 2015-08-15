#include "ext/color.hpp"
#include "ext/vector2.hpp"
#include "ext/vector3.hpp"
#include "ext/vector4.hpp"
#include "ext/matrix2.hpp"

#include <cassert>

#include <iostream>

#ifdef NDEBUG
#error "Tests cannot be build with NDEBUG defined"
#endif


int main()
{
	//--<<//>>--// color //--<<//>>--//
	ext::colorf c1;
	ext::colorf c2;
	ext::colorf c3 = c1 * c2;

	::std::cout << u8"Hello world!\n";
}
