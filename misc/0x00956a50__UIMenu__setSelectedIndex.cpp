// FUNC_NAME: UIMenu::setSelectedIndex
void __thiscall UIMenu::setSelectedIndex(int newIndex, bool skipSelectCallback)
{
    if (newIndex < 0)
        return;

    // Submenu object array at +0x54, current submenu index at +0x6c
    SubMenu* currentSubMenu = *(SubMenu**)((char*)this + 0x54 + *(int*)((char*)this + 0x6c) * 4);

    // Virtual call: getItemCount() at vtable+0x70
    int itemCount = currentSubMenu->vtbl->getItemCount();
    if (newIndex < itemCount)
    {
        // Store the selected index at +0x74
        *(int*)((char*)this + 0x74) = newIndex;

        // If skipSelectCallback is false, call the sub-menu's selectItem virtual at vtable+0x78
        if (!skipSelectCallback)
            currentSubMenu->vtbl->selectItem(newIndex);

        // Notify the UI system (debug/log update)
        FUN_005a04a0("UpdateSubMenu", 0, &DAT_00d8c174, 0);
    }
}