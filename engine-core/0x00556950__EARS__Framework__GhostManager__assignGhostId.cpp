// FUNC_NAME: EARS::Framework::GhostManager::assignGhostId
void __thiscall GhostManager::assignGhostId(uint32_t localObjectId, GhostObject* destObject, void* contextData)
{
    // in_EAX is an uninitialized register value from the original; we ignore it here.
    // Validate or pre-process the ghost assignment (first two args zero suggest no flags)
    FUN_00556ab0(0, 0, contextData, this, /* in_EAX ignored */0);

    // Set ghost ID: encode object index with type tag (0xC0000000 indicates a ghost)
    destObject->mGhostId = (localObjectId >> 2) | 0xC0000000;  // +0x2C

    // Update internal ghost state (singleton flush?)
    FUN_0043b490();

    // Log event 0x2001 (likely "Ghost ID assigned") with context
    FUN_009f01f0(0x2001, contextData, 0);
}