// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager()
// Address: 0x006b3930
// Destructor for GodfatherGameManager. Cleans up internal lists, releases singletons, and deletes allocated sub-objects.

void __fastcall GodfatherGameManager::~GodfatherGameManager(void* this) {
    int listHead;      // from param_1[0x3d] (offset 0xF4)
    int currentNode;   // from param_1[0x3c] (offset 0xF0)

    // Reset vtable pointers (first two entries)
    *this = &PTR_LAB_00d5e2a4;        // +0x00: base vtable pointer
    *(this + 4) = &PTR_LAB_00d5e294;  // +0x04: second vtable

    listHead = *(int*)(this + 0xF4);   // param_1[0x3d]

    // Walk and free a linked list of objects (each node 0x48 bytes)
    while (listHead != 0) {
        currentNode = *(int*)(this + 0xF0);  // param_1[0x3c] -> pointer to next node?
        if (currentNode == 0) {
            listHead = 0;
        } else {
            // The node's data starts 0x48 bytes before the pointer
            listHead = *(int*)(currentNode + 0xF0);  // not clear; original: iVar1 = *(int *)param_1[0x3c] + -0x48;
            // Actually the logic: iVar1 = (*(int*)param_1[0x3c]) - 0x48;
            // Reinterpret: we treat currentNode as pointing into a larger structure whose base is at (currentNode - 0x48)
            int objectToDelete = currentNode - 0x48;
            // Call some deallocation routine (probably operator delete)
            FUN_008e6320(objectToDelete, 0xffffffff);
        }
        listHead = *(int*)(this + 0xF4);
    }

    // Release global singletons (static addresses)
    FUN_004086d0(&DAT_012069c4);
    FUN_004086d0(&DAT_0112a640);

    // Prepare and call a destructor on a local stack object (likely a list or container)
    int local_c = DAT_0112a638;   // global data
    char local_4 = 0;             // unused
    void* local_8 = this;         // saved this pointer
    FUN_00408a00(&local_c, 0);    // destructor for something

    // Release another singleton
    FUN_004086d0(&DAT_0112fe38);

    // Release sub-objects via function pointers stored in the class
    // Offsets: +0x65 (0x194), +0x60 (0x180), +0x5f (0x17C), +0x57 (0x15C), +0x53 (0x14C),
    //          +0x4f (0x13C), +0x4b (0x12C), +0x47 (0x11C), +0x43 (0x10C)
    if (*(int*)(this + 0x194) != 0) {
        // Function pointer at +0x5a (0x168)
        (*(void (__fastcall**)(int))(this + 0x168))(*(int*)(this + 0x194));
    }
    if (*(int*)(this + 0x180) != 0) {
        *(void**)(this + 0x180 + 8) = 0; // +8 is likely a pointer? or ref count?
        this + 0x180 = 0; // Actually param_1[0x60] pointer cleared
    }
    if (*(int*)(this + 0x17C) != 0) {
        *(void**)(this + 0x17C + 8) = 0;
        this + 0x17C = 0;
    }
    if (*(int*)(this + 0x15C) != 0) {
        (*(void (__fastcall**)(int))(this + 0x168))(*(int*)(this + 0x15C));
        // Actually the function pointer for +0x57 is at +0x5a (0x168)
    }
    if (*(int*)(this + 0x14C) != 0) {
        (*(void (__fastcall**)(int))(this + 0x168))(*(int*)(this + 0x14C));
    }
    if (*(int*)(this + 0x13C) != 0) {
        (*(void (__fastcall**)(int))(this + 0x168))(*(int*)(this + 0x13C));
    }
    if (*(int*)(this + 0x12C) != 0) {
        (*(void (__fastcall**)(int))(this + 0x168))(*(int*)(this + 0x12C));
    }
    if (*(int*)(this + 0x11C) != 0) {
        (*(void (__fastcall**)(int))(this + 0x168))(*(int*)(this + 0x11C));
    }
    if (*(int*)(this + 0x10C) != 0) {
        (*(void (__fastcall**)(int))(this + 0x168))(*(int*)(this + 0x10C));
    }

    // Another cleanup function
    FUN_006b3540(); // likely releases managed resources

    // Release objects with function pointers at +0x38 (0xE0) using +0x3b (0xEC)
    if (*(int*)(this + 0xE0) != 0) {
        (*(void (__fastcall**)(int))(this + 0xEC))(*(int*)(this + 0xE0));
    }

    // Release multiple objects via a common release function (maybe IUnknown::Release)
    if (*(int*)(this + 0xB4) != 0) {
        FUN_009c8f10(*(int*)(this + 0xB4));
    }
    if (*(int*)(this + 0xA8) != 0) {
        FUN_009c8f10(*(int*)(this + 0xA8));
    }
    if (*(int*)(this + 0x9C) != 0) {
        FUN_009c8f10(*(int*)(this + 0x9C));
    }
    if (*(int*)(this + 0x90) != 0) {
        FUN_009c8f10(*(int*)(this + 0x90));
    }
    if (*(int*)(this + 0x84) != 0) {
        FUN_009c8f10(*(int*)(this + 0x84));
    }

    // Final cleanup
    FUN_004083d0();
    return;
}