// FUNC_NAME: EntityManager::isPointerValid
bool __fastcall EntityManager::isPointerValid(void* pointerToCheck) // param_1 in ECX is 'this'
{
    if (pointerToCheck != nullptr)
    {
        // +0x603c: pointer to the start of an array of objects (each 0x74 bytes)
        int index = (static_cast<char*>(pointerToCheck) - this->m_objectArrayBase) / 0x74;
        // Callee FUN_005e5e60 checks if the index is valid (likely within array bounds)
        char result = isIndexValid(index, 1); // second parameter 1 might indicate index validity check
        return result != '\0';
    }
    return false;
}