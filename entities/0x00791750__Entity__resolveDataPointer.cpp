// FUNC_NAME: Entity::resolveDataPointer
// Address: 0x00791750
// Returns a pointer-sized value. If the component pointer at +0x9c is non-null, not 0x48,
// and the component readiness check (via function at 0x007f4800) passes, returns the value
// from component+0x1e88. Otherwise returns the direct field at +0xd0.

int __thiscall Entity::resolveDataPointer(void) {
    // +0x9c: pointer to an optional component/state object
    int* pComponent = *(int**)(this + 0x9c);

    // Check component validity (non-null and not sentinel 0x48)
    if (pComponent != nullptr && pComponent != (int*)0x48) {
        // Check if component is in a ready/valid state (FUN_007f4800)
        if (isComponentReady(pComponent)) {
            // +0x1e88 within component: target data value
            return *(int*)((char*)pComponent + 0x1e88);
        }
    }

    // +0xd0: direct fallback value on the entity
    return *(int*)(this + 0xd0);
}