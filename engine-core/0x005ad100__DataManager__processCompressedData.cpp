// FUNC_NAME: DataManager::processCompressedData
void __fastcall DataManager::processCompressedData(void* ecx, void* edx, uint sourceSize) {
    uint destSize = 0;
    byte stackBuffer[512]; // local_200
    byte smallBuffer[16];  // local_210, likely for small allocations
    byte* dataPtr = nullptr;

    // Decompress/read data into stack buffer; on success, destSize > 0
    int result = decompressData(ecx, edx, stackBuffer, &destSize); // FUN_005ad1a0

    // Process the decompressed data
    if (destSize == 0) {
        initializeA(); // FUN_005a0980
        initializeB(); // FUN_005a1060
    } else {
        initializeA();
        initializeB();
    }

    // Check if data was placed in stack buffer or allocated heap
    if (dataPtr != smallBuffer && dataPtr != nullptr) {
        // Free allocated buffer (global deallocation function)
        gDeallocFunc(dataPtr); // DAT_0119caf4
    }
}