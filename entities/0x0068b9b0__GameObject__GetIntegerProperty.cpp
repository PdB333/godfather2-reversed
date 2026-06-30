// FUNC_NAME: GameObject::GetIntegerProperty
// Function address: 0x0068b9b0
// Retrieves an integer property from the object via an internal getter.
// The 'status' byte output is unused in this wrapper.
int __thiscall GameObject::GetIntegerProperty(void *this) {
    int result = 0;             // +0x00? output integer
    char status;                // unused output byte
    FUN_006039d0(this, &result, &status);
    return result;
}