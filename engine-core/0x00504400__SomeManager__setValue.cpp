// FUNC_NAME: SomeManager::setValue
void SomeManager::setValue(int value) {
    // Get the internal structure pointer from the global manager instance
    int* internalStruct = reinterpret_cast<int*>(FUN_00505c90(g_pSomeManager));
    // Set field at offset +8 (2 ints) to the provided value
    internalStruct[2] = value; // +0x08
}