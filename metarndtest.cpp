#include "metarnd/metarnd.h"
#include "global_constexpr_counter.h"
#include <stdio.h>
#include <typeinfo>
// DBJ added
namespace {
	// DBJ added
	using namespace metarnd;
	// print cnt random numbers
	// generated at compile time
	template<int cnt, typename R>
	struct print_randoms
	{
		static void print()
		{
			typedef typename Next<R>::type RND;
			printf("\n%2.2d -- %lu", cnt, RND::value);
			print_randoms<cnt - 1, RND >::print();
		}
	};

	template<typename R>
	struct print_randoms<0, R>
	{
		static void print()
		{
			printf("\n%2.2d -- %lu", 0, Next<R>::value);
		}
	};
} // nspace

	// DBJ added
namespace dbj {



	namespace inner {
		using namespace metarnd;
		// use metarnd values as template argument
		using X = typename init<linear_congruential_engine<unsigned long>>::type;
		// The first random number provider
		typedef Next<X>::type X0;
		// the first random number 
		constexpr unsigned long rand_1 = X0::value;
		// The second random number provider
		typedef Next<X0>::type X1;
		// the second random number 
		constexpr unsigned long rand_2 = X1::value;
	}

	template< unsigned INC, unsigned long RND = inner::rand_2 >
	constexpr unsigned long next_uid() noexcept {
		unsigned long seed_ = RND;
		return RND + INC;
	}

	template<typename T, unsigned long ID>
	struct tagged final {
		typedef tagged type;
		constexpr static unsigned long id = ID;
	};

	inline void test2(const char * prompt_ = 0)
	{
		tagged<int,   next_uid<__COUNTER__>()> v1_;
		tagged<bool,  next_uid<__COUNTER__>()> v2_;
		tagged<float, next_uid<__COUNTER__>()> v3_;

		printf("\n %lu \n%lu \n%lu", v1_.id, v2_.id, v3_.id);
	}


	template< typename engine>
	inline void test ( const char * prompt_ ) 
	{
		printf( "\n\n%s\n\nEngine:\t%s", (prompt_? prompt_ : ""), typeid(engine).name());

		// Last template argument is the random seed. It is optional.
		typedef init<engine>::type X;

		// The first random number
		typedef Next<X>::type X0;
		constexpr auto rand_1 = X0::value;
		printf("\nThe first random number\t\t%lu" , X0::value ) ;

		// The second random number
		typedef Next<X0>::type X1;
		constexpr auto rand_2 = X1::value;
		printf("\nThe second random number\t\t%lu", X1::value);

		printf("\n5 random numbers");
		print_randoms<5, typename Random<engine>::type >::print();
	};
}

extern "C" void compile_time_random();

int main()
{
	compile_time_random();

	dbj_compile_time_values_test();
	// global_constexpr_counter_test();
	dbj::test2();
	// DBJ added
	using namespace metarnd;
	// DBJ added
	// always use long aka _int32, not long long aka _int64
	using unsigned_integral = unsigned long; // _int32;

	dbj::test < fib_engine<unsigned_integral, 0xFFFF, 0xFF>>("Mickey Mouse engine");
	dbj::test < substract_with_carry_engine<unsigned_integral, 10, 2, 1, 3> >("");
	dbj::test < linear_congruential_engine<unsigned_integral> >(
		"\nInside one run, on every call we will get the same numbers"
		"\nWe will also get them between the run's of the executable"
		);
}
