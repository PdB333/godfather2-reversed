// FUNC_NAME: EntityManager::hasEntityWithId
uint8 EntityManager::hasEntityWithId(int32* idPtr) {
    // Enter critical section (global mutex at DAT_00e2cbf4)
    FUN_00ab4db0(&DAT_00e2cbf4);
    
    uint32 idx = 0;
    uint8 result = 1;
    
    // If object array (at +0x124 holds count) is non‑empty
    if (this->objectCount != 0) {
        int32** curr = (int32**)(this + 0x24); // pointer to array at this+0x24
        do {
            // Compare field at +0x3c of each object to *idPtr
            if (*(*curr + 0x3c) == *idPtr) {
                goto exit; // match found
            }
            idx++;
            curr++;
        } while (idx < this->objectCount);
    }
    result = 0; // no match

exit:
    FUN_00ab4e70(); // leave critical section
    return result;
}