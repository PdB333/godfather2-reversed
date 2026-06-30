// FUNC_NAME: GodfatherGameManager::getInstance
// Address: 0x00556650
// Returns a pointer to the GodfatherGameManager singleton via a buffer-based lookup.
// The constant 0x802 is likely a class ID or hash used by the engine's singleton registry.
GodfatherGameManager* GodfatherGameManager::getInstance()
{
    // Temporary buffer (12 bytes) to receive the singleton pointer from the engine's internal registry.
    uint32_t buffer[3];
    
    // Call the engine's singleton retrieval function with the class ID 0x802.
    // FUN_004af8c0 fills buffer[0] with the pointer to the singleton instance.
    FUN_004af8c0(buffer, 0x802);
    
    // Return the pointer stored in the first element of the buffer.
    return reinterpret_cast<GodfatherGameManager*>(buffer[0]);
}