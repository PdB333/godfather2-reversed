// FUNC_NAME: StreamManager::initialize
undefined4* StreamManager::initialize(undefined4* this, undefined4 param2) {
    int* piVar1;
    int iVar2;
    undefined4 uVar3;
    int* piVar4;
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;

    *this = &streamManagerVTable; // +0x0 vtable pointer
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    piVar1 = *(int**)(_gEngine + 4); // Global engine pointer +0x4 -> allocator?
    _gStreamManagerSingleton = this; // Store global reference

    // Call virtual function at offset +8 on the allocator: likely "startAlloc" or similar
    (**(code**)(*piVar1 + 8))();

    // Call string allocation helper: FUN_004265d0 may be a string constructor or allocation
    iVar2 = FUN_004265d0(&local_c, piVar1);
    piVar4 = piVar1;
    (**(code**)(*piVar1 + 8))(piVar1); // Another allocator call

    if (iVar2 == 0) {
        uVar3 = 0;
    } else {
        uVar3 = FUN_004265d0(iVar2, piVar4);
    }

    // Set stream path or name
    FUN_005d9fb0(piVar4, uVar3);

    // Initialize stream state fields
    this[3] = 0; // +0x0c: currentStreamIndex
    this[4] = 0; // +0x10: pendingCount
    this[5] = 0; // +0x14: nextStreamId

    if (iVar2 != 0) {
        // Call virtual function at +4 on allocator: probably "free"
        (**(code**)(*piVar1 + 4))(iVar2, 0);
    }

    // Call virtual function at +0xc: possibly "endAlloc"
    (**(code**)(*piVar1 + 0xc))();

    // Register/setup with given parameter (maybe a stream path or config)
    FUN_005d98b0(param2);

    return this;
}