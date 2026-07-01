// FUNC_NAME: Player::PlayerConstructor
// Function address: 0x007a38f0
// Role: Constructor/initializer for Player class. Sets up various subsystems, delegates, and flags.

void __thiscall Player::PlayerConstructor(Player* this) {
    uint* puVar1;
    int iVar2;
    char cVar3;

    // Call base class initializer (Sentient or SimObject)
    BaseClassInit(this, 1); // FUN_0043c490

    // If some flag at +0x264 is zero, send an event
    if (*(int*)(this + 0x264) == 0) {
        SendEvent(); // FUN_00460840
    }

    SomeGlobalFunction(); // FUN_00809330

    // Set up a delegate structure at +0x5f4
    // This structure holds function pointer FUN_0079ce60 and self reference
    iVar2 = *(int*)(this + 0x5f4);
    *(ulonglong*)(iVar2 + 0x34) = CONCAT44(FUN_0079ce60, this);
    *(undefined8*)(iVar2 + 0x3c) = 0;
    *(undefined8*)(iVar2 + 0x44) = 0x79b02000000000; // Contains address 0x79b020

    // Set a flag at +0x18 inside the delegate structure
    puVar1 = (uint*)(iVar2 + 0x18);
    *puVar1 |= 0x80000;

    // Self-reference pointer at +0x30b4
    *(int*)(this + 0x30b4) = this;

    // Initialize something at +0x30b0 (maybe a mutex or event)
    InitializeMutex(this + 0x30b0); // FUN_0054e310

    // Register this object with a manager
    RegisterWithManager(0, this); // FUN_008f6f50

    // Check if game is running
    cVar3 = IsGameRunning(); // FUN_00481620
    if (cVar3 != '\0') {
        // Additional initialization for running game
        SpecialInitForRunningGame(this); // FUN_008938b0
        AnotherGameInit(); // FUN_007e85b0
    }

    // Process four consecutive ints at +0x3188 to +0x3194 (likely a 16-byte structure)
    // Compute hash and store at +0x3180
    if (*(int*)(this + 0x3188) != 0 ||
        *(int*)(this + 0x318c) != 0 ||
        *(int*)(this + 0x3190) != 0 ||
        *(int*)(this + 0x3194) != 0) {
        *(int*)(this + 0x3180) = ComputeIDHash(this + 0x3188, &local_31); // FUN_00448100
    }

    // Process another group at +0x3198 to +0x31a4, store at +0x3184
    if (*(int*)(this + 0x3198) != 0 ||
        *(int*)(this + 0x319c) != 0 ||
        *(int*)(this + 0x31a0) != 0 ||
        *(int*)(this + 0x31a4) != 0) {
        *(int*)(this + 0x3184) = ComputeIDHash(this + 0x3198, &local_31); // FUN_00448100
    }

    // Set up a linked list node at offset +0x48
    // local_2c points to the node (this+0x48)
    // local_30 is vtable pointer PTR_FUN_00e31e2c
    // local_28 is the current next pointer at +0x4c, then we insert this node
    int* nodePtr = this + 0x48;
    undefined4* vtablePtr = &PTR_FUN_00e31e2c; // Some vtable for base class
    int oldNext = *(int*)(this + 0x4c);
    *(int**)(this + 0x4c) = &nodePtr;

    // Register strings or objects with global managers
    int global1 = DAT_01130fb4;
    RegisterString(&global1, 0); // FUN_00408a00
    int global2 = DAT_0112b53c;
    RegisterString(&global2, 0);
    int global3 = DAT_0112b51c;
    RegisterString(&global3, 0);

    // Handle special case if some ID at +0x1ed8 is not zero and not 0x48
    if (*(int*)(this + 0x1ed8) != 0 && *(int*)(this + 0x1ed8) != 0x48) {
        HandleSpecialID(this); // FUN_008c3c80
    }

    // Call some global functions
    GlobalFunc1(DAT_01131010); // FUN_0043b870
    GlobalFunc2(); // FUN_009adae0

    // Set a flag at +0x4a4 bit 0
    *(uint*)(this + 0x4a4) |= 1;

    // Remove the linked list node if it was inserted (cleanup if needed)
    if (nodePtr != 0) {
        RemoveFromLinkedList(&nodePtr); // FUN_004daf90
    }

    return;
}