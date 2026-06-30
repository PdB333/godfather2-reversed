// Xbox PDB: int __cdecl luaG_ordererror(struct lua_State *,struct lua_TObject const *,struct lua_TObject const *)
// FUNC_NAME: checkObjectTypeEquality
// Address: 0x006337e0
// Compares the type ID (field at offset 0x08) of two objects via a global type info table.
// Always calls doSomethingCommon() and returns false (0).

typedef struct TypeInfo {
    int field0;      // +0x00
    int field1;      // +0x04
    int typeId;      // +0x08 (index 2)
} TypeInfo;

extern TypeInfo* g_TypeInfoTable[];   // PTR_DAT_00e2a89c

bool __fastcall checkObjectTypeEquality(const int* objIndex1, const int* objIndex2) {
    int idx1 = *objIndex1;
    int idx2 = *objIndex2;

    // Compare the typeId (third field) of the two TypeInfo structures.
    if (g_TypeInfoTable[idx1]->typeId == g_TypeInfoTable[idx2]->typeId) {
        doSomethingCommon(); // FUN_00633920 - cleanup/notification
        return false;
    }
    doSomethingCommon(); // FUN_00633920
    return false;
}