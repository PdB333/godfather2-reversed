// FUNC_NAME: Entity::processStateFlags
// Address: 0x00900140
// Updates state flags (ushort at this+0x60) and triggers a virtual callback (vtable+0x18)
// when specific bit transitions occur: bit 0x2000 set, bit 0x1000 clear.
// The call to FUN_00471280 is likely time-slicing or a pre-update helper.

void __thiscall Entity::processStateFlags(void)
{
    ushort uVar1;
    
    FUN_00471280();
    uVar1 = *(ushort *)((int)this + 0x60);  // +0x60: state flags (ushort)
    *(ushort *)((int)this + 0x60) = uVar1 & 0x9fff;  // clear bits 0x2000 and 0x4000
    if (((uVar1 & 0x3000) != 0) && ((uVar1 & 0x1000) == 0)) {
        // Bit 0x2000 set and bit 0x1000 clear → call virtual method at vtable+0x18
        (**(code (__thiscall ***)(void))this)((int)this + 0x18);
    }
}