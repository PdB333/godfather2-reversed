// FUNC_NAME: EARSObject::~EARSObject
class EARSObject {
public:
    void* vtable;       // +0x00
    void* someMember;   // +0x04, pointer to another object or resource

    // Destructor with deallocation flag (param2)
    // Sets vtable to base class vtable (0x00d6102c) to finalize destruction,
    // releases any owned resource at +0x04, and optionally frees memory.
    void* __thiscall ~EARSObject(byte deallocFlag) {
        this->vtable = &PTR_VTABLE_EARSObject_base;  // 0x00d6102c, base vtable
        if (this->someMember != 0) {
            FUN_004daf90(this + 1);  // likely release or destruct owned object at offset +0x04
        }
        if ((deallocFlag & 1) != 0) {
            FUN_009c8eb0(this);  // custom deallocation (operator delete or pool free)
        }
        return this;
    }
};