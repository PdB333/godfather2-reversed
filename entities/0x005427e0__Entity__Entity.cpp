// FUNC_NAME: Entity::Entity
void __thiscall Entity::Entity(void)
{
    // Base class constructor call with parameters (size=3, type=0x46)
    BaseEntity::Construct(this, 3, 0x46);

    // Set up vtable pointers for multiple inheritance
    *(void**)this = (void*)0x00e394d8;                        // primary vtable at offset 0
    *(void**)((char*)this + 0x3C) = (void*)0x00e396f4;        // +0x3C (offset 0x0F * 4)
    *(void**)((char*)this + 0x48) = (void*)0x00e39704;        // +0x48 (offset 0x12 * 4)
    *(void**)((char*)this + 0x50) = (void*)0x00e39708;        // +0x50 (offset 0x14 * 4)
    *(void**)((char*)this + 0x54) = (void*)0x00e39710;        // +0x54 (offset 0x15 * 4)
    *(void**)((char*)this + 0x58) = (void*)0x00e39770;        // +0x58 (offset 0x16 * 4)

    // Initialize debug marker fields (offsets 0xAC-0xB6 in words)
    *(int*)((char*)this + 0x2B0) = 0;                         // +0xAC
    *(int*)((char*)this + 0x2B4) = 0;                         // +0xAD
    *(int*)((char*)this + 0x2B8) = 0;                         // +0xAE
    *(int*)((char*)this + 0x2BC) = 0;                         // +0xAF

    // Set canary values for debugging
    *(int*)((char*)this + 0x2C0) = 0xBADBADBA;               // +0xB0
    *(int*)((char*)this + 0x2C4) = 0xBEEFBEEF;               // +0xB1
    *(int*)((char*)this + 0x2C8) = 0xEAC15A55;               // +0xB2
    *(int*)((char*)this + 0x2CC) = 0x91100911;               // +0xB3

    // These fields are initially zeroed
    *(int*)((char*)this + 0x2D0) = 0;                         // +0xB4
    *(int*)((char*)this + 0x2D4) = 0;                         // +0xB5
    *(int*)((char*)this + 0x2D8) = 0;                         // +0xB6

    // Immediately clear the canary values (likely for initialization checking)
    *(int*)((char*)this + 0x2CC) = 0;                         // +0xB3
    *(int*)((char*)this + 0x2C8) = 0;                         // +0xB2
    *(int*)((char*)this + 0x2C4) = 0;                         // +0xB1
    *(int*)((char*)this + 0x2C0) = 0;                         // +0xB0

    // Call initialization function on some member (stack temporary used)
    InitSomeComponent(this);

    // Set flag at offset 0x52 (byte offset 0x148)
    *(int*)((char*)this + 0x148) |= 0x10;                     // +0x52
    // Dummy read (preserve side effect?) at +0x53
    (void)*(int*)((char*)this + 0x14C);                       // +0x53
}