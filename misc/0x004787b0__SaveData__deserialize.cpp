// FUNC_NAME: SaveData::deserialize
// Address: 0x004787b0
// Role: Deserialize a save data buffer into the object's fields. Supports two formats: pointer-linked list or compact bit-packed array.

#include <cstdint>

void __thiscall SaveData::deserialize(void* thisPtr, const void* dataBuffer)
{
    bool bModifiedPrimary = false;
    bool bModifiedBackup = false;

    // Initialize a data reader with a magic constant (likely format version or size hint)
    FUN_0043aff0(dataBuffer, 0xCC92646);

    // Determine format: cFormatMode == 0 means pointer-iterating format, else bitfield format
    // local_64 is uninitialized in decompiled code; this might be a member variable or parameter,
    // but we expose it as a flag for readability.
    char formatMode = this->formatMode; // hypothetical member at offset ?
    // The decompiler shows local_64 (char) used in loop. We'll assume it's stored in the object or passed inline.
    // For now, we treat it as a local variable that would be set before this function is called.
    // Since we don't have it, we keep the logic as is but provide a placeholder.
    // Actually, let's keep the local variable from decompiled code but rename it.
    // We'll assume it's a local variable that may come from a union or template parameter.
    // For safety, we replicate the original logic exactly.
    char cFormatMode = *(char*)((uintptr_t)&formatMode); // dummy to match original variable usage

    // Initial iterator values
    uint32_t* pIterPtr = local_8; // linked list pointer
    uint32_t* pBitfieldPtr = local_5c; // bitfield data pointer
    uint32_t bitfieldPos = 0; // local_58
    uint32_t bitfieldEnd = 0; // local_54
    uint32_t bitfieldBitmask = 0; // local_60

    // Local stack buffer for temporary allocation size
    uint32_t allocSize[3] = {0,0,0};

    do {
        bool bContinue;
        if (cFormatMode == '\0') {
            bContinue = (*pIterPtr == 0);
        } else {
            bContinue = (bitfieldPos == bitfieldEnd);
        }
        if (bContinue) {
            // Finished reading data, now sync backup copies if not yet modified
            if (!bModifiedPrimary) {
                // Copy primary range (0x6c..?) to backup at +0xc0
                uint32_t* src = (uint32_t*)((uint8_t*)this + 0x6C);
                uint32_t* dst = (uint32_t*)((uint8_t*)this + 0xC0);
                for (int i = 0; i < 21; i++) {
                    *dst++ = *src++;
                }
            }
            if (!bModifiedBackup) {
                // Copy primary range to second backup at +0x114
                uint32_t* src = (uint32_t*)((uint8_t*)this + 0x6C);
                uint32_t* dst = (uint32_t*)((uint8_t*)this + 0x114);
                for (int i = 0; i < 21; i++) {
                    *dst++ = *src++;
                }
            }
            // If allocation pointer is null, allocate memory based on size at +0x54
            if (*(uint32_t*)((uint8_t*)this + 0x5C) == 0) {
                void* allocator = FUN_009c89b0(); // get allocator singleton
                // Allocate: size = *(uint32_t*)(this+0x54) * 4
                uint32_t size = *(uint32_t*)((uint8_t*)this + 0x54) * 4;
                uint32_t* result = (uint32_t*)((*(code**)allocator)[0])(
                    (uint32_t)allocator,
                    size,
                    allocSize
                );
                *(uint32_t*)((uint8_t*)this + 0x5C) = (uint32_t)result;
            }
            return;
        }
        // Extract the current tag and value
        uint32_t* tagPtr;
        if (cFormatMode == '\0') {
            tagPtr = pIterPtr;
        } else {
            tagPtr = &bitfieldTag; // local_50 used as tag storage
        }
        // Determine tag value: if the short at offset +6 equals 0x25E3, then tag is the unsigned short at +4; else tag is the pointer value at +4
        uint32_t tag;
        if (*(uint16_t*)((uint8_t*)tagPtr + 6) == 0x25E3) {
            // inline short tag
            tag = (uint32_t)*(uint16_t*)((uint8_t*)tagPtr + 4);
        } else {
            tag = (uint32_t)*(uint32_t*)((uint8_t*)tagPtr + 4);
        }

        // Switch on tag, store values at appropriate offsets
        switch (tag) {
        case 0: // TAG_SET_SIZE
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x54) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x54) = (uint32_t)bitfieldValue; // local_50[2]
            }
            break;
        case 1: // TAG_SET_OFFSET_0x60
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x60) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x60) = (uint32_t)bitfieldValue;
            }
            break;
        case 2: // TAG_SET_OFFSET_0x68
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x68) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x68) = (uint32_t)bitfieldValue;
            }
            break;
        case 3: // TAG_SET_OFFSET_0x64 (100 decimal?)
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 100) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 100) = (uint32_t)bitfieldValue;
            }
            break;
        case 4:
        case 0x15:
        case 0x22: {
            // Determine array index: 0 for tag 4, 2 for tag 0x15, 1 for tag 0x22
            int arrayIndex;
            if (tag == 4) arrayIndex = 0;
            else if (tag == 0x15) arrayIndex = 2;
            else arrayIndex = 1;
            // Value at slot
            uint32_t value;
            if (cFormatMode == '\0') {
                value = (uint32_t)tagPtr[2];
            } else {
                value = (uint32_t)bitfieldValue;
            }
            // Set enum field at offset +0x6C + arrayIndex*0x54
            // Values 0-3 map to 0,1,2,3
            uint32_t* field = (uint32_t*)((uint8_t*)this + 0x6C + arrayIndex * 0x54);
            switch (value) {
            case 0: *field = 0; break;
            case 1: *field = 1; break;
            case 2: *field = 2; break;
            case 3: *field = 3; break;
            }
            break;
        }
        case 5: // TAG_INIT_0x70_0xB4
            if (cFormatMode == '\0') {
                uint32_t val = (uint32_t)tagPtr[2];
                *(uint32_t*)((uint8_t*)this + 0x70) = val;
                *(uint32_t*)((uint8_t*)this + 0xB4) = val;
            } else {
                uint32_t val = (uint32_t)bitfieldValue;
                *(uint32_t*)((uint8_t*)this + 0x70) = val;
                *(uint32_t*)((uint8_t*)this + 0xB4) = val;
            }
            break;
        case 6: // TAG_INIT_0x80_0xB8
            if (cFormatMode == '\0') {
                uint32_t val = (uint32_t)tagPtr[2];
                *(uint32_t*)((uint8_t*)this + 0x80) = val;
                *(uint32_t*)((uint8_t*)this + 0xB8) = val;
            } else {
                uint32_t val = (uint32_t)bitfieldValue;
                *(uint32_t*)((uint8_t*)this + 0x80) = val;
                *(uint32_t*)((uint8_t*)this + 0xB8) = val;
            }
            break;
        case 7: // TAG_INIT_0x90_0xBC
            if (cFormatMode == '\0') {
                uint32_t val = (uint32_t)tagPtr[2];
                *(uint32_t*)((uint8_t*)this + 0x90) = val;
                *(uint32_t*)((uint8_t*)this + 0xBC) = val;
            } else {
                uint32_t val = (uint32_t)bitfieldValue;
                *(uint32_t*)((uint8_t*)this + 0x90) = val;
                *(uint32_t*)((uint8_t*)this + 0xBC) = val;
            }
            break;
        case 8: // TAG_INIT_0xA0_0xB0
            if (cFormatMode == '\0') {
                uint32_t val = (uint32_t)tagPtr[2];
                *(uint32_t*)((uint8_t*)this + 0xA0) = val;
                *(uint32_t*)((uint8_t*)this + 0xB0) = val;
            } else {
                uint32_t val = (uint32_t)bitfieldValue;
                *(uint32_t*)((uint8_t*)this + 0xA0) = val;
                *(uint32_t*)((uint8_t*)this + 0xB0) = val;
            }
            break;
        case 9: // TAG_SINGLE_0x74
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x74) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x74) = (uint32_t)bitfieldValue;
            }
            break;
        case 0xA: // TAG_SINGLE_0x84
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x84) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x84) = (uint32_t)bitfieldValue;
            }
            break;
        case 0xB: // TAG_SINGLE_0x94
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x94) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x94) = (uint32_t)bitfieldValue;
            }
            break;
        case 0xC: // TAG_SINGLE_0xA4
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xA4) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xA4) = (uint32_t)bitfieldValue;
            }
            break;
        case 0xD: // TAG_SINGLE_0x78
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x78) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x78) = (uint32_t)bitfieldValue;
            }
            break;
        case 0xE: // TAG_SINGLE_0x88
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x88) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x88) = (uint32_t)bitfieldValue;
            }
            break;
        case 0xF: // TAG_SINGLE_0x98
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x98) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x98) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x10: // TAG_SINGLE_0xA8
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xA8) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xA8) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x11: // TAG_SINGLE_0x7C
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x7C) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x7C) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x12: // TAG_SINGLE_0x8C
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x8C) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x8C) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x13: // TAG_SINGLE_0x9C
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x9C) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x9C) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x14: // TAG_SINGLE_0xAC
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xAC) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xAC) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x16: // TAG_BACKUP_INIT_0x118 (part of backup section)
            bModifiedBackup = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x118) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x118) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x17: // TAG_BACKUP_0x128
            bModifiedBackup = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x128) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x128) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x18: // TAG_BACKUP_0x11C
            bModifiedBackup = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x11C) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x11C) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x19: // TAG_BACKUP_0x12C (300 decimal = 0x12C)
            bModifiedBackup = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x12C) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x12C) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x1A: // TAG_BACKUP_0x120
            bModifiedBackup = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x120) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x120) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x1B: // TAG_BACKUP_0x130
            bModifiedBackup = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x130) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x130) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x1C: // TAG_BACKUP_0x124
            bModifiedBackup = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x124) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x124) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x1D: // TAG_BACKUP_0x134
            bModifiedBackup = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x134) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x134) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x1E: // TAG_BACKUP_INIT_0x148_0x158
            bModifiedBackup = true;
            if (cFormatMode == '\0') {
                uint32_t val = (uint32_t)tagPtr[2];
                *(uint32_t*)((uint8_t*)this + 0x148) = val;
                *(uint32_t*)((uint8_t*)this + 0x158) = val;
            } else {
                uint32_t val = (uint32_t)bitfieldValue;
                *(uint32_t*)((uint8_t*)this + 0x148) = val;
                *(uint32_t*)((uint8_t*)this + 0x158) = val;
            }
            break;
        case 0x1F: // TAG_BACKUP_0x14C
            bModifiedBackup = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x14C) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x14C) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x20: // TAG_BACKUP_0x150
            bModifiedBackup = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x150) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x150) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x21: // TAG_BACKUP_0x154
            bModifiedBackup = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x154) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x154) = (uint32_t)bitfieldValue;
            }
            break;
        case 0x23: // TAG_UPDATE_0xC4_COPY_0xF4
            bModifiedPrimary = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xC4) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xC4) = (uint32_t)bitfieldValue;
            }
            // Copy +0xF4 to +0x104
            *(uint32_t*)((uint8_t*)this + 0x104) = *(uint32_t*)((uint8_t*)this + 0xF4);
            goto LAB_00478d23;
        case 0x24: // TAG_SINGLE_0xD4
            bModifiedPrimary = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xD4) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xD4) = (uint32_t)bitfieldValue;
            }
            goto LAB_00478d23;
        case 0x25: // TAG_SINGLE_0xC8 (200 decimal)
            bModifiedPrimary = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xC8) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xC8) = (uint32_t)bitfieldValue;
            }
            goto LAB_00478d23;
        case 0x26: // TAG_SINGLE_0xD8
            bModifiedPrimary = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xD8) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xD8) = (uint32_t)bitfieldValue;
            }
            goto LAB_00478d23;
        case 0x27: // TAG_SINGLE_0xCC
            bModifiedPrimary = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xCC) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xCC) = (uint32_t)bitfieldValue;
            }
            goto LAB_00478d23;
        case 0x28: // TAG_SINGLE_0xDC
            bModifiedPrimary = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xDC) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xDC) = (uint32_t)bitfieldValue;
            }
            goto LAB_00478d23;
        case 0x29: // TAG_SINGLE_0xD0
            bModifiedPrimary = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xD0) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xD0) = (uint32_t)bitfieldValue;
            }
            goto LAB_00478d23;
        case 0x2A: // TAG_SINGLE_0xE0
            bModifiedPrimary = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xE0) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xE0) = (uint32_t)bitfieldValue;
            }
            goto LAB_00478d23;
        case 0x2B: // TAG_SINGLE_0xF4
            bModifiedPrimary = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xF4) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xF4) = (uint32_t)bitfieldValue;
            }
            goto LAB_00478d23;
        case 0x2C: // TAG_SINGLE_0xF8
            bModifiedPrimary = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xF8) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xF8) = (uint32_t)bitfieldValue;
            }
            goto LAB_00478d23;
        case 0x2D: // TAG_SINGLE_0xFC
            bModifiedPrimary = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0xFC) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0xFC) = (uint32_t)bitfieldValue;
            }
            goto LAB_00478d23;
        case 0x2E: // TAG_SINGLE_0x100
            bModifiedPrimary = true;
            if (cFormatMode == '\0') {
                *(uint32_t*)((uint8_t*)this + 0x100) = (uint32_t)tagPtr[2];
            } else {
                *(uint32_t*)((uint8_t*)this + 0x100) = (uint32_t)bitfieldValue;
            }
