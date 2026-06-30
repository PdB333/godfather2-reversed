// FUNC_NAME: CollisionCamera::CollisionCamera
void __thiscall CollisionCamera::CollisionCamera(CollisionCamera *this) {
    // Set a 2-byte field at offset +6 to 1 (likely a flag or version indicator)
    *(unsigned short *)((unsigned char *)this + 6) = 1;

    // Initialize pointers at offsets +8 and +12 to static data tables
    *(void **)((unsigned char *)this + 8) = &PTR_LAB_00dc3dd4;
    *(void **)((unsigned char *)this + 12) = &PTR_LAB_00e39f9c;

    // Set the vtable pointer at offset 0
    this->vtable = &PTR_FUN_00e39fb0;

    // Reassign the same offsets to different static data (possibly due to multiple inheritance or relocation)
    *(void **)((unsigned char *)this + 8) = &PTR_LAB_00e39fc8;
    *(void **)((unsigned char *)this + 12) = &PTR_LAB_00e39fdc;

    // Clear a field at offset +0x30
    this->field_0x30 = 0;

    // Initialize four Vector3 fields (each 12 bytes) to (0,0,0x80000000)
    // 0x80000000 as float is -0.0f, used as sentinel for "uninitialized"
    this->vec1 = {0.0f, 0.0f, -0.0f}; // offset +0x64
    this->vec2 = {0.0f, 0.0f, -0.0f}; // offset +0x70
    this->vec3 = {0.0f, 0.0f, -0.0f}; // offset +0x7C
    this->vec4 = {0.0f, 0.0f, -0.0f}; // offset +0x88

    // Call a secondary initialization function
    FUN_005523c0();
}