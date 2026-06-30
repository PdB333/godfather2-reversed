// FUNC_NAME: MemoryManager::Deallocate
void __fastcall MemoryManager::Deallocate(void* pObject)
{
    // Check if reference count or some flag at offset 0x28 is non-zero
    // If so, call the object's destructor
    if (*(int*)((char*)pObject + 0x28) != 0) {
        FUN_004ff430(); // likely destructor
    }

    // Free list management:
    // Global buffer pointer is at DAT_01206880 + 0x14 (likely a bump allocator cursor)
    int* pCursorPtr = (int*)(DAT_01206880 + 0x14);
    
    // Write freed-object sentinel vtable at current cursor position
    **(void***)pCursorPtr = (void*)&PTR_LAB_011252c4;
    
    // Advance cursor by 4 (skip vtable write)
    *pCursorPtr += 4;
    
    // Align to next 4-byte boundary
    int* pAligned = (int*)((*pCursorPtr + 3) & 0xFFFFFFFC);
    *pCursorPtr = (int)pAligned;
    
    // Store the freed object pointer
    *pAligned = (int)pObject;
    
    // Advance cursor past the pointer
    *pCursorPtr += 4;
}