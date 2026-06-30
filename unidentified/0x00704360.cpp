// FUN_00704360: handleItemActivation
// This function takes a handle (param_1) and attempts to activate/process the corresponding item.
// It first looks up an internal index via getItemIndexFromHandle (FUN_00704150);
// if the index is valid (not -1), it calls processItemByIndex (FUN_00704260) to perform the action.
void handleItemActivation(int handle)
{
    int itemIndex = getItemIndexFromHandle(handle);
    if (itemIndex != -1) {
        processItemByIndex(itemIndex);
    }
}