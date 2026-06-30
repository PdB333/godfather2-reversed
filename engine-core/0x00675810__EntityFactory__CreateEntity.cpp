// FUNC_NAME: EntityFactory::CreateEntity
int* __cdecl EntityFactory::CreateEntity(short entityType, unsigned int entityId, void* parentData, 
                                          void* extraParam1, void* extraParam2, int* outErrorCode)
{
    int* newEntity;
    int* pResource;
    int result;
    unsigned int index;

    if (outErrorCode == nullptr) {
        return nullptr;
    }
    *outErrorCode = 0;
    
    // Allocate memory for new entity
    newEntity = (int*)allocateEntityMemory();
    if (newEntity == nullptr) {
        return nullptr;
    }
    
    // Store parameters into entity fields
    newEntity[0x2a] = (int)parentData;         // +0xA8: parent pointer
    newEntity[0x2b] = (int)extraParam1;        // +0xAC: extra param 1
    newEntity[0x2d] = (int)contextPtr;         // +0xB4: caller-provided context (in EAX)
    newEntity[0x2c] = 0;                       // +0xB0: init to 0
    newEntity[1] = 0;                          // +0x04: vtable placeholder
    newEntity[2] = 0;                          // +0x08: vtable placeholder
    newEntity[3] = 0;                          // +0x0C: field
    newEntity[4] = 0;                          // +0x10: field
    newEntity[5] = 0;                          // +0x14: field
    newEntity[6] = 0;                          // +0x18: field
    newEntity[0x30] = 1;                       // +0xC0: initial reference count or status
    *newEntity = 0;                            // +0x00: vtable or type ID
    
    // Initialize other fields to zero
    newEntity[10] = 0;   // +0x28
    newEntity[0xe] = 0;  // +0x38
    newEntity[0xf] = 0;  // +0x3C
    newEntity[0x10] = 0; // +0x40
    newEntity[0x11] = 0; // +0x44
    newEntity[0xb] = 0;  // +0x2C
    newEntity[0xc] = 0;  // +0x30
    newEntity[0x12] = 0; // +0x48
    newEntity[0x13] = 0; // +0x4C
    newEntity[0xd] = 0;  // +0x34
    newEntity[0x2e] = 0; // +0xB8
    *(short*)(newEntity + 7) = 0; // +0x1C (low word)
    
    // Call base initialization
    initializeEntityBase();
    
    // Initialize more fields to -1 or 0
    newEntity[0x1c] = -1; // +0x70
    newEntity[0x1d] = -1; // +0x74
    newEntity[0x1e] = 0;  // +0x78
    newEntity[8] = 0;     // +0x20
    newEntity[9] = 0;     // +0x24
    newEntity[0x25] = 0;  // +0x94
    newEntity[0x26] = 0;  // +0x98
    newEntity[0x27] = 0;  // +0x9C
    newEntity[0x14] = 0;  // +0x50
    newEntity[0x15] = 0;  // +0x54
    newEntity[0x16] = 0;  // +0x58
    newEntity[0x17] = 0;  // +0x5C
    
    // Check for invalid entity types
    if ((entityType == 7) || (entityType == 2) || (entityType == 5)) {
        *outErrorCode = 0x2729;  // ERROR_INVALID_TYPE
        return nullptr;
    }
    
    // Entity type 3: special initialization (e.g., derived entity)
    if (entityType == 3) {
        // Retrieve resource by parent ID
        pResource = (int*)getResourceById(newEntity[0x2a], entityId);
        newEntity[8] = (int)pResource;                // +0x20: resource pointer
        newEntity[0x13] = pResource[0x128 / 4];       // +0x4C: copy field from resource
        newEntity[0x10] = pResource[0x100 / 4];       // +0x40: copy another field
        pResource[0x100 / 4] = 0;                     // clear source field
        
        // Copy data from resource
        iVar2 = newEntity[8];
        newEntity[0x30] = *(int*)(iVar2 + 0x10);      // +0xC0
        *(short*)(newEntity + 0x1b) = *(short*)(iVar2 + 0x1e8); // +0x6C
        *(short*)((char*)newEntity + 0x6e) = *(short*)(iVar2 + 0x1ea); // +0x6E
        newEntity[0x1a] = *(int*)(iVar2 + 0x1e4);     // +0x68
        
        // Call a user-defined callback if present
        if (newEntity[0x20] != 0) {   // +0x80: function pointer
            int callbackArg = getEntitySubData(newEntity + 0x21); // +0x84
            ((void (*)(int, int, int))newEntity[0x20])(newEntity[0x10], newEntity[0x2d], callbackArg);
        }
    }
    
    // Set up vtable and vtable pointer depending on derived status
    if (newEntity[0x10] == 0) {      // +0x40: if not derived
        newEntity[1] = &vtable_primary;    // +0x04
        newEntity[2] = (int)newEntity;     // +0x08
    } else {
        newEntity[1] = &vtable_secondary;  // +0x04
        newEntity[2] = newEntity[0x10];    // +0x08: pointer to derived
    }
    
    // Determine entity index/ID for final output
    if (newEntity[8] != 0) {    // +0x20: resource pointer exists
        newEntity[0x2f] = *(short*)(newEntity[8] + 0x108); // +0xBC
        return newEntity;
    }
    
    // Fallback: compute index from sub-resources
    index = (unsigned int)*(unsigned short*)(newEntity[0xb] + 8); // +0x2C pointer
    if ((newEntity[0xc] != 0) && (result = *(int*)(newEntity[0xc] + 8), (int)index >= result)) {
        index = result - 1;
    }
    newEntity[0x2f] = index;   // +0xBC: final entity index
    return newEntity;
}