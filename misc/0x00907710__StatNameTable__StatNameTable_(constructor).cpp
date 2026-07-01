// FUNC_NAME: StatNameTable::StatNameTable (constructor)
// Address: 0x00907710
// Role: Constructor for the multiplayer stat name lookup table. Allocates and initializes an array of 45 stat name strings.

class StatNameTable {
public:
    // Vtable pointer (0x00)
    void* vtable;

    // Pointer to array of stat name strings (offset +0x04)
    char** statNames;

    // Constructor
    StatNameTable() {
        // Store this instance globally
        gStatNameTableInstance = this;

        // Set vtable to known function table at 0x00d82d2c
        this->vtable = &PTR_FUN_00d82d2c;

        // Set initial count? (offset +0x08) - stored as 4, possibly number of derived stats or version
        this->statNames[2] = (char*)4; // note: statNames[2] is actually *(this+0x08)

        // Allocate memory for 45 string pointers (0xB4 = 180 bytes)
        this->statNames = (char**)FUN_009c8e80(0xB4); // custom allocator

        // Initialize the string pointer array
        this->statNames[0]  = "MP_TOTAL_TIME_PLAYED";
        this->statNames[1]  = "MP_TOTAL_DEATHS";
        this->statNames[2]  = "MP_TOTAL_KILLS";
        this->statNames[3]  = "MP_TOTAL_EXECUTIONS";
        this->statNames[4]  = "MP_TOTAL_HEADSHOTS";
        this->statNames[5]  = "MP_TOTAL_SUICIDES";
        this->statNames[6]  = "MP_TOTAL_TEAM_KILLS";
        this->statNames[7]  = "MP_TOTAL_ASSISTS";
        this->statNames[8]  = "DERIVED_MP_OVERALL_KILLS";
        this->statNames[9]  = "DERIVED_MP_KILL_DEATH_RATIO";
        this->statNames[10] = "MP_TOTAL_HEALS";
        this->statNames[11] = "MP_TOTAL_SAFES_CRACKED";
        this->statNames[12] = "MP_TOTAL_FIRES_STARTED";
        this->statNames[13] = "MP_TOTAL_FENCES_CUT";
        this->statNames[14] = "MP_TOTAL_WALLS_DESTROYED";
        this->statNames[15] = "MP_TOTAL_BRUISER_KILLS";
        this->statNames[16] = "MP_TOTAL_MEDIC_GADGETS_CAPTURED";
        this->statNames[17] = "MP_TOTAL_CAMERAS_CAPTURED";
        this->statNames[18] = "MP_TOTAL_DEMO_GADGETS_CAPTURED";
        this->statNames[19] = "MP_TOTAL_BRUISER_GADGETS_CAPTURED";
        this->statNames[20] = "DERIVED_MP_TOTAL_GADGETS_CAPTURED";
        this->statNames[21] = "DERIVED_MP_TOTAL_DEMO_EARNINGS";
        this->statNames[22] = "DERIVED_MP_TOTAL_ENGINEER_EARNINGS";
        this->statNames[23] = "DERIVED_MP_TOTAL_MEDIC_EARNINGS";
        this->statNames[24] = "DERIVED_MP_TOTAL_BRUISER_EARNINGS";
        this->statNames[25] = "MP_TOTAL_OF_RATINGS_AS_DON";
        this->statNames[26] = "MP_TOTAL_TIMES_RATED";
        this->statNames[27] = "MP_TOTAL_WINS_AS_DON";
        this->statNames[28] = "MP_TOTAL_LOSSES_AS_DON";
        this->statNames[29] = "MP_TOTAL_WINS";
        this->statNames[30] = "MP_TOTAL_LOSSES";
        this->statNames[31] = "DERIVED_MP_TOTAL_GAMES";
        this->statNames[32] = "MP_TOTAL_EARNINGS";
        this->statNames[33] = "MP_WINS_DM";
        this->statNames[34] = "MP_LOSSES_DM";
        this->statNames[35] = "MP_EARNINGS_DM";
        this->statNames[36] = "MP_WINS_FS";
        this->statNames[37] = "MP_LOSSES_FS";
        this->statNames[38] = "MP_EARNINGS_FS";
        this->statNames[39] = "MP_WINS_SC";
        this->statNames[40] = "MP_LOSSES_SC";
        this->statNames[41] = "MP_EARNINGS_SC";
        this->statNames[42] = "MP_WINS_DA";
        this->statNames[43] = "MP_LOSSES_DA";
        this->statNames[44] = "MP_EARNINGS_DA";
    }
};

// Global singleton pointer (address 0x01129888)
StatNameTable* gStatNameTableInstance;