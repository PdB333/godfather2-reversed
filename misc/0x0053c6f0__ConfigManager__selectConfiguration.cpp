// FUNC_NAME: ConfigManager::selectConfiguration
// Address: 0x0053c6f0
// Role: Selects a configuration preset (by ID) and sets up global pointers and tables.
// The function releases old configuration if current config pointer matches a base address,
// then finds entries in two configuration tables for the new preset.

void ConfigManager::selectConfiguration(unsigned int configId)
{
    // Global configuration data pointers (offsets from some base)
    static int* selectedData1 = &DAT_0121bc24;   // +0x00
    static int* selectedData2 = &DAT_0121bc20;   // +0x04
    static char* selectedEntry1 = &DAT_0121be7c; // +0x5C? (pointer to entry in table)
    static char* selectedEntry2 = &DAT_0121bcd8; // +0x38? (pointer to entry)

    // Base pointer for current config (e.g., active config object)
    static int* currentConfigPtr = &DAT_012058e8;
    static int* configBaseAddr = &DAT_0121bc10; // base of config block

    // Table of possible config values (13 entries, each 4 bytes?)
    static int* configTable1[13] = { &PTR_DAT_010beba0 }; // actually an array of ints
    // Table of secondary config values (3 entries)
    static int* configTable2[3] = { &PTR_DAT_010bebd4 };

    // Lookup values (these are the actual IDs or pointers to selected config data)
    int lookupValue1 = 0;
    int lookupValue2 = 0;

    // Set lookup values based on configId
    switch (configId)
    {
    case 0:
        lookupValue1 = DAT_01198e54; // some global
        lookupValue2 = DAT_01219900; // default from goto
        break;
    case 1:
        lookupValue1 = DAT_0121990c;
        lookupValue2 = DAT_01219900;
        break;
    case 2:
        lookupValue1 = DAT_01198e4c;
        lookupValue2 = DAT_01219900;
        break;
    case 3:
        lookupValue1 = DAT_01198e70;
        lookupValue2 = DAT_01198e48;
        break;
    case 4:
        lookupValue1 = DAT_01198e64;
        lookupValue2 = DAT_01198e74;
        break;
    case 5:
        lookupValue1 = DAT_01198e68;
        lookupValue2 = DAT_01198e48;
        break;
    case 6:
        lookupValue1 = DAT_01198e50;
        lookupValue2 = DAT_01198e48;
        break;
    case 7:
        lookupValue1 = DAT_01198e58;
        lookupValue2 = DAT_01198e48;
        break;
    case 8:
        lookupValue1 = DAT_01198e78;
        lookupValue2 = DAT_01198e74;
        break;
    case 9:
        lookupValue1 = DAT_01198e6c;
        lookupValue2 = DAT_01198e48;
        break;
    case 10:
        lookupValue1 = DAT_01198e60;
        lookupValue2 = DAT_01198e48;
        break;
    case 11:
        lookupValue1 = DAT_01194d04;
        lookupValue2 = DAT_01219900;
        break;
    case 12:
        lookupValue1 = DAT_01198e5c;
        lookupValue2 = DAT_01219900;
        break;
    default:
        // Should not happen? But maybe default does nothing.
        break;
    }

    // If the current config pointer equals the base address of config block,
    // release the old resources (assuming FUN_0060a460 is a release/decrement)
    if (*currentConfigPtr == (int)configBaseAddr)
    {
        FUN_0060a460(lookupValue1);
        FUN_0060a460(lookupValue2);
    }

    // Search through configTable1 (13 entries) for the first value
    unsigned int i = 0;
    do {
        if (configTable1[i] == lookupValue1) {
            *selectedEntry1 = (char*)(&DAT_0121bcdc + i * 0x20); // offset into a 0x20-byte table
            break;
        }
        i++;
    } while (i < 13);

    // Search through configTable2 (3 entries) for the second value
    i = 0;
    do {
        if (configTable2[i] == lookupValue2) {
            *selectedEntry2 = (char*)(0x121bcb4 + i * 0xc); // offset into a 0xc-byte table
            return;
        }
        i++;
    } while (i < 3);
}