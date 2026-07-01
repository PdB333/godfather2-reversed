// FUNC_NAME: VideoSettings::applyResolution
void __fastcall VideoSettings::applyResolution(void* this)
{
    *(uint8_t *)((uintptr_t)this + 0x50) = 0;  // +0x50: some flag, cleared
    *(uint32_t *)((uintptr_t)this + 0x114) = DAT_0120587c; // +0x114: width
    *(uint32_t *)((uintptr_t)this + 0x110) = DAT_01205880; // +0x110: height
    *(uint32_t *)((uintptr_t)this + 0x118) = DAT_01205760; // +0x118: refresh rate
    FUN_00987db0(*(uint32_t *)((uintptr_t)this + 0x58)); // +0x58: some handle or device
    _sprintf((char *)((uintptr_t)this + 0xc4), "%d x %d @ %dHz",
             *(uint32_t *)((uintptr_t)this + 0x114),
             *(uint32_t *)((uintptr_t)this + 0x110),
             *(uint32_t *)((uintptr_t)this + 0x118)); // +0xc4: resolution string buffer
    FUN_00987530(); // probably applies the resolution to the renderer
    FUN_0069f0e0(0); // commits or triggers a switch
}