// FUNC_NAME: ManagedObject::release
void __fastcall ManagedObject::release(int thisPtr)
{
    // Check if the object is valid (flag at +0x14)
    if (*(char *)(thisPtr + 0x14) != '\0') {
        // Build a structure containing the release function table and two data members
        struct ReleaseArgs {
            void **vtable; // +0x00: pointer to global function table (PTR_LAB_00d75428)
            int data1;     // +0x04: from thisPtr+0x0c
            int data2;     // +0x08: from thisPtr+0x10
        };
        ReleaseArgs args;
        args.vtable = &PTR_LAB_00d75428; // Global release vtable
        args.data1 = *(int *)(thisPtr + 0x0c); // +0x0c: first data member
        args.data2 = *(int *)(thisPtr + 0x10); // +0x10: second data member
        FUN_004149c0(&args); // Call the actual release function
        *(char *)(thisPtr + 0x14) = 0; // Clear valid flag
    }
}