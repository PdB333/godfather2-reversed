// FUNC_NAME: GodfatherGameManager::setIndexedFloat
int __fastcall GodfatherGameManager::setIndexedFloat(uint index, float value)
{
    // Check if element array exists and index is valid (max 512 entries)
    if (m_elementArray != 0 && index < 0x200)
    {
        // Element structure is 0x74 bytes each
        Element* element = &m_elementArray[index];
        
        // Validate that the element is active (first field non-zero)
        if (element->m_handle != 0)
        {
            void* associatedObject = element->m_associatedObject; // +0x08
            
            // Store the float at offset 0x60 within the element
            element->m_storedFloat = value;
            
            // Notify a secondary system (e.g., audio or animation) of the new value
            FUN_005dbc10(index, (double)value);
            
            // If there is an associated object, update its float at +0x4c as well
            if (associatedObject != 0)
            {
                *(float*)((char*)associatedObject + 0x4c) = value;
                return 1;
            }
        }
    }
    return 0;
}