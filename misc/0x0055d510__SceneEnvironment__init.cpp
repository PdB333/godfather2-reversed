// FUNC_NAME: SceneEnvironment::init
void SceneEnvironment::init(void)
{
    // Call base class initializer (likely EARS::Framework::BaseObject::init)
    FUN_00bf0bc0(this);

    // Set vtable pointer
    *(void **)this = &PTR_FUN_00e3a3e4;

    // Initialize flags bitfield at +0x44
    int flags = 0;
    *(int *)((char *)this + 0x44) = flags;

    // Set environment constants (colors, intensities, etc.)
    *(int *)((char *)this + 0x3c) = DAT_00e2e714;   // e.g., ambient color
    *(int *)((char *)this + 0x3d) = DAT_00e39f98;   // e.g., diffuse color
    *(int *)((char *)this + 0x3e) = DAT_00e445f8;   // e.g., specular color
    int uVar1 = DAT_00e2afb8;                       // e.g., fog color
    *(int *)((char *)this + 0x3f) = DAT_00e2afb8;
    *(int *)((char *)this + 0x40) = uVar1;

    // Call a virtual method on a sub-object at +0x18 (likely a render manager)
    // The function returns a 12-byte struct (local_30) and a 4-byte value (uStack_24)
    // which is then stored at +0x41
    int *subObj = *(int **)((char *)this + 0x18);
    int vtable = *(int *)subObj;
    void (*subMethod)(int, int, char *) = *(void (**)(int, int, char *))(vtable + 0x10 + 0x1c);
    char local_30[12];
    int uStack_24;
    subMethod(&DAT_011397d0, 0, local_30); // e.g., get some resource handle or configuration
    *(int *)((char *)this + 0x41) = uStack_24;

    // Set four consecutive values (e.g., a 4-component color or vector)
    *(int *)((char *)this + 0x38) = DAT_01126060;
    *(int *)((char *)this + 0x39) = DAT_01126064;
    *(int *)((char *)this + 0x3a) = DAT_01126068;
    *(int *)((char *)this + 0x3b) = DAT_0112606c;

    // Set misc fields
    *(int *)((char *)this + 0x43) = 2;   // e.g., render layer or priority
    flags = *(int *)((char *)this + 0x44);
    flags |= 4;                           // Enable flag bit 2
    // Conditionally set bit 4 based on bit 3 (which is currently 0)
    if (((uint)flags >> 3 & 1) == 0) {
        flags &= ~0x10;                  // Clear bit 4
    } else {
        flags |= 0x10;                   // Set bit 4
    }
    flags &= ~8;                         // Clear bit 3
    *(int *)((char *)this + 0x44) = flags;

    // Zero out additional fields (maybe unused or debug counters)
    *(int *)((char *)this + 0x35) = 0;
    *(int *)((char *)this + 0x46) = 0;
    *(int *)((char *)this + 0x47) = 0;
    *(int *)((char *)this + 0x48) = 0;
    *(int *)((char *)this + 0x49) = 0;
    *(int *)((char *)this + 0x45) = 5;   // e.g., method or mode
    return;
}