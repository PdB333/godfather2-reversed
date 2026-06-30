// FUNC_NAME: NetObject::NetObject(byte)
// Function address: 0x0046bc00
// Role: Constructor for NetObject (derived from SimObject/TNL base).
// Sets up vtable chain and conditionally calls an internal initializer.

// The object's vtable pointer is stored at offset 0x00.
// Base vtable (SimObject) at 0x00e327c0, derived vtable (NetObject) at 0x00e30ea0.

// Forward declarations for the base constructor and optional init helper.
// SimObject::SimObject() at 0x0043e380
// NetObject::postConstructInit() at 0x009c8eb0 (called only if flag & 1)

class SimObject {
public:
    SimObject(); // constructor
};

// NetObject inherits from SimObject
class NetObject : public SimObject {
public:
    // Constructor with a flag parameter (byte)
    NetObject(byte flags);

private:
    // Called when flags & 1 is set – performs additional setup
    void postConstructInit();
};

NetObject::NetObject(byte flags) {
    // Step 1: Set vtable to base class vtable so that during base construction
    // virtual function calls (if any) go to SimObject’s implementations.
    void** vtablePtr = reinterpret_cast<void**>(this);
    *vtablePtr = reinterpret_cast<void*>(0x00e327c0); // SimObject vtable

    // Step 2: Initialize base class part
    SimObject::SimObject();

    // Step 3: Now that base is fully constructed, switch to derived vtable
    *vtablePtr = reinterpret_cast<void*>(0x00e30ea0); // NetObject vtable

    // Step 4: If the low bit of flags is set, call additional initialization
    // (this often handles registration, resource allocation, or dynamic memory setup)
    if (flags & 1) {
        this->postConstructInit();
    }
}