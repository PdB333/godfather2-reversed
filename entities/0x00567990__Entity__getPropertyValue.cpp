// FUNC_NAME: Entity::getPropertyValue
// Address: 0x00567990
// Retrieves a uint value from a component pointer at +0x34.
// If component exists, calls virtual function at vtable offset 0x20 (likely getValue()).
// Otherwise returns a default (in_EAX & 0xffffff00) — here simplified to 0.

uint __thiscall Entity::getPropertyValue() {
    // +0x34: Component pointer
    Component* comp = *(Component**)(this + 0x34);
    if (comp != nullptr) {
        // Virtual call at vtable offset 0x20 (index 8)
        return comp->getValue(); // assumed method name
    }
    // Fallback: use a default value (original code masks EAX with 0xffffff00)
    return 0; // simplified; originally returned residual register value
}