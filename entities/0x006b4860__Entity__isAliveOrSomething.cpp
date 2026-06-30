// FUNC_NAME: Entity::isAliveOrSomething
bool __fastcall Entity::isAliveOrSomething(int this)
{
    int iVar2;
    // +0x16c: some flag/state
    bool result = *(bool *)(this + 0x16c);
    
    // +0x34: flags field - check bits 0x120000 and bit 0
    if (((*(uint *)(this + 0x34) & 0x120000) == 0 && 
        (*(byte *)(this + 0x34) & 1) == 0 &&
        // +0x40: pointer to some sub-object
        *(int *)(this + 0x40) != 0) 
    {
        iVar2 = FUN_008c74d0(*(int *)(this + 0x40));
        if (iVar2 != 0 && ((~(byte)(*(uint *)(iVar2 + 0x84) >> 5) & 1) != 0))
        {
            return result;
        }
    }
    return true;
}