// FUNC_NAME: TNLConnection::checkAckSequence
int TNLConnection::checkAckSequence(uint param1, int expectedSeq, uint param4) {
    // Read the network-order sequence number from this+0x4 (likely received packet's sequence)
    uint seq = ntohl(*(uint*)(this + 4));
    
    // Call validation function with global context, param1, pointer to seq, param4
    int result = FUN_0065d220(g_unknownGlobal, param1, &seq, param4);
    
    // If result matches expected, return 2 (acknowledged status)
    if (result == expectedSeq) {
        result = 2;
    }
    return result;
}