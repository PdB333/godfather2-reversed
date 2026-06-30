// FUNC_NAME: InterpolatedFloat::update
// Address: 0x006c54e0
// Role: Updates a smoothed float value that interpolates toward a target integer state (0,1,2).
// The object holds a pointer to an interface (offset 0xE8) queried for a specific GUID (0xA5975EB2).
// If the interface is available and a stack condition is met, sets target state to 1.
// If a flag at offset 0x2BC is true and the interface exists, cycles target through 0->1->2.
// Performs linear interpolation with a global speed factor and clamps result.

// Global constants (likely from config)
extern float g_fInterpSpeed;      // _DAT_00d5cf70
extern float g_fMaxClamp;         // DAT_00d5eee4
extern float g_fThreshold;        // DAT_00e44598
extern uint32_t g_uiBitMask;      // DAT_00e44680

class InterpolatedFloat {
public:
    // Offsets from this:
    // +0xE8: unknown interface pointer (IUnknown*)
    // +0x2BC: bool m_bCyclicFlag
    // +0x2D8: int32_t m_targetState
    // +0x2DC: float m_currentValue

    void* queryInterface(uint32_t guid); // virtual function at vtable+0x10

    __fastcall void update(void* thisPtr /* param_1 */) {
        int* piInterface = nullptr;
        void* iUnk = nullptr;

        // Get interface from offset 0xE8 (derived class container?)
        if (*(uint32_t*)((uint32_t)thisPtr + 0xE8) != 0) {
            piInterface = (int*)(*(uint32_t*)((uint32_t)thisPtr + 0xE8) - 0x48);
        }

        bool bInterfaceValid = false;
        if (piInterface != nullptr) {
            // Virtual call: QueryInterface(0xA5975EB2)
            bInterfaceValid = (**(code**)(*piInterface + 0x10))(0xA5975EB2) != 0;
        }

        // Stack-based condition? (miscompiled from inline asm)
        bool bStackCondition = ((uint32_t)&thisPtr & 1) != 0;  // Approximation

        if (bInterfaceValid && bStackCondition) {
            *(uint32_t*)((uint32_t)thisPtr + 0x2D8) = 1;
        }

        bool bCyclicFlag = *(char*)((uint32_t)thisPtr + 700) != 0;
        if (bCyclicFlag && bInterfaceValid) {
            int state = *(uint32_t*)((uint32_t)thisPtr + 0x2D8) + 1;
            *(uint32_t*)((uint32_t)thisPtr + 0x2D8) = state % 3;
        }

        int target = *(uint32_t*)((uint32_t)thisPtr + 0x2D8);
        float current = *(float*)((uint32_t)thisPtr + 0x2DC);
        float diff = (float)target - current;

        // Bitwise AND on float (possible epsilon check)
        if (g_fThreshold < (float)((uint32_t)diff & g_uiBitMask)) {
            current = diff * g_fInterpSpeed + current;
        }

        // Clamp to [0.0, g_fMaxClamp]
        if (current < 0.0f) current = 0.0f;
        if (current > g_fMaxClamp) current = g_fMaxClamp;

        *(float*)((uint32_t)thisPtr + 0x2DC) = current;
    }
};