#ifndef THREE_RAY_IPP
#define THREE_RAY_IPP

#include <three/math/ray.hpp>

namespace three {
    

  Ray& Ray::set( const Vector3& origin, const Vector3& direction ) {
    
    this->origin.copy( origin );
    this->direction.copy( direction );

    return *this;
  }

  Ray& Ray::copy( const Ray& ray ) {

    this->origin.copy( ray.origin );
    this->direction.copy( ray.direction );

    return *this;

  }

  Vector3& Ray::at( float t ) const {
    return at( t, Vector3() );
  }

  Vector3& Ray::at( float t, const Vector3::Ptr target  ) const {
    auto result = target ? std::move(taregt) : Vector3();
    return result.copy( this->direction ).multiplyScalar( t ).add( this->origin );
  }

  Ray& Ray::recast( float t ) {

    // @todo priv member?
    auto v1 = Vector3();

    this->origin.copy( this->at( t, v1 ) );

    return *this;
  }

  Vector3& Ray::closestPointToPoint( const Vector3& point ) {
    return closestPointToPoint(point, Vector3());
  }

  Vector3& Ray::closestPointToPoint( const Vector3& point, const Vector3::Ptr target ) {

    target.subVectors( point, this->origin );
    auto directionDistance = target.dot( this->direction );

    if ( directionDistance < 0 ) {

      return target.copy( this->origin );

    }

    return target.copy( this->direction ).multiplyScalar( directionDistance ).add( this->origin );

  }

  float Ray::distanceToPoint( const Vector3& point ) const {

    // @todo priv member check
    auto v1 = Vector3();
    auto directionDistance = v1.subVectors( point, this->origin ).dot( this->direction );

    // point behind the ray

    if ( directionDistance < 0 ) {

      return this->origin.distanceTo( point );

    }

    v1.copy( this->direction ).multiplyScalar( directionDistance ).add( this->origin );

    return v1.distanceTo( point );

  }

  float Ray::distanceSqToSegment( const Vector3& v0, const Vector3& v1, 
    Vector3::Ptr optionalPointOnRay = nullptr, Vector3::Ptr optionalPointOnSegment = nullptr ) const  
  {

    // from http://www.geometrictools.com/LibMathematics/Distance/Wm5DistRay3Segment3.cpp
    // It returns the min distance between the ray and the segment
    // defined by v0 and v1
    // It can also set two optional targets :
    // - The closest point on the ray
    // - The closest point on the segment

    auto segCenter = v0.clone().add( v1 ).multiplyScalar( 0.5 );
    auto segDir = v1.clone().sub( v0 ).normalize();
    auto segExtent = v0.distanceTo( v1 ) * 0.5;
    auto diff = this->origin.clone().sub( segCenter );
    auto a01 = - this->direction.dot( segDir );
    auto b0 = diff.dot( this->direction );
    auto b1 = - diff.dot( segDir );
    auto c = diff.lengthSq();
    auto det = Math::abs( 1 - a01 * a01 );
    auto s0, s1, sqrDist, extDet;

    if ( det >= 0 ) {

      // The ray and segment are not parallel.

      s0 = a01 * b1 - b0;
      s1 = a01 * b0 - b1;
      extDet = segExtent * det;

      if ( s0 >= 0 ) {

        if ( s1 >= - extDet ) {

          if ( s1 <= extDet ) {

            // region 0
            // Minimum at interior points of ray and segment.

            auto invDet = 1 / det;
            s0 *= invDet;
            s1 *= invDet;
            sqrDist = s0 * ( s0 + a01 * s1 + 2 * b0 ) + s1 * ( a01 * s0 + s1 + 2 * b1 ) + c;

          } else {

            // region 1

            s1 = segExtent;
            s0 = Math::max( 0, - ( a01 * s1 + b0) );
            sqrDist = - s0 * s0 + s1 * ( s1 + 2 * b1 ) + c;

          }

        } else {

          // region 5

          s1 = - segExtent;
          s0 = Math::max( 0, - ( a01 * s1 + b0) );
          sqrDist = - s0 * s0 + s1 * ( s1 + 2 * b1 ) + c;

        }

      } else {

        if ( s1 <= - extDet) {

          // region 4

          s0 = Math::max( 0, - ( - a01 * segExtent + b0 ) );
          s1 = ( s0 > 0 ) ? - segExtent : Math::min( Math::max( - segExtent, - b1 ), segExtent );
          sqrDist = - s0 * s0 + s1 * ( s1 + 2 * b1 ) + c;

        } else if ( s1 <= extDet ) {

          // region 3

          s0 = 0;
          s1 = Math::min( Math::max( - segExtent, - b1 ), segExtent );
          sqrDist = s1 * ( s1 + 2 * b1 ) + c;

        } else {

          // region 2

          s0 = Math::max( 0, - ( a01 * segExtent + b0 ) );
          s1 = ( s0 > 0 ) ? segExtent : Math::min( Math::max( - segExtent, - b1 ), segExtent );
          sqrDist = - s0 * s0 + s1 * ( s1 + 2 * b1 ) + c;

        }

      }

    } else {

      // Ray and segment are parallel.

      s1 = ( a01 > 0 ) ? - segExtent : segExtent;
      s0 = Math::max( 0, - ( a01 * s1 + b0 ) );
      sqrDist = - s0 * s0 + s1 * ( s1 + 2 * b1 ) + c;

    }

    if ( optionalPointOnRay ) {

      optionalPointOnRay.copy( this->direction.clone().multiplyScalar( s0 ).add( this->origin ) );

    }

    if ( optionalPointOnSegment ) {

      optionalPointOnSegment.copy( segDir.clone().multiplyScalar( s1 ).add( segCenter ) );

    }

    return sqrDist;

  }

