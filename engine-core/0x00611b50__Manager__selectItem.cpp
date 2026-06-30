// FUNC_NAME: Manager::selectItem
void __thiscall Manager::selectItem(int this, int index)
{
    int selectedPointer;
    
    *(int *)(this + 0x138) = index;                                    // +0x138: selected index
    selectedPointer = *(int *)(this + 0x140 + index * 4);              // +0x140: array of object pointers
    *(int *)(this + 0x14) = selectedPointer;                           // +0x14: current selected pointer
    *(int *)(this + 0x10) = *(int *)(this + 0x190 + index * 4);       // +0x190: array of associated values
    if (g_theManagerSingleton == this) {                                // global singleton check
        Manager::onItemSelected(selectedPointer);                      // notify active manager
    }
    Manager::refreshUI();                                              // always refresh
}