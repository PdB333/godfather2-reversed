// FUNC_NAME: GameplayDebugger::initStage17
// Function address: 0x00932bb0
// Sets debug display stage to HUD_OVERLAY (17), clears a timer flag,
// and registers the main debug update callback if not already registered.

// External functions
extern void setDebugSubsystem();           // FUN_009823b0
extern void applyDebugConfig( int config ); // FUN_009c8eb0
extern void registerUpdateCallback( void* target, void* callback, int priority ); // FUN_005c0d50

// Globals (likely from GodfatherGameManager singleton)
extern int* g_pGameManager;           // DAT_01129928 (pointer to global manager instance)
extern int g_currentDebugStage;       // DAT_00e5672c (0x11 = 17 = HUD_OVERLAY)
extern int g_debugCallbackRegistered; // DAT_01130590 (bit 0)

// Callback function (address LAB_00931e00)
extern void debugTickUpdate();

void GameplayDebugger::initStage17( void* optionalConfig )
{
    // Apply optional initialisation if a config pointer is provided
    if ( optionalConfig != 0 )
    {
        setDebugSubsystem();
        applyDebugConfig( optionalConfig );
    }

    // Retrieve the global game manager pointer
    int* pManager = g_pGameManager;

    // Set current debug stage to 17 (HUD overlay / debug display)
    g_currentDebugStage = 0x11;

    // Clear the timer or state at offset +0x60 in the manager
    *( pManager + 0x60 / 4 ) = 0;   // offset 0x60, treat as int array

    // Register the debug update callback if not already registered
    if ( ( g_debugCallbackRegistered & 1 ) == 0 )
    {
        registerUpdateCallback( pManager + 0x14 / 4,  // offset +0x14 (likely a sub‑object)
                                &debugTickUpdate,
                                0 );                 // priority 0
        g_debugCallbackRegistered |= 1;
    }
}