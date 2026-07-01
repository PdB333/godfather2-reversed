// Xbox PDB: EARS_Apt_UIOnlineMenu_PrintJoinGameData
// FUNC_NAME: NetSession::initializeFromConfig
void __thiscall NetSession::initializeFromConfig(SessionConfig* config)
{
    // Copy config data to local buffer (0x7c = 124 bytes, 31 uint32s)
    uint32_t localConfig[31];
    memcpy(localConfig, config, sizeof(localConfig));

    // Reset global session list
    g_sessionCount = 0;
    if (g_sessionList) {
        // Cleanup existing session list (likely destructor)
        FUN_009c8f10(g_sessionList);
    }
    g_sessionList = nullptr;
    g_sessionCapacity = 0;

    // If global manager exists, iterate over items and build session list
    bool hasItems = false;
    if (g_someManager != 0) {
        uint32_t itemIndex = 0;
        char result = FUN_0095c8c0(localConfig[0x1b], &itemIndex); // local_6c is localConfig[0x1b]? Actually local_6c is at offset 0x6c from local_7c, which is localConfig[0x1b] (since 0x6c/4=0x1b)
        if (result != 0) {
            uint32_t itemCount = 0;
            if (itemIndex < *(uint32_t*)(g_someManager + 8)) {
                int* itemArray = *(int**)(g_someManager + 4);
                if (itemArray[itemIndex] != 0) {
                    itemCount = *(uint32_t*)(itemArray[itemIndex] + 8);
                }
            }
            uint32_t i = 0;
            if (itemCount != 0) {
                do {
                    int* itemData = nullptr;
                    if (itemIndex < *(uint32_t*)(g_someManager + 8)) {
                        int* itemArray = *(int**)(g_someManager + 4);
                        if (itemArray[itemIndex] != 0) {
                            itemData = *(int**)(itemArray[itemIndex] + 4) + i * 4;
                        }
                    }
                    // Get a 64-bit value from item data (offset 0x17c and 0x180)
                    uint64_t value = FUN_0095c290(itemData + 0x17c, itemData + 0x180);
                    // Add to session list (dynamic array)
                    if (g_sessionCount == g_sessionCapacity) {
                        int newCapacity = (g_sessionCapacity == 0) ? 1 : g_sessionCapacity * 2;
                        FUN_0095c7f0(newCapacity); // Resize array
                    }
                    uint64_t* dest = (uint64_t*)(g_sessionList + g_sessionCount * 8);
                    g_sessionCount++;
                    if (dest != nullptr) {
                        *dest = value;
                    }
                    i++;
                } while (i < itemCount);
            }
            hasItems = true;
        }
    }

    // Reset internal state
    *(uint32_t*)(this + 0x108) = 0; // +0x108: some flag
    FUN_0095f8b0(*(uint32_t*)(this + 0x150), 0); // +0x150: some object
    FUN_0095c450(*(uint32_t*)(this + 0xec)); // +0xec: some object

    if (hasItems) {
        // Initialize various subsystems with config data
        FUN_0095d020(*(uint32_t*)(this + 0xf0)); // +0xf0
        *(uint32_t*)(this + 0xf4) = config[0x26]; // +0xf4: some parameter
        FUN_0095cf80(*(uint32_t*)(this + 0x158)); // +0x158
        *(uint32_t*)(this + 0xf8) = config[0x22]; // +0xf8: some parameter
        FUN_0095c4c0(this + 0x148); // +0x148
        FUN_0095c4d0(this + 0x14c); // +0x14c
        FUN_0095c4f0(*(uint32_t*)(this + 0x128)); // +0x128
        FUN_0095cda0(*(uint32_t*)(this + 0xfc)); // +0xfc
        FUN_0095ccb0(*(uint32_t*)(this + 0x100)); // +0x100
        FUN_0095ccf0(*(uint32_t*)(this + 0x104)); // +0x104
        FUN_0095c490(*(uint32_t*)(this + 0x154)); // +0x154
        *(uint8_t*)(this + 0x160) = *(uint8_t*)(config + 0x13); // +0x160: byte flag
        FUN_0095ce10(*(uint32_t*)(this + 0xe4)); // +0xe4
        FUN_0095fa80(*(uint32_t*)(this + 0xe8)); // +0xe8
        FUN_0095c310(*(uint32_t*)(this + 0x138)); // +0x138
        FUN_0095c2e0(*(uint32_t*)(this + 0x13c)); // +0x13c
        FUN_0095f980(*(uint32_t*)(this + 300)); // +0x12c (300 decimal = 0x12c)
        FUN_0095f9e0(*(uint32_t*)(this + 0x130)); // +0x130
        FUN_0095cb00(*(uint32_t*)(this + 0x120)); // +0x120
        FUN_0095c340(*(uint32_t*)(this + 0x16c)); // +0x16c
        int result = FUN_00964d50(*(uint32_t*)(this + 0x16c)); // +0x16c
        *(bool*)(this + 0x170) = (result == 0); // +0x170: boolean flag
        FUN_0095cc00(*(uint32_t*)(this + 0x15c)); // +0x15c
    }

    // Log or register the join server event
    FUN_005a04a0("AddJoinServer", 0, &DAT_00d8cdec, 0);
}