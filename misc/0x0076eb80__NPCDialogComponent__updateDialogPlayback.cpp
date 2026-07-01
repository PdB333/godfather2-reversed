// FUNC_NAME: NPCDialogComponent::updateDialogPlayback
// Address: 0x0076eb80
// Role: Checks character state and plays appropriate dialog/sound line, then clears playback flags.

class NPCDialogComponent {
public:
    // +0x00: vtable pointer
    // +0x15: byte flags (bit5=0x20 = some condition, bit6=0x40 = alternate sound selection)
    // +0x50: pointer to character data block (Character*)
    // +0x64: speech type ID (0 = none, 0x48 = special value?)

    // vtable offsets
    // +0x2c: void playSound(uint hash, int arg1, int arg2, int arg3, float volume, float pitch)

    void updateDialogPlayback() {
        char flags = *(char*)(this + 0x15);
        if ((flags & 0x20) != 0) {
            // Condition prevents playback, just clear flags
            goto clear_flags;
        }

        int* pSimMgrData = *(int**)DAT_012233a0; // global SimManager
        int iVar3;
        if (pSimMgrData == 0) {
            iVar3 = 0;
        } else {
            iVar3 = *pSimMgrData - 0x1f30; // offset to get player component ID
        }

        int speechType = *(int*)(this + 0x64); // param_1[0x19]
        if (speechType != 0 && speechType != 0x48) {
            // Compare speechType to the expected player type
            if (speechType == iVar3) {
                // Access character data
                char* charData = *(char**)(this + 0x50); // param_1[0x14]
                char sentenceIndex = *(char*)(charData + 0x1ec5); // current sentence index
                uint charFlags = *(uint*)(charData + 0x8ec); // character flags

                if (sentenceIndex != -1 && (charFlags >> 6 & 1) != 0) {
                    // Voice is available
                    if ((*(char*)(this + 0x15) & 0x40) == 0) {
                        // Standard case: play from global sentence table
                        int* table = (int*)&DAT_00d663bc;
                        int index = sentenceIndex * 0x19 + *(int*)(charData + 0x1ecc);
                        uint soundHash = table[index]; // each entry 4 bytes
                        (*(void(__thiscall**)(NPCDialogComponent*, uint, int, int, int, float, float))(*this + 0x2c))
                            (this, soundHash, 1, 1, 0, 1.0f, 1.0f);
                    } else {
                        // Alternate: play specific sound based on sentenceIndex value
                        if (sentenceIndex == 0) {
                            (*(void(__thiscall**)(NPCDialogComponent*, uint, int, int, int, float, float))(*this + 0x2c))
                                (this, 0xa50b191e, 1, 1, 0, 1.0f, 1.0f); // hash for "idle" sound?
                        } else {
                            (*(void(__thiscall**)(NPCDialogComponent*, uint, int, int, int, float, float))(*this + 0x2c))
                                (this, 0xd27b939, 1, 1, 0, 1.0f, 1.0f); // hash for "combat" sound?
                        }
                    }
                }
            }
        }
clear_flags:
        // Clear bits 5 and 6 (0x60) in flags
        *(char*)(this + 0x15) = *(char*)(this + 0x15) & 0x9f;
        return;
    }
};