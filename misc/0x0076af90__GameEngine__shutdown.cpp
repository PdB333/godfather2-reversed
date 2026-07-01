// FUNC_NAME: GameEngine::shutdown
void __fastcall GameEngine::shutdown(uint32_t *this) {
    int *subsystemManager = (int *)this[0x17]; // +0x5C: pointer to subsystem manager object
    // Set vtable to parent class (base engine)
    *this = (uint32_t)&PTR_LAB_00d65f00;

    // Release various engine subsystems by ID
    Engine::releaseSubsystem(0xd); // Subsystem ID: 13 (e.g., audio)
    Engine::releaseSubsystem(0xc); // Subsystem ID: 12 (e.g., input)
    Engine::releaseSubsystem(0xe); // Subsystem ID: 14 (e.g., graphics)
    Engine::releaseSubsystem(0x37); // Subsystem ID: 55 (e.g., network)
    Engine::releaseSubsystem(0x39); // Subsystem ID: 57 (e.g., physics)
    Engine::releaseSubsystem(3);   // Subsystem ID: 3 (e.g., file system)

    Engine::shutdownCore(); // Cleanup core engine components

    // If the engine was active (flag at +0x80, bit 0), notify subsystem manager
    if ((*(uint8_t *)(this + 0x20) & 1) != 0) { // +0x80: active flag
        // Call virtual function at vtable+0x290 (index 164) on subsystem manager
        (*(void (__fastcall **)(int, int, int))(*subsystemManager + 0x290))(1, 1);
    }

    // Deallocate memory buffer at +0x70 if non-null
    if (this[0x1c] != 0) { // +0x70: pointer to some buffer
        Memory::deallocate((void *)(this + 0x1c)); // +0x1c offset from this? Actually it's this[0x1c] which is a pointer
    }

    // Switch vtable to another parent class
    *this = (uint32_t)&PTR_LAB_00d63090;

    // Deallocate second buffer at +0x68 if non-null
    if (this[0x1a] != 0) { // +0x68: pointer to another buffer
        Memory::deallocate((void *)(this + 0x1a));
    }

    // Final engine cleanup (e.g., deinitialize memory managers)
    Engine::finalCleanup();
}