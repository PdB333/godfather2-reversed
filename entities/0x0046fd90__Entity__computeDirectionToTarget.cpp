// FUNC_NAME: Entity::computeDirectionToTarget
void __thiscall Entity::computeDirectionToTarget(Entity* this, Entity* other, uint param_3)
{
    // Compute vector from this->position to other->position
    // Offsets: +0x100 = position.x, +0x104 = position.y, +0x108 = position.z
    float dx = other->position.x - this->position.x;
    float dy = other->position.y - this->position.y;
    float dz = other->position.z - this->position.z;

    // Pass the resulting direction vector and additional parameter to a helper
    // (likely applies rotation or constraint to the vector)
    FUN_0046fe50(&dx, param_3);
}