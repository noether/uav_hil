#ifndef SIRAMICOR_MISC_HH
#define SIRAMICOR_MISC_HH 1

#include <algorithm>
#include <sstream>
#include <cmath>
#include <type_traits>

namespace misc_internals
{
	template <typename T_>
	inline void CheckFloatingType(const T_ &)
	{
		static_assert(std::is_floating_point<T_>::value,
				"T needs to be a floating point type.");
	}
};

template <typename T_>
static inline T_ square(const T_ & t)
{
	return t * t;
}

template <typename T_>
static inline T_ cube(const T_ & t)
{
	return t * t * t;
}

template <typename T_>
static inline T_ rad_to_deg(const T_ & t)
{
	misc_internals::CheckFloatingType(t);
	return t * 180 / M_PI;
}

template <typename T_>
static inline T_ deg_to_rad(const T_ & t)
{
	misc_internals::CheckFloatingType(t);
	return t * M_PI / 180;
}

template <typename T_>
static inline T_ normalize_rad(T_ t)
{
	misc_internals::CheckFloatingType(t);
	while (t > M_PI)
		t -= 2 * M_PI;
	while (t <= -M_PI)
		t += 2 * M_PI;
	return t;
}

template <typename T_>
static inline T_ normalize_deg(T_ t)
{
	misc_internals::CheckFloatingType(t);
	while (t > 180)
		t -= 360;
	while (t <= -180)
		t += 360;
	return t;
}

template <typename T_>
static inline T_ sign(const T_ & t)
{
	return t >= 0 ? 1 : -1;
}

template <typename T_>
static inline T_ in_range(const T_ & min, const T_ & max, const T_ & t)
{
	return std::max(min, std::min(max, t));
}

template <typename T_>
inline std::string stringify(const T_ & t)
{
        std::ostringstream s;
        s << t;
        return s.str();
}

#endif
