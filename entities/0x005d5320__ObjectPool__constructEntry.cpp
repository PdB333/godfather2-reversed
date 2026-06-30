// FUNC_NAME: ObjectPool::constructEntry
void ObjectPool::constructEntry(uint32_t param_1)
{
    // Global memory pool base at DAT_01206880
    // Offset +0x14 holds a pointer to the next free slot (uint8_t**)
    uint8_t** ppNextFree = (uint8_t**)(DAT_01206880 + 0x14);

    // Write vtable pointer of the object class (PTR_LAB_01126bb8)
    *(void**)(*ppNextFree) = (void*)&PTR_LAB_01126bb8;
    *ppNextFree += sizeof(void*); // advance past vtable

    // Write constructor parameter (e.g., object ID or data)
    *(uint32_t*)(*ppNextFree) = param_1;
    *ppNextFree += sizeof(uint32_t); // advance past parameter
}