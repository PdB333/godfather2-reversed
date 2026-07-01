// FUNC_NAME: UIElementManager::decrementCounterAndHide
void __fastcall UIElementManager::decrementCounterAndHide(int this) {
    int index = getActiveElementIndex(); // FUN_00949380 - returns index of active UI element
    if (index < 0) {
        return;
    }

    // Get pointer to array of element handles (each handle is 8 bytes, second dword is pointer to element struct)
    int* handleArray = *(int**)(this + 0x60);
    int elementPtr = handleArray[index * 2 + 1]; // offset 4 + index*8

    // Decrement counter at offset 0x190 (400 decimal)
    int* counter = (int*)(elementPtr + 0x190);
    *counter = *counter - 1;

    // If counter reaches zero and element has a name string at +0x18, hide it via Flash
    if (*counter == 0) {
        char* elementName = *(char**)(elementPtr + 0x18);
        if (elementName != nullptr && *elementName != '\0') {
            char buffer[256];
            __snprintf(buffer, sizeof(buffer), "%s._visible", elementName);
            setFlashVariable(buffer, 1); // FUN_0059ee00 - sets Flash variable to 1 (visible? Actually 1 might mean hide? But the function name suggests setting visibility)
        }
    }
}