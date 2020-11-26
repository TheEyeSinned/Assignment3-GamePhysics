#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"


PlayScene::PlayScene()
{
	PlayScene::start();

	
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 400, 300, 0, 255, true);
	drawDisplayList();

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void PlayScene::update()
{
	updateDisplayList();


	if (SDL_GetTicks() - bulletSpawnTimerStart >= bulletSpawnTimerDuration) {
		SpawnBullet();
	}

	std::vector<Bullet*>& activeBullets = m_pPool->all;
	for (std::vector<Bullet*>::iterator myiter = activeBullets.begin(); myiter != activeBullets.end(); myiter++) {
		Bullet* bullet = *myiter;
		if (bullet->active && bullet->getTransform()->position.y >= 610) {
			m_pPool->Despawn(bullet);
			break;
		}
	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pPlayer->moveLeft();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pPlayer->moveRight();
	}
	else {
		m_pPlayer->stopMovingX();
	}


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W)) {
		m_pPlayer->moveUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)) {
		m_pPlayer->moveDown();
	}
	else {
		m_pPlayer->stopMovingY();
	}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/Background.png", "background");

	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);

	m_pPool = new BulletPool(numBullets);
	for (std::vector<Bullet*>::iterator myiter = m_pPool->all.begin(); myiter != m_pPool->all.end(); myiter++) {
		Bullet* bullet = *myiter;
		addChild(bullet);
	}
	bulletSpawnTimerStart = SDL_GetTicks();
}

void PlayScene::SpawnBullet() {
	Bullet* bullet = m_pPool->Spawn();
	if (bullet) {
		bullet->getTransform()->position = glm::vec2(50 + rand() % 700, 0 /*rand() % 100 * -1*/);
	}

	bulletSpawnTimerStart = SDL_GetTicks();
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::Button("Next Scene")) {
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

	ImGui::End();
	ImGui::EndFrame();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}