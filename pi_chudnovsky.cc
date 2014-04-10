#include "pch.hpp"

template <class T>
struct chudnovsky_series_term
{
   typedef T result_type;

   T operator()()
   {
      BOOST_MATH_STD_USING // Aid ADL for pow
      using boost::math::factorial;

      static size_t k = 0;

      const T num = factorial<T>(6 * k) * (a1 + (a2 * k));
      const T denom = (factorial<T>(3 * k) * pow(factorial<T>(k), 3)) * pow(b1, (3 * k));
      const T result = num / denom;

      return (k++ & 1) ? -result : result;
   }

private:
   static const T a1, a2, b1;
};

template<class T>
const T chudnovsky_series_term<T>::a1 = 13591409u;
template<class T>
const T chudnovsky_series_term<T>::a2 = 545140134u;
template<class T>
const T chudnovsky_series_term<T>::b1 = 640320u;


template <class T>
inline T chudnovsky_pi()
{
   BOOST_MATH_STD_USING
   using boost::math::policies::get_max_series_iterations;
   using boost::math::policies::get_epsilon;
   using boost::math::policies::policy;

   chudnovsky_series_term<T> s;
   boost::uintmax_t max_iter = get_max_series_iterations<policy<> >();

   const T result = boost::math::tools::sum_series(s, get_epsilon<T, policy<> >(), max_iter);
   return (426880u * sqrt(T(10005u))) / result;
}

int main()
{
   using namespace boost::multiprecision;
   using float_type = number<backends::gmp_float<3000u>, et_on>;
   
   const float_type pi = chudnovsky_pi<float_type>();
   std::cout << pi.str() << std::endl;
   return 0;
}
