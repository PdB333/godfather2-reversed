// FUNC_NAME: UIButton::refreshActivation

// Address: 0x00958ee0
// This function updates the button's activation state by dispatching "ActivateButton" or "DeactivateButton" UI events.
// It considers the global UIManager state and the button's internal active flag (+0x2AC).
// Additionally, it retrieves two strings from sub-objects (via vtable calls) and uses their presence to decide the final state.

// Known global: gUIManager (DAT_01130004)
// Known globals: gUIInputContext (DAT_00d8c478), gUIActivateParam (DAT_00e36da0), gUIDeactivateParam (DAT_00d796d0)

// Assumed class hierarchy: UIButton inherits from some UIElement base.
// Offsets:
// +0x84: pointer to a sub-object (e.g., button label) that has a vtable with a getString() at index 0.
// +0x108: pointer to another sub-object (e.g., command name) with a similar getString().
// +0x2AC: char flag indicating current active state (0 = inactive, 1 = active).

#include <cstdint>

// Forward declare the UI event dispatcher
void FUN_005a04a0(const char* eventName, int param, void* context, bool enable, void* extraArg);

// Global variables (guessed names)
extern void* gUIManager;          // DAT_01130004
extern void* gUIInputContext;     // DAT_00d8c478
extern void* gUIActivateParam;    // DAT_00e36da0 (used for activate)
extern void* gUIDeactivateParam;  // DAT_00d796d0 (used for deactivate)

// Helper: call virtual function at given vtable index on a sub-object
// Assumes the object has a vtable pointer as its first member.
inline char* getStringFromSubObject(void* subObj) {
    if (!subObj) return nullptr;
    void** vtable = *(void***)subObj;          // +0x00: vtable pointer
    if (!vtable) return nullptr;
    // First virtual function (index 0) returns char*
    typedef char* (*GetStringFunc)(void*);
    GetStringFunc func = (GetStringFunc)vtable[0];
    return (*func)(subObj);
}

inline bool isStringNonEmpty(const char* str) {
    if (!str) return false;
    const char* p = str;
    while (*p) p++;
    return (p - str) > 0;
}

void UIButton::refreshActivation() {
    // Step 1: If the global UI manager exists and its own active flag is set (+0x48),
    // send an initial state command based on this button's active flag.
    if (gUIManager && *(char*)((uintptr_t)gUIManager + 0x48) != '\0') {
        const char* initialCmd = (*(char*)((uintptr_t)this + 0x2AC) == '\0') ? "ActivateButton" : "DeactivateButton";
        FUN_005a04a0(initialCmd, 0, gUIInputContext, 1, gUIActivateParam);
    }

    // Step 2: Retrieve the first sub-object string (e.g., button label).
    void* subObj1 = *(void**)((uintptr_t)this + 0x84);
    char* str1 = getStringFromSubObject(subObj1);
    if (isStringNonEmpty(str1)) {
        // Step 3: Retrieve the second sub-object string (e.g., command name).
        void* subObj2 = *(void**)((uintptr_t)this + 0x108);
        char* str2 = getStringFromSubObject(subObj2);
        if (isStringNonEmpty(str2)) {
            // Both strings are non-empty → deactivate the button.
            FUN_005a04a0("DeactivateButton", 0, gUIInputContext, 1, gUIDeactivateParam);
            return;
        }
    }

    // Step 4: Default action → activate the button.
    FUN_005a04a0("ActivateButton", 0, gUIInputContext, 1, gUIDeactivateParam);
}