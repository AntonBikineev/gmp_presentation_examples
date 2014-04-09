#include "pch.hpp"

template <class T>
struct chudnovsky_series_term
{
   typedef T result_type;

   chudnovsky_series_term():
      k(0)
   {
   }

   T operator()()
   {
      BOOST_MATH_STD_USING // Aid ADL for pow
      using boost::math::factorial;

      std::cout << "iteration no " << k << std::endl;
      const T num = factorial<T>(6 * k) * (a1 + (a2 * k));
      const T denom = (factorial<T>(3 * k) * pow(factorial<T>(k), 3)) * pow(b1, (3 * k));

      const T result = num / denom;
      std::cout << "result " << result << std::endl;

      if (k++ & 1)
         return -result;
      else
         return result;
   }

private:
   size_t k;

   static const T a1, a2, b1;
};

template<class T>
const T chudnovsky_series_term<T>::a1 = 13591409u;
template<class T>
const T chudnovsky_series_term<T>::a2 = 545140134u;
template<class T>
const T chudnovsky_series_term<T>::b1 = 640320u;


template <class T, class Policy>
inline T chudnovsky_pi(const Policy& pol)
{
   BOOST_MATH_STD_USING

   chudnovsky_series_term<T> s;
   boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();

   const T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
   return (426880 * sqrt(T(10005))) / result;
}

int main()
{
	using namespace boost::multiprecision;
	using float_type = number<backends::gmp_float<3000u>, et_on>;

	const float_type pi = chudnovsky_pi<float_type>(boost::math::policies::policy<>());
	std::cout << std::setprecision(std::numeric_limits<float_type>::digits10) << pi.str() << std::endl;
	return 0;
}
