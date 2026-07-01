// FUNC_NAME: BlendSet::blendFloats
struct BlendSet {
    uint16_t count;                 // +0x00 number of floats in the array
    uint8_t pad[0x2A];              // +0x02 padding to align floats at +0x2C
    float floats[];                 // +0x2C actual float data (size = count * 4)
};

extern float _DAT_00d5780c;         // global blend weight threshold (usually 1.0f)

void __thiscall BlendSet::blendFloats(const BlendSet *src, const BlendSet *dst, float blendFactor)
{
    float maxWeight = _DAT_00d5780c;

    for (int i = 0; i < this->count; i++)
    {
        float srcVal = src->floats[i];
        float dstVal = dst->floats[i];
        float result;

        // only lerp when blendFactor is within [0, maxWeight]
        if (blendFactor >= 0.0f && blendFactor <= maxWeight)
        {
            result = (maxWeight - blendFactor) * srcVal + dstVal * blendFactor;
        }
        else
        {
            result = srcVal;
        }

        this->floats[i] = result;
    }
}