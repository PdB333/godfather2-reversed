// FUNC_NAME: GhostManager::resolveGhostEntryFlag
uint __fastcall GetGhostEntryFlag( void* this, uint handle )
{
    uint result;
    char stackVar1;
    uint stackVar2[1];

    result = FUN_005f0560( handle, &stackVar1, stackVar2 );
    if ( (result != 0) && (result != 0xFFFFFFE0) )
    {
        // +0x28 is flags field in GhostEntry
        return *(uint *)(result + 0x28) >> 6 & 0xFFFFFF01;
    }
    return result & 0xFFFFFF00;
}