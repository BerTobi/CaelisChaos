#include "Entity.h"

Entity::Entity()
{
    m_coords = SDLFPoint(0.0f, 0.0f);
    m_size = SDLFPoint(4.0f, 2.0f);
    m_fMovementSpeed = 0.0f;
    m_movementTarget = SDLFPoint(0.0f, 0.0f);
}

Entity::Entity(SDL_FPoint initialCoords)
{
	m_coords = initialCoords;
    m_size = SDLFPoint(4.0f, 2.0f);
    m_fMovementSpeed = 0.0f;
    m_movementTarget = SDLFPoint(0.0f, 0.0f);
}

void Entity::move() 
{
    if (m_movementTarget.x != m_coords.x || m_movementTarget.y != m_coords.y) {

        SDL_FPoint fDistance = { m_movementTarget.x - m_coords.x , m_movementTarget.y - m_coords.y };

        float fHypotenuse = sqrt(fDistance.x * fDistance.x + fDistance.y * fDistance.y);
        float fHorizontalAngle = acos(fDistance.x / fHypotenuse);
        float fVerticalAngle = asin(fDistance.y / fHypotenuse);

        float fSpeedX = m_fMovementSpeed * cos(fHorizontalAngle);
        float fSpeedY = m_fMovementSpeed * sin(fVerticalAngle);

        SDL_FPoint nextPosition = m_coords;

        if (m_movementTarget.x != m_coords.x)
            if (abs(m_movementTarget.x - m_coords.x) < fSpeedX)
                nextPosition.x = m_movementTarget.x;
            else
                nextPosition.x = m_coords.x + fSpeedX;

        if (m_movementTarget.y != m_coords.y)
            if (abs(m_movementTarget.y - m_coords.y) < fSpeedY)
                nextPosition.y = m_coords.y;
            else
                nextPosition.y = m_coords.y + fSpeedY;

        //float fMovementAngle = atan2f(randomPos.y - currentPos.y, randomPos.x - currentPos.x) * 180.0f / 3.14159;

        m_coords = nextPosition;
    }
}

void Entity::move(SDL_FPoint movementTarget) 
{
    m_movementTarget = movementTarget;
    move();
}


