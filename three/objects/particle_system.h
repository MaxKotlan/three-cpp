#ifndef THREE_PARTICLE_SYSTEM_H
#define THREE_PARTICLE_SYSTEM_H

#include <three/common.h>

#include <three/visitor.h>
#include <three/core/object3d.h>
#include <three/materials/material.h>
#include <three/materials/particle_system_material.h>

namespace three {

class ParticleSystem : public Object3D {
public:

  THREE_IMPL_OBJECT(ParticleSystem)

  static Ptr create( const Geometry::Ptr& geometry, const Material::Ptr& material ) {
    return three::make_shared<ParticleSystem> ( geometry, material );
  }

protected:

  ParticleSystem( const Geometry::Ptr& geometry, const Material::Ptr& material )
    : Object3D( material, geometry ) {

    frustumCulled = false;
    if(!material) {
      Properties<std::string, any> params;
      params["color"] = Math::random() * 0xffffff;
      this->material = ParticleSystemMaterial::create( params );
    }
  }

  // TODO "ParticleSystem::_clone"

};

} // namespace three

#endif // THREE_PARTICLE_SYSTEM_H