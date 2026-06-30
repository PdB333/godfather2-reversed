// FUNC_NAME: GlobalManager::dispatchVirtual0xBC
// Address: 0x005e3d90
// Calls a virtual function at offset 0xBC on a global manager object (DAT_01223510).
// This is a static dispatch wrapper, ignoring the first parameter (param1/ECX).
// The offset 0xBC likely corresponds to a member function like ProcessPacket or UpdateState.

void __fastcall dispatchVirtual0xBC(int param1, int param2, int param3)
{
    // Dereference global singleton pointer (e.g., g_netSession, g_gameManager)
    // Offset 0xBC in vtable of that object
    // Call the virtual function with param2 and param3
    (**(void (__fastcall **)(int, int))(*(int *)g_globalManager + 0xBC))(param2, param3);
}