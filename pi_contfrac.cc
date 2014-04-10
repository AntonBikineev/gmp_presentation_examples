#include "pch.hpp"

template <class T>
struct pi_continued_fraction_term
{
   typedef std::pair<T, T> result_type;

   std::pair<T, T> operator()() const
   {
      BOOST_MATH_STD_USING

      static T a = -1;
      a += 2;

      return std::make_pair(pow(a, 2), T(6));
   }
};

template <class T>
inline T pi_fraction()
{
   BOOST_MATH_STD_USING
   using boost::math::policies::get_max_series_iterations;
   using boost::math::policies::get_epsilon;
   using boost::math::policies::policy;

   pi_continued_fraction_term<T> s;
   boost::uintmax_t max_iter = get_max_series_iterations<policy<> >();

   T result = boost::math::tools::continued_fraction_a(
      s,
      get_epsilon<T, policy<> >(),
      max_iter);

   result = 3 + result;
   return result;
}

int main()
{
   using boost::multiprecision::mpf_float_100;

   mpf_float_100 pi = pi_fraction<mpf_float_100>();
   std::cout << pi.str() << std::endl;

   return 0;
}
