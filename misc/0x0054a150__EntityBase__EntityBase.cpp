// FUNC_NAME: EntityBase::EntityBase
// Constructor for base entity class. Calls a base constructor unconditionally,
// then optionally calls an additional initialization function if the low bit of initFlag is set.
class EntityBase {
public:
    // Base constructor that performs core initialization.
    // This is likely a global or static function (address 0x0054a180).
    void baseConstructor();

    // Optional post-construction initialization (address 0x009c8eb0).
    // Takes a pointer to the object being constructed.
    static void additionalInit(EntityBase* obj);

    EntityBase(byte initFlag) {
        // Unconditional base construction (e.g., zeroing fields, setting defaults)
        baseConstructor();

        // If the low bit of initFlag is set, perform additional setup
        if (initFlag & 1) {
            additionalInit(this);
        }
    }
};