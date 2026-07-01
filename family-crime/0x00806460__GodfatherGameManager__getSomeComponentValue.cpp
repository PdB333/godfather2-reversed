// FUNC_NAME: GodfatherGameManager::getSomeComponentValue
uint32_t __fastcall GodfatherGameManager::getSomeComponentValue(void* thisPtr)
{
    // offset 0x1ed8: pointer to sub-component (likely a data block or manager)
    if (*(void**)((uint8_t*)thisPtr + 0x1ed8) != nullptr) {
        // offset 0x40 from sub-component: requested value (e.g., an ID, flag, or counter)
        return *(uint32_t*)(*(uint8_t**)((uint8_t*)thisPtr + 0x1ed8) + 0x40);
    }
    // global constant at 0x88 (probably 0 or sentinel)
    return *(uint32_t*)0x88;
}