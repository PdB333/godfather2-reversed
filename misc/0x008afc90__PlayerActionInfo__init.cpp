// FUNC_NAME: PlayerActionInfo::init
// Address: 0x008afc90
// Initializes a PlayerActionInfo structure with action parameters and builds a flag mask from an array of action IDs.
// The lookup table at DAT_00d7a5c0 and DAT_00d7a5c4 maps 11 action IDs to their corresponding flag bits.
// Sentinels (0xbadbadba, etc.) are debug markers.

extern int kActionIdTable[11];  // DAT_00d7a5c0
extern int kActionFlagTable[11]; // DAT_00d7a5c4

void __thiscall PlayerActionInfo::init(
    int param2, int param3, int param4, int param5,
    int param7, int param8, int param9, int param10,
    int param11, int param12,
    uint actionCount, int* actionIds)
{
    // offset 0x00
    this->field_0 = param2;
    // offset 0x04
    this->field_4 = param3;
    // offset 0x08
    this->field_8 = param4;
    // offset 0x0C
    this->field_C = param5;

    // Sentinels for buffer overflow detection
    this->magic0 = 0xbadbadba;  // offset 0x10
    this->magic1 = 0xbeefbeef;  // offset 0x14
    this->magic2 = 0xeac15a55;  // offset 0x18
    this->magic3 = 0x91100911;  // offset 0x1C

    // Maximum number of action entries? (20 decimal)
    this->maxActionCount = 0x14; // offset 0x20

    // Action parameters
    this->actionParam1 = param7;  // offset 0x24
    this->actionParam2 = param8;  // offset 0x28
    this->actionParam3 = param9;  // offset 0x2C
    this->actionParam4 = param10; // offset 0x30
    this->actionParam5 = param11; // offset 0x34
    this->actionParam6 = param12; // offset 0x38

    // Active flag (always set to 1)
    this->isActive = 1; // offset 0x3C

    // Flags mask to be populated from action IDs
    this->actionFlags = 0; // offset 0x40

    if (actionCount != 0)
    {
        // For each action ID, look up and set the corresponding flag
        for (uint i = 0; i < actionCount; i++)
        {
            int id = actionIds[i];
            for (uint j = 0; j < 11; j++)
            {
                if (kActionIdTable[j] == id)
                {
                    this->actionFlags |= kActionFlagTable[j];
                    break;
                }
            }
        }
    }
}