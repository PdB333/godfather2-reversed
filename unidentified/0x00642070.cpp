// FUN_00642070: ScriptBytecodeParser::parseInstruction
int ScriptBytecodeParser::parseInstruction(uint* context, int defaultParam) {
    int* parsedBlock = (int*)allocateBlock();
    int value = readValue(context);
    parsedBlock[0x20 / 4] = value;
    if (value == 0) {
        parsedBlock[0x20 / 4] = defaultParam;
    }
    consumePunctuation();

    // local_c seems to be used uninitialized; likely a decompiler artifact for a field read
    int errorCode;
    if (errorCode < 0) {
        errorCode = reportError(*context, "bad integer in %s", (char*)context[4]);
    }
    parsedBlock[0x3c / 4] = errorCode;

    // Read four consecutive byte flags
    *(char*)(parsedBlock + 0x44) = readByte();
    *(char*)(parsedBlock + 0x45) = readByte();
    *(char*)(parsedBlock + 0x46) = readByte();
    *(char*)(parsedBlock + 0x47) = readByte();

    processArgList(context, parsedBlock);
    validateBlock(parsedBlock);
    processArgEnd(context, parsedBlock);
    finalizeBlock(parsedBlock);
    processArgStart(context, parsedBlock);

    int result = checkTable(parsedBlock, *(int*)(parsedBlock + 0x2c), 0xff);
    if (result == 0) {
        reportError(*context, "bad code in %s", (char*)context[4]);
    }
    return (int)parsedBlock;
}