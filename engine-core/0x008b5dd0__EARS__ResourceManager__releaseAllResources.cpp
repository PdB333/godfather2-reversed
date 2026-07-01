// FUNC_NAME: EARS::ResourceManager::releaseAllResources
int __fastcall EARS::ResourceManager::releaseAllResources(EARS::ResourceManager *this)
{
    uint count;
    uint *array;

    // Release the resource ID at offset +0x4, combined with magic "EAR\0"
    releaseTaggedResource(*(uint *)((int)this + 0x4) | 0x45415200);

    // Release the array of secondary resources (type B)
    count = 0;
    releaseHandle(*(int *)((int)this + 0x10c));  // release count holder or primary handle
    if (*(int *)((int)this + 0x10c) != 0) {
        array = (uint *)((int)this + 0x88);  // start of array at +0x88
        do {
            releasePointer(*array);           // release each element
            count++;
            array++;
        } while (count < *(uint *)((int)this + 0x10c));
    }

    // Release the array of primary resources (type A)
    count = 0;
    releaseHandle(*(int *)((int)this + 0x108));  // release count holder or primary handle
    if (*(int *)((int)this + 0x108) != 0) {
        array = (uint *)((int)this + 0x8);   // start of array at +0x8
        do {
            releaseHandle(*array);            // release each element
            count++;
            array++;
        } while (count < *(uint *)((int)this + 0x108));
    }
    return 0;
}