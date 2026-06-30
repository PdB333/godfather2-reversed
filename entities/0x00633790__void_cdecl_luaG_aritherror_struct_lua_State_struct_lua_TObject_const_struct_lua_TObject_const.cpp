// Xbox PDB: void __cdecl luaG_aritherror(struct lua_State *,struct lua_TObject const *,struct lua_TObject const *)
// FUNC_NAME: BaseObject::processArithmetic
void BaseObject::processArithmetic(void) {
    int buffer[1]; // temporary 4-byte output buffer

    // Check if the object's type field (offset +0x00) is 4 (and not 3)
    if (this->type != 3 && this->type == 4) {
        performConversion(buffer); // 0x00636850 – likely a value/type conversion
    }

    debugPrint("perform arithmetic on"); // 0x006336f0 – debug logging
}