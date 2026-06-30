// FUNC_NAME: Player::Player
void __thiscall Player::Player(void) {
    int iVar1;
    undefined4 uVar2;
    undefined4 *puVar3;

    // Initialize various fields to zero
    *(undefined4 *)(this + 0x1c0c) = 0; // +0x1c0c: some flag or pointer
    _memset((void *)(this + 0x1c10), 0, 0x100); // +0x1c10: buffer of 256 bytes
    *(undefined4 *)(this + 0x1d10) = 0; // +0x1d10: another field
    _memset((void *)(this + 0x1d14), 0, 0x800); // +0x1d14: buffer of 2048 bytes

    // Allocate a sub-object using a global allocator function
    iVar1 = (*g_allocator)(4, 0); // size 4, flags 0
    if (iVar1 == 0) {
        uVar2 = 0;
    } else {
        uVar2 = subObjectConstructor(); // FUN_005b1df0
    }
    *(undefined4 *)(this + 0x2514) = uVar2; // +0x2514: pointer to sub-object

    // Initialize an array of 64 elements (each 0x2C bytes? because puVar3 += 0xb (11 dwords = 44 bytes))
    iVar1 = 0x3f; // 63 iterations, so 64 elements
    puVar3 = (undefined4 *)(this + 0x2528); // +0x2528: start of array
    do {
        *puVar3 = 0;
        puVar3 = puVar3 + 0xb; // advance 11 dwords = 44 bytes per element
        iVar1 = iVar1 + -1;
    } while (-1 < iVar1);

    // Set up doubly linked list pointers (self-referential initially)
    *(int *)(this + 0x1404) = this; // +0x1404: next pointer
    *(int *)(this + 0x1400) = this; // +0x1400: prev pointer

    *(undefined4 *)(this + 0x1c08) = 0; // +0x1c08: some field

    // Call another initialization function
    initComponents(); // FUN_005a6280

    *(undefined4 *)(this + 0x301c) = 0; // +0x301c: field
    _memset((void *)(this + 0x2518), 0, 0xb00); // +0x2518: buffer of 2816 bytes
    *(undefined4 *)(this + 0x3018) = 0; // +0x3018: field
    *(undefined4 *)(this + 0x3120) = 0; // +0x3120: field

    return;
}