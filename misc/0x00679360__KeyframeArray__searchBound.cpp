// FUNC_NAME: KeyframeArray::searchBound
uint __thiscall KeyframeArray::searchBound(short direction, bool bUseSecondArray)
{
    short count;
    short compareValue;
    ushort targetValue;
    short *array;

    if (!bUseSecondArray) {
        // Use first array: count at offset 0, array at +1 (offset 2), compareValue at +0x84 (offset 0x108), targetValue at +0x82 (offset 0x104)
        count = *(short *)this;
        compareValue = *(short *)((char *)this + 0x108);  // +0x108
        targetValue = *(ushort *)((char *)this + 0x104);  // +0x104
        array = (short *)((char *)this + 2);
    } else {
        // Use second array: count at +0x41 (offset 0x82), array at +0x42 (offset 0x84), compareValue at +0x85 (offset 0x10A), targetValue at +0x83 (offset 0x106)
        count = *(short *)((char *)this + 0x82);  // +0x82
        compareValue = *(short *)((char *)this + 0x10A);  // +0x10A
        targetValue = *(ushort *)((char *)this + 0x106);  // +0x106
        array = (short *)((char *)this + 0x84);
    }

    uint result = (uint)targetValue;

    if (direction == 0) {
        if ((short)targetValue <= compareValue) {
            if (compareValue <= (short)targetValue) {
                // Exact match found
                return result;
            }
            direction = -1;
            goto searchDown;
        }
        direction = 1;
    } else if (direction < 1) {
        goto searchDown;
    }

    // Search up: find last index where array[i] <= targetValue
    {
        int maxIndex = (int)count;
        int idx = 0;
        if (maxIndex < 1) {
            return result;
        }
        while (array[idx] <= (short)targetValue) {
            idx++;
            if (maxIndex <= idx) {
                return result;
            }
        }
        idx = idx - 1 + (int)direction;  // direction is 1 here, so idx remains idx-1
        if (maxIndex <= idx) {
            // Overflow: clamp to last element
            return (uint)((ushort)array[maxIndex - 1] | ((uint)(maxIndex - 1) << 16));
        }
        return (uint)((ushort)array[idx] | ((uint)idx << 16));
    }

searchDown:
    // Search down: find last index where targetValue <= array[i]
    {
        int idx = (int)count - 1;
        if (idx < 0) {
            return result;
        }
        while ((short)targetValue <= array[idx]) {
            idx--;
            if (idx < 0) {
                return result;
            }
        }
        idx = idx + 1 + (int)direction;  // direction is -1, so idx remains idx
        if (idx < 0) {
            idx = 0;
        }
        return (uint)((ushort)array[idx] | ((uint)idx << 16));
    }
}