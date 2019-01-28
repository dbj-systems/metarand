#pragma once
#include <cassert>
#include <string_view>

namespace {

	namespace inner {
		// inline's added by DBJ
		constexpr inline char inits[] = __TIMESTAMP__; // __TIME__;
		constexpr unsigned int cti_[]{ 0,1,2,3,4,5,6,7,8,9 };
	}
	// constexpr bellow added by DBJ
	constexpr const inline unsigned long timestamp_compiletime_hash_ = 
		(inner::inits[0] - '0') * 100000 + (inner::inits[1] - '0') * 10000 +
		(inner::inits[3] - '0') * 1000 + (inner::inits[4] - '0') * 100 + 
		(inner::inits[6] - '0') * 10 + inner::inits[7] - '0';

	using namespace std::string_view_literals;
	constexpr std::string_view dbj_compile_time_values () {
		// store each zero padded number 00 .. 99 as two chars
		return "000102030405060708091011"sv; // until e.g. 99
	}

	// or as simple as this
	constexpr unsigned int dbj_compile_time_int( const int n) {
		return inner::cti_[n];
	}
}

void dbj_compile_time_values_test()
{
	constexpr std::string_view ctv_ = dbj_compile_time_values();
	constexpr std::string_view  number_two = ctv_.substr(4, 2);

	constexpr unsigned int second_ = dbj_compile_time_int(1);
	constexpr unsigned long timestamp_ = timestamp_compiletime_hash_;
	auto ts_ = (const char *)inner::inits;
}
