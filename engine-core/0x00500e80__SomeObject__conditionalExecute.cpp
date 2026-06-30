// FUNC_NAME: SomeObject::conditionalExecute
// Address: 0x00500e80
// Role: Conditional wrapper that calls another method if a flag is set.
// The second parameter (param_2) acts as an enable flag. When non-zero, it delegates
// to FUN_00500b50 (likely a core update/process method) and returns its result.

int SomeObject::conditionalExecute(int flag) {
    if (flag != 0) {
        return FUN_00500b50(this); // +0x?? call to specific processing function
    }
    return 0;
}