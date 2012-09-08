#ifndef THREE_RAY_HPP
#define THREE_RAY_HPP

#include <three/common.hpp>

#include <three/core/math.hpp>
#include <three/objects/mesh.hpp>

namespace three {

class Ray {
public:

	Vector3 origin;
	Vector3 direction;
	float near;
	float far;

	Ray ( const Vector3& origin = Vector3(), const Vector3& direction = Vector3(), float near = 0, float far = std::numeric_limits<float>::infinity() )
	: origin ( origin ), direction ( direction ), near ( near ), far ( far ) { }

	/////////////////////////////////////////////////////////////////////////

	// http://www.blackpawn.com/texts/pointinpoly/default.html

	static bool pointInFace3( const Vector3& p, const Vector3& a, const Vector3& b, const Vector3& c ) {

		auto v0 = sub( c, a );
		auto v1 = sub( b, a );
		auto v2 = sub( p, a );

		auto dot00 = v0.dot( v0 );
		auto dot01 = v0.dot( v1 );
		auto dot02 = v0.dot( v2 );
		auto dot11 = v1.dot( v1 );
		auto dot12 = v1.dot( v2 );

		auto invDenom = 1.f / ( dot00 * dot11 - dot01 * dot01 );
		auto u = ( dot11 * dot02 - dot01 * dot12 ) * invDenom;
		auto v = ( dot00 * dot12 - dot01 * dot02 ) * invDenom;

		return ( u >= 0.f ) && ( v >= 0.f ) && ( u + v < 1.f );

	}

	/////////////////////////////////////////////////////////////////////////

	struct Intersection {
		float distance;
		Vector3 point;
		Face3* face;
		int faceIndex;
		Object3D* object;
	};

	static bool descSort ( const Intersection& a, const Intersection& b ) {

		return a.distance < b.distance;

	}


	std::vector<Intersection> intersectObject ( const Object3D& object, bool recursive = true ) {

		std::vector<Intersection> intersects;

		if ( recursive ) {

			for ( const auto& child : object.children ) {

				auto iter_intersects = intersectObject ( *child, recursive );
				intersects.insert( intersects.end(), iter_intersects.begin(), iter_intersects.end() );

			}

		}

		if ( object.getType() == THREE::Particle ) {

			auto distance = distanceFromIntersection( origin, direction, object.matrixWorld.getPosition() );

			if ( distance > object.scale.x ) {

				return std::vector<Intersection>();//intersects;

			}

			intersects.emplace_back( distance, object.position, nullptr, 0, &object );

		} else if ( object.getType() == THREE::Mesh ) {

			const Geometry* pGeometry = nullptr;

			struct ExtractGeometry : public Visitor {
				ExtractGeometry( const Geometry*& geometry ) : pGeometry( geometry ) { }
				void operator() ( Mesh& mesh ) { pGeometry = mesh.geometry.get(); }
				const Geometry*& pGeometry;
			};

			object.visit ( ExtractGeometry(pGeometry) );

			if ( !pGeometry )
				break;

			// Checking boundingSphere

			const auto& geometry = *pGeometry;

			auto scale = Vector3( object.matrixWorld.getColumnX().length(),
			                      object.matrixWorld.getColumnY().length(),
			                      object.matrixWorld.getColumnZ().length() );
			auto scaledRadius = geometry.boundingSphere.radius * Math.max( scale.x, Math.max( scale.y, scale.z ) );

			// Checking distance to ray

			auto distance = distanceFromIntersection( origin, direction, matrixWorld.getPosition() );

			if ( distance > scaledRadius) {

				return intersects;

			}

			// Checking faces

			auto rangeSq = range * range;
			const auto& vertices = geometry.vertices;
			const auto& geometryMaterials = object.geometry.materials;
			auto isFaceMaterial = object.material.getType() == THREE::MeshFaceMaterial;
			auto side = object.material.side;

			object.matrixRotationWorld.extractRotation( object.matrixWorld );

			Vector3 vector, normal, dot;

			for ( auto f = 0, fl = geometry.faces.size(); f < fl; f ++ ) {

				const auto& face = geometry.faces[ f ];

				const auto& material = isFaceMaterial ? geometryMaterials[ face.materialIndex ] : object.material;
				if ( !material ) continue;

				auto side = material.side;

				Vector3 originCopy( origin );
				Vector3 directionCopy( direction );

				const auto& objMatrix = object.matrixWorld;

				// determine if ray intersects the plane of the face
				// note: this works regardless of the direction of the face normal

				vector = objMatrix.multiplyVector3( vector.copy( face.centroid ) ).subSelf( originCopy );
				normal = object.matrixRotationWorld.multiplyVector3( normal.copy( face.normal ) );
				dot = directionCopy.dot( normal );

				// bail if ray and plane are parallel

				if ( Math.abs( dot ) < precision ) continue;

				// calc distance to plane

				auto scalar = normal.dot( vector ) / dot;

				// if negative distance, then plane is behind ray

				if ( scalar < 0 ) continue;

				if ( side === THREE::DoubleSide || ( side === THREE::FrontSide ? dot < 0 : dot > 0 ) ) {

					intersectPoint.add( originCopy, directionCopy.multiplyScalar( scalar ) );

					auto distance = originCopy.distanceTo( intersectPoint );

					if ( distance < this.near ) continue;
					if ( distance > this.far ) continue;

					/*if ( face.getType() == THREE::Face3 ) */{

						a = objMatrix.multiplyVector3( vertices[ face.a ] );
						b = objMatrix.multiplyVector3( vertices[ face.b ] );
						c = objMatrix.multiplyVector3( vertices[ face.c ] );

						if ( pointInFace3( intersectPoint, a, b, c ) ) {

							intersects.emplace_back( distance, intersectPoint, &face, f, &object );

						}

					} /*else if ( face.getType() == THREE::Face4 ) {

						a = objMatrix.multiplyVector3( a.copy( vertices[ face.a ] ) );
						b = objMatrix.multiplyVector3( b.copy( vertices[ face.b ] ) );
						c = objMatrix.multiplyVector3( c.copy( vertices[ face.c ] ) );
						d = objMatrix.multiplyVector3( d.copy( vertices[ face.d ] ) );

						if ( pointInFace3( intersectPoint, a, b, d ) || pointInFace3( intersectPoint, b, c, d ) ) {

							intersects.emplace_back( distance, intersectPoint, face, f, &object );

						}

					}*/

				}

			}

		}

		std::sort( intersects, descSort );

		return intersects;

	}

	std::vector<Intersection> intersectObjects ( const std::vector<Object3D*>& objects, bool recursive ) {

		std::vector<Intersection> interesects;

		for ( const auto& object : objects ) {

			auto iter_intersects = intersectObject( object, recursive );
			intersects.insert( interesects.end(), iter_intersects.begin(), iter_intersects.end() );

		}

		std::sort( intersects, descSort );

		return intersects;

	}

	void setPrecision ( float value ) {

		precision = value;

	}

private:

	float distanceFromIntersection ( const Vector3& origin, const Vector3& direction, const Vector3& position ) {

		auto v0 = sub( position, origin );
		auto d  = dot( v0, direction );

		auto intersect = add( origin, Vector3( direction ).multiplyScalar( d ) );
		return position.distanceTo( intersect );

	}

	float precision = 0.0001f;

};

} // namespace three

#endif // THREE
