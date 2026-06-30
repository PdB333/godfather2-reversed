// FUNC_NAME: Entity::computeRelativeVectorToTarget
void __thiscall Entity::computeRelativeVectorToTarget(int thisPtr, uint32_t param2)
{
    // in_EAX is an implicit pointer to another Entity object (likely passed in EAX register)
    Entity* other = (Entity*)in_EAX;

    // Compute delta vector from other to this: (this->pos - other->pos)
    float deltaX = *(float*)(thisPtr + 0x100) - *(float*)(other + 0x100);
    float deltaY = *(float*)(thisPtr + 0x104) - *(float*)(other + 0x104);
    float deltaZ = *(float*)(thisPtr + 0x108) - *(float*)(other + 0x108);

    // Pass the delta vector and param2 to a helper function (likely for normalization, rotation, or clamping)
    // FUN_0046fe50 is called with address of local delta and param2
    FUN_0046fe50(&deltaX, param2);
}