// FUN_NAME: ObjectFactory::allocateAndInitVtableFloat
void ObjectFactory::allocateAndInitVtableFloat(float value)
{
    // Global memory pool structure at g_pObjectFactory
    // +0x14: current allocation pointer (int*) – points to next free slot
    int** pCurrentPtr = reinterpret_cast<int**>(reinterpret_cast<char*>(g_pObjectFactory) + 0x14);
    int* currentSlot = *pCurrentPtr;

    // Write vtable pointer into current slot (offset 0)
    *reinterpret_cast<void**>(currentSlot) = reinterpret_cast<void*>(&PTR_LAB_011251a8);

    // Advance slot pointer past vtable
    *pCurrentPtr = currentSlot + 1;

    // Write the float value into the next slot (offset 4)
    int* dataSlot = *pCurrentPtr;
    *reinterpret_cast<float*>(dataSlot) = value;

    // Advance slot pointer past the float
    *pCurrentPtr = dataSlot + 1;
}