// FUNC_NAME: GlobalState::initialize
// Function at 0x0053c3d0: Initializes global game state singleton, zeroes out members and sets vtable pointer.
// Called during engine startup to prepare the global state structure.

struct GlobalState {
    // +0x00: vtable pointer (set to PTR_LAB_00e38de4)
    void* vtable;
    // +0x04: unknown (DAT_01198e54)
    int field_04;
    // +0x08: unknown (DAT_01198e4c)
    int field_08;
    // +0x0C: unknown (DAT_01198e48)
    int field_0C;
    // +0x10: unknown (DAT_01198e70)
    int field_10;
    // +0x14: unknown (DAT_01194d04)
    int field_14;
    // +0x18: unknown (DAT_01198e74)
    int field_18;
    // +0x1C: unknown (DAT_01198e64)
    int field_1C;
    // +0x20: unknown (DAT_01198e78)
    int field_20;
    // +0x24: unknown (DAT_0121be7c)
    int field_24;
    // +0x28: unknown (DAT_0121bcd8)
    int field_28;
    // +0x2C: pointer to static data (DAT_0121bc10)
    void* field_2C;
};

// Global singleton instance pointer
GlobalState* g_globalState = nullptr;

// Initialization function
GlobalState* GlobalState::initialize() {
    // Call base initialization or memory allocation
    FUN_006126d0();

    // Zero out all fields except vtable
    g_globalState->field_04 = 0;
    g_globalState->field_08 = 0;
    g_globalState->field_0C = 0;
    g_globalState->field_10 = 0;
    g_globalState->field_14 = 0;
    g_globalState->field_18 = 0;
    g_globalState->field_1C = 0;
    g_globalState->field_20 = 0;
    g_globalState->field_24 = 0;
    g_globalState->field_28 = 0;

    // Set vtable pointer to static data table
    g_globalState->vtable = &PTR_LAB_00e38de4;

    // Return pointer to the global state structure
    return g_globalState;
}