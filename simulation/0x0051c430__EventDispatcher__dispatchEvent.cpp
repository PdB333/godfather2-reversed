// FUNC_NAME: EventDispatcher::dispatchEvent
// Address: 0x0051c430
// Role: Iterates over a list of registered event handler objects and calls their virtual method at vtable+0x30 (index 12) until one returns non-zero (handled). 
// Structure fields:
//   +0x80 : short m_handlerCount (number of registered handlers)
//   +0xF4 : array of 20-byte structures, each containing a pointer to a handler object at offset 0x00

void __thiscall EventDispatcher::dispatchEvent( int eventData )
{
    // Cast this to appropriate type
    EventDispatcher* self = this;

    // Get the count of registered handlers (signed short at +0x80)
    short handlerCount = *(short*)( (char*)self + 0x80 );

    // If there are any handlers
    if ( handlerCount > 0 )
    {
        // Base pointer to the handler array (each entry is 20 bytes)
        // First 4 bytes of each entry is a pointer to an object with a virtual method table
        char* base = (char*)self + 0xF4;

        for ( int i = 0; i < handlerCount; i++ )
        {
            // Get the pointer at the start of this entry
            void* handlerObject = *(void**)( base + i * 20 );

            // If the handler object is not null
            if ( handlerObject != nullptr )
            {
                // Call the virtual method at vtable offset 0x30 (12th entry, each 4 bytes)
                // The method takes eventData as parameter and returns char (0 = false, non-zero = true)
                // The calling convention is __thiscall (this in ECX, eventData on stack)
                // We use a function pointer typedef for clarity
                typedef char (__thiscall *HandlerMethod)( void* handlerThis, int param );
                HandlerMethod method = *(HandlerMethod*)( *(int**)handlerObject + 0x30 / sizeof(void*) );
                char handled = method( handlerObject, eventData );

                // If the handler returned non-zero (true), stop propagation
                if ( handled != 0 )
                {
                    return;
                }
            }
        }
    }
}