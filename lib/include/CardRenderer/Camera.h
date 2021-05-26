#pragma once
#include"Includes.h"
class Camera
{
public:
	vector_t pos;
	vector_t up, right;
	vector_t front;
	vector_t target;

	float speed = 0.05f;

	void init_target_zero(const vector_t& pos);
	matrix_t set_lookat(const vector_t& eye, const vector_t& at, const vector_t& up);
};

