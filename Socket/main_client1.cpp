#include"includes.h"

//int main()
//{
//	//Server server;
//	//
//	//server.Init();
//	//server.Boot();
//
//	Client client;
//	client.Init();
//	client.ConnectToServer("127.0.0.1");
//	client.Boot();
//
//	return 0;
//
//}

void draw_square(Renderer& renderer, vertex_t lb, vertex_t rb, vertex_t rt, vertex_t lt)
{
	lb.tex = { 0,1 };
	rb.tex = { 1,1 };
	rt.tex = { 1,0 };
	lt.tex = { 0,0 };
	renderer.display_primitive(lb, rb, rt);
	renderer.display_primitive(rt, lt, lb);
}

enum Flag { ally, enemy };
void draw_box(Renderer& renderer, Flag flag = ally)
{
	point_t p[8];
	p[0] = { -1,-1,-1,1 };
	p[1] = { 1,-1,-1,1 };
	p[2] = { 1,1,-1,1 };
	p[3] = { -1,1,-1,1 };
	p[4] = { -1,-1,1,1 };
	p[5] = { 1,-1,1,1 };
	p[6] = { 1,1,1,1 };
	p[7] = { -1,1,1,1 };

	vertex_t vert[8];
	color_t boxColor = { 1,1,1,1 };
	if (flag == ally) { boxColor = { 0,0,1,1 }; }
	else if (flag == enemy) { boxColor = { 1,0,0,1 }; }
	vert[0].color = boxColor;
	vert[1].color = boxColor;
	vert[2].color = boxColor;
	vert[3].color = boxColor;
	vert[4].color = boxColor;
	vert[5].color = boxColor;
	vert[6].color = boxColor;
	vert[7].color = boxColor;
	for (int i = 0; i < 8; i++) {
		vert[i].pos = p[i] * 0.5;
	}

	draw_square(renderer, vert[0], vert[1], vert[2], vert[3]);
	draw_square(renderer, vert[1], vert[5], vert[6], vert[2]);
	draw_square(renderer, vert[0], vert[3], vert[7], vert[4]);
	draw_square(renderer, vert[0], vert[4], vert[5], vert[1]);
	draw_square(renderer, vert[3], vert[2], vert[6], vert[7]);
	draw_square(renderer, vert[4], vert[7], vert[6], vert[5]);
}

void draw_light(Renderer& renderer)
{
	point_t p[8];
	p[0] = { -1,-1,-1,1 };
	p[1] = { 1,-1,-1,1 };
	p[2] = { 1,1,-1,1 };
	p[3] = { -1,1,-1,1 };
	p[4] = { -1,-1,1,1 };
	p[5] = { 1,-1,1,1 };
	p[6] = { 1,1,1,1 };
	p[7] = { -1,1,1,1 };

	vertex_t vert[8];
	vert[0].color = { 0.9f,0.9f,0.9f,1 };
	vert[1].color = { 0.9f,0.9f,0.9f,1 };
	vert[2].color = { 0.9f,0.9f,0.9f,1 };
	vert[3].color = { 0.9f,0.9f,0.9f,1 };
	vert[4].color = { 0.9f,0.9f,0.9f,1 };
	vert[5].color = { 0.9f,0.9f,0.9f,1 };
	vert[6].color = { 0.9f,0.9f,0.9f,1 };
	vert[7].color = { 0.9f,0.9f,0.9f,1 };
	for (int i = 0; i < 8; i++) {
		vert[i].pos = p[i];
	}

	draw_square(renderer, vert[3], vert[2], vert[1], vert[0]);
	draw_square(renderer, vert[2], vert[6], vert[5], vert[1]);
	draw_square(renderer, vert[4], vert[7], vert[3], vert[0]);
	draw_square(renderer, vert[1], vert[5], vert[4], vert[0]);
	draw_square(renderer, vert[7], vert[6], vert[2], vert[3]);
	draw_square(renderer, vert[5], vert[6], vert[7], vert[4]);
}

vector_t positions[2];
Window window;
void ClientThread()
{
	//client.Boot(positions, window);
}

