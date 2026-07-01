// FUNC_NAME: cleanupPointer
void __fastcall cleanupPointer(int* ptr)
{
    if (*ptr != 0) {
        releasePointer(ptr); // FUN_004daf90 - release resource
        *ptr = 0;
    }
}