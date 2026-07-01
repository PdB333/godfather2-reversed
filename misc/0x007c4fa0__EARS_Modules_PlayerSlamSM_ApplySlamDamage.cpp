// Xbox PDB: EARS_Modules_PlayerSlamSM_ApplySlamDamage
//FUNC_NAME: PlayerGrappleSM::applyBodySlamImpact
void __thiscall PlayerGrappleSM::applyBodySlamImpact(void* thisPtr)
{
    // thisPtr + 0x58: pointer to a manager (e.g., CombatManager)
    int* pManager = *(int**)((char*)thisPtr + 0x58);
    // pManager[0x3fc] (offset 0xFF0): target entity pointer
    int* pTarget = (int*)pManager[0x3fc];
    if (pTarget == nullptr)
        return;

    // pTarget - 0x48: pointer to the entity's base object (vtable at start)
    int* pEntity = (int*)((char*)pTarget - 0x48);
    if (pEntity == nullptr)
        return;

    // Read a value from the target at offset 0x644 (e.g., hit flags or direction index)
    uint hitFlags = *(uint*)((char*)pTarget + 0x644);
    uint shiftedFlags = hitFlags >> 2;

    // Buffer for a vector or transform (12 bytes)
    char buffer[12];

    // Call virtual function at vtable+0xa4 on pEntity (e.g., getHitTransform)
    // Signature: void (__thiscall*)(void* this, char* outBuffer, uint* inFlags)
    (**(void (__thiscall**)(void*, char*, uint*))(*(int*)pEntity + 0xa4))(pEntity, buffer, &hitFlags);

    // Call virtual function at vtable+0x1e8 on pManager (e.g., applyForceToEntity)
    // Signature: void (__thiscall*)(void* this, int* entity, int type, uint flags, char* buffer, int, int, int)
    (**(void (__thiscall**)(void*, int*, int, uint, char*, int, int, int))(*(int*)pManager + 0x1e8))
        (pManager, pEntity, 8, shiftedFlags, buffer, 0, 0, 1);

    // Play body slam material sound/effect
    // FUN_00805a10 is likely a function like playMaterialEffect
    // Parameters: material name, entity ID at this+0x94, position at this+0x74, channel -1
    FUN_00805a10("body_slam_material", *(int*)((char*)thisPtr + 0x94), (char*)thisPtr + 0x74, -1);

    // Check if the target's vertical velocity (or some scalar) is <= 0
    // Virtual function at vtable+0xc0 on pEntity (e.g., getVerticalSpeed)
    float verticalSpeed = (**(float (__thiscall**)(void*))(*(int*)pEntity + 0xc0))(pEntity);
    if (verticalSpeed <= 0.0f)
    {
        int slamState = *(int*)((char*)thisPtr + 0x90); // +0x90: body slam state (0=idle, 1=active, 2=finish)
        if (slamState == 0)
        {
            // Set flag 0x20 at target+0x2140 (e.g., disable movement)
            *(uint*)((char*)pTarget + 0x2140) |= 0x20;
        }
        else if (slamState == 1 || slamState == 2)
        {
            // Set flag 0x40 at target+0x2140 (e.g., enable knockdown)
            *(uint*)((char*)pTarget + 0x2140) |= 0x40;
        }
    }
}