// FUNC_NAME: EARSObject::init
// Address: 0x0064e040
// Role: Object initializer with conditional cleanup. Calls base initialization (FUN_0064e060) then if flag (param_2) has bit 0 set, calls destruction/cleanup (FUN_009c8eb0). Returns this pointer.
// Note: param_2 likely controls memory management or lifecycle policy (e.g., 0 = normal init, 1 = reinit after destruction).

class EARSObject {
public:
    // +0x00 vtable
    // Other members unknown

    // Constructor-like init with flag
    // If flag & 1, performs a full cleanup after base init (likely for pooled objects)
    EARSObject* init(byte flag) {
        // Base initialization (e.g., zero memory, set defaults)
        baseInit();

        // If flag indicates "needs destruction after init" (e.g., reinit from pool)
        if (flag & 1) {
            destruct(); // Cleanup old state
        }

        return this;
    }

private:
    void baseInit() __attribute__((alias("FUN_0064e060")));
    void destruct() __attribute__((alias("FUN_009c8eb0")));
};