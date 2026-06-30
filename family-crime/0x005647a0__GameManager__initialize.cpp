// FUNC_NAME: GameManager::initialize
void GameManager::initialize(GameManager* this)
{
    // Store singleton global reference
    DAT_012234d8 = this;

    // Set vtable pointer to GameManager's vtable
    this->vtable = (void**)&GameManager_VTable;

    // Initialize member fields
    this->field_4 = 5;  // +0x04
    this->field_C = 5;  // +0x0C
}