// FUNC_NAME: EARSArray::adjustWritePointer
// Function at 0x006255e0: adjusts a write pointer in a dynamic array of 8-byte elements.
// The container structure (unknown full layout) has at offsets +0x08 (current write pointer) and +0x0c (end/capacity pointer).
// For positive offset, zeroes elements from current to end+offset*8 and sets pointer there.
// For negative offset, moves pointer back by (offset+1)*8 bytes (i.e., move back by |offset+1| elements, with -1 meaning no move).

class EARSArray
{
public:
    int* mWritePointer; // +0x08
    int* mEndPointer;   // +0x0c

    void __thiscall adjustWritePointer(int offset)
    {
        if (offset < 0)
        {
            // Move write pointer backwards: (offset+1)*8 bytes
            mWritePointer = mWritePointer + offset * 8 + 8;
        }
        else
        {
            int newByteOffset = offset * 8;

            // Zero first 4 bytes of each slot from current to end+newByteOffset
            while ((unsigned int)mWritePointer < (unsigned int)(mEndPointer + newByteOffset))
            {
                *reinterpret_cast<int*>(mWritePointer) = 0;
                mWritePointer += 8;
            }

            // Set write pointer to end+newByteOffset
            mWritePointer = mEndPointer + newByteOffset;
        }
    }
};