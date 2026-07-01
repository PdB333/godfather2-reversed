//FUNC_NAME: releaseHandle
void __fastcall releaseHandle(HandleStruct* handle)
{
    // +0x04: field_4 (unknown, set to 0)
    handle->field_4 = 0;

    // Release the resource pointed to by the first field (+0x00)
    releaseResource(handle->resource);

    // Zero out the resource pointer (+0x00) and field_8 (+0x08)
    handle->resource = 0;
    handle->field_8 = 0;
}