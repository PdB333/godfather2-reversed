// FUNC_NAME: AssetLoader::processPathOrReset
// Address: 0x004d5b50
// This function appears to process an asset file path (with optional extension extraction)
// and either load it or reset internal state based on a flag at offset +0x04.

#include <cstring> // for strchr

class AssetLoader {
public:
    char* m_path;      // +0x00: path string
    void* m_loadedFlag; // +0x04: non-zero indicates something is loaded
    // Fields +0x08, +0x0C are zeroed in the reset branch
    // Additional fields might hold function pointers for cleanup (m_cleanup1, m_cleanup2 at +0x10, +0x14)

    // __thiscall, this in EAX
    void processPathOrReset() {
        // Local variables, probably allocated on stack
        char* pathComponents[3]; // local_20: e.g., base name, extension, etc.
        void (*cleanup1)(char*); // local_14: function pointer for cleanup
        char* extension;         // local_10: pointer to extension string
        int hasDot;              // local_c: flag for dot existence
        void (*cleanup2)(char*); // local_4: another function pointer

        if (this->m_loadedFlag != 0) {
            // Existing asset: process the path
            FUN_004d3bc0(this->m_path);                     // Handle base path
            FUN_004d5900(1);                                 // Set some global flag

            char* dotPos = strchr(pathComponents[0], '.');   // Look for dot in base component
            if (dotPos == nullptr) {
                FUN_004d3b50(pathComponents);                // No extension, process as is
            } else {
                FUN_004d4ee0(&extension);                    // Extract extension part
                char** target = (hasDot == 0) ? pathComponents : &extension;
                FUN_004d3b50(target);                        // Process the chosen component
                if (extension != nullptr) {
                    cleanup2(extension);                     // Cleanup extension if needed
                }
            }
            if (pathComponents[0] != nullptr) {
                cleanup1(pathComponents[0]);                 // Cleanup base component
            }
        } else {
            // Reset object: zero out first four fields
            this->m_path = nullptr;       // *this = 0
            this->m_loadedFlag = nullptr; // *(this+4) = 0
            // Also zero unknown fields at +0x08 and +0x0C
            *(int*)((char*)this + 8) = 0;
            *(int*)((char*)this + 12) = 0;
        }
    }

private:
    // Forward declarations of called helper functions (likely in the same module)
    void FUN_004d3bc0(char* base);
    void FUN_004d5900(int val);
    void FUN_004d3b50(char** strPtr);
    void FUN_004d4ee0(char** outExt);
};