  bool Ray::isIntersectionSphere( const Sphere& sphere ) const {

    return this->distanceToPoint( sphere.center ) <= sphere.radius;

  }

  bool Ray::isIntersectionPlane( const Plane& plane ) const {

    // check if the ray lies on the plane first

    auto distToPoint = plane.distanceToPoint( this->origin );

    if ( distToPoint === 0 ) {

      return true;

    }

    auto denominator = plane.normal.dot( this->direction );

    if ( denominator * distToPoint < 0 ) {

      return true

    }

    // ray origin is behind the plane (and is pointing behind it)

    return false;

  }

  float Ray::distanceToPlane( const Plane& plane ) const {

    auto denominator = plane.normal.dot( this->direction );
    if ( denominator == 0 ) {

      // line is coplanar, return origin
      if( plane.distanceToPoint( this->origin ) == 0 ) {

        return 0;

      }

      return -1;

    }

    auto t = - ( this->origin.dot( plane.normal ) + plane.constant ) / denominator;

    // Return if the ray never intersects the plane

    return t >= 0 ? t : -1;

  }

  Vector3::Ptr Ray::intersectPlane( const Vector3& plane ) {

    return intersectPlane( plane, Vector3() );

  }

  Vector3::Ptr Ray::intersectPlane( const Plane& plane, const Vector3::Ptr target ) {

    auto t = this->distanceToPlane( plane );

    if ( t < 0 ) {
      return nullptr;
    }

    return this->at( t, target );

  }

  bool Ray::isIntersectionBox( const Box& box ) const {
    
    //@todo priv mmeber check
    auto v = Vector3();

    return this->intersectBox( box, v ) != nullptr;
  }

  Box3::Ptr Ray::intersectBox( const Box3& box ) {
    //@todo mem check efficiency
    return intersectBox(box, nullptr);
  }

