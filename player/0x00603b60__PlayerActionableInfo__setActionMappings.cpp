// FUNC_NAME: PlayerActionableInfo::setActionMappings
void __thiscall PlayerActionableInfo::setActionMappings(void* this, void* action0, void* action1, void* action2, void* action3, void* action4)
{
    // Store action pointers at offsets +0xa0, +0xb0, +0xc0, +0xd0, +0xe0
    *(void**)((int)this + 0xa0) = action0;
    *(void**)((int)this + 0xb0) = action1;
    *(void**)((int)this + 0xc0) = action2;
    *(void**)((int)this + 0xd0) = action3;
    *(void**)((int)this + 0xe0) = action4;

    // Reset associated flag bytes at +0xa4, +0xb4, +0xc4, +0xd4, +0xe4
    *(char*)((int)this + 0xa4) = 0;
    *(char*)((int)this + 0xb4) = 0;
    *(char*)((int)this + 0xc4) = 0;
    *(char*)((int)this + 0xd4) = 0;
    *(char*)((int)this + 0xe4) = 0;

    // Clear bit 3 (0x8) of flags at +0x4c (e.g., dirty flag)
    *(unsigned int*)((int)this + 0x4c) &= 0xfffffff7;
}