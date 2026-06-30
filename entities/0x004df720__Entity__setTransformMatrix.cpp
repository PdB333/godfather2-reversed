// FUNC_NAME: Entity::setTransformMatrix
void __thiscall Entity::setTransformMatrix(int* thisPtr, const unsigned int* sourceMatrix)
{
    // Dereference thisPtr to get the actual object pointer
    int* obj = (int*)*thisPtr;
    if (obj != nullptr)
    {
        // Copy 16 unsigned integers (64 bytes) from sourceMatrix into the object's transform matrix
        // The matrix is stored at offset +0x30 through +0x6C (a 4x4 matrix, 16 floats)
        // Using memcpy for clarity; the original was a series of word copies
        __builtin_memcpy((void*)(obj + 0x0C), sourceMatrix, 0x40); // +0x30 = 0x0C words from obj base
    }
}