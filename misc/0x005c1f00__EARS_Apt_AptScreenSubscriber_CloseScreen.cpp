// Xbox PDB: EARS::Apt::AptScreenSubscriber::CloseScreen
// FUNC_NAME: UIScreen::processCloseFlag

// Method called to check and handle screen close request.
// This is likely a member of a UI screen class (EARS::Framework::UIScreen or similar).
// The 'this' pointer is passed via ECX (unaff_ESI in disassembly).
// Offsets:
//   +0x10: vtable pointer (array of function pointers)
//   +0x4a: flags (ushort), bit 2 (0x4) = close request pending

extern char g_screenIDBuffer[5]; // 4-byte big-endian screen ID + null terminator; globals at 0x01223564-0x01223568

void __thiscall UIScreen::processCloseFlag() {
    // Check if the close flag (bit 2) is set
    if ((this->flags & 0x4) != 0) {
        // Call virtual function at vtable index 1 (typically returns a 32-bit screen identifier / FourCC)
        // vtable is at *(this + 0x10), the second function is at vtable[1] (offset 4 bytes from vtable base)
        int screenID = this->vtable->getScreenID(); // simplified; actual call: (**(code **)(*(int *)(this + 0x10) + 4))()

        // Store the screen ID in big-endian order into the global buffer
        g_screenIDBuffer[0] = (screenID >> 24) & 0xFF;
        g_screenIDBuffer[1] = (screenID >> 16) & 0xFF;
        g_screenIDBuffer[2] = (screenID >> 8) & 0xFF;
        g_screenIDBuffer[3] = screenID & 0xFF;
        g_screenIDBuffer[4] = 0; // null terminator for string interpretation

        // Send the "CloseScreen" command with parameters:
        //   command name "CloseScreen" (likely a script/event name)
        //   arg1 = 0, arg2 = 0, arg3 = 1
        //   arg4 = pointer to the screen ID buffer (treated as a string)
        FUN_005a04a0("CloseScreen", 0, 0, 1, g_screenIDBuffer);

        // Clear the close flag
        this->flags &= ~0x4;
    }
}