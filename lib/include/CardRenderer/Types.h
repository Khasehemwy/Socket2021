#pragma once
#include"Includes.h"

#define PI					3.1415926f
#define KEY_A                  65
#define KEY_B                  66
#define KEY_C                  67
#define KEY_D                  68
#define KEY_E                  69
#define KEY_F                  70
#define KEY_G                  71
#define KEY_H                  72
#define KEY_I                  73
#define KEY_J                  74
#define KEY_K                  75
#define KEY_L                  76
#define KEY_M                  77
#define KEY_N                  78
#define KEY_O                  79
#define KEY_P                  80
#define KEY_Q                  81
#define KEY_R                  82
#define KEY_S                  83
#define KEY_T                  84
#define KEY_U                  85
#define KEY_V                  86
#define KEY_W                  87
#define KEY_X                  88
#define KEY_Y                  89
#define KEY_Z                  90

typedef unsigned int UINT32;

typedef struct { float m[4][4]; } matrix_t;
typedef struct { float x, y, z, w; } vector_t;
using point_t = vector_t;
//typedef vector_t point_t;
typedef struct { float r, g, b, a; } color_t;
typedef struct { float u, v; } texcoord_t;

typedef struct { point_t pos; color_t color; texcoord_t tex; float rhw; } vertex_t;

typedef struct {
	matrix_t model;         // 世界坐标变换
	matrix_t view;          // 摄影机坐标变换
	matrix_t projection;    // 投影变换
	matrix_t transform;     // transform = model * view * projection;
	float w, h;             // 屏幕大小
}	transform_t;