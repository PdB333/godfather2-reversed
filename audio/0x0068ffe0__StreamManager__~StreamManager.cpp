// FUNC_NAME: StreamManager::~StreamManager
struct StreamManager {
    void** vtable;          // +0x00
    void* field_0x04;       // +0x04, pointer to first resource
    // +0x08, +0x0C unknown
    void* field_0x10;       // +0x10, pointer to second resource
};

// External deallocation function
extern void freeMemory(void* ptr);
// Global singleton pointer
extern StreamManager* g_pStreamManager;

void __fastcall StreamManager::~StreamManager()
{
    // Free allocated resources before closing
    if (this->field_0x10 != 0) {
        freeMemory(this->field_0x10);
    }
    if (this->field_0x04 != 0) {
        freeMemory(this->field_0x04);
    }
    // Reset vtable to base class (base destructor will follow)
    this->vtable = (void**)0x00d5c85c;
    // Clear the singleton reference
    g_pStreamManager = 0;
    return;
}