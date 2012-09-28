#ifndef THREE_MESH_HPP
#define THREE_MESH_HPP

#include <three/core/object3d.hpp>
#include <three/core/geometry.hpp>
#include <three/materials/material.hpp>

//#include <three/common.hpp>

#include <vector>
#include <unordered_map>
#include <memory>

namespace three {

class Mesh : public Object3D {
public:

  typedef std::shared_ptr<Mesh> Ptr;

  static Ptr create( Geometry::Ptr geometry, Material::Ptr material ) {
    return three::make_shared<Mesh>( geometry, material );
  }

  /////////////////////////////////////////////////////////////////////////

  virtual THREE::Type type() const { return THREE::Mesh; }

  virtual void visit( Visitor& v ) { v( *this ); }
  virtual void visit( ConstVisitor& v ) const { v( *this ); }

  /////////////////////////////////////////////////////////////////////////

  float boundRadius;
  int morphTargetBase;

  std::vector<int> morphTargetForcedOrder;
  std::vector<int> morphTargetInfluences;
  std::unordered_map<std::string, int> morphTargetDictionary;

  /////////////////////////////////////////////////////////////////////////

  int getMorphTargetIndexByName( const std::string& name ) {
    auto morphTargetIndexIter = morphTargetDictionary.find( name );
    if ( morphTargetIndexIter != morphTargetDictionary.end() )
      return morphTargetIndexIter->second;

    console().log( "Three.Mesh.getMorphTargetIndexByName: morph target does not exist, returning 0" );
    return 0;
  }

protected:

  Mesh( Geometry::Ptr geometry, Material::Ptr material )
    : Object3D( material, geometry ),
      boundRadius( 0 ), morphTargetBase( -1 ) {

    if ( geometry ) {

      if ( geometry->boundingSphere.radius == 0 ) {
        geometry->computeBoundingSphere();
      }

      boundRadius = geometry->boundingSphere.radius;

      // setup morph targets

      if ( geometry->morphTargets.size() > 0 ) {

        morphTargetBase = -1;
        int m = 0;

        for ( const auto& morphTarget : geometry->morphTargets ) {
          morphTargetInfluences.push_back( 0 );
          morphTargetDictionary[ morphTarget.name ] = m++;
        }
      }
    }
  }
};

} // namespace three

#endif // THREE_MESH_HPP