// FUNC_NAME: BaseObject::init
// Address: 0x006a2190
// Role: Initialization function that calls base setup and optionally registers this object if flag bit 0 is set.

// Forward declarations for unknown callees
extern void FUN_006a3720(void);
extern void FUN_009c8eb0(BaseObject* obj);

class BaseObject {
public:
    BaseObject* init(byte flags) {
        // Call base initialization (vtable setup or base constructor) - FUN_006a3720
        FUN_006a3720();

        // If bit 0 of flags is set, perform additional registration (e.g., add to manager list)
        // FUN_009c8eb0(this)
        if (flags & 1) {
            FUN_009c8eb0(this);
        }

        return this;
    }
};