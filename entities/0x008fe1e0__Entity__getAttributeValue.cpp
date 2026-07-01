// FUNC_NAME: Entity::getAttributeValue
int __fastcall Entity::getAttributeValue(int this) {
    int iVar1;
    int uVar2;
    
    if ( (*(int *)(this + 0xC8) != 0) && (*(int *)(this + 0xC8) != 0x48) ) {
        if (*(int *)(this + 0xC8) == 0) {
            iVar1 = 0;
        } else {
            iVar1 = *(int *)(this + 0xC8) - 0x48;  // attribute index = field - 0x48
        }
        iVar1 = getAttributeDefinition(iVar1);  // lookup attribute definition table
        if (iVar1 != 0) {
            iVar1 = *(int *)(iVar1 + 4);  // attribute type
            if (iVar1 == 1) {
                return *(int *)(this + 0x58);  // stored custom value
            }
            if (((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 4)) {
                return getDefaultAttributeValue();  // global constant/default
            }
        }
    }
    return 0;
}