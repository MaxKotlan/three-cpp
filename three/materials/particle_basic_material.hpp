#ifndef THREE_PARTICLE_BASIC_MATERIAL_HPP
#define THREE_PARTICLE_BASIC_MATERIAL_HPP

#include <three/common.hpp>

#include <three/materials/material.hpp>

namespace three {

class LineParticleMaterial : public Material {
public:

	typedef std::shared_ptr<LineParticleMaterial> Ptr;

	static Ptr create( const Parameters& parameters = Parameters() ) {
		return three::make_shared<LineParticleMaterial>( parameters );
	}

	/////////////////////////////////////////////////////////////////////////

	Ptr clone ( ) {
		return Material::clone( *this );
	}

protected:

	LineParticleMaterial ( const Parameters& parameters )
	  : Material() {
		fog = true;
		setParameters( parameters, DefaultKeys() );
	}

	static const ParameterKeys& DefaultKeys() {
		static std::array<std::string, 6> sKeys = {
			"color",
			"map",
			"size",
			"sizeAttenuation",
			"vertexColors",
			"fog"
		};
		static ParameterKeys sKeysSet(sKeys.begin(), sKeys.end());
		return sKeysSet;
	}

};

} // namespace three

#endif // THREE_MATERIAL_HPP

