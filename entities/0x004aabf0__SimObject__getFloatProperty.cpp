// FUNC_NAME: SimObject::getFloatProperty
float SimObject::getFloatProperty() const {
    // Access thread-local singleton via FS:[0x2C] (EA engine global manager)
    int* basePtr = **(int**)(__readfsdword(0x2C)); // Get pointer from TLS
    int tableOffset = *(int*)(basePtr + 8);        // Offset into float table (from manager struct at +8)
    int index = *(int*)((char*)this + 0x18);       // Object-specific index (e.g., property id)
    float* floatTable = (float*)(tableOffset + 0x68); // Base address of float table (offset 0x68)
    return floatTable[index];
}