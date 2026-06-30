// FUNC_NAME: Entity::computeSquaredDistanceToPlayer
// Address: 0x00769620
// Role: Computes squared distance from this entity to the player's position.
//        Checks a flag and entity type to decide whether to use a collision/raycast method
//        (possibly for vehicles) or direct Euclidean distance.
float __fastcall Entity::computeSquaredDistanceToPlayer(void* this) // this in ECX
{
    char cVar1;
    int iVar2;
    int iVar3;
    float* pfVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float* pfVar8;
    undefined1* puVar9;
    float* pfVar10;
    float result; // local_10
    undefined1 local_c[12]; // 12 bytes = likely a 3D vector (float x,y,z)

    result = 0.0f;

    // Get the player's entity pointer (returns something like a player vehicle or character)
    iVar2 = getLocalPlayerEntity(); // FUN_00471610
    pfVar4 = (float*)(iVar2 + 0x30); // pointer to player's position vector X

    // Check if this entity has the "player contact" flag (bit 4 of flags at +0x7c)
    // and that its type at +0x74 is neither 0 nor 0x48 (0x48 likely means "in car"?)
    if ((((*(uint*)(this + 0x7c) >> 4 & 1) != 0) &&
         (*(int*)(this + 0x74) != 0) &&
         (*(int*)(this + 0x74) != 0x48)) &&
        // Some global state check (returns nonzero if a collision test is needed)
        (iVar3 = performCollisionCheck(), iVar3 != 0)) // FUN_007ff880 with no args
    {
        pfVar10 = &result;
        puVar9 = local_c; // temporary vector
        pfVar8 = pfVar4;  // player's position
        // Perform a vector transform or projection (e.g., from world to local space?)
        performCollisionCheck(pfVar4, puVar9, pfVar10); // FUN_007ff880 overload
        cVar1 = checkCollisionResult(pfVar8, puVar9, pfVar10); // FUN_00874e60
        if (cVar1 != '\0')
        {
            goto LAB_007696cf; // return 0.0
        }
    }

    // Get player's position again (may have changed, or a different reference?)
    iVar3 = getLocalPlayerEntity(); // FUN_00471610
    // Compute squared distance between this call's player position and the previous one
    // (note: uses pfVar4 from first call, which is the same as iVar2+0x30)
    fVar5 = *pfVar4 - *(float*)(iVar3 + 0x30); // delta X
    fVar6 = *(float*)(iVar2 + 0x34) - *(float*)(iVar3 + 0x34); // delta Y
    fVar7 = *(float*)(iVar2 + 0x38) - *(float*)(iVar3 + 0x38); // delta Z
    result = fVar5 * fVar5 + fVar6 * fVar6 + fVar7 * fVar7; // squared distance

LAB_007696cf:
    return (float)result;
}