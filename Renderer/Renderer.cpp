// Renderer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "PipeLine.h"
#include "Rmath.h"

const int WIDTH = 800;
const int HEIGHT = 600;
Matrix4x4 world = Matrix4x4(true), view = Matrix4x4(true), project = Matrix4x4(true);


int main()
{
	freopen("model2.obj", "w", stdout);
	/*std::cout << "P3\n";
	std::cout << WIDTH << " " << HEIGHT << "\n";
	std::cout << "255\n";*/

	PipeLine now = PipeLine(WIDTH, HEIGHT);
	now.initialize();
	now.clearBuffer(Vector4D(1.0f, 1.0f, 1.0f, 1.0f));

	Matrix4x4 scale = Matrix4x4(true), rotate = Matrix4x4(true), transform = Matrix4x4(true);
	Matrix4x4 rotateX = Matrix4x4(true), rotateY = Matrix4x4(true), rotateZ = Matrix4x4(true);

	view.setLookAt(Vector3D(0.0f, 0.0f, 2.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 1.0f, 0.0f));
	project.setPerspective(-1.0f * WIDTH / HEIGHT, 1.0f * WIDTH / HEIGHT, -1, +1, 1.0f, 100000.0f);
	//project.setOrtho(-1.0f * WIDTH / HEIGHT, 1.0f * WIDTH / HEIGHT, -1, +1, 10.0f, -100000.0f);
	//project.setPerspective(-1.0f * WIDTH / 2.0f, 1.0f * WIDTH / 2.0f, -1.0f * HEIGHT / 2.0f, +1.0f * HEIGHT / 2.0f, 1.0f, 100000.0f);
	//project.setOrtho(-1.0f * WIDTH, 1.0f * WIDTH, -1.0f * HEIGHT / 2.0f, +1.0f * HEIGHT / 2.0f, 1.0f, 100000.0f);
	now.setTransform(world, view, project);

	ObjModel obj = ObjModel("model.obj");
	for (int i = 0; i < obj.vertices.size(); i++) {
		std::cout << "v";
		for (int j = 0; j < 3; j++) {
			std::cout << " " << obj.vertices[i].position[j];
		} puts("");
	}
	for (int i = 0; i < obj.indices.size(); i += 3) {
		std::cout << "f";
		for (int j = 0; j < 3; j++) {
			std::cout << " " << obj.indices[i + j];
		} puts("");
	}
	
	/*ObjModel obj = ObjModel("model.obj");
	scale.setScale(Vector3D(1.0f, 1.0f, 1.0f));
	rotateY.setRotationY(-30.0f);
	rotate = rotateX * rotateY * rotateZ;
	transform.setTranslation(Vector3D(0.0f, 0.0f, 0.0f));
	world = scale * rotate * transform;
	
	std::cerr << obj.indices.size() << " " << obj.vertices.size() << std::endl;
	now.setTransform(world);
	now.setIndexBuffer(obj.indices);
	now.setVertexBuffer(obj.vertices);
	now.setTexture(1024, 1024, 4, "model.png");
	now.setRenderMode(RenderMode::FILL);
	//now.drawIndex(new Vector4D(0.0f, 0.0f, 0.0f));
	now.drawIndex();*/

	/*Mesh kk = Mesh();
	scale.setScale(Vector3D(1.0f, 0.5f, 1.0f));
	rotate = rotateX * rotateY * rotateZ;
	transform.setTranslation(Vector3D(0.0f, -0.5f, 0.0f));
	world = rotate * scale * transform;
	kk.asBox(1.0f, 1.0f, 1.0f);
	//kk.asTriangle(Vector3D(-1.0f, -1.0f, 1.0f), Vector3D(1.0f, 1.0f, -1.0f), Vector3D(1.0f, -1.0f, 0.5f));
	std::cerr << kk.indices.size() << "\n";

	now.setTransform(world);
	now.setIndexBuffer(kk.indices);
	now.setVertexBuffer(kk.vertices);
	now.setRenderMode(RenderMode::WIREANDFILL);
	//now.drawIndex(RenderMode::FILL);
	now.drawIndex(new Vector4D(0.0f, 0.0f, 0.0f));
	//now.drawIndex(RenderMode::FILL, new Vector4D(0.3f, 0.7f, 0.5f));*/


	
	/*scale.setScale(Vector3D(2.0f, 2.0f, 2.0f));
	//rotateX.setRotationX(45.0f), rotateY.setRotationY(45.0f);
	rotateX.setRotationX(30.0f), rotateY.setRotationY(60.0f);
	rotate = rotateX * rotateY * rotateZ;
	transform.setTranslation(Vector3D(0.0f, 0.0f, 0.0f));
	world = scale * rotate * transform;
	kk.asBox(1.0f, 1.0f, 1.0f);
	std::cerr << kk.indices.size() << "\n";

	now.setTransform(world);
	now.setIndexBuffer(kk.indices);
	now.setVertexBuffer(kk.vertices);
	now.setRenderMode(RenderMode::WIREANDFILL);
	//now.drawIndex(RenderMode::FILL);
	now.drawIndex(new Vector4D(0.0f, 0.0f, 0.0f));
	//now.drawIndex(RenderMode::FILL, new Vector4D(0.5f, 0.2f, 0.8f));*/

	/*Mesh kk;
	rotate = rotateX * rotateY * rotateZ;
	transform.setTranslation(Vector3D(0.0f, 0.0f, 0.0f));
	world = scale * rotate * transform;
	kk.asTriangle(Vector3D(1.0f, 1.0f, 1.0f), Vector3D(1.0f, 0.0f, -1.0f), Vector3D(0.0f, 0.0f, 2.0f));
	std::cerr << kk.indices.size() << "\n";

	now.setTransform(world);
	now.setIndexBuffer(kk.indices);
	now.setVertexBuffer(kk.vertices);
	now.setRenderMode(RenderMode::WIREANDFILL);
	now.drawIndex(nullptr);


	rotate = rotateX * rotateY * rotateZ;
	transform.setTranslation(Vector3D(0.0f, 0.0f, 0.0f));
	world = scale * rotate * transform;
	kk.asTriangle(Vector3D(0.0f, 2.0f, 0.0f), Vector3D(1.0f, 0.0f, 1.0f), Vector3D(0.0f, 0.0f, 1.0f));
	std::cerr << kk.indices.size() << "\n";

	now.setTransform(world);
	now.setIndexBuffer(kk.indices);
	now.setVertexBuffer(kk.vertices);
	now.setRenderMode(RenderMode::WIREANDFILL);
	now.drawIndex(nullptr);*/

	//now.printFrame();
	fclose(stdout);
}

/*
2
0.1 0.3 0.3 0.2 0.4 0.2 0.2 0.5 0.1
0.1 0.2 0.3 0.4 0.2 0.5

1
0.1 0.3 0.2 0.4 0.2 0.5

1
0.1 0.3 30 0.2 0.4 20 0.2 0.5 10

2
0.18 0.1 1 0.1 0.5 1 0.5 0.1 1
0.15 0.15 2 0.5 0.6 0.5 0.2 0.32 0.5

2
0.5 0.4 2 0.5 0.6 2 0.4 0.5 2
0.5 0.4 1 0.5 0.6 1 0.6 0.5 1

2
0.1 0.1 0.1 0.5 0.5 0.5
0.1 0.1 0.5 0.1 0.5 0.5

3
0.1 0.7 0.2 0.3 0.9 0.6
0.2 0.13 0.55 0.46 0.83 0.67
0.3 0.44 0.29 0.35 0.65 0.23

1
0.1 0.2 0.3 0.4 0.2 0.5

1
0.1 0.3 0.2 0.4 0.2 0.5
*/

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
