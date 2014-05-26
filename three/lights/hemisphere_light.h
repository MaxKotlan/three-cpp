#ifndef THREE_HEMISPHERE_LIGHT_H
#define THREE_HEMISPHERE_LIGHT_H

#include <three/common.h>

#include <three/lights/light.h>

namespace three {

class HemisphereLight : public Light {

public:

  THREE_IMPL_OBJECT(HemisphereLight);

  static Ptr create( int skyColorHex, int groundColorHex, float intensity = 1 ) {

    return make_shared<HemisphereLight>( skyColorHex, groundColorHex, intensity );

  }

  Color groundColor;

protected:

  HemisphereLight( int skyColorHex, int groundColorHex, float intensity )
    : Light( skyColorHex, intensity ),
      groundColor( groundColorHex ) {

    position().set( 0, 100, 0 );

  }

  virtual Object3D::Ptr __clone( Object3D::Ptr target, bool recursive ) const {

    Ptr light = target ? std::static_pointer_cast<HemisphereLight>(target) : create( 0, 0 );

    Light::__clone( light, recursive );

    light->groundColor = groundColor;

    return light;

  }

};

} // namespace three

#endif // THREE_HEMISPHERE_LIGHT_H