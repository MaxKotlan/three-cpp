#ifndef THREE_GEOMETRY_H
#define THREE_GEOMETRY_H

#include <three/common.h>

#include <three/core/geometry_buffer.h>
#include <three/core/geometry_group.h>

#include <three/math/math.h>
#include <three/math/color.h>
#include <three/math/vector3.h>
#include <three/math/box3.h>
#include <three/math/sphere.h>
#include <three/core/interfaces.h>

#include <three/materials/material.h>


#include <three/utils/memory.h>

#include <array>
#include <unordered_map>
#include <tuple>

namespace three {

struct MorphTarget {
  std::string name;
  std::vector<Vertex> vertices;
};

class Geometry : public IGeometry, public GeometryBuffer {

public:

  typedef std::shared_ptr<Geometry> Ptr;

  static Ptr create() {
    return make_shared<Geometry>();
  }

  virtual enums::GeometryType type() const {
    return enums::Geometry;
  }

  int id;

  const std::string uuid;

  std::string name;

  std::vector<Vertex> vertices;

  std::vector<Color> colors; // one-to-one vertex colors, used in ParticleSystem, Line and Ribbon

  std::vector<Material::Ptr> materials;
  Attributes attributes;

  std::vector<Face> faces;

  std::vector<std::vector<Vector2>> faceUvs;
  std::vector<std::vector<std::array<Vector2, 4>>> faceVertexUvs;

  std::vector<MorphTarget> morphTargets;
  std::vector<Color> morphColors;
  //std::vector<Vector3> morphNormals;
  std::vector<Face> morphNormals;

  std::vector<Vector3> skinVerticesA;
  std::vector<Vector3> skinVerticesB;
  std::vector<Vector4> skinWeights;
  struct SkinIndices {
    int x, y, z, w;
  };
  std::vector<SkinIndices> skinIndices;

  struct Offset {
    int index, count, start;
  };
  std::vector<Offset> offsets;

  Box3::Ptr boundingBox;
  Sphere::Ptr boundingSphere;

  bool hasTangents;
  bool dynamic;

  std::unordered_map<std::string, GeometryGroup::Ptr> geometryGroups;
  std::vector<GeometryGroup*> geometryGroupsList;

  bool verticesNeedUpdate;
  bool morphTargetsNeedUpdate;
  bool elementsNeedUpdate;
  bool uvsNeedUpdate;
  bool normalsNeedUpdate;
  bool tangentsNeedUpdate;
  bool colorsNeedUpdate;

  virtual void applyMatrix( Matrix4& matrix );

  virtual void computeCentroids();
  virtual void computeFaceNormals();
  virtual void computeVertexNormals();
  virtual void computeTangents();
  virtual void computeBoundingBox();
  virtual void computeBoundingSphere();

  void mergeVertices();

protected:

  Geometry();
  virtual ~Geometry();

private:

  std::vector<Vector3> normals;

  static int& GeometryCount() {
    static int sGeometryCount = 0;
    return sGeometryCount;
  }

};

} // namespace three

#endif // THREE_GEOMETRY_H