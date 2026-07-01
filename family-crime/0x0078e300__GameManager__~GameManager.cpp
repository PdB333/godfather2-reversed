// FUNC_NAME: GameManager::~GameManager
void __fastcall GameManager::~GameManager(GameManager *this)
{
    // Set vtable to debug/base vtable for destruction phase 1
    this->_vtable = &PTR_FUN_00d69b98;
    this->_base2Vtable = &PTR_LAB_00d69b94;

    // Release global reference (e.g., decrement reference count on a global singleton)
    FUN_004086d0(&DAT_012069c4);

    // Release internal resource if it exists
    if (this->_resource != 0) {
        FUN_009c8f10(this->_resource);
    }

    // Switch vtable to final destruction phase (no more virtual calls)
    this->_base2Vtable = &PTR_LAB_00d69b90;

    // Reset global instance counter
    DAT_0112a68c = 0;

    // Perform final cleanup
    FUN_004083d0();
}