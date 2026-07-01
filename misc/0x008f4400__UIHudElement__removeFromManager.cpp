// FUNC_NAME: UIHudElement::removeFromManager
// Function address: 0x008f4400
// Role: Hides or removes a UI HUD element and performs cleanup.
// References: Outer object (UIHudManager?) starts at this - 0x2080.
//   The method operates on an inner widget structure (UIHudElement) that is a member of a larger container.
//   Uses ESI register as an implicit parameter (likely a pointer to some manager or global).

// Structure representing the outer object (e.g. HUD manager)
struct UIHudManager {
    uint32_t flags;           // +0x00 (contains bit0 = active, bit3 = something else)
    // +0x04 padding?
    uint32_t field_0x08;      // +0x08 (stored from ESI, used later in callback)
    // +0x0C-0x17 unknown
    void** vtable;            // +0x18 (virtual function table, index 1 used)
    uint32_t field_0x20;      // +0x20 (parameter for FUN_008f1e20)
    uint32_t field_0x24;      // +0x24 (parameter for FUN_008f1e20)
    // ... more fields up to +0x2080
    // At offset 0x2080 the UIHudElement begins
};

// Structure representing the inner UI element
struct UIHudElement {
    uint32_t field_0x00;      // +0x00 (unknown)
    // +0x04-0x0B unknown
    uint32_t field_0x0C;      // +0x0C (passed as first argument to vfunc)
    // ... up to
    uint8_t field_0x1E0;      // +0x1E0 (active/visible flag, set to 0)
    // +0x1E1-... (size unknown, but < 0x2080? no)
};

// Callee function declarations
void FUN_009119E0();                                      // Likely "stopRender" or "deactivate"
void FUN_008F1F40();                                      // Likely "releaseResources" or "stopAnimation"
void FUN_008F3A90();                                      // Likely "finalizeCleanup"
void FUN_008F1E20(int action, int param1, int param2);    // action = 4 (e.g. DELETE or HIDE)
void FUN_008F2CF0(void* ptr);                             // Callback with the saved pointer

void __fastcall UIHudElement::removeFromManager(void) // ECX = this (points to UIHudElement)
{
    // Get outer manager object (this - 0x2080)
    UIHudManager* manager = reinterpret_cast<UIHudManager*>(reinterpret_cast<char*>(this) - 0x2080);
    // ESI register holds some implicit parameter (probably a manager pointer)
    int esiValue; // unaff_ESI

    // Check bit 3 of manager->flags
    if ((manager->flags >> 3) & 1) {
        FUN_009119E0();  // Deactivate something (e.g. timer, sound)
    }

    // Check bit 0 of manager->flags
    if (manager->flags & 1) {
        manager->flags &= ~1;                   // Clear active flag
        FUN_008F1F40();  // Release resources / stop animation
    }

    // Call virtual function at vtable index 1 (offset 4)
    // with parameters: this->field_0x0C and constant 0x40c (e.g. resource ID or message)
    void (*vfunc)(int, int) = (void (*)(int, int))manager->vtable[1];
    vfunc(this->field_0x0C, 0x40c);

    this->field_0x0C = 0;  // Clear the field

    FUN_008F3A90();  // Finalize cleanup

    // Notify the manager with action 4 (e.g. ERASE or HIDE)
    FUN_008F1E20(4, manager->field_0x20, manager->field_0x24);

    // Store ESI into manager field
    manager->field_0x08 = esiValue; // This value was passed implicitly via ESI

    // Clear bits 0x1800 (11 and 12) in manager flags
    manager->flags &= 0xFFFFE7FF; // ~0x1800

    // Clear the active byte in this element
    this->field_0x1E0 = 0;

    // Invoke callback with the saved manager field
    FUN_008F2CF0(manager->field_0x08);
}