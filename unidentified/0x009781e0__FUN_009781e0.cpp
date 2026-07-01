// FUNC_NAME: SomeClass::toggleResource
// Address: 0x009781e0
// Role: Toggles initialization of a resource based on a flag bit (bit 12 at +0x60).
// If flag is set, releases the resource and clears flag; if not set, initializes and sets flag.

void __thiscall SomeClass::toggleResource(void)
{
    // Check bit 12 (0x1000) of flags at +0x60
    if ((*(uint *)(this + 0x60) >> 0xc & 1) != 0) {
        // Resource is active: release it
        *(undefined4 *)(this + 0x130) = 0;          // +0x130: clear some field
        FUN_009c8f10(*(undefined4 *)(this + 300));  // +0x12C: release resource handle
        *(undefined4 *)(this + 300) = 0;            // +0x12C: clear handle
        *(undefined4 *)(this + 0x134) = 0;          // +0x134: clear another field
        // Clear bit 12
        *(uint *)(this + 0x60) = *(uint *)(this + 0x60) & 0xffffefff;
    }
    // If flag is not set, initialize the resource
    if ((*(uint *)(this + 0x60) >> 0xc & 1) == 0) {
        FUN_00922200(this + 300);                   // +0x12C: initialize resource
        // Set bit 12
        *(uint *)(this + 0x60) = *(uint *)(this + 0x60) | 0x1000;
    }
    return;
}