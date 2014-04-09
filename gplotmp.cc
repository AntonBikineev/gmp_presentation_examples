#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include <boost/math/special_functions.hpp>
#include <boost/math/distributions/students_t.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/lexical_cast.hpp>
#include <gnuplot_i.hpp>

namespace
{

template <class T, class Func>
void plotFunction(Func&& func, T a, T b, size_t num = 40u)
{
	using std::vector;
	using std::generate;
	using std::transform;
	using std::string;
	using boost::lexical_cast;

	BOOST_ASSERT(num != 0);

	vector<T> x(num);
	vector<T> y(num);

	const T d = (b - a) / num;

	generate(x.begin(), x.end(), [&](){
			const T result = a;
			a += d;
			return a;
		});
	transform(x.begin(), x.end(), y.begin(), func);

	static Gnuplot gplot;
	gplot.set_xlabel(lexical_cast<string>(num) + " points");
	gplot.set_style("lines");
	gplot.set_grid();
	gplot.plot_xy(x, y);
}

template <class T, class Distr>
void plotPdf(Distr&& distr, T a, T b, size_t num = 40)
{
	using std::bind;
	using std::placeholders::_1;
	using boost::math::pdf;
	using boost::math::policies::policy;

	auto binded_pdf = bind(static_cast<T (*)(const Distr&, const T&)>(pdf<T, policy<> >), distr, _1);
	::plotFunction(binded_pdf, a, b, num);
}

} // namespace

int main()
{
	using namespace boost::math;
	//using boost::math::cyl_bessel_j_derivative;
	using std::placeholders::_1;

	//::plot(std::bind(cyl_bessel_j<double, double>, 3u, _1), -15., 15., 80u);
	//::plot(std::bind(cyl_bessel_j_derivative<double, double>, 3u, _1), -15., 15., 80u);
	//::plot(std::bind(hypergeometric_1f1<double, double, double>, 1u, 3u, _1), -100., 200., 8000u);
	::plotPdf(normal(), -30., 30., 500);
	::plotPdf(students_t(3), -30., 30., 500);
	::plotPdf(students_t(2), -30., 30., 500);

	std::cin.get();
}
