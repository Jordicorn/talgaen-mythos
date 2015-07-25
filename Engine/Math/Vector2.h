#pragma once

namespace talga
{
	class Vector3;

	class Vector2 {
	public:
		Vector2(float x = 0, float y = 0);
		Vector2(const Vector3& cpy);
		virtual ~Vector2();

		float& operator[](int index);
		float operator[](int index) const { return arr[index]; }
		float operator()(int index);

		const Vector2& operator=(const Vector3& vec3Cpy);

		float x() const { return arr[0]; }
		float y() const { return arr[1]; }
	private:
		float arr[2];
	};

	typedef Vector2 vec2;
}