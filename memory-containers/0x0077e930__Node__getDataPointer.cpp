// FUNC_NAME: Node::getDataPointer
// Function at 0x0077e930
// Returns a pointer to data (either inline at +0x70 or external from a factory function).
// If param_2 is non-zero and the node's type field (+0x54) equals 0x25 (a specific type),
// it returns the result of getOrCreateExternalData(). Otherwise returns this+0x70.

int __thiscall Node::getDataPointer(int param_2) {
    // +0x54: type/enum field (e.g., node type identifier)
    if (param_2 != 0 && *(int *)(this + 0x54) == 0x25) {
        // FUN_0071e3e0: creates or retrieves external data block
        return getOrCreateExternalData();
    }
    // Return inline data buffer at offset 0x70
    return (int)(this + 0x70);
}