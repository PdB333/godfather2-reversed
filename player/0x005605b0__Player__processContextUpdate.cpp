// FUNC_NAME: Player::processContextUpdate
void __fastcall Player::processContextUpdate(int arg1, int arg2, void* context)
{
    // this in ESI (unaff_ESI)
    Player* this = (Player*)unaff_ESI;
    void* vtablePtr;
    int contextField;
    char localBuffer[28]; // stack buffer for callback

    // Call base update or some initialization
    FUN_009de610(arg2, arg1, *(void**)((int)this + 0x0C), *(void**)((int)context + 0x18));
    // Call debug/update routine on this
    FUN_0053f390(this);
    // Fetch a field from this
    vtablePtr = *(void**)((int)this + 0x08);
    // Get a pointer from context
    contextField = *(int*)((int)context + 0x18);
    // Global update function
    FUN_009f2000();
    // Call a virtual function on an object (contextField) using offset 0xD0->0x58
    // The function takes two args: vtablePtr and localBuffer
    (**(code**)(*(int*)(contextField + 0xD0) + 0x58))(vtablePtr, localBuffer);
}