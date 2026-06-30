// FUNC_NAME: forwardCallToSubroutine
// Address: 0x00494d50 - A simple wrapper function that forwards its second argument to another internal function (0x004d0210).
// The first parameter (param_1) is ignored, likely a relic of the calling convention or unused argument.
void forwardCallToSubroutine(uint param_1, uint param_2) {
    // Delegate to the actual handler at 0x004d0210
    sub_004d0210(param_2);
}