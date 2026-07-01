// FUNC_NAME: sendEventWithParams
void sendEventWithParams(uint32_t param1, uint32_t param2) {
    // Local struct holding two uint32_t values, order matches called function expectation
    uint32_t local_8 = param2;  // Stored at offset 0
    uint32_t local_4 = param1;  // Stored at offset 4
    // Call the actual processing function with pointer to struct
    FUN_00827e40(&local_8);  // Address of local_8 points to struct starting with param2
}