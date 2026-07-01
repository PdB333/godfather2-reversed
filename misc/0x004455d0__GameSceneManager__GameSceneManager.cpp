// FUNC_NAME: GameSceneManager::GameSceneManager
GameSceneManager* __thiscall GameSceneManager::GameSceneManager(GameSceneManager* this, undefined4 param_2, undefined4 param_3, int* resourceManager, undefined4 param_5, undefined4 param_6, undefined4 param_7)
{
    void* buffer;
    undefined4 result;
    undefined4* vtablePtr;
    int i;
    undefined4 stackAlloc[2]; // not sure
    undefined4* stackPtr;
    int magicGuard;
    code* guardFunc;
    undefined4 guardData;
    undefined1* guardLabel;

    // Setup initial state and vtable pointers
    this[1] = 1; // +0x04: some flag
    this[2] = 0; // +0x08: some counter
    this[3] = &PTR_FUN_00e3522c; // +0x0C: vtable pointer
    this[4] = 0; // +0x10: unused?
    this[5] = &PTR_LAB_00e311d4; // +0x14: another vtable
    DAT_01223410 = this; // Global pointer to this instance

    // Set the main vtable and additional vtables
    *this = &PTR_FUN_00e311b4; // +0x00: primary vtable
    this[3] = &PTR_LAB_00e311c4; // +0x0C
    this[5] = &PTR_LAB_00e311d0; // +0x14

    // Initialize various fields
    this[8] = 0;  // +0x20
    this[0x0e] = param_7; // +0x38: store param_7
    this[9] = 0;  // +0x24
    this[10] = 0; // +0x28
    *(undefined1*)(this + 0x0f) = 0; // +0x3C: byte
    this[0x10] = 0; // +0x40
    this[0x11] = 0; // +0x44
    this[0x13] = 0x43; // +0x4C: array size = 67 (0x43)
    this[0x12] = 0; // +0x48: pointer to buffer1
    this[0x14] = 0; // +0x50
    this[0x15] = 0; // +0x54
    this[0x16] = 0; // +0x58
    *(undefined1*)(this + 0x17) = 0; // +0x5C: byte

    // Allocate buffer 1: 0x10C bytes, each entry 4 bytes, 67 entries
    buffer = (void*)FUN_009c8e80(0x10C);
    this[0x12] = buffer; // +0x48
    _memset(buffer, 0, this[0x13] * 4); // Zero-initialize

    // More fields
    this[0x18] = 0; // +0x60
    this[0x19] = 0; // +0x64
    this[0x1a] = 0; // +0x68
    this[0x1b] = 0; // +0x6C
    this[0x1d] = 0x7d3; // +0x74: array size = 2003 (0x7D3)
    this[0x1c] = 0; // +0x70: pointer to buffer2
    this[0x1e] = 0; // +0x78
    *(undefined1*)(this + 0x1f) = 0; // +0x7C: byte

    // Allocate buffer 2: 0x1F4C bytes, each entry 4 bytes, 2003 entries
    buffer = (void*)FUN_009c8e80(0x1F4C);
    this[0x1c] = buffer; // +0x70
    _memset(buffer, 0, this[0x1d] * 4);

    // More fields
    this[0x20] = 0; // +0x80: pointer to buffer3
    this[0x21] = 0x1ff; // +0x84: array size = 511 (0x1FF)
    this[0x22] = 0; // +0x88
    *(undefined1*)(this + 0x23) = 0; // +0x8C: byte

    // Allocate buffer 3: 0x7FC bytes, each entry 4 bytes, 511 entries
    buffer = (void*)FUN_009c8e80(0x7FC);
    this[0x20] = buffer; // +0x80
    _memset(buffer, 0, this[0x21] * 4);

    // Initialize 3 pairs of ints at offset 0x90 (+0x24, +0x28, +0x2C)
    vtablePtr = this + 0x24;
    i = 3;
    do {
        *vtablePtr = 0;
        vtablePtr[1] = 0;
        vtablePtr += 2;
        i--;
    } while (i >= 0);

    // Local stack variables for resource handle
    stackAlloc[0] = 0; // local_30
    stackAlloc[1] = 0; // local_2c (pointer)
    magicGuard = 0;   // local_28

    this[0x2d] = 0;  // +0xB4
    this[0x2e] = 0x50; // +0xB8: maybe size 80

    // Get a resource handle via resourceManager
    result = FUN_004265d0(stackAlloc, resourceManager);
    this[0x2f] = result; // +0xBC: store handle
    this[0x30] = resourceManager; // +0xC0: store resource manager pointer

    // Call virtual function on resourceManager (offset +0x08 = probably addRef)
    (**(code**)(*resourceManager + 8))();

    // Use resource handle to create another object
    vtablePtr = (undefined4*)this[0x2f]; // handle
    if (vtablePtr == (undefined4*)0x0) {
        vtablePtr = &DAT_01218a14; // fallback global
    }
    // Call resource manager's function with size 0x280 and handle
    result = (*(code*)**(undefined4**)this[0x30])(0x280, vtablePtr);
    this[0x2c] = result; // +0xB0: store result

    this[0x32] = param_2; // +0xC8
    *(undefined1*)(this + 0x31) = 1; // +0xC4: byte flag
    this[0x33] = 0; // +0xCC
    this[0xb4] = 0; // +0x2D0? large offset, careful: 0xb4 * 4 = 0x2D0
    this[0xb5] = resourceManager; // +0x2D4: store resourceManager again

    // Call virtual function on resourceManager (addRef again)
    (**(code**)(*resourceManager + 8))();

    // Register a global atexit cleanup if not already done
    if ((_DAT_01226f54 & 1) == 0) {
        _DAT_01226f54 |= 1;
        FUN_00484b10(); // initialize something
        _atexit((_func_4879*)&LAB_00d50760); // register cleanup
    }

    // Register event handler for message 0x712 with callback FUN_00487620
    FUN_00484000(); // maybe event system init
    FUN_00483ba0(0x712, FUN_00487620); // register callback

    ADD_OBJECTS:
    // Register SimGroup with count 1
    FUN_0049c6e0("SimGroup", 1);

    // Add various global SimGroups/objects to this manager
    if (DAT_01206778 != 0) {
        FUN_00407e60(this, &DAT_01206778);
    }
    if (DAT_01206780 != 0) {
        FUN_00407e60(this, &DAT_01206780);
    }
    if (DAT_0120678c != 0) {
        FUN_00407e60(this, &DAT_0120678c);
    }
    if (DAT_01206760 != 0) {
        FUN_00407e60(this, &DAT_01206760);
    }

    // Look up and connect to message "iMsgPostSpawnInitialize"
    result = FUN_004dafd0("iMsgPostSpawnInitialize");
    FUN_00408260(&DAT_0120e93c, result);

    // Setup a guard for stack-allocated object (Torque pattern)
    guardData = 0;
    guardFunc = FUN_00447820; // destructor or guard function
    guardLabel = &LAB_00449640;
    magicGuard = 0x2a7ed975;
    stackPtr = this;
    // Call some function that likely sets up the guard and then runs init code
    FUN_00486b90(param_5, param_6);

    // If guard was not cleaned up, call cleanup
    if (guardLabel != (undefined1*)0x0 && magicGuard != 0x2a7ed975) {
        FUN_00407640(); // cleanup
    }

    return this;
}