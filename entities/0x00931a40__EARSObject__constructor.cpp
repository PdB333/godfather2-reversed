// FUNC_NAME: EARSObject::constructor
// Function at 0x00931a40
// Constructor for a base EARS object (Entity or similar).
// Takes a flag byte (bit 0 controls additional initialization).
uint32_t __thiscall EARSObject::constructor(uint32_t thisPtr, uint8_t flags) {
    // Call base class initialization (e.g., Entity::Entity)
    FUN_00930d60(); // Base constructor – clears/initializes core fields
    
    if ((flags & 1) != 0) {
        // If bit 0 is set, perform optional extended initialization
        // (e.g., allocate memory, set up subsystems)
        FUN_005c4480(thisPtr); // Additional init function
    }
    
    return thisPtr; // Return pointer to constructed object
}