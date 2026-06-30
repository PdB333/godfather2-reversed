// FUNC_NAME: multiplyAndCallFunction
void multiplyAndCallFunction(int a, int b)
{
    int result[3] = {0, 0, 0}; // Buffer for output (3 ints)
    // Call function pointer from global table at offset +4
    // The function likely takes (product, output buffer)
    (**(code **)(*(undefined4 **)(DAT_012234ec + 4)))(a * b, result);
}