// FUNC_NAME: EARSObject::EARSObject
// Address: 0x004c2fb0
// Constructor for an EARS engine object. Calls base initialization and conditionally
// performs a post-construct hook (e.g., registration or allocation) if the low bit of flags is set.
class EARSObject {
public:
    EARSObject(byte flags) {
        // Base class initialization (calls FUN_004c2ef0)
        baseConstruct();
        
        // Optional post-construction step (calls FUN_009c8eb0)
        if (flags & 1) {
            postConstruct();
        }
    }

private:
    void baseConstruct() {
        // Placeholder for actual base constructor logic at 0x004c2ef0
    }

    void postConstruct() {
        // Placeholder for post‑construction hook at 0x009c8eb0
        // Typically registers the object in a manager or allocates from a pool.
    }
};