// FUN_NAME: Player::updateGroundedState
// Reconstructed from 0x00798320
// Updates player's grounded flag and stores current velocity magnitude.
// Fields at offsets (relative to this as int*):
//   +0x24E4 (indices 0x939,0x93a) : previous position/velocity X,Y (8 bytes)
//   +0x24EC (index 0x93b)        : previous position/velocity Z (4 bytes)
//   +0x24A4 (index 0x929)        : flags (bit 0x2000 = isGrounded)
//   +0x30BC (index 0xc2f)        : squared speed (stored as int)

#include <cstdint>

void __thiscall Player::updateGroundedState()
{
    float velocityX, velocityY, velocityZ;  // from virtual call output
    void* movementComponent = (void*)getPlayerMovementData();
    // Copy 12-byte vector from movement component's +0x30 to this+0x24E4
    *(uint64_t*)(((uint8_t*)this) + 0x24E4) = *(uint64_t*)((uint8_t*)movementComponent + 0x30);
    *(int32_t*)(((uint8_t*)this) + 0x24EC) = *(int32_t*)((uint8_t*)movementComponent + 0x38);
    // Call virtual function at vtable+0x4c (likely GetVelocity)
    void** vtable = *(void***)this;
    typedef void(__thiscall* GetVelocityFunc)(void*, float&, float&, float&);
    GetVelocityFunc getVelocity = (GetVelocityFunc)vtable[0x13]; // 0x4c / 4 = 19 (0x13)
    getVelocity(this, velocityX, velocityY, velocityZ);
    // Store squared magnitude (drop decimals)
    *(int32_t*)(((uint8_t*)this) + 0x30BC) = (int32_t)(velocityX*velocityX + velocityY*velocityY + velocityZ*velocityZ);
    // Update grounded flag
    bool onGround = isOnGround(); // FUN_007fd720
    if (onGround) {
        *(int32_t*)(((uint8_t*)this) + 0x24A4) |= 0x2000;
    } else {
        *(int32_t*)(((uint8_t*)this) + 0x24A4) &= ~0x2000;
    }
}

// Dummy placeholder functions (original addresses)
int* __fastcall getPlayerMovementData() // FUN_00471610
{
    // Returns pointer to some movement/input data structure
    return nullptr;
}

bool __fastcall isOnGround() // FUN_007fd720
{
    // Returns whether the player is on the ground
    return false;
}