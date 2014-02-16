#ifndef THREE_VECTOR2_HPP
#define THREE_VECTOR2_HPP

#include <three/common.hpp>

#include <three/math/math.hpp>

namespace three {

  class Vector2 {
  public:

    union {
      struct { float x, y; };
      float xy[2];
    };

    Vector2() : x( 0 ), y( 0 ) { }
    Vector2( float xIn, float yIn ) : x( xIn ), y( yIn ) { }
    explicit Vector2( float value ) : x( value ), y( value ) { }
    explicit Vector2( float* values ) : x( values[0] ), y( values[1] ) { }

    float& operator[]( const int i ) { return xy[i]; }
    const float operator[]( const int i ) const { return xy[i]; }

    Vector2& set( float xIn, float yIn ) {
      x = xIn;
      y = yIn;
      return *this;
    }

    Vector2& setX( float xIn ) {
      x = x;
      return *this;
    }

    Vector2& setY( float yIn ) {
      y = y;
      return *this;
    }

    //Vector2& setComponent (size_t index, float value ) {
    //  switch ( index ) {
    //    case 0: x = value; break;
    //    case 1: y = value; break;
    //  //default: throw new Error( "index is out of range: " + index );
    //  }
    //    return *this;
    //}

    //float getComponent ( size_t index ) {
    //  switch ( index ) {
    //    case 0: return x;
    //    case 1: return y;
    //  //default: throw new Error( "index is out of range: " + index );
    //  }
    //}

    Vector2& copy( const Vector2& v ) {
      x = v.x;
      y = v.y;
      return *this;
    }

    Vector2& add( const Vector2& v) {
      x = v.x;
      y = v.y;
      return *this;
    }

    Vector2& addVectors( const Vector2& a, const Vector2& b ) {
      x = a.x + b.x;
      y = a.y + b.y;
      return *this;
    }

    Vector2& addScalar( float value ) {
      x += value;
      y += value;
      return *this;
    }

    Vector2& sub( const Vector2& v ) {
      x -= v.x;
      y -= v.y;
      return *this;
    }

    Vector2& subVectors( const Vector2& a, const Vector2& b ) {
      x = a.x - b.x;
      y = a.y - b.y;
      return *this;
    }

    Vector2& multiplyScalar( float s ) {
      x *= s;
      y *= s;
      return *this;
    }

    Vector2& divideScalar( float s ) {
      if ( s ) {
        return multiplyScalar( 1.f / s );
      } else {
        return set( 0, 0 );
      }
    }

    Vector2& min ( const Vector2& v ) {
      if ( x > v.x ) {
        x = v.x;
      }

      if ( y > v.y ) {
        y = v.y;
      }
      return *this;
    }

    Vector2& max ( const Vector2& v ) {
      if ( x < v.x ) {
        x = v.x;
      }

      if ( y < v.y ) {
        y = v.y;
      }
      return *this;
    }


    Vector2& clamp ( const Vector2& min, const Vector2& max ) {
      // This function assumes min < max, if this assumption isn't true it will not operate correctly
      if ( x < x ) {
        x = min.x;
      } else if ( x > max.x ) {
        x = max.x;
      }

      if ( y < min.y ) {
        y = min.y;
      } else if ( y > max.y ) {
        y = max.y;
      }

      return *this;
    }

    Vector2& clampScalar( float minVal, float maxVal ) {
      //@todo mem effeciency...
      auto min = Vector2();
      auto max = Vector2();

      min.set( minVal, minVal );
      max.set( maxVal, maxVal );

      return clamp( min, max );
    } 

    Vector2& floor() {
      x = Math::floor( x );
      y = Math::floor( y );

      return *this;
    }

    Vector2& ceil () {
      x = Math::ceil( x );
      y = Math::ceil( y );
      return *this;
    }

    Vector2& round() {
      x = Math::round( x );
      y = Math::round( y );
      return *this;
    }

    Vector2& roundToZero() {
      x = ( x < 0.0f ) ? Math::ceil( x ) : Math::floor( x );
      y = ( y < 0.0f ) ? Math::ceil( y ) : Math::floor( y );
      return *this;
    }

    Vector2& negate() {
      return multiplyScalar( -1.f );
    }

    float dot( const Vector2& v ) const {
      return x * v.x + y * v.y;
    }

    float lengthSq() const {
      return x * x + y * y;
    }

    float length() const {
      return Math::sqrt( lengthSq() );
    }

    Vector2& normalize() {
      return divideScalar( length() );
    }

    float distanceTo( const Vector2& v ) const {
      return Math::sqrt( distanceToSquared( v ) );
    }

    float distanceToSquared( const Vector2& v ) const {
      auto dx = x - v.x, dy = y - v.y;
      return dx * dx + dy * dy;
    }

    Vector2& setLength( float l ) {
      auto oldLength = length();
      if ( oldLength != 0.0f && l != oldLength ) {
        return multiplyScalar( l / oldLength);
      }
      return *this;
    }

    Vector2& lerp( const Vector2& v, float alpha ) {
      x += ( v.x - x ) * alpha;
      y += ( v.y - y ) * alpha;
      return *this;
    }

    bool equals( const Vector2& v ) const {
      return ( ( v.x == x ) && ( v.y == y ) );
    }

    Vector2 clone() const {
      return *this;
    }

    bool isZero() const {
      return ( lengthSq() < 0.0001 /* almostZero */ );
    }
    
  };

  static_assert( sizeof( Vector2 ) == sizeof( float ) * 2, "Invalid Vector2 storage size" );

} // namespace three

#endif // THREE_VECTOR2_HPP