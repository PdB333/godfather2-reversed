// FUNC_NAME: SingletonManager::SingletonManager
// Reconstructed constructor for a singleton manager class (address 0x00565cc0)
// Stores the instance pointer in a global variable and initializes the vtable.

void __fastcall SingletonManager::SingletonManager(undefined4 *this)
{
    // +0x00: vtable pointer (set to PTR_LAB_00e3a59c)
    *this = &PTR_LAB_00e3a59c;  // vtable for SingletonManager

    // Store this instance globally
    DAT_0122343c = this;
}