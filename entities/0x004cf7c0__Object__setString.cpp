// FUNC_NAME: Object::setString
void __thiscall Object::setString(char* value)
{
    // Member at +0x50 is a pointer to a reference-counted string data
    int** stringDataPtr = reinterpret_cast<int**>(this + 0x50);

    // Release old string (may be two references – e.g., shared and weak?)
    releaseStringData(*stringDataPtr); // FUN_004086d0
    releaseStringData(*stringDataPtr); // FUN_004086d0
    destroyStringData(*stringDataPtr); // FUN_00408310 – final cleanup

    if (value != nullptr && *value != '\0') {
        int newHandle = duplicateString(value); // FUN_004dafd0 – copy or intern
        assignStringDataPtr(stringDataPtr, newHandle); // FUN_00408260 – set pointer
        if (*stringDataPtr != nullptr) {
            notifyStringChanged(this + 0x3c, stringDataPtr); // FUN_00407e60 – callback
        }
    }
}