// FUNC_NAME: Entity::addToActiveList
void __fastcall Entity::addToActiveList()
{
    // Register the node at offset 0x1c with the manager (type 1, no flags)
    FUN_008c51a0(1, reinterpret_cast<int>(&reinterpret_cast<char*>(this)[0x1c]), 0);
}