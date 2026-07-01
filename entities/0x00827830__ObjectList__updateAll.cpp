// FUNC_NAME: ObjectList::updateAll
void __fastcall ObjectList::updateAll(ObjectList* thisPtr)
{
    uint count = 0;
    if (*(int*)(thisPtr + 8) != 0) {
        do {
            // Call update method (vtable+0x10) on each object in the list
            // List entries are 8 bytes each, starting at offset +4
            (**(code**)(**(int**)(*(int*)(thisPtr + 4) + count * 8) + 0x10))();
            count = count + 1;
        } while (count < *(uint*)(thisPtr + 8));
    }
}