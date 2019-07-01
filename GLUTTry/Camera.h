#pragma once

#define CAMERASPEED 0.05f

typedef struct Vector3f
{
	float x, y, z;
	Vector3f() {}
	Vector3f(float new_x, float new_y, float new_z) {
		x = new_x;
		y = new_y;
		z = new_z;
	}

	Vector3f operator+(Vector3f Vector)
	{
		return Vector3f(Vector.x + x, Vector.y + y, Vector.z + z);
	}

	Vector3f operator-(Vector3f Vector)
	{
		return Vector3f(x - Vector.x, y - Vector.y, z - Vector.z);
	}

	Vector3f operator/(float del)
	{
		return Vector3f(x / del, y / del, z / del);
	}
}Vector3f;


Vector3f Cross(Vector3f Vector1, Vector3f Vector2);
Vector3f Normalize(Vector3f Vector);

class Camera
{
public:
	Vector3f mPos;
	Vector3f mView;
	Vector3f mUp;

	void Move_Camera_Forward(float speed);
	void Move_Camera_Side(float speed);

	void Position_Camera(float pos_x,  float pos_y,  float pos_z,
						 float view_x, float view_y, float view_z,
						 float up_x,   float up_y,   float up_z);

	void Mouse_Move(int Width, int Height);

	void RotateView(float speed);
};

