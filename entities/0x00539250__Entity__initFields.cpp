// FUNC_NAME: Entity::initFields
void __thiscall Entity::initFields(Entity *this)
{
    // Call to parent class or base initialization function (FUN_00612e00)
    FUN_00612e00();

    // Zero out various member fields.
    // Offsets are based on the object layout.
    *(int *)((char *)this + 0x10) = 0;      // +0x10: likely a pointer or integer
    *(int *)((char *)this + 0x14) = 0;      // +0x14: another field
    *(int *)((char *)this + 0xa4) = 0;      // +0xa4: e.g., state flags
    *(int *)((char *)this + 0xe0) = 0;      // +0xe0: e.g., timer or counter
    *(int *)((char *)this + 0x120) = 0;     // +0x120: maybe some handle
    *(int *)((char *)this + 0x124) = 0;     // +0x124: adjacent field
    *(int *)((char *)this + 0x180) = 0;     // +0x180: another pointer
    *(int *)((char *)this + 0x184) = 0;     // +0x184: adjacent
    *(int *)((char *)this + 0x1c0) = 0;     // +0x1c0: e.g., flags
    *(int *)((char *)this + 0x230) = 0;     // +0x230: e.g., component index
    *(int *)((char *)this + 0x250) = 0;     // +0x250: e.g., last used value
    *(int *)((char *)this + 0x134) = 0;     // +0x134: some counter
    *(int *)((char *)this + 0x138) = 0;     // +0x138: adjacent
}