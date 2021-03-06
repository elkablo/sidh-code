#ifndef PQC_SIDH_PARAMS_HPP
#define PQC_SIDH_PARAMS_HPP

#include <vector>
#include <pqc_weierstrass.hpp>

namespace pqc
{

class sidh_params
{
public:
	enum class side {
		A,
		B
	};

	sidh_params() = delete;
	sidh_params(side);

	sidh_params other_side() const;

	side s;
	const std::vector<int>& strategy;
	const int &l, &e;
	const Z &prime, &le, &lem1;
	const WeierstrassPoint &P, &Q, &P_peer, &Q_peer;

private:
	static void initialize();

	static std::vector<int> s_strategy;
	static int la, ea, lb, eb;
	static Z p, lea, leam1, leb, lebm1;
	static WeierstrassCurveConstPtr E;
	static WeierstrassPoint Pa, Qa, Pb, Qb;
};

}

#endif /* PQC_SIDH_PARAMS_HPP */
