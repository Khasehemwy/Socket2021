#pragma once
#include"Includes.h"

vector_t vector_add(const vector_t& x, const vector_t& y);
vector_t operator+(const vector_t& x, const vector_t& y);
vector_t vector_sub(const vector_t& x, const vector_t& y);
vector_t operator - (const vector_t& x, const vector_t& y);
const vector_t operator - (const vector_t& x);
vector_t vector_normalize(const vector_t& v);
float vector_length(const vector_t& v);
vector_t vector_cross(const vector_t& x, const vector_t& y);
float vector_dot(const vector_t& x, const vector_t& y);
vector_t operator*(const vector_t& v, const float value);
vector_t operator*(const float value, const vector_t& v);
vector_t vector_reflect(const vector_t& I, const vector_t& N);
void vertex_set_rhw(vertex_t* v);

void matrix_set_identity(matrix_t* m);
void matrix_set_perspective(matrix_t* m, float fovy, float aspect, float z_near, float z_far);
matrix_t matrix_ortho(float left, float right, float bottom, float top, float z_near, float z_far);
matrix_t matrix_lookat(const vector_t& eye, const vector_t& at, const vector_t& up);
void matrix_set_zero(matrix_t* m);
matrix_t matrix_mul(const matrix_t& left, const matrix_t& right);
matrix_t operator*(const matrix_t& left, const matrix_t& right);
vector_t matrix_apply(const vector_t& x, const matrix_t& m);
vector_t operator*(const vector_t& x, const matrix_t& m);
matrix_t matrix_translate_build(float x, float y, float z);
matrix_t matrix_rotate_build(float angle, const vector_t& v);
matrix_t matrix_transpose(const matrix_t& m);
matrix_t matrix_scale(const matrix_t& m, const vector_t& v);
matrix_t matrix_translate(const matrix_t& m, const vector_t& v);
matrix_t matrix_get_inverse(const matrix_t& m);
float matrix_get_A(const matrix_t& m, int n);
matrix_t matrix_get_AStar(const matrix_t& m);

vector_t transform_apply(const vector_t& x, const transform_t& ts);
vector_t operator*(const vector_t& x, const transform_t& ts);
void transform_init(transform_t* ts, int width, int height);

color_t color_add(const color_t& x, const color_t& y);
color_t operator+(const color_t& x, const color_t& y);
void operator+=(color_t& x, const color_t& y);
color_t color_mul_num(const color_t& x, const float& y);
color_t operator*(const color_t& x, const float& y);
color_t operator*(const float& y, const color_t& x);
void operator*=(color_t& x, const float y);
void operator*=(color_t& x, const color_t y);
color_t color_mul_color(const color_t& x, const color_t& y);
color_t operator*(const color_t& x, const color_t& y);
color_t color_sub(const color_t& x, const color_t& y);
color_t operator-(const color_t& x, const color_t& y);
const color_t operator - (const color_t& x);
color_t color_div(const color_t& x, const float& y);
color_t operator/(const color_t& x, const float& y);

float time_get();

vector_t viewport_transform(const vector_t& x, const transform_t& ts);
vector_t anti_viewport_transform(const vector_t& x, const transform_t& ts);
int check_cvv(const vector_t& v);

#define CMID(x,min,max) ((x<min)?min:((x>max)?max:x))
//inline int CMID(int x, int min, int max) { return (x < min) ? min : ((x > max) ? max : x); }

float interp(float length_total, float length_place, float x1, float x2);


inline UINT32 color_trans_255(const color_t &color) {
	int R = CMID((int)(color.r * 255.0f), 0, 255);
	int G = CMID((int)(color.g * 255.0f), 0, 255);
	int B = CMID((int)(color.b * 255.0f), 0, 255);
	int A = CMID((int)(color.a * 255.0f), 0, 255);
	return (UINT32)((A << 24) | (R << 16) | (G << 8) | (B));
}

inline color_t color_trans_1f(const UINT32& color) {
	int x = 0b11111111;
	float R = CMID((float)((color & (x << 16)) >> 16) / 255.0f, 0.0f, 1.0f);
	float G = CMID((float)((color & (x << 8)) >> 8) / 255.0f, 0.0f, 1.0f);
	float B = CMID((float)((color & (x))) / 255.0f, 0.0f, 1.0f);
	float A = CMID((float)((color & (x << 24)) >> 24) / 255.0f, 0.0f, 1.0f);
	return { R, G, B, A };
}

inline float radians(float degrees) { return (degrees * 0.01745329251994329576923690768489); }

template <typename T>
T** create_2D_array(unsigned nrows, unsigned ncols, const T& val = T())
{
	if (nrows == 0)
		throw std::invalid_argument("number of rows is 0");
	if (ncols == 0)
		throw std::invalid_argument("number of columns is 0");
	T** ptr = nullptr;
	T* pool = nullptr;
	try
	{
		ptr = new T * [nrows];  // allocate pointers (can throw here)
		pool = new T[nrows * ncols]{ val };  // allocate pool (can throw here)

		// now point the row pointers to the appropriate positions in
		// the memory pool
		for (unsigned i = 0; i < nrows; ++i, pool += ncols)
			ptr[i] = pool;

		// Done.
		return ptr;
	}
	catch (std::bad_alloc& ex)
	{
		delete[] ptr; // either this is nullptr or it was allocated
		throw ex;  // memory allocation error
	}
}

