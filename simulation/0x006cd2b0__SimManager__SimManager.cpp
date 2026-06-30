// FUNC_NAME: SimManager::SimManager
// Function address: 0x006cd2b0
// Role: Constructor for SimManager class, initializes all fields to zero, sets vtable, and seeds random number generator once.

class SimManager : public SomeBaseClass {
public:
    // Vtable pointer at +0x00
    // Some base class pointer at +0x08 (based on param_1[2])
    // Fields from +0xC0 to +0x16C (indices 0x30 to 0x5b) are mostly zeroed except +0xD8 and +0xDC

    // Constructor
    SimManager(void* managerParent) {
        // Call base class constructor with managerParent and a global singleton
        BaseClassConstructor(managerParent, g_globalManager); // FUN_006c9760

        // Set vtable pointers (multiple inheritance)
        this->vtable = &s_vtable1;      // +0x00
        this->baseVtable = &s_vtable2;  // +0x08 (param_1[2])

        // Clear large block of fields (indices 0x30 to 0x58, except 0x36 and 0x37)
        // These are likely arrays of 3-element structs (e.g., positions)
        for (int i = 0x30; i <= 0x35; i++) { this->field[i] = 0; }
        for (int i = 0x38; i <= 0x58; i++) { this->field[i] = 0; }

        // Set specific values
        this->field[0x36] = s_constantValue;    // +0xD8
        this->field[0x37] = 0x21;               // +0xDC (possibly version/count)

        // Clear fields after the block (indices 0x59 to 0x5b)
        this->field[0x59] = 0;
        this->field[0x5a] = 0;
        this->field[0x5b] = 0;

        // Static counter for seeding random number generator
        static int s_constructorCount = g_constructorCount + 1;
        bool firstConstructor = (g_constructorCount == 0);
        g_constructorCount = s_constructorCount;

        if (firstConstructor) {
            // Seed the random number generator with a time-based seed
            TimeSeed seed; // local_c
            seed.high = g_randomSeedSource; // DAT_0112a814
            seed.low = 0;
            seed.unused = 0;
            SeedRandomGenerator(&seed, 0); // FUN_00408a00
        }
    }
};