// FUNC_NAME: AnimationController::updateCurrentAction
class AnimationController {
public:
    // vtable pointer
    void* vtable; // offset +0x00

    // Known fields (in order, but may not be contiguous; offsets are from this as int*)
    int m_actionIndex; // offset +0x16 (0x58)
    int m_actionFlags[4]; // offsets +0x1c-0x1f (0x70-0x7C)
    int m_actionType;     // offset +0x20 (0x80)
    int m_specialState;   // offset +0x22 (0x88)
    unsigned char m_flagsByte; // offset +0x23 (0x8C)

    void updateCurrentAction();
};

// Virtual function type at vtable+0x1c
typedef void* (__thiscall *VirtualCall_t)(void*);

// Extern functions referenced
extern void FUN_0043c740(int* param1, uint param2); // likely: setNewAnimation(index, flags)
extern int* FUN_00445ff0(void* param1, int param2); // returns a pointer or nullptr
extern void FUN_00440590(int* param1, int index, int zero, void* param4, uint param5); // e.g., playAnimation

void AnimationController::updateCurrentAction() {
    // Compute local flag from byte at +0x23: mask with 0xFFFFFF01
    // 0xFFFFFF01 keeps bit0 intact, sets bits 8-31 to 1 (preserves high bits)
    uint localFlag = (uint)m_flagsByte & 0xFFFFFF01;

    uint uVar3 = 0;
    if ((m_flagsByte & 1) != 0) {
        uVar3 = 2; // bit0 set → use mode 2
    }

    // Call virtual function at vtable+0x1c (returns some pointer)
    VirtualCall_t vfunc = *(VirtualCall_t*)(*(int*)vtable + 0x1c);
    void* pReturn = vfunc(this);

    // Check action type: 0 or 0x48 (72 = "action" or "moving")
    if ((m_actionType == 0) || (m_actionType == 0x48)) {
        // Check if all direction flags are zero
        if ((m_actionFlags[0] == 0) && (m_actionFlags[1] == 0) &&
            (m_actionFlags[2] == 0) && (m_actionFlags[3] == 0)) {
            if (m_specialState == -1) {
                // No special override → use index 0
                int index = 0;
                FUN_00440590(&m_actionIndex, index, 0, pReturn, uVar3);
                return;
            }
            // Otherwise, call a function that may set a new action based on flags
            int stack_14 = m_actionIndex;
            char stack_c = 0;
            void* stack_10 = pReturn;
            FUN_0043c740(&stack_14, localFlag);
            // Skip the later call to FUN_00440590
            if (pReturn != nullptr) {
                (*(void(__thiscall**)(int))pReturn)(1); // likely some release/cleanup
            }
            return;
        }
        // Some flag set: get pointer from actionFlags area
        int* pNode = FUN_00445ff0(m_actionFlags, 0);
        if ((pNode == nullptr) || ((*(uint*)(pNode + 0x14) & 0x8000000) == 0)) {
            // Not a valid node or flag not set → do cleanup and return
            if (pReturn != nullptr) {
                (*(void(__thiscall**)(int))pReturn)(1);
            }
            return;
        }
        // Continue to use derived index +0x3c
        int index = (int)(pNode) + 0x3c; // note: pNode is not the index but the node pointer; decompiled uses iVar2 as pointer+0x3c
        FUN_00440590(&m_actionIndex, (int)pNode + 0x3c, 0, pReturn, uVar3);
    }
    else if ((m_actionType == 0) || ((int)(m_actionType - 0x48) == 0)) {
        // Fallback: index = 0
        FUN_00440590(&m_actionIndex, 0, 0, pReturn, uVar3);
    }
    else {
        // Other case: use index = m_actionType - 0x48 + 0x3c? Actually decompiled shows:
        // iVar2 = iVar2 + 0x3c; where iVar2 = m_actionType - 0x48
        int index = m_actionType - 0x48 + 0x3c;
        FUN_00440590(&m_actionIndex, index, 0, pReturn, uVar3);
    }
}