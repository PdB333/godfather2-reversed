// FUNC_NAME: DebugConsole::processInputAction

// Reconstructed C++ function from Ghidra decompilation at 0x00981b80
// Handles input actions (arrow keys, enter, etc.) for a debug console or UI text input.

// Offsets for the DebugConsole object (this pointer):
// +0x64: field_0x64 (int) - flag indicating console active?
// +0x6C: field_0x6C (int) - some state
// +0x104: field_0x104 (int) - state3
// +0x108: field_0x108 (int) - state4
// +0x128: field_0x128 (char) - command/edit mode flag? (0x12a = 0x128 + 2? Actually offset 0x12a is a byte, so it's at this + 0x12a)
// +0x12A: field_0x12A (char) - edit/command mode flag

// External functions (forward declarations)
extern int __fastcall getInputSourceA();     // FUN_00466840
extern int __fastcall getInputSourceB();     // FUN_00466860
extern void __fastcall consoleMoveLeft();    // FUN_00981a20
extern void __fastcall consoleMoveRight();   // FUN_00981b20
extern void __fastcall consoleMoveUp();      // FUN_009819d0
extern void __fastcall consoleSubmitAction(int param); // FUN_00980510
extern void __fastcall consoleTabAction();   // FUN_009811b0
extern void __fastcall logInputAction(const char* action, int* data1, int* data2, int* data3); // FUN_00929a20
extern void __fastcall resetGlobalFlag(int* global, int value); // FUN_00402050
extern void __fastcall setupLocalFlag(void* local, int value);  // FUN_00408a00

// Global data (likely pointers or structures)
extern int gDAT_011302c0;   // some global UI state
extern int gDAT_011302e8;   // another global
extern int gDAT_011304d8;   // horizontal data
extern int gDAT_011301c0;   // vertical data
extern int gDAT_011302c8;   // another global
extern int gDAT_00d8fe44;   // some string/data

int __thiscall DebugConsole::processInputAction(int param_2)
{
    int result = 0;
    int inputA;
    int inputB;

    // If console is inactive, return success (1)
    if (this->field_0x64 == 0)
    {
        return 1;
    }

    inputA = getInputSourceA();
    if (param_2 == inputA)
    {
        // First input source action handling
        if ((this->field_0x6C == -1) || (this->field_0x104 != 3) ||
            ((this->field_0x108 != 1) && (this->field_0x108 != 8)))
        {
            // Default case: clear local flag with global
            setupLocalFlag(&gDAT_011302c0, 0);
            return 0;
        }

        // Check edit mode flag (byte at +0x12A)
        if (this->field_0x12A != 0)
        {
            consoleMoveLeft();
            resetGlobalFlag(&gDAT_011302e8, 0);
            return 0;
        }

        if (this->field_0x108 == 8)
        {
            consoleMoveRight();
            resetGlobalFlag(&gDAT_011302e8, 0);
            return 0;
        }

        consoleMoveUp();
        resetGlobalFlag(&gDAT_011302e8, 0);
        return 0;
    }

    inputB = getInputSourceB();
    if (param_2 == inputB)
    {
        // Second input source action handling
        if (this->field_0x12A != 0)
        {
            consoleSubmitAction(0);
            return 0;
        }

        // Call virtual function (likely enter action)
        (this->vtable[0x2c])();
        return 0;
    }

    // Switch on other action IDs (map to keyboard)
    switch (param_2)
    {
    case 0: // Enter/confirm?
        if (this->field_0x12A != 0)
        {
            consoleSubmitAction(1);
            return 0;
        }
        // Fall through to default return 1
        return 1;

    case 6: // Left arrow
        logInputAction("MoveLeft", &gDAT_00d8fe44, &gDAT_011304d8, &gDAT_011302c0);
        return 0;

    case 7: // Right arrow
        logInputAction("MoveRight", &gDAT_00d8fe44, &gDAT_011304d8, &gDAT_011302c0);
        return 0;

    case 8: // Up arrow
        logInputAction("MoveUp", &gDAT_00d8fe44, &gDAT_011301c0, &gDAT_011302c0);
        return 0;

    case 9: // Down arrow
        logInputAction("MoveDown", &gDAT_00d8fe44, &gDAT_011301c0, &gDAT_011302c0);
        return 0;

    case 10: // Tab/switch
        if (this->field_0x12A != 0)
        {
            consoleTabAction();
            resetGlobalFlag(&gDAT_011302c8, 0);
        }
        return 0;

    default:
        return result; // 0
    }
}