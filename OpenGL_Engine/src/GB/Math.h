#pragma once
/*
This class need platform abstraction 

*/
#include "gbpch.h"


#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\quaternion.hpp"
#include "glm\gtx\matrix_decompose.hpp"


inline std::ostream& operator<<(std::ostream& os, const glm::vec3& e)
{

	return os << "Vector3: (" << e.x << "," << e.y << "," << e.z << ")";
}
inline std::ostream& operator<<(std::ostream& os, const glm::vec2& e)
{

	return os << "Vector3: (" << e.x << "," << e.y << ")";
}
inline std::ostream& operator <<(std::ostream& os, const glm::quat& e)
{
	return os << "Quaternion: (" << e.x << "," << e.y << "," << e.z << "," << e.w << ")";
}

typedef glm::vec4 color;
typedef glm::vec3 vector3;
typedef glm::vec2 vector2;
typedef glm::mat4 matrix4;
typedef glm::quat quaternion;
namespace GB
{

	class Mathf
	{
	public:

    uint32_t seed;
    template <class T>
    static T inline Clamp(T value, T min, T max)
    {
      T r = value > max ? max : value < min ? min : value;
      return r;
    }
    template <class T>
    static T inline ClampValue(T* value, T min, T max)
    {
      T r = &value > max ? max : &value < min ? min : &value;
      &value = r;
    }
    template <class T>
    static T inline Clamp0(T value)
    {
      return Clamp(value, 0, 1);
    }
		static const inline float PI()  { return 3.1416f; }
		static const inline float ToDegrees(float d)  { return d * 180.0f / PI(); }
		static const inline float ToRadians(float d)  { return d * PI() / 180.0f; }


    //inclusive random number: need to fix error while the range is > MAX RANGE ;
    static inline  int Random(int min, int max)
    {
      auto diff = max - min;
      int r = std::rand() % diff;
      r += min; 
      return r;
    }
		static const glm::vec3 ToEuler(glm::quat q) 
		{

			//roll x-axis
			float sinr_cosp = 2 * (q.w * q.x + q.y *q.z);
			float cosr_cosp = 1 - 2 * (q.x*q.x + q.y*q.y);
			float roll = std::atan2(sinr_cosp, cosr_cosp);

			//pitch y-axis
			float sinp = 2 * (q.w*q.y - q.z*q.x);
			float pitch = std::fabs(sinp) >= 1 ? std::copysign(3.1416f / 2, sinp) : std::asin(sinp);

			//yaw z-axis;
			float siny_cosp = 2 * (q.w *q.z + q.x *q.y);
			float cosy_cosp = 1 - 2 * (q.y*q.y + q.z*q.z);
			float yaw = std::atan2(siny_cosp, cosy_cosp);
			return glm::vec3(roll, pitch, yaw);
		}
	};
}