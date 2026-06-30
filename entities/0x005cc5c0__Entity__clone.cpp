// FUNC_NAME: Entity::clone
int Entity::clone(void* source) // source pointer in EAX
{
    // Allocation parameters: size 0x90, flags (2,4,0)
    int allocFlags[3] = {2, 4, 0};
    // Call custom allocator from global table at g_allocatorTable[1]
    int newObj = ((AllocFunc)(*(void**)(g_allocatorTable + 4)))(0x90, allocFlags);
    
    // Set field at offset 0x1c to 2 (likely type or version)
    *(int*)(newObj + 0x1c) = 2;
    
    // Initialize field at 0x84 with result of helper function
    *(int*)(newObj + 0x84) = FUN_005cc170();
    
    // Zero out fields at 0x88 and 0x8c
    *(int*)(newObj + 0x88) = 0;
    *(int*)(newObj + 0x8c) = 0;
    
    // If global manager flag is set, initialize field at 0x88 from source
    if (*(int*)(g_someManager + 0x2c) != 0) {
        *(int*)(newObj + 0x88) = FUN_005cc330(*(int*)(source + 0x5c)); // source[0x17] = offset 0x5c
    }
    
    // Increment global clone counter
    g_cloneCounter++;
    
    // Copy 25 dwords (100 bytes) from source at offset 0x20 to new object at offset 0x20
    int* src = (int*)((char*)source + 0x20);
    int* dst = (int*)(newObj + 0x20);
    for (int i = 0; i < 25; i++) {
        dst[i] = src[i];
    }
    
    return newObj;
}