// FUNC_NAME: NetReflectable::packUpdate
void __thiscall NetReflectable::packUpdate(int thisPtr, int updateMask, StreamWriteFuncs* funcs) {
    // Call sub-update for base class components
    packSubUpdateA(); // FUN_00636e20

    // Write int field at +0x3c (e.g., object ID or state)
    int field3c = *(int*)(thisPtr + 0x3c);
    funcs->write(funcs->stream, &field3c, 4, funcs->context);

    // Write four bytes at +0x44 through +0x47 (flags or small fields)
    char byte44 = *(char*)(thisPtr + 0x44);
    funcs->write(funcs->stream, &byte44, 1, funcs->context);
    char byte45 = *(char*)(thisPtr + 0x45);
    funcs->write(funcs->stream, &byte45, 1, funcs->context);
    char byte46 = *(char*)(thisPtr + 0x46);
    funcs->write(funcs->stream, &byte46, 1, funcs->context);
    char byte47 = *(char*)(thisPtr + 0x47);
    funcs->write(funcs->stream, &byte47, 1, funcs->context);

    // Write dynamic array: pointer at +0x14, count at +0x30 (each element 4 bytes)
    int count30 = *(int*)(thisPtr + 0x30);
    funcs->write(funcs->stream, &count30, 4, funcs->context);
    void* data14 = *(void**)(thisPtr + 0x14);
    funcs->write(funcs->stream, data14, count30 * 4, funcs->context);

    // Call additional sub-update functions for this component
    packSubUpdateB(thisPtr); // FUN_00636ed0
    packSubUpdateC(thisPtr); // FUN_00637000
    packSubUpdateD(thisPtr); // FUN_006370b0

    // Write second dynamic array: pointer at +0xc, count at +0x2c (each element 4 bytes)
    int count2c = *(int*)(thisPtr + 0x2c);
    funcs->write(funcs->stream, &count2c, 4, funcs->context);
    void* data0c = *(void**)(thisPtr + 0xc);
    funcs->write(funcs->stream, data0c, count2c * 4, funcs->context);
}