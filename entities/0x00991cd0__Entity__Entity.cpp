//FUNC_NAME: Entity::Entity

void __fastcall Entity::Entity(int thisPtr)
{
    int listPtr;
    if (thisPtr == 0) {
        listPtr = 0;
    } else {
        listPtr = thisPtr + 4; // +0x04: offset to list head pointer
    }
    // Initialize a linked list (e.g., child list or observer list) with vtable pointer
    FUN_005c0c50(listPtr, &LAB_00991ca0);
    // Zero out fields
    *(short*)(thisPtr + 0x88) = 0; // +0x88: 2-byte field (e.g., flags)
    *(int*)(thisPtr + 0x8c) = 0;   // +0x8c: 4-byte field (e.g., counter or pointer)
    // Additional initialization
    FUN_00991ad0();
}