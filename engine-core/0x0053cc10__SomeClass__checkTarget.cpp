// FUNC_NAME: SomeClass::checkTarget
void __thiscall SomeClass::checkTarget(void) {
    undefined4 localVector[4]; // Vector4 or similar struct

    // Base class update or common per-frame function
    BaseClass::update(); // FUN_00612a60

    // Check if our entity type matches the expected global type
    if ((this->mEntityType == s_expectedEntityType) && (s_targetManager != nullptr)) {
        // Initialize local vector to zero
        localVector[0] = 0;
        localVector[1] = 0;
        localVector[2] = 0;
        localVector[3] = 0;

        // Set target position relative to our entity and the target manager
        SomeManager::setPosition(this->mEntityType, s_targetManager, localVector); // FUN_0060add0
    }
}