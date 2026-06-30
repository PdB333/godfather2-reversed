// FUNC_NAME: Player::Player
// Function address: 0x006abdd0
// Role: Constructor for Player class (EARS engine). Sets up vtable, calls base initialization, and conditionally performs destruction if flag indicates heap allocation.

class Player {
public:
    // Vtable pointer at offset +0x00
    void** vtable;

    // Constructor: takes a flag byte (bit 0 indicates if this is a heap-allocated object requiring destruction on failure)
    // param_1 = this (ECX), param_2 = flags (byte)
    // Returns this pointer
    Player(byte flags) {
        // Set initial vtable to base class (maybe object or sentient)
        // PTR_FUN_00d5da74 corresponds to base class vtable
        this->vtable = &PTR_FUN_00d5da74;  // +0x00: Vtable for base class

        // Store a second vtable pointer? Possibly for derived class or second base
        // PTR_LAB_00d5da64 is a static address (maybe another vtable or static data)
        this->vtable[1] = &PTR_LAB_00d5da64;  // +0x04: Second vtable pointer? (or virtual base offset)

        // Call base class initializer with a global reference (DAT_012069c4)
        // FUN_004086d0 is likely the base class constructor (e.g., Sentient::Sentient)
        FUN_004086d0(&DAT_012069c4);  // Pass a global singleton or reference

        // Call another initialization function (e.g., Player::initCommon)
        FUN_004083d0();

        // Set final vtable pointer to the actual Player vtable
        // PTR_LAB_00d5da60 is the derived class vtable
        this->vtable = &PTR_LAB_00d5da60;  // +0x00: Overwritten with Player vtable

        // Global flag (DAT_01129900) set to 0 – likely a player initialization flag
        DAT_01129900 = 0;  // e.g., g_bPlayerInitialized = false

        // If the object was heap-allocated (flag bit 0 set), call cleanup/destroy function
        // FUN_009c8eb0 is likely a custom destructor or deallocation helper
        if ((flags & 1) != 0) {
            FUN_009c8eb0(this);  // Possibly delete this; or cleanup on failure?
        }

        return;  // implicit return of this
    }

private:
    // Internal function declarations (addresses known)
    void FUN_004086d0(void*);   // Base constructor
    void FUN_004083d0();        // Common initialization
    void FUN_009c8eb0(Player*); // Cleanup/destroy on heap allocation

    // Global variable (static)
    static int DAT_01129900;  // Player initialization flag

    // Static vtable pointers (defined elsewhere)
    static void* PTR_FUN_00d5da74;
    static void* PTR_LAB_00d5da64;
    static void* PTR_LAB_00d5da60;

    // The global object DAT_012069c4 is referenced but not stored here
};
```