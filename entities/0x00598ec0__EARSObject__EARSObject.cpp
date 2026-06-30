// FUNC_NAME: EARSObject::EARSObject
class EARSObject {
public:
    // Constructor: Sets vtable pointer at offset 0x00
    // Corresponds to function at 0x598ec0, sets vtable from PTR_LAB_00e3b044
    __thiscall EARSObject() {
        // Assign the vtable pointer to the first member (offset +0x0)
        *(void**)this = (void*)&gEARSObjectVTable;  // PTR_LAB_00e3b044
    }
};