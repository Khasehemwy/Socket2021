#pragma once
#include"Includes.h"


//渲染模式
#define RENDER_STATE_WIREFRAME 0b1		// 渲染线框
#define RENDER_STATE_COLOR 0b10			// 渲染颜色
#define RENDER_STATE_TEXTURE 0b100		// 渲染纹理


//特性
#define RENDER_FEATURE_BACK_CULLING 0b1	//背面剔除
#define RENDER_FEATURE_LIGHT 0b10	//是否开启光照
#define RENDER_FEATURE_CVV_CLIP 0b100	//是否开启cvv裁剪
#define RENDER_FEATURE_SHADOW 0b1000	//是否开启阴影

//片段着色器-着色算法
#define RENDER_SHADER_PIXEL_SCANLINE 0b1		//扫描线算法-进行片段着色,更快但不够精准
#define RENDER_SHADER_PIXEL_BOUNDINGBOX 0b10		//边界盒算法-进行片段着色,精准但不快

class Renderer
{
public:
	transform_t transform;      // 坐标变换器
	const Camera* camera = nullptr;
	float width, height;

	UINT32** frame_buffer = nullptr;		// 像素缓存：frame_buffer[y] 代表第 y行,像素缓存为不同Renderer共用
	float** z_buffer = nullptr;				// 深度缓存：z_buffer[y] 为第 y行指针,深度缓存为每个Renderer独用

	Texture* texture;			// 纹理：每行索引
	int tex_width;              // 纹理宽度
	int tex_height;             // 纹理高度
	float tex_max_u;            // 纹理最大宽度：tex_width - 1
	float tex_max_v;            // 纹理最大高度：tex_height - 1
	int tex_limit_size;

	float min_clip_x = 0;
	float min_clip_y = 0;
	float max_clip_x;
	float max_clip_y;

	UINT32 background;			// 背景颜色
	UINT32 foreground;			// 线框颜色

	int render_state = RENDER_STATE_WIREFRAME;	// 渲染状态
	int render_shader_state = RENDER_SHADER_PIXEL_SCANLINE;	// 片段着色器算法选择

	std::map<int, int> features;	//特性

	std::vector<const Light*>lights;
	const Light* current_light;

	Renderer();

	void init(int width, int height, void* fb);
	void destroy();
	void clear();

	void set_texture(const Texture& tex);
	color_t texture_read(const Texture& tex, float u, float v);
	void add_light(const Light& light);

	void draw_line(int x1, int y1, int x2, int y2, UINT32 color);
	int	display_primitive(vertex_t v1, vertex_t v2, vertex_t v3);
	void transform_update();

	void FXAA(bool on);

private:
	void draw_pixel(int x, int y, UINT32 color);
	void draw_triangle(vertex_t v1, vertex_t v2, vertex_t v3);
	void draw_triangle_StandardAlgorithm(const vertex_t& top, const vertex_t& left, const vertex_t& right);
	void draw_triangle_BresenhamAlgorithm(const vertex_t& top, const vertex_t& left, const vertex_t& right);
	void draw_triangle_BoundingBox(const vertex_t& v1, const vertex_t& v2, const vertex_t& v3);

};

