// FUNC_NAME: getValueIfCondition
undefined4 getValueIfCondition(undefined4 this, int condition) {
    undefined4 uVar1;
    if (condition != 0) {
        uVar1 = FUN_00505720(this);  // internal helper function
        return uVar1;
    }
    return 0;
}