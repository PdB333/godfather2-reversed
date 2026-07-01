// FUNC_NAME: SomeClass::~SomeClass
void __fastcall SomeClass::~SomeClass(SomeClass* this)
{
    // Set vtable pointer to derived class vtable (likely for cleanup)
    this->vtable = &PTR_FUN_00d7c768;

    // Check if member at offset 0x2C (m_pChild) is non-null
    if (this->m_pChild != nullptr) {
        // Call destructor for the child object
        sub_4df590();
    }

    // Get the child pointer again
    void* pChild = this->m_pChild;
    if (pChild != nullptr) {
        // Clear the vtable pointer of the child (offset 0x8)
        *(uint32_t*)((uint8_t*)pChild + 8) = 0;
        // Set the child pointer to null
        this->m_pChild = nullptr;
    }

    // Set vtable to base class vtable
    this->vtable = &PTR_LAB_00e315b0;

    // Call base class destructor
    BaseClass::~BaseClass();
}