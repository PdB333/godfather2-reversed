// FUNC_NAME: Entity::getWorldPosition
// Address: 0x00546730
// Role: Retrieves the world-space position of an entity by copying three floats from an internal transform structure.
// The 'this' pointer contains a pointer to a transform node at offset 0x2e8.
// That transform node stores position as a 3-float vector at offsets +0x1a0, +0x1a4, +0x1a8.

void __thiscall Entity::getWorldPosition(Entity *this, Vec3 *outPosition)
{
    // Get the pointer to the transform node (e.g., scene node or render object)
    void *transformNode = *(void **)((char *)this + 0x2e8);
    
    // Copy the three floats representing position (X, Y, Z) from the transform node
    outPosition->x = *(float *)((char *)transformNode + 0x1a0);
    outPosition->y = *(float *)((char *)transformNode + 0x1a4);
    outPosition->z = *(float *)((char *)transformNode + 0x1a8);
}