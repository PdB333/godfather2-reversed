// FUNC_NAME: UIRect::init
void __thiscall UIRect::init(int param1, int param2)
{
    // +0x00: x position / left
    this->x = param1;
    // +0x04: y position / top
    this->y = param2;
    // +0x08: width (default 0)
    this->width = 0;
    // +0x0C: height (default 0)
    this->height = 0;
    // +0x10: unused / reserved
    this->field_10 = 0;
    // +0x14: unused / reserved
    this->field_14 = 0;
    // +0x18: byte visibility/active flag (set to 1 = visible)
    this->visible = 1;
    // +0x1C: unused / reserved
    this->field_1C = 0;
}