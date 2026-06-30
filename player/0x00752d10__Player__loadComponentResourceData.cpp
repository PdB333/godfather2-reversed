// FUNC_NAME: Player::loadComponentResourceData
// Address: 0x00752d10
// Called during initialization to load a 20-byte resource block into a sub-object at this+0x50 (PlayerData).
// Offsets: PlayerData+0x828, +0x830, +0x838 receive data from resource identified by value at PlayerData+0x8a4.

void __fastcall Player::loadComponentResourceData(int this) // __fastcall implies this in ecx
{
    // Pointer to the large data structure at this+0x50
    PlayerData* pData = *(PlayerData**)(this + 0x50);
    
    // Resource identifier/offset stored at pData+0x8a4
    int resourceId = (int)pData + 0x8a4; // iVar6, used as parameter
    
    // Constants likely representing resource type/size
    const uint32_t resourceType1 = 0x40b3e;  // e.g., hash or type ID
    const uint32_t resourceType2 = 0x20001;  // e.g., sub-type or size
    
    // First call: obtain a handle or intermediate token
    uint32_t resourceHandle = FUN_0043b490(resourceType1, resourceType2, resourceId, 0);
    
    // Second call: load the actual resource data (20 bytes)
    // Parameters: 4 (size?), resourceHandle, resourceType1, resourceType2, resourceId, 0
    ResourceData* pResource = (ResourceData*)FUN_00540bf0(4, resourceHandle, resourceType1, resourceType2, resourceId, 0);
    
    // Copy the three fields from the resource into pData
    pData->field_0x828 = pResource->data0;  // undefined8, 8 bytes
    pData->field_0x830 = pResource->data1;  // undefined8, 8 bytes
    pData->field_0x838 = pResource->data2;  // undefined4, 4 bytes
}

// Assumed structures (not defined in original code):
struct ResourceData {
    uint64_t data0;     // offset 0x00 (8 bytes)
    uint64_t data1;     // offset 0x08 (8 bytes)
    uint32_t data2;     // offset 0x10 (4 bytes)
};

// The PlayerData structure is large; only relevant offsets shown:
struct PlayerData {
    // ... many fields ...
    /* +0x828 */ uint64_t field_0x828;  // receives data0
    /* +0x830 */ uint64_t field_0x830;  // receives data1
    /* +0x838 */ uint32_t field_0x838;  // receives data2
    // ... more fields ...
};