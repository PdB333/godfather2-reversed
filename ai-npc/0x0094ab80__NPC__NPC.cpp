// FUNC_NAME: NPC::NPC
undefined4 __thiscall NPC::NPC(NPC *this, byte allocFlag)
{
    // Call base class constructor (likely Sentient::Sentient)
    Sentient::Sentient(this);
    // If the low bit of allocFlag is set, perform cleanup/destruction
    // (common pattern for allocation-aware constructors in EARS engine)
    if ((allocFlag & 1) != 0) {
        // This likely calls operator delete or a custom deallocator
        FUN_005c4480(this);
    }
    return this;
}