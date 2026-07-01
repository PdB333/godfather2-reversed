// Xbox PDB: EARS_Modules_Sentient_InitializeBones
// FUNC_NAME: CharacterBoneCache::initializeBones
// Function address: 0x007f4810
// Role: Initializes bone index members for a character skeleton by resolving bone names via vtable method at +0x94.
// Bones are stored as offsets from this pointer (each offset is an int index).
// If both "r_ankle" and "l_ankle" are found, sets a flag to enable ankle IK or similar.

typedef bool (__thiscall* BoneNameResolver)(void* this, const char* boneName);  // returns non-zero if bone found

void __thiscall CharacterBoneCache::initializeBones(char* thisPtr)  // thisPtr is the object base
{
    BoneNameResolver resolver = *(BoneNameResolver*)(*(void**)thisPtr + 0x94);  // vtable method

    // Ankles: only set flag if both exist
    if (resolver(thisPtr + 0x6D8, "r_ankle"))  // offset 0x1b6 * 4 = 0x6D8? actually int index 0x1b6 => byte offset 0x6D8
    {
        if (resolver(thisPtr + 0x6D4, "l_ankle"))  // offset 0x1b5 => 0x6D4
        {
            // Set flag bit 0x100000 at offset 0x1B94 (int index 0x6e5)
            *(int*)(thisPtr + 0x1B94) |= 0x100000;
        }
    }

    // Core skeleton bones (unconditional)
    resolver(thisPtr + 0x6DC, "m_neck1");     // +0x1b7
    resolver(thisPtr + 0x6E0, "m_head");      // +0x1b8 (DAT_00d5f5f0 likely "m_head" or similar)
    resolver(thisPtr + 0x6E4, "m_pelvis");    // +0x1b9
    resolver(thisPtr + 0x6E8, "m_lumbar");    // +0x1ba
    resolver(thisPtr + 0x6EC, "m_thoracic");  // +0x1bb
    resolver(thisPtr + 0x6F0, "m_grabber");    // +0x1bc
    resolver(thisPtr + 0x6F8, "BP_grabPoint_F"); // +0x1be
    resolver(thisPtr + 0x6F4, "BP_grabPoint_K"); // +0x1bd
    resolver(thisPtr + 0x6FC, "l_shoulder");   // +0x1bf
    resolver(thisPtr + 0x700, "r_shoulder");   // +0x1c0
    resolver(thisPtr + 0x704, "l_knee");       // +0x1c1
    resolver(thisPtr + 0x708, "r_knee");       // +0x1c2
    resolver(thisPtr + 0x70C, "l_weapon");     // +0x1c3
    resolver(thisPtr + 0x710, "r_weapon");     // +0x1c4
    resolver(thisPtr + 0x718, "eye_R");        // +0x1c6
    resolver(thisPtr + 0x714, "eye_L");        // +0x1c5
}