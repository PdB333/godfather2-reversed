// FUNC_NAME: SomeClass::batchProcessWithCheck
void __thiscall SomeClass::batchProcessWithCheck(uint param2, uint param3)
{
    uint iter = 0;
    if (param3 != 0) {
        do {
            int result = isReady((void*)param2);  // FUN_00792900 - check if resource is ready
            if (result == 0) {
                return;
            }
            processItem(this, 0xffffffff);         // FUN_00791250 - process with special handle (-1)
            iter++;
        } while (iter < param3);
    }
    return;
}