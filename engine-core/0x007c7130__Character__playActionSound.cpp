// FUNC_NAME: Character::playActionSound
// Address: 0x007c7130
// Role: Plays a contextual sound effect based on the character's action state and whether the local player exists and has a specific flag set.

void __thiscall Character::playActionSound(int param_2)
{
    int iVar1;
    int iVar2;
    
    // Get the local player character (global function)
    Character* localPlayer = getLocalPlayer(); // FUN_007ab1e0()
    
    // Check if local player exists and if a specific flag (bit 10) is set at offset 0x8E0 in some structure
    // The structure is pointed to by this->somePointer (offset 0x58 = this[0x16])
    if ((localPlayer == nullptr) || ((*(uint*)(this->somePointer + 0x8E0) >> 10 & 1) == 0)) {
        // Branch when local player is null or flag not set
        iVar2 = this->actionState; // offset 0x118 = this[0x46]
        // Select sound ID based on actionState
        // If actionState == 2: soundID = 0xA7456DC9
        // Else: soundID = 0x42B120B1 + 0xA7456DC9 = 0xE9F68E7A
        iVar1 = (-(uint)(iVar2 != 2) & 0x42B120B1) + 0xA7456DC9;
    } else {
        // Branch when local player exists and flag is set
        iVar2 = this->actionState; // offset 0x118
        if (*(char*)(localPlayer + 0x1AA) == '\x02') {
            // If local player's byte at offset 0x1AA equals 2, use different sound IDs
            // If actionState == 2: soundID = 0xD41AC450
            // Else: soundID = 0x74E31563 + 0xD41AC450 = 0x48FDD9B3
            iVar1 = (-(uint)(iVar2 != 2) & 0x74E31563) + 0xD41AC450;
            goto LAB_007c7186;
        }
        // If local player's byte is not 2, fall through to the same logic as the first branch
        iVar1 = (-(uint)(iVar2 != 2) & 0x42B120B1) + 0xA7456DC9;
    }
LAB_007c7186:
    // Call virtual method at vtable offset 0x2C (likely playSound)
    // Parameters: soundID, loop=1, param_2, unknown=1, volume=1.0f, pitch=1.0f
    (this->vtable[0x2C])(iVar1, 1, param_2, 1, 1.0f, 1.0f);
    return;
}