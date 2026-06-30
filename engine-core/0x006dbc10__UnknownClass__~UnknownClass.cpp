// FUNC_NAME: UnknownClass::~UnknownClass
void __fastcall UnknownClass::~UnknownClass(void* thisPtr) {
    int* mem = (int*)thisPtr;

    // Release member at offset +8
    if (mem[2] != 0) {
        releaseResource((void*)mem[2]);
    }

    // Release member at offset +0
    if (mem[0] != 0) {
        releaseResource((void*)mem[0]);
    }
}