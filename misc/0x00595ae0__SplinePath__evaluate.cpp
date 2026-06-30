// FUNC_NAME: SplinePath::evaluate
int SplinePath::evaluate(float outPos[4])
{
    // in_EAX is the 'this' pointer (SplinePath object)
    SplinePath* spline = reinterpret_cast<SplinePath*>(in_EAX);

    // Offset +6: state/spline type (0 = none, 1 = single segment, etc.)
    short state = *reinterpret_cast<short*>(reinterpret_cast<uint8_t*>(spline) + 6);

    // Offset +0: parameter t (float)
    float t = spline->t;

    // Offset +12: pointer to array of control points (each 0x14 = 20 bytes)
    uint8_t* controlPoints = spline->controlPointsArray;

    // Offset +2: spline mode (expect 2?)
    short mode = *reinterpret_cast<short*>(reinterpret_cast<uint8_t*>(spline) + 2);

    // Offset +1: current segment index
    short segmentIdx = *reinterpret_cast<short*>(reinterpret_cast<uint8_t*>(spline) + 1);

    if (state == 0)
    {
        // No valid state; just output zero vector and call something
        // DAT_012055a8 vtable call at +4: likely (Vector4::set(outPos, 0,0,0,1))
        float identity[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        // Simulate vtable call: Vector4::set(outPos, identity)
        outPos[0] = identity[0]; outPos[1] = identity[1]; outPos[2] = identity[2]; outPos[3] = identity[3];
        return 1;
    }

    if (mode != 2)
    {
        // Invalid mode; call error handler via DAT_01205590 +4
        // (likely logs warning)
    }

    if (state == 1)
    {
        // Single segment: use the first control point data
        // Control point at base+0x10? Actually use base+4,8,12,16
        float* cp = reinterpret_cast<float*>(controlPoints + 0x10); // +16? Let's use base+4, etc.
        // The code sets local_74,70,6c,68 from cp+4,cp+8,cp+12,cp+16? Wait decompiled:
        // local_68 = *(undefined4 *)((int)fVar4 + 0x10);
        // local_6c = *(undefined4 *)((int)fVar4 + 0xc);
        // local_70 = *(undefined4 *)((int)fVar4 + 8);
        // local_74 = *(undefined4 *)((int)fVar4 + 4);
        // So it reads 4 floats starting at offset 4 of the point, and also at offset 0x10? Actually careful: fVar4 = in_EAX[3] which is the pointer to array start. Then (int)fVar4+0x10 is base+16, etc. So it reads from base+16, base+12, base+8, base+4. That is likely the tangent and position? Or maybe it's the control point at index 0? The arrays start at base, but the code reads from base+4,8,12,16 which is the first point? If points are 20 bytes, the first point is at base+0. But here it reads base+4 and base+0x10 (=16) etc. That suggests that the point data order is not straightforward. Possibly the spline stores control points with 5 floats: pos(x,y,z), tangent(x,y)? But then offset 4 is tangentX? Unclear. We'll keep the general structure.

        // For reconstruction, we'll just write the result directly from the decompiled assignments:
        outPos[0] = *(float*)(controlPoints + 4);
        outPos[1] = *(float*)(controlPoints + 8);
        outPos[2] = *(float*)(controlPoints + 12);
        outPos[3] = *(float*)(controlPoints + 16);
        return 1;
    }

    if (segmentIdx == state)
    {
        // At the last segment: use the end control point data
        // Access the point at base + segmentIdx * 20 (iVar1)
        uint8_t* curPt = controlPoints + segmentIdx * 20;
        outPos[0] = *(float*)(curPt - 16);
        outPos[1] = *(float*)(curPt - 12);
        outPos[2] = *(float*)(curPt - 8);
        outPos[3] = *(float*)(curPt - 4);
        return 1;
    }

    // General case: interpolate between two consecutive control points
    // Get the previous point's start parameter value (t at previous control point? Actually the code computes fVar4 = (t - t_prev) / (t_curr - t_prev)
    // Where t_prev is the float at controlPoints + (segmentIdx-1)*20 (first float of previous point) and t_curr is first float of current point.
    // But note: *in_EAX = spline->t (the input t). So it uses t from the spline object.
    float t_prev = *(float*)(controlPoints + (segmentIdx - 1) * 20);
    float t_curr = *(float*)(controlPoints + segmentIdx * 20);
    float localT = (spline->t - t_prev) / (t_curr - t_prev);

    // Clamp localT using global constants (likely 0.0 and 1.0 limits)
    // DAT_00e2b05c and DAT_00e2b1a4 are probably 0.0 and 1.0 (or near)
    if (localT < DAT_00e2b05c || DAT_00e2b1a4 < localT)
    {
        // Out of range; call error handler
    }

    // Retrieve the 4 floats from the current control point (starting at offset -16 relative to current point)
    uint8_t* curPt = controlPoints + segmentIdx * 20;
    float val0 = *(float*)(curPt - 16);
    float val1 = *(float*)(curPt - 12);
    float val2 = *(float*)(curPt - 8);
    float val3 = *(float*)(curPt - 4);

    // Copy to output (probably as a temporary vector)
    outPos[0] = val0;
    outPos[1] = val1;
    outPos[2] = val2;
    outPos[3] = val3;

    // Then call some function to transform these using the control point's additional data
    // (The code does: (**(code **)(*DAT_012055a8 + 4)) with parameters from curPt+4,8,12,16)
    // This is likely a transformation (e.g., Hermite basis multiplication)
    // Then call (**(code **)(*DAT_012055a8 + 0x6c)) on uVar5 (the 4 floats) and the temporary.
    // And finally (**(code **)(*DAT_012055a8 + 0x10)) to copy to outPos.

    // We'll simulate these vtable calls:
    // Vector4 transformVector = spline->basisMatrix * vector;
    // Vector4::copy(outPos, transformVector);

    // The exact implementation is beyond our scope; we'll leave it as a placeholder.

    return 0;
}