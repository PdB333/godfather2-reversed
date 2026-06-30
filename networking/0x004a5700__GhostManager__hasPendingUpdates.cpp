// FUNC_NAME: GhostManager::hasPendingUpdates
// Function at 0x004a5700 - Checks if any ghost or connection state has pending updates (dirty flag or virtual isDirty).
// The class manages multiple ghost structures: 8-byte entries, 16-byte entries, and direct ghost pointers.
// Offsets: +0x78 = count of 8-byte entries; +0x74 = array pointer; +0x6c = count of 16-byte entries; +0x68 = array pointer; +0x60 = count of ghost pointers; +0x5c = array of ghost pointers
// Bit 0x10 in the first two arrays indicates "dirty" (needs update).

class Ghost;
class GhostInfoBase;

class GhostManager {
public:
    bool hasPendingUpdates();
};

// Assume Ghost has a virtual bool isDirty() at vtable offset 8 (index 2)
class Ghost {
public:
    virtual bool isDirty() = 0;
};

bool GhostManager::hasPendingUpdates()
{
    // Check 8-byte entries (e.g., GhostInfo8)
    uint32_t count8 = *(uint32_t*)((uint8_t*)this + 0x78);
    if (count8 != 0) {
        uint8_t* base8 = *(uint8_t**)((uint8_t*)this + 0x74);
        uint8_t* data8 = base8 + 4; // Flag byte at offset 4
        for (uint32_t i = 0; i < count8; i++) {
            if ((*data8 & 0x10) != 0) {
                return true;
            }
            data8 += 8; // Step to next 8-byte entry
        }
    }

    // Check 16-byte entries (e.g., GhostInfo16)
    uint32_t count16 = *(uint32_t*)((uint8_t*)this + 0x6c);
    if (count16 != 0) {
        uint8_t* base16 = *(uint8_t**)((uint8_t*)this + 0x68);
        uint8_t* data16 = base16 + 4; // Flag byte at offset 4
        for (uint32_t i = 0; i < count16; i++) {
            if ((*data16 & 0x10) != 0) {
                return true;
            }
            data16 += 16; // Step to next 16-byte entry
        }
    }

    // Check ghost pointers (each has a virtual isDirty())
    uint32_t ghostCount = *(uint32_t*)((uint8_t*)this + 0x60);
    if (ghostCount != 0) {
        Ghost** ghostArray = *(Ghost***)((uint8_t*)this + 0x5c);
        for (uint32_t i = 0; i < ghostCount; i++) {
            Ghost* ghost = ghostArray[i];
            if (ghost->isDirty()) {
                return true;
            }
        }
    }

    return false;
}