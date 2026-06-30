// FUNC_NAME: copyIntArray
// Address: 0x00657ca0
// Copies an array of 32-bit integers from an external source to an internal buffer.
// The destination buffer pointer is stored at offset +0x8 of the object (this in EDI).
// The number of elements to copy is passed in the ESI register (not a function parameter).

void __thiscall copyIntArray( int* source )
{
    // The count is expected to be set in ESI before this call.
    // For reconstruction we assume a variable 'count' holds that value.
    uint count = static_cast<uint>(unaff_ESI);   // unaff_ESI holds the element count

    if ( count != 0 )
    {
        uint i = 0;
        do
        {
            // Retrieve the destination array pointer from object at offset +0x8
            int* destArray = *(int**)( reinterpret_cast<byte*>(this) + 8 );

            // The original code checks the computed address (destArray + i) for null, 
            // which is a likely decompilation artifact. The intended check is that
            // the destination array pointer itself is not null.
            if ( destArray != nullptr )
            {
                destArray[ i ] = source[ i ];
            }
            i++;
        } while ( i < count );
    }
}