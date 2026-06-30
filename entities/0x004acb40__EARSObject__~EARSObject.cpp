// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::e_releaseManagers(EARSObject* this) {
    // Set vtable to base class destructor vtable
    *(void***)this = &PTR_FUN_00e356f0;

    // Iterate through 6 component manager groups (each with a manager instance and two child pointers)
    struct ManagerGroup {
        int mgrOffset;    // offset of manager pointer from this (points to Manager with vtable)
        int child1Offset; // offset of first child pointer
        int child2Offset; // offset of second child pointer (may be null)
    };

    ManagerGroup groups[] = {
        { 0x20, 0x1c, 0x1f },  // group 5 (first destroyed)
        { 0x1b, 0x17, 0x1a },  // group 4
        { 0x16, 0x12, 0x15 },  // group 3
        { 0x11, 0x0d, 0x10 },  // group 2
        { 0x0c, 0x08, 0x0b },  // group 1
        { 0x05, 0x01, 0x04 }   // group 0 (last destroyed)
    };

    for (int i = 0; i < 6; ++i) {
        // Get manager pointer (it points to a struct whose first member is a vtable pointer)
        Manager** mgrPtr = (Manager**)((char*)this + groups[i].mgrOffset * 4);
        Manager* mgr = *mgrPtr;
        if (mgr == nullptr) continue; // safety, though probably always valid

        // vtable pointer for the manager
        ManagerVTable* vtable = *(ManagerVTable**)mgr;

        // First child pointer (always present)
        void* child1 = *(void**)((char*)this + groups[i].child1Offset * 4);
        vtable->release(child1, 0); // release method at vtable[1]

        // Second child pointer (may be null)
        void* child2 = *(void**)((char*)this + groups[i].child2Offset * 4);
        if (child2 != nullptr) {
            vtable->release(child2, 0);
        }

        // Cleanup method at vtable[3]
        vtable->cleanup();
    }
}