// FUNC_NAME: SomeClass::~SomeClass
// Address: 0x0078a6a0
// Destructor for an unknown class.  
// param_1: this pointer  
// param_2: flags (bit 0 indicates deletion)

class SomeSubObject; // unknown, defined elsewhere

class SomeClass {
public:
    void** vtable;                 // +0x00
    SomeSubObject* m_pSubObject;   // +0x04 (nullable)
};

// Forward declarations of called functions
void __thiscall subObjectDestructor(SomeSubObject* pObj);  // FUN_004daf90
void __cdecl operatorDelete(void* ptr);                    // FUN_009c8eb0

void __thiscall SomeClass::~SomeClass(SomeClass* this, byte flags) {
    if (this->m_pSubObject != nullptr) {
        subObjectDestructor(this->m_pSubObject);  // destroy sub-object
    }
    
    // Set vtable to base class vtable (or null vtable)
    this->vtable = (void**)&PTR_LAB_00e2f0c0;   // external vtable label
    
    if ((flags & 1) != 0) {
        operatorDelete(this);  // free memory
    }
}