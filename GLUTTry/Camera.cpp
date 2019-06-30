#include "main.h"

void Camera::Position_Camera(float pos_x,  float pos_y,  float pos_z,
							 float view_x, float view_y, float view_z,
							 float up_x,   float up_y,   float up_z)
{
	mPos  =  Vector3f(pos_x,  pos_y,  pos_z);
	mView =  Vector3f(view_x, view_y, view_z);
	mUp   =  Vector3f(up_x,   up_y,   up_z);
}

void Camera::Move_Camera(float speed)
{
	Vector3f Vector = mView - mPos;

	mPos.x  = mPos.x  + Vector.x * speed;
	mPos.z  = mPos.z  + Vector.z * speed;
	mView.x = mView.x + Vector.x * speed;
	mView.z = mView.z + Vector.z * speed;
}

void Camera::RotateView(float speed)
{
	Vector3f Vector = mView - mPos;

	mView.z = (float)(mPos.z + sin(speed) * Vector.x + cos(speed) * Vector.z);
	mView.x = (float)(mPos.x + cos(speed) * Vector.x - sin(speed) * Vector.z);
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

	mView.y += angle_z * 8;

	if ((mView.y - mPos.y) > 8)  mView.y = mPos.y + 8;
	if ((mView.y - mPos.y) < -8)  mView.y = mPos.y - 8;

	RotateView(-angle_y);
}


void Draw_Grid()
{
	for (int i = -400; i <= 400; i += 10)
	{
		glBegin(GL_LINES);
			glColor3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-500, -20, i);
			glVertex3f(500, -20, i);
			glVertex3f(i, -20, -500);
			glVertex3f(i, -20, 500);
		glEnd();
	}
}