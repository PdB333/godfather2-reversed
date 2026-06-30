// FUN_004d9bd0: EngineManager::initialize

class EngineManager {
public:
    // Member variables (offsets inferred from decompilation)
    int m_initializedFlag;        // +0x?? (local_c)
    char* m_defaultPath;          // +0x?? (local_10)
    void (*m_cleanupFunc)(void*); // +0x?? (local_4)

    uint __thiscall initialize(uint* outHandle);
};

// External functions (placeholders – names derived from observed role)
extern void __cdecl initializeBase(EngineManager* thisPtr);       // FUN_004d3bc0
extern void __cdecl staticSystemInit(void);                      // FUN_004d54c0
extern uint __cdecl allocateHandle(int param);                    // FUN_004d5900
extern uint __cdecl processResource(const char* resourcePath);   // FUN_004dafd0

// Constant default resource string
static const char kDefaultResourcePath[] = "default_resource_path"; // DAT_0120546e

uint EngineManager::initialize(uint* outHandle) {
    uint handle;
    const char* path;

    // Step 1: Initialize base engine component
    initializeBase(this);

    // Step 2: Perform global system initialization
    staticSystemInit();

    // Step 3: Allocate a handle (parameter 1 indicates type/system)
    handle = allocateHandle(1);

    // If the object's flag indicates something is ready, process the resource
    if (this->m_initializedFlag != 0) {
        // Use the member path if set, otherwise fall back to default
        path = this->m_defaultPath;
        if (path == nullptr) {
            path = kDefaultResourcePath;
        }
        handle = processResource(path);
        *outHandle = handle;  // Store result into output parameter
    }

    // If a resource path was set, perform cleanup via callback
    if (this->m_defaultPath != nullptr) {
        this->m_cleanupFunc(this->m_defaultPath);
    }

    // Return the handle with the low byte masked off (likely a status/error code)
    return handle & 0xFFFFFF00u;
}