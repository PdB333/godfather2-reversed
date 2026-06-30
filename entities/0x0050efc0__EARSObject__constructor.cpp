// FUNC_NAME: EARSObject::constructor
class EARSObject {
public:
    /// Flags: bit 0 – if set, calls additional initialization (e.g. register for lifecycle management)
    /// Returns this pointer, typical of a placement constructor or factory.
    /// @param flags  Flags affecting construction behavior.
    /// Address: 0x0050efc0
    __thiscall EARSObject* constructor(uint8 flags) {
        // Step 1: Base class / common initialization (FUN_0050efe0)
        baseInit();

        // Step 2: If flag bit 0 is set, perform extra setup (FUN_009c8eb0)
        // In EARS engine this often registers the object for automatic cleanup
        // or hooks into the object management system.
        if (flags & 1) {
            registerForAutoCleanup(this);
        }

        return this;
    }

private:
    /// Internal base initialization (FUN_0050efe0)
    void baseInit();

    /// Registers this object for automatic cleanup/destruction (FUN_009c8eb0)
    /// Called when the "auto-manage" flag is set.
    void registerForAutoCleanup(EARSObject* obj);
};