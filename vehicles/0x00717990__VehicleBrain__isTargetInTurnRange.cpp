// FUNC_NAME: VehicleBrain::isTargetInTurnRange
uint __thiscall VehicleBrain::isTargetInTurnRange(VehicleBrain* this, float threshold)
{
    uint result = 0;
    uint baseFlags = 0; // in_EAX & 0xffffff00, but we'll compute later

    // Check if the vehicle's state is not null and not 0x48 (72)
    if ((*(int*)(this + 0x330) != 0) && (*(int*)(this + 0x330) != 0x48))
    {
        // Get current object pointers from some global iteration
        PathObject* obj1 = getCurrentPathObject();    // FUN_00471610
        PathObject* obj2 = getCurrentPathObject();    // FUN_00471610
        // Compute difference vector between their positions (offset +0x30 = x, +0x34 = y, +0x38 = z)
        float diffX = *(float*)(obj1 + 0x30) - *(float*)(obj2 + 0x30);
        float diffY = *(float*)(obj1 + 0x34) - *(float*)(obj2 + 0x34);
        float diffZ = *(float*)(obj1 + 0x38) - *(float*)(obj2 + 0x38);

        // Get another object for orientation
        PathObject* obj3 = getCurrentPathObject();    // FUN_00471610
        // Use first row of orientation matrix (forward vector at offsets +0x10, +0x14, +0x18)
        float forwardX = *(float*)(obj3 + 0x10);
        float forwardY = *(float*)(obj3 + 0x14);
        float forwardZ = *(float*)(obj3 + 0x18);

        // Project difference onto forward direction, scaled by global factor
        float projection = (forwardX * diffX + forwardY * diffY + forwardZ * diffZ) * turnScaleFactor; // DAT_00d5ccf8

        // Add back to difference (adjust to be relative to forward direction)
        diffX += forwardX * projection;
        diffY += forwardY * projection;
        diffZ += forwardZ * projection;

        // Normalize the adjusted vector
        normalizeVector(&diffX, &diffX); // FUN_0056afa0 - note: same address passed for in/out

        // Get three more objects
        PathObject* obj4 = getCurrentPathObject();    // FUN_00471610
        PathObject* obj5 = getCurrentPathObject();    // FUN_00471610
        PathObject* obj6 = getCurrentPathObject();    // FUN_00471610

        // Use second row of orientation matrix (up or right vector at offsets +0x20, +0x24, +0x28)
        float rightX = *(float*)(obj4 + 0x20);
        float rightY = *(float*)(obj5 + 0x24);
        float rightZ = *(float*)(obj6 + 0x28);

        // Compute dot product with the normalized adjusted vector
        float dot = rightX * diffX + rightY * diffY + rightZ * diffZ;

        // Compare with threshold
        if (threshold <= dot)
        {
            // Build return value: combine upper byte of (obj6 + 0x20) with low byte 1
            uint upperPart = (uint)(obj6 + 0x20) >> 8; // Note: this seems odd, likely a miscalculation. Original: (uint)(iVar4 + 0x20) >> 8
            // Actually iVar4 is obj6, so we take the address and shift
            result = (upperPart << 8) | 1; // CONCAT31(upperPart,1)
        }
        else
        {
            // Keep only the upper 24 bits of the original EAX? We'll simulate a default
            result = 0; // Since we don't have in_EAX, we default to 0
        }
    }
    else
    {
        // Return the input EAX masked (but we don't have it, so return 0)
        result = 0;
    }

    return result;
}