  Box3::Ptr Ray::intersectBox( const Box3& box , const Vector3::Ptr target ) {

    // http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-7-intersecting-simple-shapes/ray-box-intersection/

    auto tmin,tmax,tymin,tymax,tzmin,tzmax;

    auto invdirx = 1/this->direction.x,
      invdiry = 1/this->direction.y,
      invdirz = 1/this->direction.z;

    auto origin = this->origin;

    if (invdirx >= 0) {
        
      tmin = (box.min.x - origin.x) * invdirx;
      tmax = (box.max.x - origin.x) * invdirx;

    } else { 

      tmin = (box.max.x - origin.x) * invdirx;
      tmax = (box.min.x - origin.x) * invdirx;
    }     

    if (invdiry >= 0) {
    
      tymin = (box.min.y - origin.y) * invdiry;
      tymax = (box.max.y - origin.y) * invdiry;

    } else {

      tymin = (box.max.y - origin.y) * invdiry;
      tymax = (box.min.y - origin.y) * invdiry;
    }

    if ((tmin > tymax) || (tymin > tmax)) return null;

    // These lines also handle the case where tmin or tmax is NaN
    // (result of 0 * Infinity). x !== x returns true if x is NaN
    
    if (tymin > tmin || tmin !== tmin ) tmin = tymin;

    if (tymax < tmax || tmax !== tmax ) tmax = tymax;

    if (invdirz >= 0) {
    
      tzmin = (box.min.z - origin.z) * invdirz;
      tzmax = (box.max.z - origin.z) * invdirz;

    } else {

      tzmin = (box.max.z - origin.z) * invdirz;
      tzmax = (box.min.z - origin.z) * invdirz;
    }

    if ((tmin > tzmax) || (tzmin > tmax)) return null;

    if (tzmin > tmin || tmin !== tmin ) tmin = tzmin;

    if (tzmax < tmax || tmax !== tmax ) tmax = tzmax;

    //return point closest to the ray (positive side)

    if ( tmax < 0 ) return nullptr;

    return this->at( tmin >= 0 ? tmin : tmax, target );

  }

  Vector3::Ptr Ray::intersectTriangle( const Vector3& a, const Vector3& b, const Vector3& c, bool backfaceCulling, const Vector3::Ptr optionalTarget ) {

    // @todo priv member check
    // Compute the offset origin, edges, and normal.
    auto diff = Vector3();
    auto edge1 = Vector3();
    auto edge2 = Vector3();
    auto normal = Vector3();

    // from http://www.geometrictools.com/LibMathematics/Intersection/Wm5IntrRay3Triangle3.cpp
    edge1.subVectors( b, a );
    edge2.subVectors( c, a );
    normal.crossVectors( edge1, edge2 );

    // Solve Q + t*D = b1*E1 + b2*E2 (Q = kDiff, D = ray direction,
    // E1 = kEdge1, E2 = kEdge2, N = Cross(E1,E2)) by
    //   |Dot(D,N)|*b1 = sign(Dot(D,N))*Dot(D,Cross(Q,E2))
    //   |Dot(D,N)|*b2 = sign(Dot(D,N))*Dot(D,Cross(E1,Q))
    //   |Dot(D,N)|*t = -sign(Dot(D,N))*Dot(Q,N)
    auto DdN = this->direction.dot( normal );
    auto sign;

    if ( DdN > 0 ) {

      if ( backfaceCulling ) return nullptr;
      sign = 1;

    } else if ( DdN < 0 ) {

      sign = - 1;
      DdN = - DdN;

    } else {

      return nullptr;

    }

    diff.subVectors( this->origin, a );
    auto DdQxE2 = sign * this->direction.dot( edge2.crossVectors( diff, edge2 ) );

    // b1 < 0, no intersection
    if ( DdQxE2 < 0 ) {

      return nullptr;

    }

    auto DdE1xQ = sign * this->direction.dot( edge1.cross( diff ) );

    // b2 < 0, no intersection
    if ( DdE1xQ < 0 ) {

      return nullptr;

    }

    // b1+b2 > 1, no intersection
    if ( DdQxE2 + DdE1xQ > DdN ) {

      return nullptr;

    }

    // Line intersects triangle, check if ray does.
    auto QdN = - sign * diff.dot( normal );

    // t < 0, no intersection
    if ( QdN < 0 ) {

      return nullptr;

    }

    // Ray intersects triangle.
    return this->at( QdN / DdN, optionalTarget );
  }

  Ray& Ray::applyMatrix4( const Matrxi4& matrix4 ) {

    this->direction.add( this->origin ).applyMatrix4( matrix4 );
    this->origin.applyMatrix4( matrix4 );
    this->direction.sub( this->origin );
    this->direction.normalize();

    return *this;
  }

  bool Ray::equals( const Ray& ray ) const {
    return ray.origin.equals( this->origin ) && ray.direction.equals( this->direction );
  }

  Ray Ray::clone() {
    return *this;
  }  
  
};

} // namespace three

#endif // THREE
