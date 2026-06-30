// FUNC_NAME: PlayerController::initControllerState
void __fastcall PlayerController::initControllerState(PlayerController* thisPtr)
{
    // Call base initializer (likely parent class constructor)
    FUN_0059b5e0();

    // +0x7c: flags field - clear bits, set 0x700 (e.g., enable analog sticks or something)
    thisPtr->flags = (thisPtr->flags & 0xFFFFC700) | 0x700;

    // +0xb0, +0xb4: read from global constants (e.g., sensitivity/deadzone for axes)
    thisPtr->field_b0 = DAT_00e2b1a4;
    thisPtr->field_b4 = DAT_00e35654;
    thisPtr->field_b8 = 0;
    thisPtr->field_bc = 0;

    // Initialize two 4-element vectors via global math singleton's vtable
    // First vector at +0xa0: set to (0, 0, 0, 1.0f)
    (**(void (__cdecl**)(float, float, float, float, float*))*DAT_012055a8 + 4)(0.0f, 0.0f, 0.0f, 1.0f, &thisPtr->vecA0);

    // Second vector at +0x80: set to (0, 0, 1.0f, 0)
    (**(void (__cdecl**)(float, float, float, float, float*))*DAT_012055a8 + 4)(0.0f, 0.0f, 1.0f, 0.0f, &thisPtr->vec80);

    // Normalize first vector (only one parameter = this pointer?)
    (**(void (__cdecl**)(float*))*DAT_012055a8 + 8)(&thisPtr->vecA0);

    // Initialize left analog stick state (offsets +0xf0 to +0xfc)
    thisPtr->leftStick.x = 0;
    thisPtr->leftStick.y = 0;
    thisPtr->leftStick.deadZone = 4;
    thisPtr->leftStick.magnitude = 0;
    thisPtr->leftStick.reserved = 0;
    thisPtr->leftStickFlags = 0;

    // Initialize right analog stick state (offsets +0x100 to +0x10c)
    thisPtr->rightStick.x = 0;
    thisPtr->rightStick.y = 0;
    thisPtr->rightStick.deadZone = 4;
    thisPtr->rightStick.magnitude = 0;
    thisPtr->rightStick.reserved = 0;
    thisPtr->rightStickFlags = 0;

    // Set additional fields (+0x130, +0x134, +0x138, +0x13c, etc.)
    thisPtr->field_130 = DAT_00e2b1a4;
    thisPtr->field_134 = DAT_00e2b1a4;
    thisPtr->field_138 = DAT_00e2afac;
    thisPtr->field_13c = 0;
    thisPtr->field_140 = 8;
    thisPtr->field_144 = 0;
    thisPtr->field_148 = 0;
    thisPtr->field_14c = 0;
    thisPtr->field_150 = 0;
    thisPtr->field_154 = 0;
    thisPtr->field_158 = 0;
    thisPtr->field_15c = 0;
    thisPtr->field_160 = 0;
}