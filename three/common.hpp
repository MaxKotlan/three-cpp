#ifndef THREE_COMMON_HPP
#define THREE_COMMON_HPP

#include <three/config.hpp>
#include <three/fwd.hpp>

namespace three {

typedef void(*LogP)(const char*);

class THREE {
public:

	enum Side {
		FrontSide  = 0,
		BackSide   = 1,
		DoubleSide = 2
	};

	enum Shading {
		NoShading     = 0,
		FlatShading   = 1,
		SmoothShading = 2
	};

	enum Colors {
		NoColors     = 0,
		FaceColors   = 1,
		VertexColors = 2
	};

	enum Blending {
		NoBlending          = 0,
		NormalBlending      = 1,
		AdditiveBlending    = 2,
		SubtractiveBlending = 3,
		MultiplyBlending    = 4,
		CustomBlending      = 5
	};

	enum BlendEquation {
		AddEquation = 100,
		SubtractEquation = 101,
		ReverseSubtractEquation = 102
	};

	enum BlendFactor {
		ZeroFactor             = 200,
		OneFactor              = 201,
		SrcColorFactor         = 202,
		OneMinusSrcColorFactor = 203,
		SrcAlphaFactor         = 204,
		OneMinusSrcAlphaFactor = 205,
		DstAlphaFactor         = 206,
		OneMinusDstAlphaFactor = 207,
		DstColorFactor         = 208,
		OneMinusDstColorFactor = 209,
		SrcAlphaSaturateFactor = 210
	};

	enum TextureConstant {
		MultiplyOperation = 0,
		MixOperation = 1
	};

	enum Wrapping {
		RepeatWrapping         = 1000,
		ClampToEdgeWrapping    = 1001,
		MirroredRepeatWrapping = 1002
	};

	enum Filter {
		NearestFilter              = 1003,
		NearestMipMapNearestFilter = 1004,
		NearestMipMapLinearFilter  = 1005,
		LinearFilter               = 1006,
		LinearMipMapNearestFilter  = 1007,
		LinearMipMapLinearFilter   = 1008
	};

	enum DataType {
		UnsignedByteType  = 1009,
		ByteType          = 1010,
		ShortType         = 1011,
		UnsignedShortType = 1012,
		IntType           = 1013,
		UnsignedIntType   = 1014,
		FloatType         = 1015
	};

	enum PixelType {
		//UnsignedByteType    = 1009,
		UnsignedShort4444Type = 1016,
		UnsignedShort5551Type = 1017,
		UnsignedShort565Type  = 1018
	};

	enum PixelFormat {
		AlphaFormat          = 1019,
		RGBFormat            = 1020,
		RGBAFormat           = 1021,
		LuminanceFormat      = 1022,
		LuminanceAlphaFormat = 1023
	};

	enum Order {
		XYZ = 0,
		YXZ,
		ZXY,
		ZYX,
		YZX,
		XZY
	};

	enum Type {
		Object3D = 0,
		Bone,
		Camera,
		Light,
		Scene,
		Particle,
		Sprite,
		Mesh,
		Line
	};

	enum FaceType {
		Face3 = 0,
		Face4
	};

	enum LightType {
		Ambient = 0,
		Directional,
		Point,
		Spot
	};

	enum MaterialType {
		Material = 0,
		MeshFaceMaterial = 1
	};

};

/////////////////////////////////////////////////////////////////////////

struct Visitor {
	virtual void operator() (const Object3D&) { }
	virtual void operator() (const Bone&)     { }
	virtual void operator() (const Camera&)   { }
	virtual void operator() (const Light&)    { }
	virtual void operator() (const Scene&)    { }
	virtual void operator() (const Particle&) { }
	virtual void operator() (const Sprite&)   { }
	virtual void operator() (const Mesh&)     { }
	virtual void operator() (const Line&)     { }
	virtual ~Visitor() { }
};

/////////////////////////////////////////////////////////////////////////


class Console {
public:
	LogP info;
	LogP log;
	LogP debug;
	LogP warn;
	LogP error;

	static Console& instance() {
		static Console sConsole;
		return sConsole;
	}

private:

	Console()
	: info ( dummy ),
	log    ( dummy ),
	debug  ( dummy ),
	warn   ( dummy ),
	error  ( dummy ) { }

	static void dummy(const char*) { }
};

//static Console console;

static Console& console() {
	return Console::instance();
}


} // namespace three

#endif // THREE_COMMON_HPP
