// FUNC_NAME: Entity::getMovementSpeed
float __thiscall Entity::getMovementSpeed(Entity* this)
{
    // +0x218: pointer to movement component (e.g., MovementComponent*)
    void* movementComponent = *(void**)((char*)this + 0x218);
    if (movementComponent != 0) {
        // +0x1c: float field containing current speed
        return *(float*)((char*)movementComponent + 0x1c);
    }
    return 0.0f;
}