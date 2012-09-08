#ifndef THREE_LINE_HPP
#define THREE_LINE_HPP

#include <three/common.hpp>

#include <three/core/object3d.hpp>
#include <three/core/geometry.hpp>
#include <three/materials/material.hpp>

namespace three {

class Line : public Object3D {
public:

	typedef std::shared_ptr<Line> Ptr;

	static Ptr create( Geometry::Ptr geometry, Material::Ptr material, THREE::LineType lineType = THREE::LineStrip ) {
		//return make_shared<Line>( geometry, material, lineType );
		return Ptr( new Line( geometry, material, lineType ) );
	}

	/////////////////////////////////////////////////////////////////////////

	virtual THREE::Type type() const { return THREE::Line; }

	virtual void visit( Visitor& v ) { v( *this ); }
	virtual void visit( ConstVisitor& v ) const { v( *this ); }

	/////////////////////////////////////////////////////////////////////////

	Geometry::Ptr geometry;
	Material::Ptr material;

	THREE::LineType lineType;

protected:

	Line ( Geometry::Ptr geometry, Material::Ptr material, THREE::LineType lineType )
	 : Object3D(), geometry ( geometry ), material ( material ), lineType ( lineType ) {

		if ( geometry ) {

			if ( geometry->boundingSphere.radius == 0) {
				geometry->computeBoundingSphere();
			}

		}
	 }
};

struct ExtractLineData : public ConstVisitor {
	ExtractLineData( ) : geometry( nullptr ), material ( nullptr ) { }
	void operator() ( const Mesh& mesh ) {
		geometry = mesh.geometry.get();
		material = mesh.material.get();
	}
	const Geometry* geometry;
	const Material* material;
};

} // namespace three

#endif // THREE_MESH_HPP