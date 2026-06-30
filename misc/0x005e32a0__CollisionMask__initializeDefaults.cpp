// FUNC_NAME: CollisionMask::initializeDefaults
void __fastcall CollisionMask::initializeDefaults(byte* this) {
    *this = 0;                              // +0x00: reserved byte
    *(int*)(this + 0x04) = 0x3200000;      // +0x04: layerMaskTerrain (combination)
    *(int*)(this + 0x08) = 0x800000;       // +0x08: layerMaskBuildings
    *(int*)(this + 0x0C) = 0x2000000;      // +0x0C: layerMaskVehicles
    *(int*)(this + 0x10) = 0xC0000;        // +0x10: layerMaskNPCs
    *(int*)(this + 0x14) = 0x180000;       // +0x14: layerMaskPlayer
    *(int*)(this + 0x18) = 0;              // +0x18: reserved mask (unused)
    *(int*)(this + 0x1C) = 0;              // +0x1C: reserved
    *(int*)(this + 0x20) = 0;              // +0x20: reserved
    *(int*)(this + 0x24) = 0;              // +0x24: reserved
    *(int*)(this + 0x28) = 1;              // +0x28: isInitialized flag
}