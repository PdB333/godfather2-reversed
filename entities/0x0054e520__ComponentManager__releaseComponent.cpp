// FUNC_NAME: ComponentManager::releaseComponent
// Address: 0x0054e520
// Releases the sub-object stored at offset +0x1c by forwarding to a destructor/release function.
void __fastcall ComponentManager::releaseComponent(int thisPtr)
{
    // +0x1c: pointer to the component instance that must be released
    FUN_0054e3d0(*(int*)(thisPtr + 0x1c));
}