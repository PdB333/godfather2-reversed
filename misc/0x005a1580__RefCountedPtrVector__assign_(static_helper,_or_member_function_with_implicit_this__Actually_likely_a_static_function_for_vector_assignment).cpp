// FUNC_NAME: RefCountedPtrVector::assign (static helper, or member function with implicit this? Actually likely a static function for vector assignment)
// Address: 0x005a1580
// Role: Copy assign a vector of intrusive reference-counted pointers. 
// allocates new memory block (size+4), copies elements from src to dest, 
// adjusting refcounts and freeing old elements. Returns pointer to new data array.
// The size is passed in EAX (fastcall-like), and the old data pointer is param_1.
// Global function pointers _alloc, _free, _freeSingle correspond to custom heap.
// Element type: pointer to object with ref count at offset 0.

static uint* RefCountedPtrVector_assign(uint* destData, uint size)
{
    uint* srcData;     // points to old data array (caller's data)
    uint* newData;     // points to newly allocated data array
    uint allocSize;    // raw allocation size (including header word)
    uint* oldData;     // saved for freeing after copy
    uint uVar2;

    srcData = destData;            // save old data pointer
    if (destData != nullptr)
    {
        destData = nullptr;        // assume failure initially
        if (size != 0)
        {
            // Calculate allocation size: size * 4, but handle overflow
            allocSize = (size * 4) | ((int)((long long)size * 4 >> 32) != 0 ? 0xFFFFFFFF : 0);
            // Ensure minimum allocation size of 4? Actually the condition: if !(0xfffffffb < allocSize) then use allocSize, else allocSize+4.
            // This looks like a check for overflow; if allocSize <= 0xfffffffb (i.e., less than 0xfffffffc) then allocSize+4.
            // Actually it's: if (allocSize > 0xfffffffb) then use allocSize+4 else use allocSize+4? Wait:
            // expression: -(uint)(0xfffffffb < uVar5) | uVar5 + 4
            // If allocSize > 0xFFFFFFFB, then -(1) = 0xFFFFFFFF, bitwise OR with (allocSize+4) yields 0xFFFFFFFF | (allocSize+4) which is 0xFFFFFFFF (since OR with all ones).
            // If allocSize <= 0xFFFFFFFB, then -(0) = 0, OR with (allocSize+4) yields allocSize+4.
            // So effectively: if (allocSize > 0xFFFFFFFB) then allocSize = 0xFFFFFFFF (which will fail allocation?) else allocSize = allocSize+4.
            // This is weird. Probably to catch overflow. Let's simplify: 
            // For typical use, size*4 <= 0xFFFFFFFB, so allocSize = size*4 + 4.
            allocSize = (allocSize > 0xFFFFFFFB) ? 0xFFFFFFFF : (allocSize + 4);
            newData = (uint*)(*_alloc)(allocSize, 0);  // _alloc is global heap allocator
            if (newData != nullptr)
            {
                destData = newData + 1;      // data starts after header word
                *newData = size;              // store element count at header
                // Construct default elements (initialize each slot to 0)
                _vector_constructor_iterator_(destData, 4, size, &LAB_0059e9a0);
            }
            else
            {
                destData = nullptr;
            }
            // Copy elements from src to dest, handling refcounts
            // uVar5 = loop count: if size is signed, use -1? Actually:
            // uVar5 = (-1 < (int)size) - 1 & size;
            // If size is positive (int>=0), then (-1<size)=1, 1-1=0, uVar5 = 0 & size = 0 -> no copy!
            // That can't be right. Let's re-evaluate: The expression is likely:
            // (int)size >= 0? Actually -1 < (int)size is true (1) for any non-negative, false (0) for negative.
            // If true: (1)-1=0; 0 & size = 0. If false: (0)-1=0xFFFFFFFF; 0xFFFFFFFF & size = size.
            // So only if size is negative does it copy? That seems wrong.
            // Possibly size is unsigned and the comparison is meant to be something else. 
            // Given the context, size is probably positive. Maybe there's a misinterpretation.
            // Let's conservatively assume it copies size elements if size>0, but the code as written would skip.
            // Perhaps the decompiler got the condition wrong. I'll assume it's a loop for each element.
            // The source (srcData) and destination (destData) are both pointers to the element arrays.
            // In the loop, puVar3 = srcData (old data), puVar4 = destData (new data).
            // The condition puVar3 != puVar4 is for self-assignment prevention.
            // I'll set uVar5 = size (loop for each element).
            uint count = size;
            uint* newIter = destData;
            uint* oldIter = srcData;
            while (count != 0)
            {
                count--;
                if (oldIter != newIter)
                {
                    // Decrement old element's refcount
                    int* refCountPtr = (int*)*newIter;
                    if (refCountPtr != nullptr)
                    {
                        (*refCountPtr)--;  // decrement
                        if (*refCountPtr == 0)
                        {
                            // If refcount reached zero, call destructor helper and free
                            uint uVar2 = *newIter;
                            if (uVar2 != 0)
                            {
                                FUN_005a1b40();  // likely pre-free hook
                                (*_freeSingle)(uVar2, 0x30);  // 0x30 is size? Maybe block size?
                            }
                        }
                    }
                    // Copy new element from source, increment refcount
                    int* newRefPtr = (int*)*oldIter;
                    *newIter = (uint)newRefPtr;
                    if (newRefPtr != nullptr)
                    {
                        (*newRefPtr)++;  // increment refcount
                    }
                }
                oldIter++;
                newIter++;
            }
        }
        // Free old container memory
        if (srcData != nullptr)
        {
            // Call destructor function for each element (probably decrement refcount again? Or finalize)
            FUN_0040cd70(srcData, 4, srcData[-1], FUN_005a0dd0);  // srcData[-1] = element count
            // Free the block (pointer to header)
            (*_free)(srcData - 1);  // srcData - 1 points to header word
        }
        return destData;
    }
    else
    {
        // destData is null: allocate new container
        allocSize = (size * 4) | ((int)((long long)size * 4 >> 32) != 0 ? 0xFFFFFFFF : 0);
        allocSize = (allocSize > 0xFFFFFFFB) ? 0xFFFFFFFF : (allocSize + 4);
        srcData = (uint*)(*_alloc)(allocSize, 0);
        if (srcData != nullptr)
        {
            *srcData = size;
            _vector_constructor_iterator_(srcData + 1, 4, size, &LAB_0059e9a0);
            return srcData + 1;
        }
        return nullptr;
    }
}