#ifndef ENGINE_H
#define ENGINE_H

#include <glew.h>
#include <glfw3.h>
#include <map>
#include <System.h>
#include <Renderer.h>
#include <Action.h>
#include <Entity.h>
#include <Mesh.h>
#include <Shader.h>
#include <Texture.h>
#include <DebugCamera.h>
#include <PlayerInput.h>
#include <RigidBody.h>
#include <Collider.h>
#include <Triangle.h>
#include <Sphere.h>
#include <Terrain.h>


class Engine
{
public:
	static void init();
	static void run();
	static void terminate();

	static void addRunningSystem(int _enum, System*);

private:
	static GLFWwindow* window;
	static std::map<int, System*> runningSystems;
};

#endif