// FUNC_NAME: EARSObject::constructor
// Function address: 0x00453390
// Role: Constructor for EARSObject. Sets vtable, calls base class constructor,
// and optionally performs post-construction initialization if bit 0 of flags is set.
// param_2 = flags (byte): bit 0 controls additional setup (e.g., registration).

class EARSObjectBase; // Forward declaration for base class constructor

class EARSObject {
public:
    // +0x00: vtable pointer (set to 0x00e31864)
    void* vtable;

    // Constructor with optional post-init
    __thiscall EARSObject* constructor(byte flags) {
        // Set vtable to the class-specific virtual table (offset 0x00e31864)
        this->vtable = reinterpret_cast<void*>(0x00e31864);

        // Call base class constructor (likely EARSObjectBase or similar)
        // FUN_0064d5b0 is the base constructor (e.g., EARSObjectBase::EARSObjectBase)
        FUN_0064d5b0(this);

        // If the lowest bit of flags is set, perform additional initialization
        // FUN_009c8eb0 is likely a member function (e.g., registerSelf, finalizeConstruct)
        if (flags & 1) {
            FUN_009c8eb0(this);
        }

        return this;
    }

private:
    // Placeholder for base constructor declaration
    void FUN_0064d5b0(void* obj); // Base class constructor
    void FUN_009c8eb0(void* obj); // Post-construction initialization
};