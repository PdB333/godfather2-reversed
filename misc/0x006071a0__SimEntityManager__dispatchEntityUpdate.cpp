// FUNC_NAME: SimEntityManager::dispatchEntityUpdate
void SimEntityManager::dispatchEntityUpdate(void* context) {
    // context points to a structure with fields:
    // +0x14: entityIndex (uint)
    // +0x18: flags byte
    // +0x0c: action flags
    // +0x1c: extra parameter
    uint entityIndex = *(uint*)((char*)context + 0x14);
    
    if (entityIndex < 0x1000) {
        // Global entity table: each entry is 0x38 bytes
        // DAT_011a0f28 is the base of the table
        EntityEntry* entityEntry = (EntityEntry*)((char*)0x011a0f28 + entityIndex * 0x38);
        
        // Check if entry exists and matches state
        if (entityEntry != nullptr) {
            // Entry first byte indicates status: 4 = active, 5 = pending removal
            if (entityEntry->status == 4 ||
                ((*(uint*)((char*)context + 0x18) & 8) != 0 && entityEntry->status == 5)) {
                
                // Get the entity's vtable pointer (first 4 bytes of entry)
                void* entityVtable = *(void**)entityEntry;
                // vtable+0x50 is the update method
                void (*updateMethod)(void*, int) = (void (*)(void*, int))(*(int*)((int)entityVtable + 0x50));
                
                // Check action flags at context+0x0c
                if ((*(uint*)((char*)context + 0x0c) & 2) == 0) {
                    // Bit 1 not set: single-argument call
                    if ((*(uint*)((char*)context + 0x0c) & 4) == 0) {
                        // Bit 2 not set: use context+0x1c as argument
                        updateMethod(entityEntry, *(int*)((char*)context + 0x1c));
                    } else {
                        // Bit 2 set: pass 0 as argument
                        updateMethod(entityEntry, 0);
                    }
                } else {
                    // Bit 1 set: three-argument call (second arg is extra parameter, third is 0)
                    void (*updateMethod3)(void*, int, int) = (void (*)(void*, int, int))updateMethod;
                    updateMethod3(entityEntry, *(int*)((char*)context + 0x1c), 0);
                }
                
                // If not in removal state, call cleanup function
                if (entityEntry->status != 5) {
                    if (entityIndex == -1) {
                        FUN_00606830(0xFFFFFFFF, entityEntry);
                    } else {
                        FUN_00606830(entityIndex, entityEntry);
                    }
                }
            }
        }
    }
}