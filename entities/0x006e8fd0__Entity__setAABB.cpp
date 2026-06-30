// FUNC_NAME: Entity::setAABB
void __thiscall Entity::setAABB(void* this, void* param_2) {
    // Local buffer of 0x38 bytes (56 bytes) - likely a temporary struct from a transform/matrix
    char buffer[0x38];
    // Fill buffer with AABB data computed from param_2 (likely a matrix or transform)
    computeAABBFromTransform(buffer, param_2); // FUN_0043a2a0

    // Copy 8 bytes (two floats) for min.x and min.y
    *(uint64*)((char*)this + 0x6c) = *(uint64*)(buffer + 0x2C);
    // Copy 8 bytes (two floats) for max.x and max.y
    *(uint64*)((char*)this + 0x78) = *(uint64*)(buffer + 0x20);
    // Copy 4 bytes for min.z
    *(uint32*)((char*)this + 0x74) = *(uint32*)(buffer + 0x34);
    // Copy 4 bytes for max.z
    *(uint32*)((char*)this + 0x80) = *(uint32*)(buffer + 0x28);
}