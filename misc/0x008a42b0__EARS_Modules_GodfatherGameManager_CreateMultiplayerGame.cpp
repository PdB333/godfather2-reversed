// Xbox PDB: EARS_Modules_GodfatherGameManager_CreateMultiplayerGame
// FUNC_NAME: CApplication::Initialize
// Function address: 0x008a42b0
// Role: Initializes the game application window/display system.
// Sets up display mode, app name, command-line flags, and a self-referential linked list node.

void __thiscall CApplication::Initialize(void* config, int param3)
{
    // Local variables
    // local_314: array of 189 void pointers (likely output buffer for display mode enumeration)
    void* displayModeList[189];
    // local_1c = 4 (maybe screen resolution index or bit depth)
    int screenDepth = 4;
    // local_20 = 2 (maybe refresh rate or something)
    int refreshRate = 2;
    // local_c = 1 (maybe windowed flag)
    int windowedFlag = 1;
    // local_13: flag based on config byte at +0x4c
    char fullscreenFlag = (*(char*)((int)config + 0x4c) == 0) ? 1 : 0;  // +0x4c: fullscreen bool

    // Call engine initialization functions (names guessed based on context)
    // Likely named: setDisplayMode(deviceIndex, resolution)
    EngineSetDisplayMode(0, param3);   // FUN_00ad9f40(0, param_3)

    // Set window style (0 = windowed?)
    EngineSetWindowStyle(0);           // FUN_00ada270(0)

    // Set application name
    EngineSetAppName("Godfather2");    // FUN_00ad9ea0("Godfather2")

    // Set command-line flag for test play now
    EngineSetCommandLineFlag("GF2_TESTPLAYNOW"); // FUN_00ad9e20("GF2_TESTPLAYNOW")

    // Get something (e.g., window handle or device context) and pass to another init
    void* something = EngineGetSomething();  // FUN_00ad9f90
    EngineRegisterCallback(something);       // FUN_008a3530(uVar1)

    // Enumerate display modes into the output buffer
    EngineEnumerateDisplayModes(displayModeList); // FUN_00b22400(local_314)

    // Initialize self-referential linked list node at offsets +0x344 and +0x34c
    // +0x344: pointer to next node (points to &this[0x34c] initially)
    *(int*)(this + 0x344) = this + 0x34c;
    // +0x34c: likely start of node data (or another pointer)

    // Call another initialization (e.g., for input or sound)
    EngineSecondaryInit();  // FUN_00568360

    // Set function pointer table (vtable) for display mode list?
    displayModeList[0] = (void*)&VTable_DisplayModeFunctions;  // PTR_FUN_00e3a9cc

    // Finalize initialization (e.g., apply settings, show window)
    EngineFinalizeInit();   // FUN_00ad9db0

    return;
}