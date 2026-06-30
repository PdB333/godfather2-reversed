// FUN_004aaac0: InputManager::getControllerAxisValue
float __fastcall getControllerAxisValue(void* thisPtr)
{
    // Access TLS (Thread Local Storage) to get base address of input state table.
    // FS:[0x2C] is the TLS pointer array.
    // First dereference: get pointer to TLS array.
    int** tlsArrayPtr = (int**)__readfsdword(0x2C);
    // Second dereference: get base address of input data (likely an array of structures).
    int* inputDataBase = *tlsArrayPtr;  // Base of input state table.
    // Read offset from base + 8 (probably pointer to an array of floats for analog axes).
    int axisArrayPtr = *(int*)((char*)inputDataBase + 8);
    // Calculate address of desired axis: base of axis array + 0x74 + index.
    // 0x74 is likely a fixed offset within the per-controller structure to the axis values.
    int axisIndex = *(int*)((char*)thisPtr + 0x18); // Index into axis array (e.g., left stick X).
    float axisValue = *(float*)(axisArrayPtr + 0x74 + axisIndex);
    return axisValue;
}