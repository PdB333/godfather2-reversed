// FUNC_NAME: TLSBuffer::SetFloat4
// Address: 0x004fc930
// Role: Copies 4 DWORDs (assumed float4) from source array into a thread-local storage buffer.
//       The destination address is computed via a chain of indirections starting from FS segment TLS data.
void TLSBuffer::SetFloat4( int param_1, const unsigned int* source )
{
    // Load thread-local storage base (FS:[0x2C])
    void* tlsPointer = reinterpret_cast<void*>( __readfsdword( 0x2C ) );

    // Double indirection: first get a pointer from the TLS structure, then read an int from that address.
    int temp = *reinterpret_cast<int*>( *reinterpret_cast<void**>( tlsPointer ) );

    // Add 8 (byte offset) to that int, treat as pointer, and dereference again to get another int.
    int offset = *reinterpret_cast<int*>( temp + 8 );

    // Compute final destination: base offset 0x40 + an additional offset from param_1+0x10.
    unsigned int* destination = reinterpret_cast<unsigned int*>(
        offset + 0x40 + *reinterpret_cast<int*>( param_1 + 0x10 )
    );

    // Copy 4 DWORDs from source into computed destination.
    destination[0] = source[0];
    destination[1] = source[1];
    destination[2] = source[2];
    destination[3] = source[3];
}