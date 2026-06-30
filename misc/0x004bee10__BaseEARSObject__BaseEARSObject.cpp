// FUNC_NAME: BaseEARSObject::BaseEARSObject

// Constructor for an unknown EA EARS engine base class at 0x004bee10.
// Sets up two vtable pointers (likely for multiple inheritance) and calls a base/member initializer.
// The byte parameter is a flag (bit0) that triggers an additional cleanup/construction call (possibly operator delete on exception?).
class BaseEARSObject {
public:
    void* vtable;          // +0x00: primary vtable pointer (PTR_FUN_00e35d30)
    void* secondaryVtable; // +0x04: secondary vtable pointer (PTR_LAB_00e35d78)

    // Constructor. Returns 'this'.
    // param_2: low bit controls whether to call additional function (FUN_009c8eb0).
    __thiscall void* constructor(byte flag) {
        this->vtable = &PTR_FUN_00e35d30;
        this->secondaryVtable = &PTR_LAB_00e35d78;
        FUN_00567a20(); // base class constructor or member initializer (likely sets up other fields)
        if (flag & 1) {
            FUN_009c8eb0(this); // optional cleanup/additional construction (e.g., operator delete on throw)
        }
        return this;
    }
};