// FUNC_NAME: initializeGameSystems
void initializeGameSystems(void)
{
    // Local buffer for a temporary object (20 bytes)
    uint8_t tempObject[20]; // +0x00

    // Initialize memory/system allocator
    FUN_0091ebb0();
    // Initialize debug/logging
    FUN_0040a7d0();
    // Construct temp object with flag 0
    FUN_0068b580(tempObject, 0);
    // Initialize physics/collision system
    FUN_0067c4f0();
    // Initialize input/controller system
    FUN_006817d0();
}