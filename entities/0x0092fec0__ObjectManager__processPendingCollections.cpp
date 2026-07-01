// FUNC_NAME: ObjectManager::processPendingCollections
void __thiscall ObjectManager::processPendingCollections( int this )
{
    int *list1Base;
    int list1Count;
    int *list2Base;
    int list2Count;
    int objectId;
    int *entryPtr;
    int currentIndex;
    uint i;

    // Mark beginning of collection processing (e.g., log or synchronize)
    FUN_0092faf0( 1 );

    list1Base = ( int * )( *( int * )DAT_0112ebb4 + 0xf0 );
    list2Base = ( int * )( *( int * )DAT_0112ebb4 + 0xfc );
    list1Count = *( int * )( *( int * )DAT_0112ebb4 + 0xf4 );
    list2Count = *( int * )( *( int * )DAT_0112ebb4 + 0x100 );

    // Only proceed if the global game flag is set and this object's flag is non-null
    if ( ( DAT_01223484 != 0 ) && ( *( int * )( this + 0x16c ) != 0 ) )
    {
        // Process first collection (e.g., pending removals)
        if ( ( list1Count != 0 ) && ( list1Base != ( int * )0x0 ) )
        {
            i = 0;
            do
            {
                // Resolve object ID to a game object pointer
                objectId = FUN_004baf90( *( undefined4 * )( *list1Base + i * 4 ) );
                // Get the underlying object (e.g., script object) from the game object
                int obj = FUN_0092e040( objectId );
                if ( obj != 0 )
                {
                    // Notify or process the object (e.g., mark for removal)
                    FUN_0092f240( obj );
                }
                i = i + 1;
            } while ( i < ( uint )list1Count );
        }

        // Process second collection (e.g., pending additions)
        if ( ( list2Count != 0 ) && ( list2Base != ( int * )0x0 ) )
        {
            i = 0;
            do
            {
                objectId = FUN_004baf90( *( undefined4 * )( *list2Base + i * 4 ) );
                int obj = FUN_0092e040( objectId );
                if ( obj != 0 )
                {
                    // Grow the local buffer if needed
                    int capacity = *( int * )( this + 0xe4 );
                    int count = *( int * )( this + 0xe0 );
                    if ( count == capacity )
                    {
                        if ( capacity == 0 )
                        {
                            capacity = 1;
                        }
                        else
                        {
                            capacity = capacity * 2;
                        }
                        FUN_0092db60( capacity );
                    }
                    // Append the object to the local buffer
                    entryPtr = ( int * )( *( int * )( this + 0xdc ) + *( int * )( this + 0xe0 ) * 4 );
                    *( int * )( this + 0xe0 ) = *( int * )( this + 0xe0 ) + 1;
                    if ( entryPtr != ( int * )0x0 )
                    {
                        *entryPtr = obj;
                    }
                }
                i = i + 1;
            } while ( i < ( uint )list2Count );
        }
    }

    // Invoke a virtual notification callback (e.g., onProcessingComplete)
    ( ** ( code ** )( *( int * )( this + 0x84 ) + 0x6c ) )( *( undefined4 * )( this + 0x128 ) );
    return;
}