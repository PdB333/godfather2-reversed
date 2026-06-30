// FUNC_NAME: EARSObject::conditionalCleanup
void __fastcall EARSObject::conditionalCleanup(int thisPtr)
{
    // Check if pointer at offset +0xD0 is non-null; if so, perform global cleanup
    if (*(int *)(thisPtr + 0xD0) != 0) {
        FUN_004df6e0();  // Likely a global cleanup routine (e.g., resource release)
    }
}