#include "pch.hpp"

using namespace boost::multiprecision;
using namespace boost::random;

int main()
{
   uniform_real_distribution<mpf_float_50> uf(-1, 1);
   independent_bits_engine<mt19937, 50L*1000L/301L, mpz_int> gen;

   mpz_int count_inside = 0;
   const mpz_int count = 1000000;
   for (mpz_int k = 0; k < count; ++k)
   {
      mpf_float_50 point = boost::math::hypot(uf(gen), uf(gen));

      if (point < 1)
         ++count_inside;
   }

   mpf_float_50 pi = (mpf_float_50(4.) * count_inside) / count;

   std::cout << pi.str() << std::endl;

   return 0;
}
