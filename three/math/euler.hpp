#ifndef THREE_EULER_HPP
#define THREE_EULER_HPP

#include <three/common.hpp>
#include <three/math/quaternion.hpp>

namespace three {
    
class Euler {

public:

  static const enums::EulerRotationOrder DefaultOrder = enums::EulerRotationOrder::XYZ;

  Euler()
    : _x(0.f), _y(0.f), _z(0.f), _order(enums::EulerRotationOrder::XYZ) {};

  Euler(float xIn, float yIn, float zIn)
    : _x(xIn), _y(yIn), _z(zIn), _order(enums::EulerRotationOrder::XYZ) {};

  Euler(float xIn, float yIn, float zIn, enums::EulerRotationOrder orderIn)
    : _x(xIn), _y(yIn), _z(zIn), _order(orderIn) {};

  inline float x() const;

  inline Euler& x(float value);

  inline float y() const;

  inline Euler& y(float value);

  inline float z() const;

  inline Euler& z(float value);

  inline enums::EulerRotationOrder order() const;

  inline Euler& w(const enums::EulerRotationOrder& value);

  inline Euler& set( float xIn, float yIn, float zIn);

  inline Euler& set( float xIn, float yIn, float zIn, enums::EulerRotationOrder orderIn );

  inline Euler& copy ( const Euler& euler );

  Euler& setFromRotationMatrix( const Matrix4& m );

  Euler& setFromRotationMatrix( const Matrix4& m, enums::EulerRotationOrder order );

  Euler& setFromQuaternion( const Quaternion& q, bool update = true);

  Euler& setFromQuaternion( const Quaternion& q, enums::EulerRotationOrder order, bool update = true);

  Euler& reorder(enums::EulerRotationOrder newOrder);

  inline bool equals( const Euler& euler ) const;

  inline Euler clone() {
      return *this;
  }

private:
    
    float _clamp( float x );
    
    void _updateQuaternion();
    
    float _x, _y, _z;
    
    enums::EulerRotationOrder _order;
    
    std::shared_ptr<Quaternion> _quaternion;

};

} // namespace three

#endif // THREE_EULER_HPP