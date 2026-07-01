// FUNC_NAME: Sentient::setTarget
// Address: 0x0097b8e0
// Stores a target pointer and sets a flag to indicate the target has changed.

void __thiscall Sentient::setTarget(Sentient* this, void* target) {
    // +0xa4: target pointer (e.g., to an Entity or SimObject)
    *(void**)((uintptr_t)this + 0xa4) = target;
    // +0x102: 16-bit flag field; set bit 1 (0x2) to mark as dirty/updated
    *(uint16_t*)((uintptr_t)this + 0x102) |= 2;
}