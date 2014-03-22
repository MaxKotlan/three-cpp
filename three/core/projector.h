#ifndef THREE_PROJECTOR_HPP
#define THREE_PROJECTOR_HPP

#include <three/common.h>

#include <three/math/ray.h>
#include <three/math/vector3.h>

#include <three/renderers/renderables/renderable_object.h>

#include <three/utils/noncopyable.h>

#include <vector>

namespace three {

class Projector : public NonCopyable {
public:

  Projector();

  Vector3& projectVector( Vector3& vector, const Camera& camera );
  Vector3& unprojectVector( Vector3& vector, const Camera& camera );

  Ray pickingRay( Vector3 vector, const Camera& camera );

  struct RenderData {
    // TODO: Fill these with pointers AFTER creating with the pool
    std::vector<RenderableObject> objects;
    std::vector<RenderableObject> sprites;
    std::vector<Object3D*>        lights;
    std::vector<Renderable*>      elements;
  };

  RenderData& projectGraph( Object3D& root, bool sort );
  RenderData& projectScene( Scene& scene, Camera& camera, bool sort );

  struct Impl;

protected:

  std::unique_ptr<Impl> impl;

};

} // namespace three

#if defined(THREE_HEADER_ONLY)
# include <three/core/impl/projector.cpp>
#endif // defined(THREE_HEADER_ONLY)

#endif // THREE_PROJECTOR_HPP