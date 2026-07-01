// FUNC_NAME: SomeManagerClass::setActiveItem

void __fastcall SomeManagerClass::setActiveItem(int this) {
    int newItem = FUN_007058f0();  // Gets some object/pointer
    int* headPtr = *(int**)(*(int*)(this + 0x58) + 0x24B4);  // Access manager via +0x58, then head slot at +0x24B4
    int newHead;
    
    if (newItem == 0) {
        newHead = 0;
    } else {
        newHead = newItem + 0x48;  // Offset to get the actual list node (likely embedded in the object)
    }
    
    if (*headPtr != newHead) {
        if (*headPtr != 0) {
            FUN_004daf90(headPtr);  // Remove old head from the list
        }
        *headPtr = newHead;
        if (newHead != 0) {
            // Save previous backlink from new node, then set new backlink to head pointer
            *(int*)(*(int*)(this + 0x58) + 0x24B8) = *(int*)(newHead + 4);  // +0x24B8 stores old prev pointer
            *(int**)(newHead + 4) = headPtr;  // Node's prev now points to head slot
        }
    }
}