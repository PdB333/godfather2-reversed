// FUNC_NAME: EARSObject::constructor
extern void constructBase();                       // FUN_006a3720 – base class constructor
extern void cleanupAndFree(EARSObject* obj);        // FUN_009c8eb0 – placement delete or cleanup

class EARSObject {
public:
    // +0x00: pointer to class vtable (set in constructor)
    void** vtable;

    /*
     * Constructor with an optional destruction flag.
     * If (flag & 1) != 0, calls cleanupAndFree after construction.
     * Used for placement new / two-phase construction.
     */
    EARSObject* constructor(byte doCleanup) {
        this->vtable = &PTR_FUN_00d5d3c0;         // assign vtable for this class
        constructBase();                          // chain to base constructor

        if ((doCleanup & 1) != 0) {
            cleanupAndFree(this);                 // early cleanup (e.g., if allocation failed)
        }
        return this;
    }
};

// External vtable symbol (defined elsewhere in the binary)
extern void* PTR_FUN_00d5d3c0;