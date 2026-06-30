// FUNC_NAME: BaseObject::BaseObject

// Global manager pointer (used for class construction vtable lookup)
extern void* DAT_01223410;

// Base construction function (initializes core members)
extern void __cdecl FUN_00474090();

typedef void (__thiscall *FinalConstructFunc)(void* self, int param);

class BaseObject {
public:
    // Constructor with optional full initialization
    // param_1: this pointer (implicit)
    // param_2: byte flag; if bit 0 set, performs final construction via vtable
    BaseObject(bool performFullInit) {
        // Call base construction (initializes base class members)
        FUN_00474090();

        // If full initialization requested, call the virtual finalizer
        if (performFullInit) {
            // Global manager +0x2d4 holds a pointer to a vtable array
            // Index 1 (offset 4) is the final construction function
            FinalConstructFunc func = reinterpret_cast<FinalConstructFunc>(
                *reinterpret_cast<int*>(
                    *reinterpret_cast<int**>(
                        static_cast<char*>(DAT_01223410) + 0x2d4
                    ) + 4
                )
            );
            func(this, 0);  // Calls final construction with parameter 0
        }
        // Constructor implicitly returns this (param_1)
    }
};