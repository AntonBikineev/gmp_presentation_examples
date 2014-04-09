#include "pch.hpp"

template <class T>
struct pi_continued_fraction_term
{
   typedef std::pair<T, T> result_type;

   result_type operator()()
   {
      BOOST_MATH_STD_USING

      static T a = -1;
      a += 2;
      return std::make_pair(pow(a, 2), T(6));
   }
};

template <class T, class Policy>
inline T pi_continued_fraction(const Policy& pol)
{
   BOOST_MATH_STD_USING
   boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
   pi_continued_fraction_term<T> s;

   T result = boost::math::tools::continued_fraction_a(
      s,
      boost::math::policies::get_epsilon<T, Policy>(),
      max_iter);

   result = 3 + result;
   return result;
}

int main()
{
   using boost::multiprecision::mpf_float_100;

   mpf_float_100 pi = pi_continued_fraction<mpf_float_100>(boost::math::policies::policy<>());
   std::cout << pi.str() << std::endl;

   return 0;
}
