#include "main.h"


void Camera::Position_Camera(float pos_x,  float pos_y,  float pos_z,
							 float view_x, float view_y, float view_z,
							 float up_x,   float up_y,   float up_z)
{
	mPos  =  Vector3f(pos_x,  pos_y,  pos_z);
	mView =  Vector3f(view_x, view_y, view_z);
	mUp   =  Vector3f(up_x,   up_y,   up_z);
}

void Camera::Move_Camera_Forward(float speed)
{
	Vector3f Vector = mView - mPos;

	mPos.x  = mPos.x  + Vector.x * speed;
	mPos.y  = mPos.y  + Vector.y * speed;
	mPos.z  = mPos.z  + Vector.z * speed;
	mView.x = mView.x + Vector.x * speed;
	mView.y = mView.y + Vector.y * speed;
	mView.z = mView.z + Vector.z * speed;
}

void Camera::Move_Camera_Side(float speed)
{
	speed *= 5;
	Vector3f Vector1 = mView - mPos;
	Vector3f Vector2 = mUp - mPos;
	Vector3f VectorShift = Normalize(Cross(Vector1, Vector2));

 	mPos.x  = mPos.x  + VectorShift.x * speed;
	mPos.z  = mPos.z  + VectorShift.z * speed;
	mView.x = mView.x + VectorShift.x * speed;
	mView.z = mView.z + VectorShift.z * speed;
}

void Camera::RotateView(float speed)
{
	Vector3f Vector = mView - mPos;

	mView.x = (float)(mPos.x + cos(speed) * Vector.x - sin(speed) * Vector.z);
	mView.z = (float)(mPos.z + sin(speed) * Vector.x + cos(speed) * Vector.z);
}

void Camera::Mouse_Move(int Width, int Height) 
{
	POINT mousePos;
	
	int mid_x = Width >> 1;
	int mid_y = Height >> 1;

	float angle_y = 0.0f;
	float angle_z = 0.0f;

	GetCursorPos(&mousePos);

	if ((mousePos.x == mid_x) && (mousePos.y == mid_y)) return;

	SetCursorPos(mid_x, mid_y);

	angle_y = (float)((mid_x - mousePos.x)) / 500;
	angle_z = (float)((mid_y - mousePos.y)) / 500;

	if (arc) {
		Vector3f Vector = mView - mPos;
		
		mPos.y += angle_z * 4;
		mPos.x = (float)(cos(-angle_y) * Vector.x - sin(-angle_y) * Vector.z);
		mPos.z = (float)(sin(-angle_y) * Vector.x + cos(-angle_y) * Vector.z);
		
		arc = false;
		
		return;
	}
	mView.y += angle_z * 4;

	if ((mView.y - mPos.y) > 8)  mView.y = mPos.y + 8;
	if ((mView.y - mPos.y) < -8)  mView.y = mPos.y - 8;

	RotateView(-angle_y);
}

Vector3f Cross(Vector3f Vector1, Vector3f Vector2)
{
	Vector3f VectorRes;

	VectorRes.x = Vector1.y * Vector2.z - Vector1.z * Vector2.y;
	VectorRes.y = Vector1.z * Vector2.x - Vector1.x * Vector2.z;
	VectorRes.z = Vector1.x * Vector2.y - Vector1.y * Vector2.x;

	return VectorRes;
}

Vector3f Normalize(Vector3f Vector)
{
	float Len = sqrt(Vector.x * Vector.x + Vector.y * Vector.y + Vector.z * Vector.z);

	return Vector / Len;
}
