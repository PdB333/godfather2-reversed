// FUNC_NAME: decodePacketHeader
void decodePacketHeader(int* input, int* output) // input from EAX, output from ESI
{
    int threshold = DAT_010c2328; // global threshold (likely max packet type ID or version)
    // Magic 0xE1E2E3E4: Type A (status 0)
    if (*input == 0xE1E2E3E4) {
        output[0] = 0;      // status = 0 (success/known type)
        output[1] = input[1]; // copy second word from input
        return;
    }
    // Magic 0xF1F2F3F4: Type B (status 2)
    if (*input != 0xF1F2F3F4) {
        // Unknown magic: status 1
        output[0] = 1;
        if (threshold > 18) { // 0x12
            output[1] = 0;    // default data if threshold exceeded
            return;
        }
        // Get data from sub-function (likely fallback to protocol version)
        int subResult = FUN_004eb950(0);
        output[1] = subResult;
        return;
    }
    // Known magic 0xF1F2F3F4: status 2
    output[0] = 2;
    output[1] = input[1]; // copy second word from input
}