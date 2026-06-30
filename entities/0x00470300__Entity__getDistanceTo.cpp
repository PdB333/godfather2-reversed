// FUNC_NAME: Entity::getDistanceTo
#include <cmath>

float Entity::getDistanceTo(Entity* other) const
{
    // Position is stored at offset 0x100 (x), 0x104 (y), 0x108 (z)
    float dx = other->position.x - this->position.x;
    float dy = other->position.y - this->position.y;
    float dz = other->position.z - this->position.z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}