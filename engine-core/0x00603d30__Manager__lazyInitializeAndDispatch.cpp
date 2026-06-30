// FUNC_NAME: Manager::lazyInitializeAndDispatch
void __thiscall Manager::lazyInitializeAndDispatch(int arg2, int arg3, int arg4)
{
    // +0x4c: bitfield for initialization state; bit 1 = component initialization done
    if ((*(uint *)(this + 0x4c) >> 1 & 1) == 0) {
        // First-time initialization: set up three subsystems (e.g., physics, AI, networking)
        FUN_00603c50(this);
        FUN_00603c50(this);
        FUN_00603c50(this);
        *(uint *)(this + 0x4c) = *(uint *)(this + 0x4c) | 2;  // Set bit 1 to mark done
    }
    // Log debug message (channel 0xF)
    FUN_004d3fe0(0xf);
    // Post string message (likely debug label at 0x00e3266c) with arg2 as context
    FUN_004d4ad0(arg3, &DAT_00e3266c, arg2);
    // Final dispatch to another handler with arg4
    FUN_00603ec0(this, arg4);
}