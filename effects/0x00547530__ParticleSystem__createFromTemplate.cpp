// FUNC_NAME: ParticleSystem::createFromTemplate
int __thiscall ParticleSystem::createFromTemplate(void* thisContext, int* templateObj) {
    int* bufferPtr;
    uint maxParticles;
    uint activeParticles;
    int diffCount;
    int newObj;
    int blockIdx;
    int remainingCount;
    uint i;
    
    // Get particle counts from template object via virtual functions
    maxParticles = (*(code**)(*templateObj + 0x220))();   // ++0x220: getMaxParticles
    activeParticles = (*(code**)(*templateObj + 0x228))(0); // ++0x228: getActiveParticleCount
    diffCount = maxParticles - activeParticles;            // Number of new particles to allocate
    
    TlsGetValue(someTlsIndex);  // Thread-local storage for pool
    
    // Allocate new particle system object (0x1a0 bytes)
    newObj = allocMem(0x1a0, 0xb);  // size 0x1a0, type 0xb
    *(short*)(newObj + 0x4) = 0x1a0;  // Store allocation size
    
    newObj = someGlobalPoolFunction();  // Returns a pointer to the object (maybe aligns it)
    bufferPtr = (int*)(newObj + 0x8c);  // Pointer to particle data array pointer
    *(char*)(newObj + 0x20) = (char)maxParticles;  // Store max particles at offset 0x20
    
    // Resize particle data array if needed
    uint currentCapacity = *(uint*)(newObj + 0x94) & 0x3fffffff;  // offset 0x94: capacity
    if ((int)currentCapacity < (int)maxParticles) {
        uint newCapacity = currentCapacity * 2;
        if ((int)newCapacity <= (int)maxParticles) {
            newCapacity = maxParticles;
        }
        reallocArray(bufferPtr, newCapacity, 0x28);  // Reallocate 0x28-sized elements
    }
    *(uint*)(newObj + 0x90) = maxParticles;  // offset 0x90: particle count
    
    // Initialize particle flags (active/inactive)
    if (diffCount != 0) {
        for (i = 0; i < diffCount; i++) {
            *(char*)(i * 0x28 + 0x24 + *bufferPtr) = 0;  // Mark existing particles as inactive? (flag = 0)
        }
    }
    if (diffCount < maxParticles) {
        int startIdx = diffCount;
        int newCount = maxParticles - diffCount;
        for (i = 0; i < newCount; i++) {
            *(char*)((startIdx + i) * 0x28 + 0x24 + *bufferPtr) = 1;  // Mark new particles as active (flag = 1)
        }
    }
    
    // Default particle property values (loaded from globals)
    int defaultVal1 = DAT_00e445dc;  // e.g., float for some component
    int defaultVal2 = DAT_00e2b1a4;  // e.g., position x
    int defaultVal3 = DAT_00e2b04c;  // e.g., position z?
    int defaultVal4 = DAT_00e2eff4;  // e.g., scaling factor?
    
    // Write default values to each particle element (0x28 bytes each)
    // Each particle has 6 floats: offset 0xc,0x10,0x14,0x1c,0x18,0x20
    // Group of 4 particles processed together (0xA0 bytes) for efficiency
    i = 0;
    if (3 < maxParticles) {
        int groupStart = 0;
        int numGroups = ((maxParticles - 4) >> 2) + 1;
        i = numGroups * 4;
        do {
            // Group of 4 particles, each with 6 floats
            // Particle 1
            *(int*)(groupStart + 0xc + *bufferPtr) = defaultVal2; // pos.x or similar
            *(int*)(groupStart + 0x10 + *bufferPtr) = 0;          // pos.y = 0
            *(int*)(groupStart + 0x14 + *bufferPtr) = defaultVal3; // pos.z
            *(int*)(groupStart + 0x1c + *bufferPtr) = defaultVal2; // vel.x or similar
            *(int*)(groupStart + 0x18 + *bufferPtr) = 0;          // vel.y = 0
            *(int*)(groupStart + 0x20 + *bufferPtr) = defaultVal1; // vel.z or other component
            *(int*)(groupStart + 0x34 + *bufferPtr) = defaultVal2;
            *(int*)(groupStart + 0x38 + *bufferPtr) = 0;
            *(int*)(groupStart + 0x3c + *bufferPtr) = defaultVal3;
            *(int*)(groupStart + 0x44 + *bufferPtr) = defaultVal2;
            *(int*)(groupStart + 0x40 + *bufferPtr) = 0;
            *(int*)(groupStart + 0x48 + *bufferPtr) = defaultVal1;
            // Particle 2
            *(int*)(groupStart + 0x5c + *bufferPtr) = defaultVal2;
            *(int*)(groupStart + 0x60 + *bufferPtr) = 0;
            *(int*)(groupStart + 0x64 + *bufferPtr) = defaultVal3; // Note: offset misalignment? Actually 0x64 = 100 decimal? But code says "iVar8 + 100 + *piVar1" which is 0x64
            *(int*)(groupStart + 0x6c + *bufferPtr) = defaultVal2;
            *(int*)(groupStart + 0x68 + *bufferPtr) = 0;
            *(int*)(groupStart + 0x70 + *bufferPtr) = defaultVal1;
            // Particle 3
            *(int*)(groupStart + 0x84 + *bufferPtr) = defaultVal2;
            *(int*)(groupStart + 0x88 + *bufferPtr) = 0;
            *(int*)(groupStart + 0x8c + *bufferPtr) = defaultVal3;
            *(int*)(groupStart + 0x94 + *bufferPtr) = defaultVal2;
            *(int*)(groupStart + 0x90 + *bufferPtr) = 0;
            *(int*)(groupStart + 0x98 + *bufferPtr) = defaultVal1;
            groupStart += 0xa0; // Advance to next group of 4 particles (0x28*4)
            numGroups--;
        } while (numGroups != 0);
    }
    
    // Handle remaining particles (less than a full group)
    if (i < maxParticles) {
        int remainderStart = i * 0x28;
        int remaining = maxParticles - i;
        do {
            *(int*)(remainderStart + 0xc + *bufferPtr) = defaultVal2;
            *(int*)(remainderStart + 0x10 + *bufferPtr) = 0;
            *(int*)(remainderStart + 0x14 + *bufferPtr) = defaultVal3;
            *(int*)(remainderStart + 0x1c + *bufferPtr) = defaultVal2;
            *(int*)(remainderStart + 0x18 + *bufferPtr) = 0;
            *(int*)(remainderStart + 0x20 + *bufferPtr) = defaultVal1;
            remainderStart += 0x28;
            remaining--;
        } while (remaining != 0);
    }
    
    // Initialize transformation matrix (4x3 or 4x4?) at offsets 0x30-0x5c
    *(int*)(newObj + 0x34) = defaultVal2;  // matrix row0.x
    *(int*)(newObj + 0x30) = 0;            // matrix row0.y
    *(int*)(newObj + 0x38) = 0;            // matrix row0.z
    *(int*)(newObj + 0x3c) = 0;            // matrix row0.w (if present)
    *(int*)(newObj + 0x48) = defaultVal2;  // matrix row1.x
    *(int*)(newObj + 0x40) = 0;            // row1.y
    *(int*)(newObj + 0x44) = 0;            // row1.z
    *(int*)(newObj + 0x4c) = 0;            // row1.w
    *(int*)(newObj + 0x50) = defaultVal4;  // matrix row2.x (scale factor?)
    *(int*)(newObj + 0x54) = 0;            // row2.y
    *(int*)(newObj + 0x58) = 0;            // row2.z
    *(int*)(newObj + 0x5c) = 0;            // row2.w
    
    // Call parent/base class initialization
    FUN_005477e0(thisContext, templateObj);
    
    return newObj;
}