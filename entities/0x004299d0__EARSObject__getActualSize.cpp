// FUNC_NAME: EARSObject::getActualSize

int EARSObject::getActualSize() {
    int baseSize;
    // Calls internal function to retrieve the object's base size (e.g., from a vtable or allocation header)
    getBaseSize(&baseSize, this);
    // Add 4 bytes for the object header (e.g., vtable pointer or size field)
    return baseSize + 4;
}