// FUNC_NAME: Presentation::updateMainLoop
// Function address: 0x008A3F50
// Role: Updates the main loop state for the frontend menu.
// It checks if the current game state is "FrontendMainLoop" and if the presentation
// flags indicate the frontend is active, then processes input. Also handles a
// frontend renderer object with a flag at this+0x36C.

// Global pointers (from Ghidra symbols)
extern void* g_stateManager;          // DAT_0112980c - points to a state manager structure (offset +4 stores current state ID)
extern Presentation* g_presentation;  // DAT_01129930 - global presentation instance (likely singleton)
extern FrontendRenderer* g_frontendRenderer; // DAT_0112ebb0 - a renderer/manager object (vtable-based)

// Forward declarations of called functions
extern void simTick();                              // FUN_004bf3b0
extern int getStateIdFromString(const char* name);  // FUN_00683280 + FUN_006833d0 combined
extern void processFrontendInput();                 // FUN_00970700
extern void setBlockInput(bool block);              // FUN_00454310

class Presentation {
public:
    void updateMainLoop();

private:
    // Member at offset +0x36C (unknown type; treated as int)
    int m_frontendFlag; // +0x36C - if non-zero, block input is cleared
};

void Presentation::updateMainLoop()
{
    // Call the simulation tick
    simTick();

    // Get the ID for the "FrontendMainLoop" state
    int loopStateId = getStateIdFromString("FrontendMainLoop");

    // Retrieve current state from global state manager
    int currentState = *(int*)((char*)g_stateManager + 4);

    // Check if we are in the frontend main loop and the presentation is active
    if (loopStateId == currentState &&
        g_presentation != nullptr &&
        *(char*)&g_presentation->m_flag48 != '\0' &&                   // +0x48: bool (e.g., m_isActive)
        (*(unsigned char*)&g_presentation->m_flag49 & 0x0A) == 0)     // +0x49: byte flags (bit1 and bit3 must be 0)
    {
        processFrontendInput();
    }

    // If the global frontend renderer exists
    if (g_frontendRenderer != nullptr)
    {
        // Check the this pointer's flag at +0x36C
        if (this->m_frontendFlag != 0)
        {
            setBlockInput(false);  // unblock input
        }

        if (g_frontendRenderer != nullptr)
        {
            // Call the second virtual function (index 1) with argument 1
            // This is likely an update or render function
            g_frontendRenderer->vtable->functionAtIndex1(1);
        }
    }
}