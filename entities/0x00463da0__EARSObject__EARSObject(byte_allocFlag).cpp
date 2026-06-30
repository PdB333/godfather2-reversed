// FUNC_NAME: EARSObject::EARSObject(byte allocFlag)
class EARSObject {
public:
    void* vtable;                   // +0x00
    void* field_4;                  // +0x04 (unused here)
    void* subObjectVtablePtr;       // +0x08 (points to sub-object vtable)
    void* subObjectBase;            // +0x0C (base of sub-object, used for virtual call)

    EARSObject(byte allocFlag) {
        // Set primary vtable
        this->vtable = (void*)&PTR_FUN_00e31e58;

        // Initialize sub-object vtable pointer
        this->subObjectVtablePtr = (void*)&PTR_LAB_00e31e64;

        // Call a virtual function at offset 0xC on the sub-object
        // subObjectBase is actually a pointer to the sub-object's vtable pointer
        void* subVtable = *(void**)this->subObjectBase;
        void (*initFunc)() = (void(*)())(*(int*)((int)subVtable + 0xC));
        initFunc();

        // Update sub-object vtable to a different one
        this->subObjectVtablePtr = (void*)&PTR_LAB_00e31e68;

        // Reset global singleton flag
        DAT_01223460 = 0;

        // Call common initialization
        FUN_0049c640();

        // If allocation flag indicates dynamically allocated, delete this instance
        if (allocFlag & 1) {
            FUN_009c8eb0(this);  // operator delete
        }
    }

    // Note: operator delete is called via FUN_009c8eb0, which is likely `delete` or a custom deallocator.
    // The constructor returns this pointer implicitly.
};