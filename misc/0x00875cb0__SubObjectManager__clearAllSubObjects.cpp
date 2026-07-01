// FUNC_NAME: SubObjectManager::clearAllSubObjects
void __fastcall SubObjectManager::clearAllSubObjects(int thisPtr)
{
    // THIS + 0xBC0: array of 4 sub-objects, each 0x30 bytes
    int subObjPtr = thisPtr + 0xBC0;
    int count = 4;

    do {
        SubObject::reset(subObjPtr); // FUN_0045edc0
        subObjPtr += 0x30;
        count--;
    } while (count != 0);
}