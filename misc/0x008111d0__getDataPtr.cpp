// FUNC_NAME: getDataPtr
// Function address: 0x008111d0
// Role: Returns pointer to internal data at offset 0x60 (likely a member pointer)

int __fastcall getDataPtr(int thisPtr)
{
    return thisPtr + 0x60;
}