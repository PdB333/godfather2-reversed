// FUNC_NAME: engineInitialize
// Function address: 0x00514af0
// Role: Initializes engine globals, calls virtual functions, sets up static state.

// Forward declarations for external functions
int __cdecl FUN_0060d740(int param);
extern void* DAT_0121b740; // VTable pointer (or pointer to object with function pointer array)
extern int DAT_012058ec; // Will be set to address of DAT_0121b740
extern int DAT_012058f8; // Reference/init count
extern int _DAT_0121b748; // Result of conversion
extern int _DAT_0121b74c; // Copy of init count
extern int DAT_00e2b1a4; // Default constant value (possibly 0 or -1)
extern int DAT_00e2eb58; // Another default constant
// Global fields being zeroed
extern int _DAT_012191e0;
extern int _DAT_012191e4;
extern int _DAT_012191e8;
extern int _DAT_012191ec;
extern int _DAT_012191f0;
extern int _DAT_012191f4;
extern int _DAT_012191f8;
extern int _DAT_012191fc;
extern int _DAT_0121920c;
extern int _DAT_0121921c;
extern int DAT_01219210;
extern int DAT_01219214;
extern int DAT_01219218;
extern int DAT_01219220;
extern int DAT_0121922c;
extern int DAT_01219224;
extern int DAT_01219228;
extern int DAT_01219230;
extern int DAT_01219240;

// Pointer to function pointer table (vtable)
typedef int (__stdcall *FuncPtr)(void);

void engineInitialize(void)
{
    int uVar1;
    FuncPtr* vtable;

    // Interpret DAT_0121b740 as a pointer to an array of function pointers
    vtable = (FuncPtr*)DAT_0121b740;

    // Call second vtable entry (offset 4) - likely a factory/constructor returning an object
    uVar1 = vtable[1]();
    // Convert the returned object using external function
    _DAT_0121b748 = FUN_0060d740(uVar1);

    // Call fifth vtable entry (offset 0x10)
    vtable[4]();

    // Set global pointer to the vtable pointer itself (address of DAT_0121b740)
    DAT_012058ec = (int)&DAT_0121b740;

    // Increment initialization counter
    DAT_012058f8 = DAT_012058f8 + 1;

    // Initialize several global fields to a default constant
    DAT_01219200 = DAT_00e2b1a4;
    DAT_01219204 = DAT_00e2b1a4;
    DAT_01219208 = DAT_00e2b1a4;

    // Set previously set pointer (now pointing to DAT_0121b740)
    DAT_012058ec = (int)&DAT_0121b740;

    // Store the current init count
    _DAT_0121b74c = DAT_012058f8;

    // Zero a block of 8 words (offsets 0x191e0 - 0x191fc)
    _DAT_012191ec = 0;
    _DAT_012191e8 = 0;
    _DAT_012191e4 = 0;
    _DAT_012191e0 = 0;
    _DAT_012191fc = 0;
    _DAT_012191f8 = 0;
    _DAT_012191f4 = 0;
    _DAT_012191f0 = 0;

    // Zero more globals
    _DAT_0121920c = 0;
    _DAT_0121921c = 0;
    DAT_01219218 = 0;
    DAT_01219214 = 0;
    DAT_01219210 = 0;
    DAT_01219220 = 0;
    DAT_0121922c = 0;

    // Set two globals to another constant
    DAT_01219224 = DAT_00e2eb58;
    DAT_01219228 = DAT_00e2eb58;

    // Zero remaining
    DAT_01219230 = 0;
    DAT_01219240 = 0;

    return;
}