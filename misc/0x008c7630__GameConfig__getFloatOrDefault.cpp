//FUNC_NAME: GameConfig::getFloatOrDefault
float GameConfig::getFloatOrDefault(int param_1) {
    float result = _DAT_00d5780c; // global default value
    int objPtr = FUN_008c7490(param_1); // lookup object by ID
    if (objPtr != 0) {
        result = *(float *)(objPtr + 0xf0); // +0xf0: some float field
    }
    return result;
}