LAB_00478d23:
            bModifiedPrimary = true;
            break;
        } // end switch

        // Advance iterator
        if (cFormatMode == '\0') {
            // Pointer-iterating format: each entry has a size field at offset 0 of the entry.
            int32_t entrySize = *(int32_t*)pIterPtr;
            if ((int32_t)bitfieldPos < 0) {
                // Special case: treat as relative pointer?
                pIterPtr = (uint32_t*)((uint8_t*)pIterPtr + entrySize);
                FUN_0043b140(); // likely a debug hook
                continue;
            }
            else if ((int32_t)bitfieldPos < (int32_t)(bitfieldEnd - 1)) {
                bitfieldPos++;
                pIterPtr = (uint32_t*)((uint8_t*)pIterPtr + entrySize);
            }
            else {
                // Reached end, set to sentinel
                pIterPtr = (uint32_t*)0x01163cf8; // global end marker
            }
        } else {
            // Bitfield format: advance bit position
            bitfieldPos++;
            if (bitfieldPos != bitfieldEnd) {
                uint16_t bitIndex = (uint16_t)bitfieldPos;
                // Check if this bit is set in the "present" bitmask
                uint8_t bitByte = *((uint8_t*)bitfieldBitmask + (bitfieldPos >> 3));
                uint8_t bit = (1 << (bitfieldPos & 7));
                if ((bitByte & bit) == 0) {
                    // Bit not set: read next value from the value array (local_5c)
                    bitfieldTag = *pBitfieldPtr;
                    pBitfieldPtr++;
                }
                else {
                    // Bit set: tag is null (skip)
                    bitfieldTag = 0;
                }
            }
        }
    } while (true);
}