// FUNC_NAME: SomeManager::conditionalDelegate
void __thiscall SomeManager::conditionalDelegate(int unusedArg, int arg3, int arg4) {
    // Check if a count or state value stored in this object is less than 2.
    // If so, delegate to another function with the last two arguments.
    if (this->field_0x00 < 2) { // offset of this->someCount is unknown, likely at +0x00
        delegateAction(arg3, arg4); // FUN_00458670
    }
}