#include "BBall.h"
#include "TextureManager.h"
#include "Util.h"

BBall::BBall()
{
	TextureManager::Instance()->load("../Assets/textures/EnemyCircle.png", "ball");
	TextureManager::Instance()->load("../Assets/textures/EnemySquare.png", "square");
	TextureManager::Instance()->load("../Assets/textures/EnemyTriangle.png", "triangle");

	auto size = TextureManager::Instance()->getTextureSize("ball");
	setWidth(size.x);
	setHeight(size.y);


	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);

	getRigidBody()->isColliding = false;
	setType(BALLS);
}

BBall::~BBall()
= default;

void BBall::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	if (shape == 0) {
		TextureManager::Instance()->draw("ball", x, y, 0, 255, true);
	}
	else if (shape == 1) {
		TextureManager::Instance()->draw("square", x, y, 0, 255, true);
	}
	else if (shape == 2) {
		TextureManager::Instance()->draw("triangle", x, y, 0, 255, true);
	}

	
}

void BBall::update() {

	getRigidBody()->acceleration = glm::vec2(0, 9.8 * 10);
	float deltaTime = 1.0f / 60.0f;

	getRigidBody()->velocity = getRigidBody()->velocity + (getRigidBody()->acceleration * deltaTime);
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * deltaTime;
	

	m_checkbounds();
}

void BBall::clean()
{
}

bool BBall::isColliding(GameObject* pOther)
{
	float myRadius = getWidth() * 0.5f;
	float otherRadius = pOther->getWidth() * 0.5f;

	return (getDistance(pOther) <= myRadius + otherRadius);
}

float BBall::getDistance(GameObject* pOther)
{
	glm::vec2 myPos = getTransform()->position;
	glm::vec2 otherPos = pOther->getTransform()->position;

	// Use pythagorean to calculate distance c = sqrt(a^2 + b^2)
	float a = myPos.x - otherPos.x;
	float b = myPos.y - otherPos.y;
	return sqrt(a * a + b * b);
}

void BBall::m_checkbounds()
{
	//left and right
	if (getTransform()->position.x >= 790)
	{
		getRigidBody()->velocity = glm::vec2(getRigidBody()->velocity.x * -0.9f, getRigidBody()->velocity.y);
	}

	if (getTransform()->position.x <= 10)
	{
		getRigidBody()->velocity = glm::vec2(getRigidBody()->velocity.x * -0.9f, getRigidBody()->velocity.y);
	}


	//up and down
	if (getTransform()->position.y >= 590)
	{
		getRigidBody()->velocity = glm::vec2(getRigidBody()->velocity.x, getRigidBody()->velocity.y * -0.9f);
	}

	if (getTransform()->position.y <= 10)
	{
		getRigidBody()->velocity = glm::vec2(getRigidBody()->velocity.x, getRigidBody()->velocity.y * -0.9f);
	}
}

void BBall::m_reset()
{
	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
}

