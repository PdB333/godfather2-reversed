// FUNC_NAME: Entity::cleanup
// Function at 0x006b1d10: releases internal resources and optionally frees memory.
// __thiscall, this = ecx, param_2 = flag (bit 0 = delete object)
int * __thiscall Entity::cleanup(Entity *this, byte flags)
{
    // Release internal resource if present (e.g., handle or pointer at offset 0)
    if (this->m_handle != NULL) {
        releaseResource(this);
    }
    // If flag bit 0 is set, deallocate the object itself (operator delete)
    if ((flags & 1) != 0) {
        operatorDelete(this);
    }
    return this;
}