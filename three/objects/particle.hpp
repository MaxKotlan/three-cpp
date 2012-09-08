#ifndef THREE_PARTICLE_HPP
#define THREE_PARTICLE_HPP

#include <three/common.hpp>

#include <three/core/object3d.hpp>
#include <three/materials/material.hpp>

namespace three {

class Particle : public Object3D {
public:

	typedef std::shared_ptr<Particle> Ptr;

	static Ptr create( Material::Ptr material ) {
		//return make_shared<Line>( geometry, material, lineType );
		return Ptr( new Particle( material ) );
	}

	/////////////////////////////////////////////////////////////////////////

	virtual THREE::Type type() const { return THREE::Particle; }

	virtual void visit( Visitor& v ) { v( *this ); }
	virtual void visit( ConstVisitor& v ) const { v( *this ); }

	/////////////////////////////////////////////////////////////////////////

	Material::Ptr material;

protected:

	Particle ( Material::Ptr material )
	 : Object3D(), material ( material ) { }

};

} // namespace three

#endif // THREE_PARTICLE_HPP