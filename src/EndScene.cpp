#include "EndScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"


EndScene::EndScene()
{
	EndScene::start();
}

EndScene::~EndScene()
= default;

void EndScene::draw()
{
	TextureManager::Instance()->draw("background", 400, 300, 0, 255, true);
	drawDisplayList();

	drawDisplayList();

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void EndScene::update()
{
	if (m_pBall->isColliding(m_pBrick)) {
		if (m_pBrick->getRigidBody()->velocity.x < 0) {
			m_pBall->getRigidBody()->velocity.x -= m_pBrick->getRigidBody()->velocity.x * 3;
		}

		if (m_pBrick->getRigidBody()->velocity.x > 0) {
			m_pBall->getRigidBody()->velocity.x -= m_pBrick->getRigidBody()->velocity.x * 3;
		}
		m_pBall->getRigidBody()->velocity.y = m_pBall->getRigidBody()->velocity.y * -1.1f; //glm::vec2(-((m_pBrick->getRigidBody()->velocity.x * 0.1f ) + m_pBall->getRigidBody()->velocity.x), -((m_pBrick->getRigidBody()->velocity.x * 0.1f) + m_pBall->getRigidBody()->velocity.y));
	}
	updateDisplayList();

}

void EndScene::clean()
{
	removeAllChildren();
}

void EndScene::handleEvents()
{
	EventManager::Instance().update();

	m_pBrick->getTransform()->position.x = EventManager::Instance().getMousePosition().x;

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}


}

void EndScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/Background.png", "background");

	// Player Sprite
	m_pBrick = new Brick();
	addChild(m_pBrick);

	m_pBall = new BBall();
	addChild(m_pBall);
	
}

void EndScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::Button("Previous Scene")) {
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}

	if (ImGui::Button("Reset Ball")) {
		m_pBall->m_reset();
	}


	ImGui::Separator();


	if (ImGui::Button("Shape: Ball")) {
		m_pBall->shape = 0;
	}

	if (ImGui::Button("Shape: Square")) {
		m_pBall->shape = 1;
	}

	if (ImGui::Button("Shape: Triangle")) {
		m_pBall->shape = 2;
	}


	/*if (ImGui::Button("Square")) {
		m_pBall->square();
	}

	if (ImGui::Button("Reset")) {
		m_pBall->m_reset();
	}
	ImGui::Separator();

	static bool isGravityEnabled = false;
	if (ImGui::Checkbox("Gravity off", &isGravityEnabled)) {
		m_pBall->isGravityEnabled = isGravityEnabled;
	}

	ImGui::Separator();

	static int xRise = 155;
	if (ImGui::SliderInt("Rise", &xRise, 10, m_pRamp->yPosition - 50)) {
		m_pRamp->rise = xRise;
		m_pBall->throwPosition.y = xRise - 15;
	}*/

	/*static int xPosEnemy = 640;
	if (ImGui::SliderInt("Plane's X Position", &xPosEnemy, 450, 800)) {
		m_pPlane->getTransform()->position.x = xPosEnemy;
	}*/

	/*static float velocity[2] = { 40 , 60 };
	if (ImGui::SliderFloat2("Throw Speed", velocity, 0, 100)) {
		m_pBall->throwSpeed = glm::vec2(velocity[0], -velocity[1]);
	}*/

	ImGui::End();
	ImGui::EndFrame();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}