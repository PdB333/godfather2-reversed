// FUNC_NAME: BaseClass::constructor (calls FUN_008a1340 as base init)
class BaseClass {
public:
    virtual ~BaseClass(); // vtable at +0
    // +0x00: vtable pointer
    // +0x3C: pointer to some table (PTR_LAB_00d7ae64)
    // +0x48: pointer to some table (PTR_LAB_00d7ae60)
    // +0x58: int field (set to 0x1d = 29)
    void* fieldAt0x3C;
    void* fieldAt0x48;
    int fieldAt0x58;
};

BaseClass* __thiscall BaseClass::constructor(BaseClass* this, int param2) {
    // Call base class constructor with param2
    FUN_008a1340(param2); // likely base init
    
    // Set vtable for this class
    *reinterpret_cast<void**>(this) = &PTR_FUN_00d7ae74;
    
    // Initialize other virtual table pointers (for multiple inheritance or interfaces)
    this->fieldAt0x3C = &PTR_LAB_00d7ae64; // +0x3C, possibly interface vtable
    this->fieldAt0x48 = &PTR_LAB_00d7ae60; // +0x48, another interface vtable
    
    // Set a type/size field to 0x1d (29)
    this->fieldAt0x58 = 0x1d; // +0x58, likely a type enum or size constant
    
    return this;
}