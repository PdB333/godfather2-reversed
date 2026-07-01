// FUNC_NAME: AudioManager::constructor
undefined4 * __thiscall AudioManager::constructor(undefined4 *this, undefined4 param2, undefined4 param3)
{
    // Base class constructor call
    BaseClass::constructor(param2, param3);

    // Set vtable pointer
    *this = &PTR_LAB_00d6e3e8;

    // Initialize linked list node at offset +0x84 (piVar1 = this + 0x21)
    int *listNode = reinterpret_cast<int *>(this + 0x21);
    *listNode = 0;
    this[0x22] = 0;           // offset +0x88 (next pointer)

    // Get singleton managers and store pointers
    // AudioDataManager singleton
    void *audioMgr = FUN_007ab130();
    this[0x1d] = *(undefined4 *)((int)audioMgr + 4);   // offset +0x74: store some field from audioMgr
    void *puVar4 = static_cast<void*>(audioMgr);
    (*(code **)puVar4)(0x3f);                // Call first virtual function with 63 (max volume range?)

    // Stream manager singleton
    void *streamMgr = FUN_007ab140();
    this[0x1e] = *(undefined4 *)((int)streamMgr + 4);   // offset +0x78
    puVar4 = static_cast<void*>(streamMgr);
    (*(code **)puVar4)(0x3ff);               // Call first virtual with 1023 (max sample rate?)

    // Input device manager singleton
    void *inputMgr = FUN_007ab150();
    this[0x1f] = ((int*)inputMgr)[1];        // offset +0x7c: copy second DWORD (some pointer/state)
    puVar4 = static_cast<void*>(inputMgr);
    (*(code **)puVar4)(2);                    // Call first virtual with 2 (stereo mode?)
    (*(code **)puVar4)(1);                    // Call first virtual with 1 (mono mode?)

    // Initialize default settings
    FUN_0045f2a0(0);                         // Some global initialization
    FUN_007f63e0(0x5c);                      // Allocate 92 bytes for internal data

    // Get or create a linked list node (+0x48 offset) from another manager
    int iVar3 = FUN_007e0d20();              // returns pointer to some structure
    int iVar6 = 0;
    if (iVar3 != 0) {
        iVar6 = iVar3 + 0x48;                // offset to node within structure
    }

    // Update linked list: replace old node with new one
    if (*listNode != iVar6) {
        if (*listNode != 0) {
            FUN_004daf90(listNode);          // remove old node from list (unsafe, but game code)
        }
        *listNode = iVar6;                   // set new node
        if (iVar6 != 0) {
            this[0x22] = *(undefined4 *)(iVar6 + 4); // copy next pointer from node
            *(int **)(iVar6 + 4) = listNode;          // set node's next to point back to list head
        }
    }

    // Get the original container pointer (subtract 0x48)
    int containerPtr = 0;
    if (*listNode == 0) {
        containerPtr = 0;
    } else {
        containerPtr = *listNode - 0x48;      // back to container
    }
    FUN_007e0b90(containerPtr);               // register container with some system

    // Set a flag or pointer based on a global condition
    if (this[0x16] == 0) {                    // offset +0x58
        this[0x23] = 0;                       // offset +0x8c
    } else {
        this[0x23] = FUN_0043b870(DAT_01130950); // call with global data
    }

    // Enable debug overlay if exists
    char cVar2 = FUN_00481660();              // debug check
    if (cVar2 != '\0') {
        FUN_00472130(1);                      // enable debug rendering
    }

    // Compute hash for a string key (0x1ff = 511, maybe hash table size)
    FUN_007ab120(0x1ff);                      // prepare hashtable
    this[0x20] = FUN_00896db0(0x1ff);         // store hash result (offset +0x80)

    return this;
}