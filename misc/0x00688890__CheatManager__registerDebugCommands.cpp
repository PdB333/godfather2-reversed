// FUNC_NAME: CheatManager::registerDebugCommands
// Address: 0x00688890
// Registers developer/release debug console commands: refillhealth, fullammo, unlockmovies, somemoney

// Forward declarations for external handler functions
typedef void (*CheatHandler)();

void CheatManager::registerDebugCommands() {
    // Bitmask for which commands have been registered
    static int s_debugCommandFlags = 0;
    
    // Console command manager singleton (offsets: +0x80 = command count, +0x84 = pointer array)
    struct ConsoleCommandManager {
        // ... other fields ...
        uint32_t commandCount;      // +0x80
        const void* commands[32];   // +0x84 (array of pointers to CheatCommandDef)
    };
    
    // Layout of a cheat command definition (size 0x14)
    struct CheatCommandDef {
        const char* name;           // +0x00
        int type;                   // +0x04 (1 = toggle? 2 = action?)
        CheatHandler handler;       // +0x08
        int flags;                  // +0x0C (0 normally)
        const char* description;    // +0x10
    };
    
    // Static command definitions
    static const CheatCommandDef cmd1 = {
        "refillhealth",
        2,
        reinterpret_cast<CheatHandler>(0x007aa6d0),
        0,
        reinterpret_cast<const char*>(0x00e5017c) // description string
    };
    
    static const CheatCommandDef cmd2 = {
        "fullammo",
        2,
        reinterpret_cast<CheatHandler>(0x007aa750),
        0,
        reinterpret_cast<const char*>(0x00e5016c)
    };
    
    static const CheatCommandDef cmd3 = {
        "unlockmovies",
        1,
        reinterpret_cast<CheatHandler>(0x00688820),
        0,
        reinterpret_cast<const char*>(0x00e5015c)
    };
    
    static const CheatCommandDef cmd4 = {
        "somemoney",
        2,
        reinterpret_cast<CheatHandler>(0x007aa800),
        0,
        reinterpret_cast<const char*>(0x00e5014c)
    };
    
    // Register command 1: refillhealth
    if ((s_debugCommandFlags & 1) == 0) {
        s_debugCommandFlags |= 1;
        ConsoleCommandManager* mgr = reinterpret_cast<ConsoleCommandManager*>(0x0040ede0()); // getCommandRegistry()
        if (mgr != nullptr && mgr->commandCount < 32) {
            mgr->commands[mgr->commandCount] = &cmd1;
            mgr->commandCount++;
        }
    }
    
    // Register command 2: fullammo
    if ((s_debugCommandFlags & 2) == 0) {
        s_debugCommandFlags |= 2;
        ConsoleCommandManager* mgr = reinterpret_cast<ConsoleCommandManager*>(0x0040ede0());
        if (mgr != nullptr && mgr->commandCount < 32) {
            mgr->commands[mgr->commandCount] = &cmd2;
            mgr->commandCount++;
        }
    }
    
    // Register command 3: unlockmovies
    if ((s_debugCommandFlags & 4) == 0) {
        s_debugCommandFlags |= 4;
        ConsoleCommandManager* mgr = reinterpret_cast<ConsoleCommandManager*>(0x0040ede0());
        if (mgr != nullptr && mgr->commandCount < 32) {
            mgr->commands[mgr->commandCount] = &cmd3;
            mgr->commandCount++;
        }
    }
    
    // Register command 4: somemoney
    if ((s_debugCommandFlags & 8) == 0) {
        s_debugCommandFlags |= 8;
        ConsoleCommandManager* mgr = reinterpret_cast<ConsoleCommandManager*>(0x0040ede0());
        if (mgr != nullptr && mgr->commandCount < 32) {
            mgr->commands[mgr->commandCount] = &cmd4;
            mgr->commandCount++;
        }
    }
}