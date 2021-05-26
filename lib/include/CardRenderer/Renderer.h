#pragma once
#include"Includes.h"


//��Ⱦģʽ
#define RENDER_STATE_WIREFRAME 0b1		// ��Ⱦ�߿�
#define RENDER_STATE_COLOR 0b10			// ��Ⱦ��ɫ
#define RENDER_STATE_TEXTURE 0b100		// ��Ⱦ����


//����
#define RENDER_FEATURE_BACK_CULLING 0b1	//�����޳�
#define RENDER_FEATURE_LIGHT 0b10	//�Ƿ�������
#define RENDER_FEATURE_CVV_CLIP 0b100	//�Ƿ���cvv�ü�
#define RENDER_FEATURE_SHADOW 0b1000	//�Ƿ�����Ӱ

//Ƭ����ɫ��-��ɫ�㷨
#define RENDER_SHADER_PIXEL_SCANLINE 0b1		//ɨ�����㷨-����Ƭ����ɫ,���쵫������׼
#define RENDER_SHADER_PIXEL_BOUNDINGBOX 0b10		//�߽���㷨-����Ƭ����ɫ,��׼������

class Renderer
{
public:
	transform_t transform;      // ����任��
	const Camera* camera = nullptr;
	float width, height;

	UINT32** frame_buffer = nullptr;		// ���ػ��棺frame_buffer[y] ����� y��,���ػ���Ϊ��ͬRenderer����
	float** z_buffer = nullptr;				// ��Ȼ��棺z_buffer[y] Ϊ�� y��ָ��,��Ȼ���Ϊÿ��Renderer����

	Texture* texture;			// ����ÿ������
	int tex_width;              // ������
	int tex_height;             // ����߶�
	float tex_max_u;            // ��������ȣ�tex_width - 1
	float tex_max_v;            // �������߶ȣ�tex_height - 1
	int tex_limit_size;

	float min_clip_x = 0;
	float min_clip_y = 0;
	float max_clip_x;
	float max_clip_y;

	UINT32 background;			// ������ɫ
	UINT32 foreground;			// �߿���ɫ

	int render_state = RENDER_STATE_WIREFRAME;	// ��Ⱦ״̬
	int render_shader_state = RENDER_SHADER_PIXEL_SCANLINE;	// Ƭ����ɫ���㷨ѡ��

	std::map<int, int> features;	//����

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

