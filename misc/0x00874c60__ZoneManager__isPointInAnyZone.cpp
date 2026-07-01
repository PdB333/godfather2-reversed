// FUNC_NAME: ZoneManager::isPointInAnyZone

// Helper function at 0x0084ca90: computes squared distance from a 2D point to (x,y) with a flag.
// likely returns distSq = (centerX - x)^2 + (centerY - y)^2  (ignores z when flag is 0)
float __fastcall computeSquaredDistance2D(void* center, float x, float y, int unkFlag, float z);

struct ZoneEntry {
    char pad_0x00[0x10];
    float centerX;             // +0x10
    float centerY;             // +0x14
    float radius;              // +0x18
};

class ZoneManager {
public:
    char pad_0x00[0xCB4];      // unknown data before zone array
    ZoneEntry* zoneEntries[3]; // +0xCB4 each pointer 4 bytes
    // offsets: +0xCB4, +0xCB8, +0xCBC

    // Returns true if the point (x, y, z) is within any of the three circular zones.
    bool __thiscall isPointInAnyZone(float x, float y, float z);
};

bool __thiscall ZoneManager::isPointInAnyZone(float x, float y, float z) {
    for (int i = 0; i < 3; i++) {
        ZoneEntry* zone = this->zoneEntries[i];
        if (zone != nullptr) {
            float distSq = computeSquaredDistance2D(&zone->centerX, x, y, 0, z);
            if (distSq <= zone->radius * zone->radius) {
                return true;
            }
        }
    }
    return false;
}