// FUNC_NAME: CharacterEntity::initializeComponents
// Address: 0x00546300
// Role: Initializes character entity components (animation, physics, networking)

void __thiscall CharacterEntity::initializeComponents(char* thisPtr) {
    char local_40[16]; // buffer for vector data (direction)
    float* directionData = reinterpret_cast<float*>(local_40);
    
    // Retrieve a direction vector from the animation component (offset 0x2E8 + 0xD0)
    int* animComponent = *reinterpret_cast<int**>(thisPtr + 0x2E8); // param_1[0xba]
    int* animVtable = *reinterpret_cast<int**>(animComponent + 0xD0);
    (*(void(__thiscall*)(int*, char*))(animVtable[5]))(animComponent + 0xD0, local_40); // +0x14
    
    float fVar1 = *reinterpret_cast<float*>(animComponent + 0x19c); // scale factor
    int* velocityComponent = *reinterpret_cast<int**>(thisPtr + 0x368); // param_1[0xda]
    *reinterpret_cast<float*>(velocityComponent + 0x7c) = directionData[0] * fVar1; // x?
    *reinterpret_cast<float*>(velocityComponent + 0x74) = directionData[1] * fVar1; // y?
    *reinterpret_cast<float*>(velocityComponent + 0x78) = directionData[2] * fVar1; // z?
    
    // Finalize animation direction
    sub_009e6ff0(animComponent, 1);
    
    // Allocate character controller (0x170 bytes)
    TlsGetValue(poolKey); // thread-local memory pool
    int* controller = allocateMemory(0x170, 0xB);
    *reinterpret_cast<short*>(controller + 1) = 0x170;
    
    int* movComponent = sub_0055d510(); // create movement component
    *reinterpret_cast<int*>(thisPtr + 0x360) = reinterpret_cast<int>(movComponent); // param_1[0xd8]
    *reinterpret_cast<int*>(movComponent + 0x1c) = velocityComponent; // param_1[0xda]
    *reinterpret_cast<int*>(movComponent + 0x20) = *reinterpret_cast<int*>(thisPtr + 0x378); // param_1[0xde]
    *reinterpret_cast<int*>(movComponent + 0x24) = *reinterpret_cast<int*>(thisPtr + 0x380); // param_1[0xe0]
    *reinterpret_cast<int*>(movComponent + 0x28) = *reinterpret_cast<int*>(thisPtr + 0x374); // param_1[0xdd]
    *reinterpret_cast<int*>(movComponent + 0x2c) = *reinterpret_cast<int*>(thisPtr + 0x37C); // param_1[0xdf]
    *reinterpret_cast<int*>(movComponent + 0x30) = *reinterpret_cast<int*>(thisPtr + 0x384); // param_1[0xe1]
    int vtableResult = (*(int(__thiscall*)(void*))(*(int*)thisPtr + 0x234))(); // vtable call
    *reinterpret_cast<int*>(movComponent + 0x34) = vtableResult;
    *reinterpret_cast<int*>(movComponent + 0x38) = *reinterpret_cast<int*>(thisPtr + 0x388); // param_1[0xe2]
    *reinterpret_cast<int*>(movComponent + 0x44) = *reinterpret_cast<int*>(thisPtr + 0x38C); // param_1[0xe3]
    
    // Allocate network ghost (0x30 bytes)
    TlsGetValue(poolKey);
    int* netGhost = allocateMemory(0x30, 0xB);
    *reinterpret_cast<short*>(netGhost + 1) = 0x30;
    sub_00bed040(); // some initialization
    *reinterpret_cast<int*>(netGhost) = &s_netGhostVtable; // PTR_LAB_00e39b6c
    *reinterpret_cast<int*>(netGhost + 9) = 0;
    *reinterpret_cast<int*>(netGhost + 10) = 0;
    *reinterpret_cast<int*>(netGhost + 11) = 0x80000000;
    int flags = (*(int(__thiscall*)(void*))(*(int*)thisPtr + 0x22c))(); // vtable call
    *reinterpret_cast<int*>(netGhost + 0xC) = (flags & 0x1F) << 5 | 7;
    *reinterpret_cast<int*>(thisPtr + 0x36C) = reinterpret_cast<int>(netGhost); // param_1[0xdb]
    *reinterpret_cast<int*>(movComponent + 0x3C) = reinterpret_cast<int>(netGhost);
    *reinterpret_cast<int*>(movComponent + 0x9C) = *reinterpret_cast<int*>(*reinterpret_cast<int*>(thisPtr + 0x378) + 0x18); // copy from sub-object
    
    // Set up ragdoll component
    sub_009f3d60(*reinterpret_cast<int*>(thisPtr + 0x370)); // param_1[0xdc]
    
    // Initialize movement component
    (*(void(__thiscall*)(int*))(*(int*)movComponent + 0x20))();
    
    // TODO: Understand this call – uses netGhost field at offset 0x10
    sub_009e7450(*reinterpret_cast<int*>(*reinterpret_cast<int*>(movComponent + 0x3C) + 0x10));
    
    // Register for messages
    sub_009f1f90(reinterpret_cast<int*>(thisPtr + 0x2E0)); // param_1 + 0xB8
    
    // Create animation state (0x160 bytes)
    unsigned int seedVal = sub_0043b490(); // get seed
    unsigned int vtableResult2 = (*(int(__thiscall*)(void*))(*(int*)thisPtr + 0x22c))();
    TlsGetValue(poolKey);
    int* animState = allocateMemory(0x160, 0x31);
    *reinterpret_cast<short*>(animState + 1) = 0x160;
    
    // Build animation key
    int key = (seedVal & 0xFFF) << 0x10 | (vtableResult2 & 0x1F) << 5 | 6;
    *reinterpret_cast<int*>(thisPtr + 0x364) = sub_009f7230(*reinterpret_cast<int*>(animComponent + 0x10),
                                                           animComponent + 0xE0, key); // param_1[0xd9]
    
    sub_0043b490(); // possibly finalize seed
    sub_009f01f0(0x2001, thisPtr, 0); // register message handler 0x2001
    sub_009e7450(*reinterpret_cast<int*>(thisPtr + 0x364)); // pass animation state
}