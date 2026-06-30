// FUNC_NAME: Entity::initMatrices
void __fastcall Entity::initMatrices(void* this) {
    // DAT_00e2b1a4 is a global sentinel value (likely 0x7F800000 for infinity, or 0xBF800000 for -1.0f)
    int sentinel = DAT_00e2b1a4;

    // Initialize 4 sets of 5 ints (20 bytes each) – possibly matrix rows or vectors.
    // Each set starts with the sentinel, followed by zeros.
    *(int*)((char*)this + 0x40) = sentinel;
    *(int*)((char*)this + 0x44) = 0;
    *(int*)((char*)this + 0x48) = 0;
    *(int*)((char*)this + 0x4c) = 0;
    *(int*)((char*)this + 0x50) = 0;

    *(int*)((char*)this + 0x54) = sentinel;
    *(int*)((char*)this + 0x58) = 0;
    *(int*)((char*)this + 0x5c) = 0;
    *(int*)((char*)this + 0x60) = 0;
    *(int*)((char*)this + 0x64) = 0;

    *(int*)((char*)this + 0x68) = sentinel;
    *(int*)((char*)this + 0x6c) = 0;
    *(int*)((char*)this + 0x70) = 0;
    *(int*)((char*)this + 0x74) = 0;
    *(int*)((char*)this + 0x78) = 0;

    // Last set – only the first field is initialized here.
    *(int*)((char*)this + 0x7c) = sentinel;

    // Call sub‑initialization (likely another member of the same class)
    FUN_006101b0();
}