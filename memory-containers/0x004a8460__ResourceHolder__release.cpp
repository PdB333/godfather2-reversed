// FUNC_NAME: ResourceHolder::release
// Address: 0x004a8460
// Releases the resource held by this object, potentially passing ownership to another context.
// param_2 is an optional pointer to a "context" object that may finalize the release.
uint ResourceHolder::release(ResourceHolder* this, Context* context) {
    uint uVar2 = this->handle; // +0x0: handle/resource pointer
    if (uVar2 != 0) {
        // Call the release function pointer stored at offset 0xC
        uVar2 = ((uint (*)(uint))this->releaseFunc)(uVar2); // +0xC: function pointer
    }
    // Clear the resource fields
    this->handle = 0;         // +0x0
    this->field_4 = 0;        // +0x4
    this->field_8 = 0;        // +0x8

    if (context != 0) {
        byte flags = *(byte*)((int)context + 2); // +0x2: low byte of short, flags
        // Call finalizeRelease with context data at +0x40
        uVar2 = FUN_004a8580((int)context + 0x40,   // +0x40: data buffer
                            (flags & 1) == 1,       // bit 0: needDeinit?
                            (flags & 0x40) == 0x40); // bit 6: needUnload?
        return uVar2;
    }
    // If no context, mask the return value (likely clear low byte error flag)
    return uVar2 & 0xffffff00;
}