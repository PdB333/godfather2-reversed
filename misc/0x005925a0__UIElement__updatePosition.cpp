// FUNC_NAME: UIElement::updatePosition
void __thiscall UIElement::updatePosition(uint param_1, byte* param_2)
{
    // Global constants (likely screen dimensions or scale factors)
    extern float DAT_00e44564; // Base X offset
    extern float DAT_00e44820; // Scale factor

    // this->data is a ushort array (e.g., packed coordinates)
    ushort* data = this->someData; // in_EAX

    // Compute horizontal position: base - (data[2] * scale)
    float x = DAT_00e44564 - (float)data[2] * DAT_00e44820;

    // Compute vertical position: -scale * (data[0] - (param_2[0] << 4))
    // param_2[0] is a byte, shifted left by 4 (likely a sub-pixel offset)
    float y = -DAT_00e44820 * ((float)data[0] - (float)((uint)*param_2 << 4));

    // Apply the computed position (likely sets a 2D coordinate)
    FUN_0056d040(x, y, param_1);
}