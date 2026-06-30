// FUNC_NAME: EARSObject::getIntAttribute
int __thiscall EARSObject::getIntAttribute(EARSObject* this) {
    int result = 0;             // local_4, default value
    char unusedFlag;            // local_5, output parameter (likely a status/flag, ignored here)
    // Internal getter that populates result and possibly a flag
    // FUN_006039d0 is the actual implementation (likely EARSObject::getIntAttribute_impl)
    FUN_006039d0(this, &result, &unusedFlag);
    return result;
}