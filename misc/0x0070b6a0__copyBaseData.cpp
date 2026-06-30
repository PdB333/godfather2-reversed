// FUNC_NAME: copyBaseData
void __thiscall copyBaseData(void* this, void* source)
{
    // Copy 17 DWORDs (68 bytes) from source to destination
    *(int*)this = *(int*)source;
    ((int*)this)[1] = ((int*)source)[1];
    ((int*)this)[2] = ((int*)source)[2];
    ((int*)this)[3] = ((int*)source)[3];
    *(int64_t*)((int*)this + 4) = *(int64_t*)((int*)source + 4); // copy 2 ints at once
    ((int*)this)[6] = ((int*)source)[6];
    *(int64_t*)((int*)this + 7) = *(int64_t*)((int*)source + 7); // copy 2 ints
    ((int*)this)[9] = ((int*)source)[9];
    ((int*)this)[10] = ((int*)source)[10];
    ((int*)this)[11] = ((int*)source)[11];
    ((int*)this)[12] = ((int*)source)[12];
    ((int*)this)[13] = ((int*)source)[13];
    ((int*)this)[14] = ((int*)source)[14];
    ((int*)this)[15] = ((int*)source)[15];
    ((int*)this)[16] = ((int*)source)[16];
    // Total 17 ints = 68 bytes copied
}