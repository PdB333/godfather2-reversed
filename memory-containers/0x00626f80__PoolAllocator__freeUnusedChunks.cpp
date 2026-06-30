// FUNC_NAME: PoolAllocator::freeUnusedChunks
// Function at 0x00626f80: Iterates through a singly-linked free list of chunks.
// For each chunk: if the chunk size (byte at +5) is greater than threshold,
// clear its "free" flag (bit 0); otherwise remove it from list and deallocate.
// Returns number of chunks removed.

int PoolAllocator::freeUnusedChunks(int threshold)
{
    // 'this' is in_EAX; points to a pointer to the head of the free list.
    // This member is at offset 0 from this.
    Chunk* current = *reinterpret_cast<Chunk**>(this);
    int removedCount = 0;

    while (current != nullptr)
    {
        // +5: byte storing chunk size (or a small tag that includes size)
        unsigned int chunkSize = static_cast<unsigned int>(current->sizeByte); // byte at +5

        if (threshold < static_cast<int>(chunkSize))
        {
            // Chunk is too large; clear flag (bit 0) to mark it as "in use" or "non-freeable"
            current->flags &= 0xfe;  // byte at +5
            // Update the list head pointer stored in 'this' to keep it as the new head?
            // But the code does: in_EAX = puVar1; so it continues iteration from this node.
            // Actually, the pointer to the head is stored at *this.
            *reinterpret_cast<Chunk**>(this) = current;
        }
        else
        {
            // Chunk size <= threshold: remove it from list
            *reinterpret_cast<Chunk**>(this) = current->next; // advance head
            removedCount++;
            // Deallocate the chunk
            FUN_00626ed0();  // likely freeChunk(current);
        }

        // Move to next node
        current = *reinterpret_cast<Chunk**>(this);
    }

    return removedCount;
}