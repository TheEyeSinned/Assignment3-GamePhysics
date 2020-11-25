#include "Brick.h"
#include "TextureManager.h"
#include "Util.h"

Brick::Brick()
{
	TextureManager::Instance()->load("../Assets/textures/EnemyCircle.png", "brick");

	auto size = TextureManager::Instance()->getTextureSize("brick");
	setWidth(size.x);
	setHeight(size.y);


	getTransform()->position = glm::vec2(400.0f, 500.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(BRICK);

}

Brick::~Brick()
= default;

void Brick::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("brick", x, y, 0, 255, true);
}

void Brick::update()
{
	const float deltaTime = 1.0f / 60.f;

	// Normalize direction vector
	float dirmagnitude = Util::magnitude(m_direction);
	if (dirmagnitude > 0) {
		getRigidBody()->acceleration = Util::normalize(m_direction) * ACCELERATION;

	}
	else if (Util::magnitude(getRigidBody()->velocity) > 0) {
		getRigidBody()->acceleration = Util::normalize(getRigidBody()->velocity) * -ACCELERATION;
	}

	getRigidBody()->velocity += getRigidBody()->acceleration;

	// to stop the jittering, resets acceleration and velocity once velocity is low enough
	if (Util::magnitude(getRigidBody()->velocity) < ACCELERATION) {
		getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
		getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	}

	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;

	getTransform()->position = pos;

	m_checkbounds();
}

void Brick::clean()
{
}

void Brick::moveLeft()
{
	m_direction.x = -1;
}

void Brick::moveRight()
{
	m_direction.x = 1;
}

void Brick::stopMovingX()
{
	m_direction.x = 0;
}

bool Brick::isColliding(GameObject* pOther)
{
	float myRadius = getWidth() * 0.5f;
	float otherRadius = pOther->getWidth() * 0.5f;

	return (getDistance(pOther) <= myRadius + otherRadius);
}

float Brick::getDistance(GameObject* pOther)
{
	glm::vec2 myPos = getTransform()->position;
	glm::vec2 otherPos = pOther->getTransform()->position;

	// Use pythagorean to calculate distance c = sqrt(a^2 + b^2)
	float a = myPos.x - otherPos.x;
	float b = myPos.y - otherPos.y;
	return sqrt(a * a + b * b);
}

void Brick::m_checkbounds()
{
	if (getTransform()->position.x > Config::SCREEN_WIDTH)
	{
		getTransform()->position = glm::vec2(800.0f, getTransform()->position.y);
	}

	if (getTransform()->position.x < 0)
	{
		getTransform()->position = glm::vec2(0.0f, getTransform()->position.y);
	}

	if (getTransform()->position.y > Config::SCREEN_HEIGHT)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 600.0f);
	}

	if (getTransform()->position.y < 0)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 0.0f);
	}
}

