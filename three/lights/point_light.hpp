#ifndef THREE_POINT_LIGHT_HPP
#define THREE_POINT_LIGHT_HPP

#include <three/common.hpp>

#include <three/lights/light.hpp>

namespace three {

class PointLight : public Light {
public:

	typedef std::shared_ptr<PointLight> Ptr;

	static Ptr create( int hex, float intensity = 1, float distance = 0 ) {
		return std::make_shared<PointLight>( hex, intensity, distance );
	}

	/////////////////////////////////////////////////////////////////////////

	float intensity;
	float distance;

	/////////////////////////////////////////////////////////////////////////


private:

	PointLight ( int hex, float intensity, float distance )
	 : Light ( hex ), intensity ( intensity ), distance ( distance ) {

		position.set ( 0, 0, 0 );

	}

};

} // namespace three

#endif // THREE_POINT_LIGHT_HPP