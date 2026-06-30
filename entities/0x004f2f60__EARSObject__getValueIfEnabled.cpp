// FUNC_NAME: EARSObject::getValueIfEnabled
int __thiscall EARSObject::getValueIfEnabled(int param_2)
{
    if (param_2 != 0)
    {
        int* internalPtr = *(int**)(this + 4);      // this+4 : pointer to internal data block
        int handle = *(int*)((char*)internalPtr + 0xc); // +0xc : handle/ID within internal block
        return FUN_004f2de0(handle);                 // returns value derived from handle
    }
    return 0;
}