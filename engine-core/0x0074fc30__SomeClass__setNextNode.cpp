// FUNC_NAME: SomeClass::setNextNode
void __thiscall SomeClass::setNextNode(int this_Ptr, int param_2) {
    int* nextPtr = (int*)(this_Ptr + 0x38); // pointer to the "next" field at offset 0x38
    if (param_2 == 0) {
        param_2 = 0;
    } else {
        param_2 = param_2 + 0x48; // adjust param_2 to point to the embedded node (at offset 0x48 in the object)
    }
    if (*nextPtr != param_2) {
        if (*nextPtr != 0) {
            // Remove the old next from its list
            FUN_004daf90(nextPtr); // likely unlinkNode or removeFromList
        }
        *nextPtr = param_2; // set new next pointer
        if (param_2 != 0) {
            // Update the prev pointer of the new node to point back to the location of this->next
            *(int*)(this_Ptr + 0x3c) = *(int*)(param_2 + 4); // store old value (if any) into this->prev
            *(int**)(param_2 + 4) = nextPtr; // new node's prev points to the location of this->next
        }
    }
}