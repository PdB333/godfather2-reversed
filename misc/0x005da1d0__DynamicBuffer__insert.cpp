// FUNC_NAME: DynamicBuffer::insert
// Address: 0x005da1d0
// Role: Inserts a block of elements into a dynamic buffer (array of 0x28-byte structs).
// Uses a growth factor of 1.5x when capacity is exceeded.

void __thiscall DynamicBuffer::insert( uint count, void* pData )
{
    int iUsed;
    uint uCapacity;
    int iNewCapacity;
    int iNewBuf;
    uint uAlignedCount;
    int iRet;
    uint uTemp;
    int iOldBufEnd;

    // Current buffer start (if null, capacity is 0)
    int* pBuf = this->m_pBuffer; // +0x08
    if ( pBuf == nullptr )
    {
        uCapacity = 0;
    }
    else
    {
        // capacity = (endAlloc - start) / sizeof(element)
        uCapacity = ( this->m_pEndAlloc - pBuf ) / 0x28;
    }

    if ( count == 0 )
        return;

    // Current used count
    if ( pBuf == nullptr )
    {
        iUsed = 0;
    }
    else
    {
        iUsed = ( this->m_pEnd - pBuf ) / 0x28;
    }

    // Overflow check: max elements is 0x6666666 (approx 107M)
    if ( 0x6666666U - iUsed < count )
    {
        DynamicBuffer::errorOutOfMemory(); // 0x005d9ed0
        return;
    }

    // Check if we need to grow the buffer
    if ( uCapacity < iUsed + count )
    {
        // New capacity = old capacity * 1.5
        if ( 0x6666666 - ( uCapacity >> 1 ) < uCapacity )
        {
            uTemp = 0;
        }
        else
        {
            uTemp = uCapacity + ( uCapacity >> 1 );
        }

        // Recompute used count (in case buffer was null)
        if ( pBuf == nullptr )
        {
            iUsed = 0;
        }
        else
        {
            iUsed = ( this->m_pEnd - pBuf ) / 0x28;
        }

        // If new capacity still insufficient, allocate exact needed size
        if ( uTemp < iUsed + count )
        {
            int iAllocSize = DynamicBuffer::calculateNewAllocSize(); // 0x005d9a60
            uTemp = iAllocSize + count;
        }

        // Allocate new buffer
        iNewBuf = DynamicBuffer::allocateNewBuffer(); // 0x005da050

        // Round count to 256-byte alignment for copy operations
        uAlignedCount = ( count >> 8 ) << 8;     // = (count / 256) * 256

        // Copy old data to new buffer
        void* pNewStart = DynamicBuffer::memcpy( pBuf, uAlignedCount, uAlignedCount ); // 0x005dab00
        DynamicBuffer::padOrMove( pNewStart, uAlignedCount, uAlignedCount ); // 0x005da830

        // Copy source data after old data
        DynamicBuffer::memcpy( pData, uAlignedCount, uAlignedCount ); // 0x005dab00 (returns new pointer?)

        // If old buffer existed, call its destructor (virtual call via vtable+4)
        int iOldBuf = this->m_pBuffer;
        if ( iOldBuf != 0 )
        {
            int iOldCapacity = ( this->m_pEndAlloc - iOldBuf ) / 0x28;
            (*(code**)(*(int*)this->m_pVtable + 4))( iOldBuf, iOldCapacity * 0x28 ); // vtable+4 likely deallocate
        }

        // Update pointers
        this->m_pEndAlloc = iNewBuf + uTemp * 0x28;
        this->m_pEnd = iNewBuf + ( count + iUsed ) * 0x28;
        this->m_pBuffer = iNewBuf;
        return;
    }

    // Enough capacity; shift elements to make room
    iOldBufEnd = this->m_pEnd; // current end pointer
    if ( ( (uint)( iOldBufEnd - (int)pData ) / 0x28 ) < count )
    {
        // Insertion point is near the end, shift data forward
        int iBytes = count * 0x28;
        DynamicBuffer::memmove( iOldBufEnd, iBytes + (int)pData ); // 0x005da6d0 - shift elements
        DynamicBuffer::padOrMove( this->m_pEnd, count, count ); // 0x005da830
        this->m_pEnd = this->m_pEnd + iBytes;
        DynamicBuffer::freeData( pData ); // 0x005da8a0 - release source?
        return;
    }

    // Insert in middle: shift data from insertion point to end
    int iNewEnd = DynamicBuffer::memmove( iOldBufEnd, iOldBufEnd ); // 0x005da6d0
    this->m_pEnd = iNewEnd;
    DynamicBuffer::shiftAndCopy( pData, iOldBufEnd + count * -0x28 ); // 0x005da710
    DynamicBuffer::freeData( pData ); // 0x005da8a0
}