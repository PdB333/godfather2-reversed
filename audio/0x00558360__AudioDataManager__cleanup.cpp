// FUNC_NAME: AudioDataManager::cleanup
void __thiscall AudioDataManager::cleanup(void)
{
    int *pRefCountedObj; // Undefined4* in original, but likely int* for vtable
    int subObj;

    FUN_00558770(this);
    // Check if pointer at +0x1C is non-null, then free it (likely a stream or buffer)
    if (*(int *)(this + 0x1c) != 0) {
        FUN_009f01a0();
    }
    // Access a reference-counted object at +0x20
    pRefCountedObj = *(int **)(this + 0x20);
    if (pRefCountedObj != (int *)0x0) {
        // Check short at offset +4 (maybe a reference count or type)
        if (*(short *)((int)pRefCountedObj + 4) != 0) {
            // Decrement short at offset +6 (reference count)
            *(short *)((int)pRefCountedObj + 6) = *(short *)((int)pRefCountedObj + 6) - 1;
            if (*(short *)((int)pRefCountedObj + 6) == 0) {
                // If count reaches zero, call virtual function at vtable[0] with argument 1 (release)
                (**(code **)*pRefCountedObj)(1);
            }
        }
    }
    subObj = *(int *)(this + 4);
    if (subObj != 0) {
        FUN_00559ca0(subObj); // Release or delete sub-object
        FUN_009c8eb0(subObj); // Another cleanup step
    }
    return;
}