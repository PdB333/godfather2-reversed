// FUNC_NAME: GameObjectBase::reset
void __fastcall GameObjectBase::reset(GameObjectBase* thisPtr)
{
    thisPtr->field0 = 0; // +0x00
    thisPtr->field1 = 0; // +0x04
    thisPtr->field2 = 0; // +0x08
    thisPtr->field3 = 0; // +0x0C
    thisPtr->field4 = 0; // +0x10
    thisPtr->field5 = 0; // +0x14
    thisPtr->field7 = 0; // +0x1C (ordered before field6)
    thisPtr->field6 = 0; // +0x18
}