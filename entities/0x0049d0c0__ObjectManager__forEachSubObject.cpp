// FUNC_NAME: ObjectManager::forEachSubObject
void __thiscall ObjectManager::forEachSubObject(ObjectManager* thisPtr, ForEachCallback callback, int param)
{
    // ObjectList at +0xA0
    int list = *(int*)(thisPtr + 0xA0);
    uint count = 0;

    // Count of objects in list at +0x34
    if (*(int*)(list + 0x34) != 0)
    {
        int offset = 0;
        do
        {
            // Each object entry at +0x50, stride 0xB0
            int obj = *(int*)(list + 0x50 + offset);
            if (obj != 0)
            {
                // Call the callback with object, this+0x10 (likely base context), and param
                callback(obj, thisPtr + 0x10, param);
            }
            count++;
            offset += 0xB0;
        } while (count < *(uint*)(list + 0x34));
    }
    return;
}