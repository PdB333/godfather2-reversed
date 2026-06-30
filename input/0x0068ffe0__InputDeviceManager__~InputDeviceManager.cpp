// FUNC_NAME: InputDeviceManager::~InputDeviceManager
// Function address: 0x0068ffe0
// Destructor for InputDeviceManager, releases two resources and zeros global flag.

class InputDeviceManager {
public:
    // Virtual table pointer at offset 0x00
    // m_pResource1 at offset 0x04
    // m_pResource2 at offset 0x10
    
    void* m_pResource1; // +0x04
    void* m_pResource2; // +0x10

    void __thiscall ~InputDeviceManager() {
        // Release resources if they exist
        if (m_pResource2 != nullptr) {
            ReleaseResource(m_pResource2);
        }
        if (m_pResource1 != nullptr) {
            ReleaseResource(m_pResource1);
        }
        // Set vtable to a known base (purecall or default)
        this->vtable = &PTR_LAB_00d5c85c; // possibly base vtable
        // Clear global instance flag
        g_bInputDeviceManagerActive = false; // DAT_01129bb4
    }

private:
    void ReleaseResource(void* pResource); // FUN_009c8f10
};

// Global variable
extern bool g_bInputDeviceManagerActive; // 0x01129bb4
extern void* PTR_LAB_00d5c85c; // Vtable pointer