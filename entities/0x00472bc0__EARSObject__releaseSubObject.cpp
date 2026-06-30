// FUNC_NAME: EARSObject::releaseSubObject
void __fastcall EARSObject::releaseSubObject(int thisPointer)
{
    EARSObject* baseObject;
    struct ReleaseInfo {
        int field0;
        EARSObject* objPtr;
        char field8;
    } info;
    
    if (thisPointer == 0x58) {
        baseObject = nullptr;
    }
    else {
        baseObject = (EARSObject*)(thisPointer - 0x1C);
    }
    
    if (baseObject != nullptr && (*((byte*)baseObject + 4) & 2) != 0) {
        info.field0 = DAT_012067dc;  // global static handle
        info.field8 = 0;
        info.objPtr = baseObject;
        (*(void (__thiscall**)(ReleaseInfo*))(*(int*)baseObject + 4))(&info);
    }
    (*(void (__thiscall**)(int))(*(int*)baseObject))(1);
}