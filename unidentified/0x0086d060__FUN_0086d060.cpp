// FUNC_NAME: UnknownClass::setSomeStateOrTarget
// Address: 0x0086d060
// Role: Setter method that updates a member variable at +0xC4 and triggers an update (FUN_0086cb20) if changed.

void __thiscall UnknownClass::setSomeField(int this, int newValue)
{
    // +0xC4: some state identifier or target ID
    if (*(int *)(this + 0xC4) != newValue) {
        *(int *)(this + 0xC4) = newValue;
        FUN_0086cb20(); // Update/notify after field change
    }
}