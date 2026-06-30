// FUNC_NAME: SlotManager::processSlotBindings

// Slot binding entry (0x30 bytes per slot)
struct SlotBinding {
    uint32_t            count;           // +0x00: unused? (only checked in calling context)
    ActionFunc          func1;           // +0x04: function pointer for first action
    ActionFunc          func2;           // +0x08: function pointer for second action
    uint32_t            data1;           // +0x0C: argument to func1
    uint32_t            data2;           // +0x10: argument to func2
    DynamicAction**     dynamicList;     // +0x14: array of pointers to dynamic action objects
    uint32_t            dynamicCount;    // +0x18: number of entries in dynamicList
    uint32_t            pad1c;           // +0x1C: unused
    ActionFunc          func3;           // +0x20: function pointer for third action
    ActionFunc          func4;           // +0x24: function pointer for fourth action
    uint32_t            data3;           // +0x28: argument to func3
    uint32_t            data4;           // +0x2C: argument to func4
};

// Dynamic action object (size unknown, assumed at least 16 bytes for vtable ptr + data)
struct DynamicAction {
    void** vtable;     // +0x00: vtable pointer
    uint32_t someData; // +0x0C: data at offset 12 (passed as argument to virtual function)
    // ... possibly more
};

// Slot manager
struct SlotManager {
    uint32_t      slotCount;    // +0x00: number of slots
    SlotBinding*  bindings;     // +0x04: pointer to array of SlotBinding[slotCount]
};

// Global context set before each callback call
SlotManager* g_currentManager = (SlotManager*)0x012053e4;   // updated to param_1
uint32_t     g_currentSlot    = 0;                          // updated to param_2 (DAT_0110abe8)
int32_t      g_currentIndex  = -1;                          // loop index or -1 (DAT_012053e8)

typedef bool (*ActionFunc)(uint32_t slotIndex, uint32_t data);

// Process all bindings for a given slot index.
// Returns true if all callbacks returned true; false if any failed.
bool SlotManager::processSlotBindings(uint32_t slotIndex) {
    bool allOk = true;

    // Bounds check: slotIndex must be less than total slots
    if (slotCount <= slotIndex) {
        return false;
    }

    SlotBinding* binding = &bindings[slotIndex];
    g_currentManager = this;
    g_currentSlot = slotIndex;

    // Process the first pair of fixed actions (func1, func2) with their data
    ActionFunc* funcs = &binding->func1;
    uint32_t*   datas = &binding->data1;
    for (int i = 0; i < 2; i++) {
        if (funcs[i] != nullptr) {
            allOk = allOk && funcs[i](slotIndex, datas[i]);
        }
    }

    // Process dynamic action list (array of DynamicAction*)
    uint32_t dynCount = binding->dynamicCount;
    if (dynCount > 0) {
        DynamicAction** dynList = binding->dynamicList;
        for (uint32_t j = 0; j < dynCount; j++) {
            g_currentIndex = j;
            DynamicAction* action = dynList[j];
            // Call the first virtual function (vtable[0]) with argument at offset 0x0C
            typedef bool (*VirtualFunc)(uint32_t arg);
            VirtualFunc vfunc = (VirtualFunc)action->vtable[0];
            allOk = allOk && vfunc(action->someData);
        }
    }

    // Process the second pair of fixed actions (func3, func4) with their data
    g_currentIndex = -1;
    funcs = &binding->func3;
    datas = &binding->data3;
    for (int i = 0; i < 2; i++) {
        if (funcs[i] != nullptr) {
            allOk = allOk && funcs[i](slotIndex, datas[i]);
        }
    }

    // Reset global context
    g_currentSlot = -1;
    g_currentManager = nullptr; // actually set to 0 (since iVar3 becomes -1? original code sets to iVar3 which is 0 after loops)
    return allOk;
}