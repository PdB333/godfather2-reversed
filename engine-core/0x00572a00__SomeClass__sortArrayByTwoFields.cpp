// FUNC_NAME: SomeClass::sortArrayByTwoFields
void SomeClass::sortArrayByTwoFields(int count)
{
    // Array of 0x20-byte structures starts at this+0x04
    // Each structure has two short fields: field0 at offset 0, field1 at offset 0x0A
    if (count <= 1) return;

    short* base = reinterpret_cast<short*>(reinterpret_cast<char*>(this) + 4);
    int i = 1;
    while (i < count)
    {
        short* current = base + (i * 0x10); // 0x10 shorts = 0x20 bytes per element
        int j = i;
        while (j > 0)
        {
            short* prev = current - 0x10; // previous element
            // Compare: next element's field0 < current's field0, or equal and next's field1 < current's field1
            if (current[0x10] < *prev || (current[0x10] == *prev && current[0x15] < prev[5]))
            {
                // Swap 32 bytes (4 qwords)
                uint64_t tmp0 = *reinterpret_cast<uint64_t*>(prev + 0x0E);
                uint64_t tmp1 = *reinterpret_cast<uint64_t*>(prev + 0x12);
                uint64_t tmp2 = *reinterpret_cast<uint64_t*>(prev + 0x16);
                uint64_t tmp3 = *reinterpret_cast<uint64_t*>(prev + 0x1A);
                *reinterpret_cast<uint64_t*>(prev + 0x0E) = *reinterpret_cast<uint64_t*>(current - 2);
                *reinterpret_cast<uint64_t*>(prev + 0x12) = *reinterpret_cast<uint64_t*>(current + 2);
                *reinterpret_cast<uint64_t*>(prev + 0x16) = *reinterpret_cast<uint64_t*>(current + 6);
                *reinterpret_cast<uint64_t*>(current - 2) = tmp0;
                *reinterpret_cast<uint64_t*>(current + 2) = tmp1;
                *reinterpret_cast<uint64_t*>(current + 6) = tmp2;
                *reinterpret_cast<uint64_t*>(prev + 0x1A) = *reinterpret_cast<uint64_t*>(current + 10);
                *reinterpret_cast<uint64_t*>(current + 10) = tmp3;
                current = prev;
                j--;
            }
            else
            {
                break;
            }
        }
        i++;
    }
}