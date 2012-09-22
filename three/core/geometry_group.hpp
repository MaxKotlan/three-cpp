#ifndef THREE_GEOMETRY_GROUP_HPP
#define THREE_GEOMETRY_GROUP_HPP

#include <three/common.hpp>

#include <three/core/geometry_buffer.hpp>

#include <vector>

namespace three {

struct GeometryGroup : public GeometryBuffer {

    typedef GeometryBuffer::GLBuffer GLBuffer;

    int id;

    std::vector<std::vector<float>>   __morphNormalsArrays;
    std::vector<std::vector<float>>   __morphTargetsArrays;

    std::vector<int>  faces3;
    std::vector<int>  faces4;

    int    materialIndex;

    std::vector<int>  offsets;

    GLBuffer vertexColorBuffer;
    GLBuffer vertexIndexBuffer;
    GLBuffer vertexNormalBuffer;
    GLBuffer vertexPositionBuffer;
    GLBuffer vertexUvBuffer;

    int vertices;

    explicit GeometryGroup( int materialIndex = -1, int numMorphTargets = 0, int numMorphNormals = 0 )
        : GeometryBuffer( numMorphTargets, numMorphNormals ),
        id ( -1 ),
        materialIndex ( materialIndex ),
        vertexColorBuffer ( 0 ),
        vertexIndexBuffer ( 0 ),
        vertexNormalBuffer ( 0 ),
        vertexPositionBuffer ( 0 ),
        vertexUvBuffer ( 0 ),
        vertices ( 0 ) { }
};

} // namespace three

#endif // THREE_GEOMETRY_GROUP_HPP