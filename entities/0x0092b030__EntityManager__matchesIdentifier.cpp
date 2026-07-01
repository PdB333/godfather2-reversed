// FUNC_NAME: EntityManager::matchesIdentifier
uint __thiscall EntityManager::matchesIdentifier( int param_1, int *identifier, uint8 extraByte )
{
    int *pRecord;
    
    if ( *(int *)(param_1 + 0x50) == 0 ) {
        // Offline/local mode: use global table
        // g_TableBase + 0x2c is the start of an array of 0x24-byte records
        // g_IndexBase + 0x6c holds the current index (e.g., count or selector)
        pRecord = (int *)( g_TableBase + 0x2c + *(int *)( g_IndexBase + 0x6c ) * 0x24 );
        // Compare all 4 DWORDs of the identifier
        if ( ( identifier[0] == *pRecord ) &&
             ( identifier[1] == pRecord[1] ) &&
             ( identifier[2] == pRecord[2] ) &&
             ( identifier[3] == pRecord[3] ) )
        {
            // Return matching record pointer with success flag (low byte = 1)
            return ( (uint)pRecord & 0xFFFFFF00 ) | 1;
        }
        // Return record pointer with failure flag (low byte = 0)
        return (uint)pRecord & 0xFFFFFF00;
    }
    else {
        // Online/networked mode: use a different global structure
        pRecord = *(int **)*( undefined4 ** )( g_OtherGlobal + 4 );
        if ( pRecord != (int *)0x0 ) {
            pRecord = pRecord + -0x7cc; // Adjust pointer to containing structure
            if ( pRecord != (int *)0x0 ) {
                pRecord = (int *)FUN_00705ab0( extraByte ); // Lookup by extra byte
                if ( pRecord != (int *)0x0 ) {
                    // Compare the 4-DWORD identifier with fields at offsets 0x20,0x24,0x28,0x2C (8,9,10,11 *4)
                    if ( ( pRecord[8] == identifier[0] ) &&
                         ( pRecord[9] == identifier[1] ) &&
                         ( pRecord[10] == identifier[2] ) &&
                         ( (int *)pRecord[11] == (int *)identifier[3] ) ) // last field is a pointer
                    {
                        return ( (uint)pRecord & 0xFFFFFF00 ) | 1;
                    }
                    // Return record pointer with failure flag
                    return (uint)pRecord & 0xFFFFFF00;
                }
            }
        }
        // Return zero with failure flag if lookup failed
        return (uint)pRecord & 0xFFFFFF00;
    }
}