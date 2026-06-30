// FUNC_NAME: UIWidget::SetRectangle
void __thiscall UIWidget::SetRectangle(int* rect, int updateDimensions, int param_3, int param_4)
{
    int left = rect[0];
    int top = rect[1];
    int right = rect[2];
    int bottom = rect[3];

    // Store rectangle (offsets +0x08 to +0x14)
    *(int*)((int)this + 0x08) = left;
    *(int*)((int)this + 0x0C) = top;
    *(int*)((int)this + 0x10) = right;
    *(int*)((int)this + 0x14) = bottom;

    // Check if rectangle represents a full UV or infinite region (0x10000 = 1.0 in 16.16 fixed-point?)
    bool isFullRect = (left == 0x10000 && top == 0 && right == 0 && bottom == 0x10000);
    *(bool*)((int)this + 0x1C) = isFullRect;

    // Store texture or source dimensions
    *(int*)((int)this + 0x124) = param_3; // textureWidth?
    *(int*)((int)this + 0x128) = param_4; // textureHeight?

    // Update previous dimensions if flag is set and dimensions changed
    if (updateDimensions != 0 &&
        (*(int*)((int)this + 0x168) != param_3 || *(int*)((int)this + 0x16C) != param_4))
    {
        *(int*)((int)this + 0x168) = param_3; // previousWidth?
        *(int*)((int)this + 0x16C) = param_4; // previousHeight?
    }
}