// FUNC_NAME: StealData
// Address: 0x0098df80
// Custom move operation: frees four 16‑byte sub‑blocks from `source` and copies
// the trailing 12 bytes (tail data) into `this`. Typically used to transfer
// ownership of embedded dynamic arrays while keeping the last scalar/vector fields.
int __thiscall StealData(int this, int source) {
    // Release each 16‑byte sub‑block (offsets 0x00, 0x10, 0x20, 0x30)
    subBlockRelease(source + 0x00);
    subBlockRelease(source + 0x10);
    subBlockRelease(source + 0x20);
    subBlockRelease(source + 0x30);

    // Copy the tail data (12 bytes = three 4‑byte fields, e.g. a Vector3)
    *(int*)(this + 0x40) = *(int*)(source + 0x40);
    *(int*)(this + 0x44) = *(int*)(source + 0x44);
    *(int*)(this + 0x48) = *(int*)(source + 0x48);

    return this;
}