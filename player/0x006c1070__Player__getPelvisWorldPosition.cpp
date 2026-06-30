// FUNC_NAME: Player::getPelvisWorldPosition
// Address: 0x006c1070
// This function retrieves the world position of the pelvis bone, computes its height above a reference point, and returns a pointer to the player's position vector at offset 0x30 from the player object.
// The virtual calls at +0x94 and +0xa4 are likely bone access methods (e.g., getBoneWorldPosition and getBoneIndex).
// The global constants _DAT_00d5ef5c, _DAT_00d5ef58, _DAT_00d5780c are thresholds for height checks (e.g., water/ground level).

int Player::getPelvisWorldPosition(int* this)
{
    // Output bone position (likely a float3)
    float pelvisPos[3]; // local_1c was originally an int, but used as float vector
    // Bone name string
    const char* boneName = "m_pelvis";
    // Temporary buffer for bone name lookup (not used here)
    char boneNameBuffer[20]; // auStack_14
    char* boneNamePtr; // pcStack_24

    // Call vtable[0x94] -> getBoneWorldPosition(boneName, &pelvisPos)
    // In original code, this might be a method that takes a bone name and writes to a vector.
    // The CONCAT44 was likely a compiler artifact; we pass the bone name directly.
    (*(void (__thiscall**)(int*, int, float*))(*this + 0x94))(this, (int)boneName, pelvisPos);

    // Call vtable[0xa4] -> getBoneNameToIndex? This fills boneNameBuffer and returns pointer to name.
    (*(void (__thiscall**)(int*, char*, char**))(*this + 0xa4))(this, boneNameBuffer, &boneNamePtr);

    // Obtain the player object from a global function
    int* playerObj = (int*)FUN_00471610(); // Returns pointer to player object

    // Read a 64-bit value from playerObj + 0x30, then extract the high 32 bits as a float? This is likely a reference height (e.g., ground level).
    // The decompiler shows a shift, but the original probably reads a float directly.
    float referenceHeight = *(float*)((int)playerObj + 0x30); // Or maybe *(double*)(playerObj + 0x30) but we take high part.

    // Compute height difference relative to ground offset
    float heightAboveGround = (pelvisPos[1] - referenceHeight - _DAT_00d5ef5c) * _DAT_00d5ef58;

    // Check if height is within a valid range (e.g., for swimming or falling state)
    if (0.0f < heightAboveGround && heightAboveGround < _DAT_00d5780c)
    {
        // Height is within range; return pointer to player position (or maybe pelvis position)
        return (int)(playerObj + 0x30);
    }
    // Default return (same as above, possibly for debugging)
    return (int)(playerObj + 0x30);
}