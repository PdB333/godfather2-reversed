// FUNC_NAME: NPCDialogManager::playDialogByID
// Address: 0x0097ff40
// This function activates a dialog by its ID. If the ID is a special sentinel (0x637b907), it starts the default dialog.
// Otherwise, it searches the dialog ID list and activates the matching dialog if found.
// Returns 1 on success, 0 on failure.

int __thiscall NPCDialogManager::playDialogByID( NPCDialogManager *this, int dialogID )
{
    int iVar1;
    int iVar2;
    
    // Call virtual function at vtable+0x6c (likely preloadDefaultDialog or init)
    ( *(code **)( *this + 0x6c ) )();
    
    // Check for special sentinel value (0x637b907) - perhaps "non-specific" or "random dialog"
    if ( dialogID == 0x637b907 ) {
        // Set current dialog index to 0 (default)
        this->m_currentDialogIndex = 0;   // +0x60 (this[0x18])
        // Get somemthing via FUN_00471610 (maybe getDialogPlayer?) and add 0x30
        iVar1 = FUN_00471610();
        // Play the dialog using the retrieved data
        FUN_00976bc0( *(undefined4 *)( DAT_0112a66c + 8 ), iVar1 + 0x30 );
        return 1;
    }
    
    // Get total number of dialogs via virtual function at vtable+0x70 (likely getDialogCount)
    iVar1 = ( *(code **)( *this + 0x70 ) )();
    if ( 1 < iVar1 ) {
        iVar1 = 1; // Start from index 1? (0 might be reserved for default)
        do {
            // Compare dialog ID with stored IDs in the list at +0x54 (this[0x15])
            if ( *(int *)( this->m_dialogIDList + iVar1 * 4 ) == dialogID ) {
                // Found dialog: set current index
                this->m_currentDialogIndex = iVar1;   // +0x60
                // Look up dialog data structure by ID
                iVar1 = FUN_008c74d0( dialogID );
                if ( iVar1 == 0 ) {
                    return 0;
                }
                // Get a sub-component at offset 0x22c from the dialog structure
                iVar1 = FUN_006b0ee0( *(undefined4 *)( iVar1 + 0x22c ) );
                if ( iVar1 == 0 ) {
                    return 0;
                }
                // Play dialog using the sub-component (offset 0x48 and 0x10)
                FUN_00976bc0( *(undefined4 *)( iVar1 + 0x48 ), iVar1 + 0x10 );
                return 1;
            }
            iVar1 = iVar1 + 1;
            iVar2 = ( *(code **)( *this + 0x70 ) )();
        } while ( iVar1 < iVar2 );
    }
    return 0;
}