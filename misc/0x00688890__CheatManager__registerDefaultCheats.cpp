// FUNC_NAME: CheatManager::registerDefaultCheats
// Address: 0x00688890
// Registers built-in cheat commands (refillhealth, fullammo, unlockmovies, somemoney) into the cheat registry.

struct CheatCommand {
    const char* name;       // +0x00
    int type;               // +0x04 - likely command type (e.g., 1=toggle, 2=action)
    void (*handler)();      // +0x08 - callback function
    int unk;                // +0x0C
    const char* description; // +0x10
};

// Global pointer used by the cheat registry system (FUN_0040ede0 returns this)
static int* g_cheatRegistry = nullptr; // placeholder for _DAT_01129a28? Actually _DAT_01129a28 is a bitmask

// These globals are the actual allocated command structures (static storage)
static int _DAT_01129a28; // bitmask: 1=refillhealth,2=fullammo,4=unlockmovies,8=somemoney

void FUN_0040ede0(); // returns a pointer to a struct with an array at +0x80

void CheatManager::registerDefaultCheats()
{
    // Register "refillhealth" (bit 0)
    if ((_DAT_01129a28 & 1) == 0) {
        _DAT_01129a28 |= 1;
        // Setup static command structure (addresses correspond to global data)
        static CheatCommand refillCmd = {
            "refillhealth",  // name
            2,               // type (some category)
            (void (*)())0x007aa6d0, // handler function
            0,               // unknown
            (const char*)0x00e5017c // description string
        };
        int* registry = (int*)FUN_0040ede0();
        if (*(unsigned int*)(registry + 0x80/4) < 0x20) {
            *(void**)((char*)registry + *(unsigned int*)(registry + 0x80/4) * 4) = &refillCmd;
            (*(int*)((char*)registry + 0x80))++;
        }
    }

    // Register "fullammo" (bit 1)
    if ((_DAT_01129a28 & 2) == 0) {
        _DAT_01129a28 |= 2;
        static CheatCommand fullAmmoCmd = {
            "fullammo",
            2,
            (void (*)())0x007aa750,
            0,
            (const char*)0x00e5016c
        };
        int* registry = (int*)FUN_0040ede0();
        if (*(unsigned int*)(registry + 0x80/4) < 0x20) {
            *(void**)((char*)registry + *(unsigned int*)(registry + 0x80/4) * 4) = &fullAmmoCmd;
            (*(int*)((char*)registry + 0x80))++;
        }
    }

    // Register "unlockmovies" (bit 2)
    if ((_DAT_01129a28 & 4) == 0) {
        _DAT_01129a28 |= 4;
        static CheatCommand unlockMoviesCmd = {
            "unlockmovies",
            1,
            (void (*)())0x00688820, // handler likely a smaller function
            0,
            (const char*)0x00e5015c
        };
        int* registry = (int*)FUN_0040ede0();
        if (*(unsigned int*)(registry + 0x80/4) < 0x20) {
            *(void**)((char*)registry + *(unsigned int*)(registry + 0x80/4) * 4) = &unlockMoviesCmd;
            (*(int*)((char*)registry + 0x80))++;
        }
    }

    // Register "somemoney" (bit 3)
    if ((_DAT_01129a28 & 8) == 0) {
        _DAT_01129a28 |= 8;
        static CheatCommand someMoneyCmd = {
            "somemoney",
            2,
            (void (*)())0x007aa800,
            0,
            (const char*)0x00e5014c
        };
        int* registry = (int*)FUN_0040ede0();
        if (*(unsigned int*)(registry + 0x80/4) < 0x20) {
            *(void**)((char*)registry + *(unsigned int*)(registry + 0x80/4) * 4) = &someMoneyCmd;
            (*(int*)((char*)registry + 0x80))++;
        }
    }
}