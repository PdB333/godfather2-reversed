//FUNC_NAME: validateAndProcessGuid
void validateAndProcessGuid(int* guid) {
    // Check if the 16-byte GUID (4 ints) is all zeros
    if ((guid[0] != 0) || (guid[1] != 0) || (guid[2] != 0) || (guid[3] != 0)) {
        // GUID is non-null – log and copy to local buffer
        debugPrint(); // FUN_005e3070 – likely a debug/log function
        int localBuffer[4]; // 16-byte temporary buffer
        copyGuid(guid, localBuffer); // FUN_005e6500 – copies GUID to local buffer
    }
}