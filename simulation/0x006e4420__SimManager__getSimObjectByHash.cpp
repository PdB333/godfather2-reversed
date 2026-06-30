// FUNC_NAME: SimManager::getSimObjectByHash
void SimManager::getSimObjectByHash(SimManager* this, void** outPtr)
{
    // Get the hash lookup interface at offset +0x100 from this
    HashLookup* lookup = *(HashLookup**)((intptr_t)this + 0x100);
    void* result = 0;
    // Call virtual function at vtable+0x10 (index 4) on lookup
    // It takes a hash (0x383225a1) and an output pointer to store the found object
    bool found = ((bool (*)(HashLookup*, uint32_t, void**))(*(void***)(*(intptr_t*)lookup))[4])(lookup, 0x383225a1, &result);
    
    // unaff_ESI is assumed to be a saved global pointer (e.g., g_CurrentPlayer)
    if (found && g_CurrentPlayer != 0) {
        // Use the current player's stored pointer at +0x28d0
        *outPtr = *(void**)((intptr_t)g_CurrentPlayer + 0x28d0);
    } else {
        // Fallback to default pointer from lookup's internal data at +0x1f90
        *outPtr = *(void**)((intptr_t)lookup + 0x1f90);
    }
}