#ifndef THREE_BOX2_HPP
#define THREE_BOX2_HPP

#include <three/common.hpp>

#include <three/math/math.hpp>

namespace three {

  class Box2 {
  public:

    union {
      struct { Vector2 min, max; };
      Vector2 minmax[2];
    };

    Box2();
    Box2( Vector2 minIn, Vector2 maxIn ) : min( minIn ), max( maxIn ) { }
    
    explicit Box2( Vector2* values ) : min( values[0] ), max( values[1] ) { }

    THREE_DECL Box2&    set( const Vector2& minIn, const Vector2& maxIn );
    THREE_DECL Box2&    copy( const Box2& b );
    THREE_DECL float    distanceToPoint( const Vector2& point ) const;
    THREE_DECL Box2&    setFromPoints(const std::vector<Vector2>& points );
    THREE_DECL Box2&    setFromCenterAndSize( const Vector2& center, const Vector2& size );
    THREE_DECL Box2&    makeEmpty();
    THREE_DECL bool     empty() const;
    THREE_DECL Box2&    expandByPoint( const Vector2& point );
    THREE_DECL Box2&    expandByVector( const Vector2& vector );
    THREE_DECL Box2&    expandByScalar( float scalar );
    THREE_DECL Vector2  center() const;
    THREE_DECL Vector2  center( const Vector2& target ) const;
    THREE_DECL bool     containsBox( const Box2& box ) const;
    THREE_DECL bool     containsPoint ( const Vector2& point ) const;
    THREE_DECL Vector2  clampPoint( const Vector2& point ) const;
    THREE_DECL Vector2  clampPoint( const Vector2& point, const Vector2& target ) const;
    THREE_DECL Box2     clone() const;
    THREE_DECL Vector2  size() const;
    THREE_DECL Vector2  size( const Vector2& target ) const;
    THREE_DECL Box2&    intersect( const Box2& box );
    THREE_DECL bool     isIntersectionBox( const Box2& box ) const;
    THREE_DECL Box2&    unionBox( const Box2& box );
    THREE_DECL Box2&    translate( float& offset );
    THREE_DECL bool     equals ( const Box2& box ) const;
    THREE_DECL Vector2  getParameter( const Vector2& point, const Vector2& target ) const;
    THREE_DECL Vector2  getParameter( const Vector2& point ) const;

  };

  static_assert( sizeof( Box2 ) == sizeof( Vector2 ) * 2, "Invalid Box2 storage size" );

} // namespace three

#endif // THREE_BOX2_HPP