// FUNC_NAME: Entity::processPendingFlags
// Address: 0x00598980
// Purpose: Processes a set of pending state flags (bits 0-6) in the object's flags field at offset +0x4.
// For each set bit, it checks a condition (via internal functions) and if the condition passes,
// clears the bit and invokes the corresponding virtual handler from the vtable.
// Two types of condition checks are used: one that returns a simple bool (FUN_00595610) and one that fills three stack values (FUN_00595950).
// The context parameter is passed through to the condition and handler functions.

class Entity {
public:
    // Assume vtable at offset 0 (pointer to array of function pointers)
    // Offset 0x1C: handler1 (virtual), 0x20: handler2, 0x2C: handler3, 0x30: handler4,
    // 0x3C: handler5, 0x40: handler6, 0x44: handler7.
    // Flag bits: 0x1 -> handler1, 0x2 -> handler2, 0x4 -> handler3, 0x8 -> handler4,
    // 0x10 -> handler5, 0x20 -> handler6, 0x40 -> handler7.

    uint32_t m_flags; // +0x4 bitfield of pending actions

    void processPendingFlags(void* context);

private:
    // Internal condition check helpers (renamed from FUN_00595610 and FUN_00595950)
    bool checkConditionSingle(void* context); // Returns true if condition met (no outputs)
    bool checkConditionTriple(void* context, int& out1, int& out2, int& out3); // Returns true if condition met, fills three outputs

    // Virtual function table dispatch helpers (renamed)
    // The actual virtual functions are stored in vtable at given offsets.
    void callHandler1(void* context);
    void callHandler2(int a, int b, int c);
    void callHandler3(void* context);
    void callHandler4(int a, int b, int c);
    void callHandler5(void* context);
    void callHandler6(void* context);
    void callHandler7(int a, int b, int c);
};

void Entity::processPendingFlags(void* context) {
    // --- Bit 0: 0x1 ---
    if (m_flags & 0x1) {
        FUN_00595490(context); // Internal pre-check/acquire? (Original name retained)
        if (checkConditionSingle(context)) {
            m_flags &= ~0x1;
            callHandler1(context); // vtable[0x1c/4] = virtual function #7
        }
    }

    // --- Bit 1: 0x2 ---
    if (m_flags & 0x2) {
        FUN_00595490(context);
        int out1, out2, out3;
        if (checkConditionTriple(context, out1, out2, out3)) {
            m_flags &= ~0x2;
            callHandler2(out1, out2, out3); // vtable[0x20/4] = virtual function #8
        }
    }

    // --- Bit 2: 0x4 ---
    if (m_flags & 0x4) {
        FUN_00595490(context);
        if (checkConditionSingle(context)) {
            m_flags &= ~0x4;
            callHandler3(context); // vtable[0x2c/4] = virtual function #11
        }
    }

    // --- Bit 3: 0x8 ---
    if (m_flags & 0x8) {
        FUN_00595490(context);
        int out1, out2, out3;
        if (checkConditionTriple(context, out1, out2, out3)) {
            m_flags &= ~0x8;
            callHandler4(out1, out2, out3); // vtable[0x30/4] = virtual function #12
        }
    }

    // --- Bit 4: 0x10 ---
    if (m_flags & 0x10) {
        FUN_00595490(context);
        if (checkConditionSingle(context)) {
            m_flags &= ~0x10;
            callHandler5(context); // vtable[0x3c/4] = virtual function #15
        }
    }

    // --- Bit 5: 0x20 ---
    if (m_flags & 0x20) {
        FUN_00595490(context);
        if (checkConditionSingle(context)) {
            m_flags &= ~0x20;
            callHandler6(context); // vtable[0x40/4] = virtual function #16
        }
    }

    // --- Bit 6: 0x40 ---
    if (m_flags & 0x40) {
        FUN_00595490(context);
        int out1, out2, out3;
        if (checkConditionTriple(context, out1, out2, out3)) {
            m_flags &= ~0x40;
            callHandler7(out1, out2, out3); // vtable[0x44/4] = virtual function #17
        }
    }
}