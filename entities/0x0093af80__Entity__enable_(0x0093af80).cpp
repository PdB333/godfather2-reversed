// FUNC_NAME: Entity::enable (0x0093af80)
// Sets bit 0x2000 at offset +0x5c (flags field) and calls an internal helper.

void __thiscall Entity::enable(Entity* this)
{
    *(uint*)((int)this + 0x5c) |= 0x2000; // +0x5c: flags
    FUN_0081efa0(0); // internal activation callback
}