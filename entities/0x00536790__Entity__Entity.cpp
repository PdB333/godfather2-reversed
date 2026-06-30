// FUNC_NAME: Entity::Entity
void __fastcall Entity::Entity(int thisPtr)
{
    // Call base class constructor (likely EARS::Framework::Entity base)
    FUN_00612e00();

    // Zero out three consecutive 4-byte fields at offsets 0x120, 0x124, 0x128
    // These could be pointers, flags, or counters
    *(int32_t*)(thisPtr + 0x120) = 0; // +0x120:  first field
    *(int32_t*)(thisPtr + 0x124) = 0; // +0x124:  second field
    *(int32_t*)(thisPtr + 0x128) = 0; // +0x128:  third field
}