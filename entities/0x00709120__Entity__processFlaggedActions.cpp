// FUNC_NAME: Entity::processFlaggedActions
void __thiscall Entity::processFlaggedActions( void )
{
    int *nodePtr;
    int listTail;
    int newNode;
    int unknownValue;
    char buffer[76];
    int sourceListHead;

    // Check if any of the four flags at offsets 0x88-0x8B are set.
    if ( ( this->flags[0] != 0 ) || ( this->flags[1] != 0 ) || 
         ( this->flags[2] != 0 ) || ( this->flags[3] != 0 ) )
    {
        // Get some current value (e.g., time or ID) and format it into buffer
        unknownValue = getCurrentTime(); // FUN_00471610
        formatString( buffer, unknownValue ); // FUN_0044b4e0

        // Call virtual function at vtable+0x58 (e.g., getResourceID)
        int resourceID = ( *(code **)( *(int *)this + 0x58 ) )( 0, this, -1, 0 );

        // Create a new node from the flags and buffer, and obtain the head of a source list
        sourceListHead = createNodeFromFlags( &listTail, &this->flags[0x88/sizeof(int)], buffer, resourceID ); // FUN_004df330

        nodePtr = &this->pendingListHead; // offset 0x8C

        // If there's an existing head, clear its prev pointer and zero the head
        if ( *nodePtr != 0 )
        {
            *( (int *)( *nodePtr ) + 2 ) = 0; // node->prev = NULL
            *nodePtr = 0;
        }

        // Move the new node from the source list to our list
        newNode = *sourceListHead;
        *nodePtr = newNode;
        if ( newNode != 0 )
        {
            *( (int **)( newNode + 8 ) ) = nodePtr; // newNode->prev = &pendingListHead
            *sourceListHead = 0; // detach from source
        }

        // If there was a tail in the source list, clear its next? (prev pointer)
        if ( listTail != 0 )
        {
            *( (int *)( listTail + 8 ) ) = 0; // tail->prev = NULL (safe cleanup)
        }
    }
}