int main()
{
	//渲染
	window.screen_init(800, 600, _T("SoftwareRenderer - 方向键移动,Y/H缩放视角."));
	float fov = 45.0f;

	//客户端线程
	Client client;
	client.Init();
	client.ConnectToServer("127.0.0.1");
	//std::thread t(ClientThread);
	//t.detach();

	Renderer renderer;
	renderer.init(window.screen_width, window.screen_height, window.screen_fb);
	Renderer renderer_light;
	renderer_light.init(window.screen_width, window.screen_height, window.screen_fb);
	renderer_light.z_buffer = renderer.z_buffer;//因为深度缓存是每个Renderer独用的,但是现在想让它们一起显示.
	Renderer renderer_ground;
	renderer_ground.init(window.screen_width, window.screen_height, window.screen_fb);
	renderer_ground.z_buffer = renderer.z_buffer;

	Camera camera;
	float posz = -13;
	float posy = 5;
	float posx = 0;
	camera.init_target_zero({ posx,posy,posz,1 });
	camera.front = { 0,-0.3,1,1 };

	float angle = 0;
	vector_t rotate_axis = { 1,-0.5,0.5,1 };
	renderer.camera = &camera;
	//renderer.render_state = RENDER_STATE_WIREFRAME;
	renderer.render_state = RENDER_STATE_COLOR;
	//renderer.render_state = RENDER_STATE_TEXTURE;
	//renderer.features[RENDER_FEATURE_BACK_CULLING] = false;
	//renderer.features[RENDER_FEATURE_LIGHT] = false;

	//renderer-light
	renderer_light.camera = &camera;
	renderer_light.render_state = RENDER_STATE_COLOR;
	renderer_light.features[RENDER_FEATURE_LIGHT] = false;

	//renderer-ground
	renderer_ground.camera = &camera;
	renderer_ground.render_state = RENDER_STATE_TEXTURE;
	renderer_ground.features[RENDER_FEATURE_CVV_CLIP] = false;
	//renderer_ground.features[RENDER_FEATURE_BACK_CULLING] = false;


	Texture texture;
	texture.init();
	renderer.set_texture(texture);
	renderer_ground.set_texture(texture);

	Light dir_light;
	dir_light.pos = { 25,25,10,1 };
	dir_light.direction = { -50,-50,-20,1 };
	dir_light.ambient = { 0.3f,0.2f,0.1f,1 };
	dir_light.diffuse = { 0.6f,0.6f,0.6f,1 };
	dir_light.specular = { 0.8f,0.7f,0.6f,1 };
	dir_light.light_state = LIGHT_STATE_DIRECTIONAL;
	renderer.add_light(dir_light);
	renderer_ground.add_light(dir_light);

	Light point_light;
	point_light.pos = { 0,3,0,1 };
	point_light.ambient = { 0.2f,0.2f,0.2f,1 };
	point_light.diffuse = { 0.9f,0.9f,0.9f,1 };
	point_light.specular = { 1.0f,1.0f,1.0f,1 };
	point_light.light_state = LIGHT_STATE_POINT;
	renderer.add_light(point_light);
	renderer_ground.add_light(point_light);

	Light spot_light;
	spot_light.light_state = LIGHT_STATE_SPOTLIGHT;
	spot_light.ambient = { 1.0,1.0,1.0,1 };
	spot_light.diffuse = { 0.8,0.8,0.8,1 };
	spot_light.specular = { 0.9,0.9,0.9,1 };
	//手电筒衰减强一些
	spot_light.linear = 0.14;
	spot_light.quadratic = 0.07;
	renderer.add_light(spot_light);
	renderer_ground.add_light(spot_light);

	//设置主renderer
	float aspect = (float)renderer.width / ((float)renderer.height);
	renderer.current_light = &dir_light;
	renderer_ground.current_light = &dir_light;

	//时间
	float delta_time = 0.0f;
	float last_frame = 0.0f;

	int iDataNum;

	while (window.screen_exit[0] == 0 && window.screen_keys[VK_ESCAPE] == 0) {
		//时间,使移动速度不受帧率变化
		//float current_frame = time_get();
		//delta_time = current_frame - last_frame;
		//last_frame = current_frame;
		camera.speed = 0.1f;

		window.screen_dispatch();
		renderer.clear();

		if (window.screen_keys[VK_LEFT]) {}
		if (window.screen_keys[VK_RIGHT]) {}
		if (window.screen_keys[VK_UP]) {}
		if (window.screen_keys[VK_DOWN]) {}

		if (window.screen_keys[KEY_Y]) { fov -= 0.04f; }
		if (window.screen_keys[KEY_H]) { fov += 0.04f; }
		fov = CMID(fov, 44.6f, 45.6f);

		//与服务端交互
		//大小不能写sizeof(window.screen_keys),因为window.screen_keys是一个指针,不是数组
		send(client.serverSocket, (char*)window.screen_keys, 512, 0);
		iDataNum = recv(client.serverSocket, (char*)positions, sizeof(positions), 0);

		matrix_t model;
		//************正常场景************//
		//更新摄像机
		camera.target = camera.pos + camera.front;
		matrix_t view = matrix_lookat(renderer.camera->pos, renderer.camera->target, renderer.camera->up);
		renderer.transform.view = view;

		matrix_set_perspective(&renderer.transform.projection, fov, aspect, 0.1f, 100.0f);

		//设置聚光
		spot_light.pos = camera.pos;
		spot_light.direction = camera.front;

		//画地面
		renderer_ground.transform = renderer.transform;
		matrix_set_identity(&model);
		model = matrix_scale(model, { 10,0.1,10,1 });
		model = matrix_translate(model, { 0,-3,5,1 });
		renderer_ground.transform.model = model;
		renderer_ground.transform_update();
		draw_box(renderer_ground);

		//画我方盒子
		matrix_set_identity(&model);
		model = matrix_translate(model, positions[1]);
		renderer.transform.model = model;
		renderer.transform_update();
		draw_box(renderer, ally);
		//画敌方盒子
		matrix_set_identity(&model);
		model = matrix_translate(model, positions[0]);
		renderer.transform.model = model;
		renderer.transform_update();
		draw_box(renderer, enemy);

		//画点光源
		renderer_light.transform = renderer.transform;
		matrix_set_identity(&model);
		model = matrix_scale(model, { 0.2,0.2,0.2,1 });
		model = matrix_translate(model, point_light.pos);
		renderer_light.transform.model = model;
		renderer_light.transform_update();
		draw_light(renderer_light);

		//画太阳(定向光)
		matrix_set_identity(&model);
		model = matrix_scale(model, { 10,10,20,1 });
		model = matrix_translate(model, { 50,50,20,1 });
		renderer_light.transform.model = model;
		renderer_light.transform_update();
		draw_light(renderer_light);


		renderer.draw_line(10, 10, 20, 10, 0x0);
		renderer.draw_line(10, 10, 10, 20, 0x0);

		window.screen_update();
	}
}



