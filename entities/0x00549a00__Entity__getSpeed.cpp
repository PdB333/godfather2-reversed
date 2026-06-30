// FUNC_NAME: Entity::getSpeed
float Entity::getSpeed() const
{
    // this+0x18: pointer to movement component (e.g., PhysicsComponent or Transform)
    // component+0x14: speed scalar (e.g., linear velocity magnitude)
    return *(float*)(*(int*)((char*)this + 0x18) + 0x14);
}