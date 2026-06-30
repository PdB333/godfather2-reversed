// FUNC_NAME: standard_memmove_backward
undefined1 * __fastcall standard_memmove_backward(undefined4 param_1, int dest, int src)
{
    int count;
    undefined1 *dstPtr;
    undefined1 *srcPtr;

    count = dest - src;
    srcPtr = (undefined1 *)(dest + -1);
    dstPtr = (undefined1 *)(in_EAX + -1 + count);
    for (; count != 0; count = count + -1) {
        *dstPtr = *srcPtr;
        srcPtr = srcPtr + -1;
        dstPtr = dstPtr + -1;
    }
    return dstPtr;
}