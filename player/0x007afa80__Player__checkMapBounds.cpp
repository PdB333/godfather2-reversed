// FUNC_NAME: Player::checkMapBounds
void __fastcall Player::checkMapBounds(Player* this)
{
    // Local variables for coordinates retrieved from external call
    float xPos;
    float yPos;

    // Call to get player position or some world-relative coordinates
    // FUN_0079eab0: likely getPositionFromWorld(0, &xPos, &yPos, 0, 1, g_SomeConstant, g_SomeConstant, g_SomeConstant)
    FUN_0079eab0(0, &xPos, &yPos, 0, 1, g_SomeConstant, g_SomeConstant, g_SomeConstant);

    // Global bounds (likely map min/max X)
    float minX = g_MapMinX;  // DAT_00d5f520
    float maxX = g_MapMaxX;  // DAT_00d62b78

    int flag;
    // Check if point lies within a specific region (appears to be a boundary test)
    if ( (minX < xPos && (flag = g_FlagLeft, yPos < maxX || minX < yPos)) ||
         (xPos < maxX && (flag = g_FlagRight, yPos < maxX || minX < yPos)) )
    {
        // Call virtual function at vtable offset 0x60 on a global object (e.g., g_SomeGlobal)
        // The vtable pointer is stored at this+0x58
        // The function signature: void __thiscall (void* globalObject, int flag)
        typedef void (__thiscall *VirtualFunc)(void*, int);
        VirtualFunc method = *(VirtualFunc*)(*(int*)((char*)this + 0x58) + 0x60);
        method((void*)&g_GlobalObject, flag);
    }
    return;
}