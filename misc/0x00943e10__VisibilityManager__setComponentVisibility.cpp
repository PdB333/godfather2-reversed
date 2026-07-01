// FUNC_NAME: VisibilityManager::setComponentVisibility
void __thiscall VisibilityManager::setComponentVisibility(void *this, const char *componentName, ushort componentBit, char isVisible)
{
    char nameBuffer[256]; // Buffer for constructing property name

    if (isVisible == '\0') {
        // If the component is currently visible (bit set) and we want to hide it
        if ((*(ushort *)((int)this + 0xfc) & componentBit) != 0) {
            // Build property name: componentName + "_visible"
            FUN_00941220(nameBuffer, componentName, "_visible");
            // Set the property to false (0) via some global setter
            FUN_0059ee00(nameBuffer, 0);
            // Clear the visibility bit
            *(ushort *)((int)this + 0xfc) &= ~componentBit;
        }
    }
    else {
        // If the component is currently hidden (bit not set) and we want to show it
        if ((*(ushort *)((int)this + 0xfc) & componentBit) == 0) {
            FUN_00941220(nameBuffer, componentName, "_visible");
            FUN_0059ee00(nameBuffer, 1);
            *(ushort *)((int)this + 0xfc) |= componentBit;
        }
    }
}