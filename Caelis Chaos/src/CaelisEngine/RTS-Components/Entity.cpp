#include "Entity.h"

Entity::Entity()
{
    m_coords = SDLFPoint(0.0f, 0.0f);
    m_size = SDLFPoint(4.0f, 2.0f);
    m_fMovementSpeed = 0.0f;
    m_movementTarget = SDLFPoint(0.0f, 0.0f);
	m_nTeam = 0;
	m_fBaseAttack = 0.0f;
	m_fBaseHealth = 0.0f;
	m_fCurrentHealth = 0.0f;
	m_fAttackRange = 0.0f;
	m_fVisionRange = 0.0f;
	m_entityTarget = nullptr;
}

Entity::Entity(SDL_FPoint initialCoords, int nTeam)
{
	m_coords = initialCoords;
    m_size = SDLFPoint(4.0f, 2.0f);
    m_fMovementSpeed = 0.0f;
    m_movementTarget = SDLFPoint(0.0f, 0.0f);
	m_nTeam = nTeam;
	m_fVisionRange = 0.0f;
	m_entityTarget = nullptr;
}

Entity::Entity(std::string sSubclass, std::string spriteID) {
	m_coords = SDLFPoint(0.0f, 0.0f);
    m_fMovementSpeed = 0.0f;
    m_movementTarget = SDLFPoint(0.0f, 0.0f);
	m_nTeam = 0;
	m_sSubclass = sSubclass;
    m_spriteID = spriteID;
    m_size = SDLFPoint(1.0f, 1.0f);
	m_entityTarget = nullptr;
}

Entity::Entity(std::string sSubclass, std::string spriteID, SDL_FPoint size) {
	m_coords = SDLFPoint(0.0f, 0.0f);
    m_fMovementSpeed = 0.0f;
    m_movementTarget = SDLFPoint(0.0f, 0.0f);
	m_nTeam = 0;
	m_sSubclass = sSubclass;
    m_spriteID = spriteID;
    m_size = size;
	m_entityTarget = nullptr;
}

Entity::Entity(std::string sSubclass, std::string sType, std::string spriteID, SDL_FPoint size) {
	m_coords = SDLFPoint(0.0f, 0.0f);
    m_fMovementSpeed = 0.0f;
    m_movementTarget = SDLFPoint(0.0f, 0.0f);
	m_nTeam = 0;
	m_sSubclass = sSubclass;
    m_spriteID = spriteID;
    m_size = size;
    m_sType = sType;
	m_entityTarget = nullptr;
}

Entity::Entity(Entity* prototype, SDL_FPoint initialCoords, int nTeam)
{
	m_coords = initialCoords;
	m_nTeam = nTeam;
	m_sSubclass = prototype->m_sSubclass;
	m_sType = prototype->m_sType;
    m_spriteID = prototype->m_spriteID;
    m_size = prototype->m_size;
    m_fMovementSpeed = 0.1f;
    m_movementTarget = SDLFPoint(0.0f, 0.0f);
	m_abilities = prototype->m_abilities;
	m_fBaseAttack = prototype->m_fBaseAttack;
	m_fBaseHealth = prototype->m_fBaseHealth;
	m_fCurrentHealth = m_fBaseHealth;
	m_fAttackRange = prototype->m_fAttackRange;
	m_fVisionRange = prototype->m_fVisionRange;
	m_entityTarget = nullptr;
}

void Entity::move() 
{
	if (m_entityTarget != nullptr)
	{
		m_movementTarget = m_entityTarget->m_coords;
	}
	float fDistanceToTarget = calculateDistance(m_movementTarget, m_coords);
    if (fDistanceToTarget > (m_size.x / 2.0f)) {

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

void Entity::executeAbility(std::string sAbilityName)
{
    m_abilities[sAbilityName]->Execute(this);
}

void Entity::executeAbility(std::string sAbilityName, Entity* target)
{
    m_abilities[sAbilityName]->Execute(this, target);
}

void Entity::addAbility(std::string sAbilityName, Ability* ability)
{
    m_abilities[sAbilityName] = ability;
}

void Entity::takeDamage(float fDamageReceived)
{
	m_fCurrentHealth = m_fCurrentHealth - fDamageReceived;
}

void Entity::setEntityTarget(Entity* newTarget)
{
	m_entityTarget = newTarget;
}