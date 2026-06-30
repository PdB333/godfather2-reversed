// FUNC_NAME: MemoryManager::freeObject

void MemoryManager::freeObject(void* ptr)
{
    // Pointer is expected in EAX (possibly __fastcall or custom ABI)
    if (ptr == nullptr) {
        return;
    }

    // Interpret the first DWORD as a type tag / sentinel
    int* tag = static_cast<int*>(ptr);
    if ((*tag != 0) && (*tag != 0x48)) {
        // Unexpected tag value – might be memory corruption or wrong type
        // Call likely debug/reporting function
        FUN_00449e90();  // DebugReport("Invalid memory tag")
    }

    // Perform actual deallocation (likely free or pool release)
    FUN_004e97e0(ptr);
}