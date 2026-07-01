// FUNC_NAME: PacketBuilder::initializeFromThreeArguments
PacketBuilder* __thiscall PacketBuilder::initializeFromThreeArguments(uint headerData, uint bodyData, uint auxData) {
    unsigned char intermediateBuffer[96];   // Temporary buffer for first stage (CRC/hash)
    unsigned char outputBuffer[108];        // Temporary buffer for second stage (packet header)
    uint stageResult;

    // First stage: compute intermediate value from auxData and bodyData, store in intermediateBuffer
    stageResult = FUN_00835f60(intermediateBuffer, auxData, bodyData);

    // Second stage: combine with headerData and previous result, write to outputBuffer
    stageResult = FUN_008360c0(outputBuffer, headerData, stageResult);

    // Final stage: apply the constructed output to this object using bodyData as a key
    FUN_00835eb0(this, bodyData, stageResult);

    return this;
}