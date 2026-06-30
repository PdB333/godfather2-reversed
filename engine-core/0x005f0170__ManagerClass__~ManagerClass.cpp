// FUNC_NAME: ManagerClass::~ManagerClass
class ManagerClass {
public:
    // Scalar deleting destructor (byte flag for delete)
    virtual ~ManagerClass(byte shouldDelete) {
        // Set vtable pointer to class-specific vtable (first)
        *(void**)this = &PTR_FUN_00e3fd80;

        // Release sub-object at offset 0x93 (0x24c bytes from this)
        if (this->m_pSubObject != nullptr) {
            destroySubObject(this->m_pSubObject); // FUN_009c8f10
        }

        // Set vtable pointer to base class vtable (second)
        *(void**)this = &PTR_LAB_00e3fd84;

        // Reset global manager state counter
        g_managerCounter = 0; // DAT_01223514

        // If requested, free the memory (scalar delete)
        if ((shouldDelete & 1) != 0) {
            operatorDelete(this); // FUN_009c8eb0
        }
    }

private:
    void* m_pSubObject; // +0x93 (offset 0x24c from this)
};

// Global variable (likely a reference count or active instance flag)
int g_managerCounter = 0; // DAT_01223514

// Hypothetical helper functions (placeholders for actual implementations)
void destroySubObject(void* obj); // FUN_009c8f10
void operatorDelete(void* ptr);   // FUN_009c8eb0