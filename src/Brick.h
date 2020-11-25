#pragma once
#ifndef __BRICK__
#define __BRICK__

#include "Sprite.h"

class Brick final : public Sprite
{
public:
	Brick();
	~Brick();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void moveLeft();
	void moveRight();
	void stopMovingX();

	bool isColliding(GameObject*);
	float getDistance(GameObject*);

private:
	const float ACCELERATION = 10.0f;
	glm::vec2 m_direction;
	void m_checkbounds();

};

#endif /* defined (__PLANE__) */
