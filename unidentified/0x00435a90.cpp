// FUN_00435A90: SomeClass::constructor
// Likely a base object constructor that performs standard initialization and optionally additional setup based on a flag.
class SomeClass
{
public:
    // Constructor: takes a flags byte to control optional initialization.
    // Returns this pointer.
    void* constructor(uint8_t flags);
private:
    // Internal initialization routines (callees)
    void defaultInit();           // Calls FUN_00435b70 - base setup (e.g., zero memory, set vtable)
    void optionalAdditionalInit(); // Calls FUN_009c8eb0 - extended init (e.g., allocate resources)
};

// Reconstructed implementation
void* SomeClass::constructor(uint8_t flags)
{
    // Always perform default initialization
    defaultInit();

    // If the lowest bit is set, perform additional initialization
    if (flags & 0x01)
    {
        optionalAdditionalInit();
    }

    return this;
}