// FUNC_NAME: setFlagFromInteger
// Address: 0x004e9f50 - wrapper that converts an integer parameter to a boolean and forwards to SetObjectFlag

extern void SetObjectFlag(void* obj, bool enable);

void setFlagFromInteger(void* this, void* obj, int param3)
{
    // If param3 equals 2, the flag is set to true; otherwise false.
    // 'this' is unused in the body but likely part of a class context.
    SetObjectFlag(obj, param3 == 2);
}