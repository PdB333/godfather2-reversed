// FUNC_NAME: GlobalFunctionTable::callEntryD4
void GlobalFunctionTable::callEntryD4(void* arg) {
    // Calls a function pointer stored at offset 0xD4 from the global function table pointed to by DAT_01223510.
    (*(void (**)(void*))(*DAT_01223510 + 0xD4))(arg);
}