// FUNC_NAME: ControllerSlot::assign(const ControllerSlot&)

void __thiscall ControllerSlot::assign(ControllerSlot* this, const ControllerSlot* src)
{
    // Copy 17 DWORDs (68 bytes) from src to this – equivalent to memcpy(this, src, 0x44)
    // This is a member function of the controller slot structure used by InputDeviceManager
    int* dst = reinterpret_cast<int*>(this);
    const int* srcData = reinterpret_cast<const int*>(src);
    for (int i = 0; i < 17; i++)
    {
        dst[i] = srcData[i];
    }
}