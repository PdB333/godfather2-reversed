// FUNC_NAME: SomeClass::setClearList
void __thiscall SomeClass::setClearList(int listId)
{
    // Store the list identifier/pointer at offset 0xEC
    *(int*)(this + 0xEC) = listId; // +0xEC: m_listId or m_listHandle

    // Log a clear list event; likely debugging/tracking
    DebugPrint("ClearList", 0, &g_clearListData, 0); // FUN_005a04a0
}