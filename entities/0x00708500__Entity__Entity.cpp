// FUNC_NAME: Entity::Entity
// Address: 0x00708500
// Role: Constructor for Entity class (or similar base object).
// Sets vtable to a known table and calls base class constructor (SimObject or similar).
// Flag parameter param_2: if bit 0 is set, calls a cleanup/destructor function (likely for placement reinitialization).

class SimObject {
public:
    // Base constructor at 0x004149b0
    SimObject();
};

class Entity : public SimObject {
public:
    // vtable at 0x00d610b8
    virtual ~Entity();

    // Constructor at 0x00708500
    Entity(byte reinitFlag) {
        // Set vtable pointer for this class
        vfptr = (void*)0x00d610b8;
        // Call base class constructor (SimObject)
        SimObject::SimObject();
        // If the flag bit 0 is set, call a cleanup routine (possibly destructor or reinitialization)
        if ((reinitFlag & 1) != 0) {
            // Function at 0x009c8eb0 – likely a virtual destructor or cleanup method
            ((Entity*)this)->~Entity(); // or a separate cleanup function
        }
    }

    // Destructor (virtual) at 0x009c8eb0 – performs actual destruction
    ~Entity();
};