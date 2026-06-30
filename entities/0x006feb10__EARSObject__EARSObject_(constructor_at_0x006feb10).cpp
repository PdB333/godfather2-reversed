// FUNC_NAME: EARSObject::EARSObject (constructor at 0x006feb10)
// Address: 0x006feb10
// Role: Constructor for EARSObject, calls base initializer and optionally performs additional setup based on a flag.

class EARSObject;

// Forward declarations of callees – actual names unknown, but represent base constructor/initializer
// and an optional initialization or cleanup routine.
void __thiscall baseConstructor(EARSObject* this);    // FUN_006fdf80
void __thiscall optionalInit(EARSObject* this);       // FUN_009c8eb0

class EARSObject {
public:
    // Constructor: takes a byte flag (param_2) that controls whether optionalInit is called.
    // If (flags & 1) is non-zero, optionalInit (likely a secondary initializer) is invoked.
    __thiscall EARSObject(byte flags) {
        baseConstructor(this);      // Base class or common initialization
        if ((flags & 1) != 0) {
            optionalInit(this);     // Additional setup when the lowest bit of flags is set
        }
        // Note: Return this is implicit for constructors; Ghidra decompiler shows return param_1.
    }
};