// Xbox PDB: EARS_Apt_UITutorials_OnShow
// FUNC_NAME: UIManager::setupCreateMenu

// Reconstructed C++ for function at 0x0098fc00
// Based on Ghidra decompile output

// Forward declarations for external functions
void __cdecl FUN_00408a00(TextInit* textData, int param2);
void __cdecl FUN_005a04a0(const char* command, int param2, void* param3, int param4);

// External global data
extern const char* DAT_01130918; // Some global string constant
extern void* DAT_00d91b68;       // Some global data (likely a function pointer or struct)

// Simple text initialization structure
struct TextInit {
    const char* text;  // +0x00: String pointer
    int length;        // +0x04: Length (or zero)
    int flags;         // +0x08: Flags
};

// Member function of UIManager (hypothesized class)
void __thiscall UIManager::setupCreateMenu()
{
    // Disable flag at offset 0x185 (maybe "ready" or "initialized")
    this->m_flag_0x185 = 0;

    // Prepare text init data from global string
    TextInit textInit;
    textInit.text = DAT_01130918;
    textInit.length = 0;
    textInit.flags = 0;

    // Call to initialize text (e.g., static text object)
    FUN_00408a00(&textInit, 0);

    // Enable flag at +0x184 (maybe menu active)
    this->m_flag_0x184 = 1;

    // Register the "CreateMenu" action/command
    FUN_005a04a0("CreateMenu", 0, &DAT_00d91b68, 0);

    // Clear flag at +0x186 (maybe menu visible state)
    this->m_flag_0x186 = 0;
}