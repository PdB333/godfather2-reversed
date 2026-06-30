// FUNC_NAME: ResourceHandler::releaseResource
void __fastcall ResourceHandler::releaseResource(int thisPtr)
{
    // Temporary buffer (8 bytes) used for resource ownership transfer or copy
    char local_8[8];

    // Call to some internal function that may release or transfer the resource.
    // Arguments: output buffer, this, double-deref of resource pointer (pointer to pointer?), this again, resource pointer
    FUN_00695e30(local_8, thisPtr, **(int**)(thisPtr + 4), thisPtr, *(int**)(thisPtr + 4));

    // Free the resource memory pointed to by the field at offset +0x04
    FUN_009c8eb0(*(int*)(thisPtr + 4));

    // Clear the resource pointer and associated count/size (offset +0x08)
    *(int*)(thisPtr + 4) = 0;
    *(int*)(thisPtr + 8) = 0;
}