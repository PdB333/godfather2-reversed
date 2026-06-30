// FUNC_NAME: CurveSystem::processKeyframe
void __thiscall sampleCurveKeyframe(float inputValue, int* evaluatorContext, CurveSegment* segment, OutputBuffer* output)
{
    // segment->keyframes is a pointer to the keyframe list (at segment+4)
    int* keyframe = *(int**)(segment + 4);
    int functionIndex = keyframe[0];      // index into global function table
    float localValue = inputValue;

    // Validate function index and call the evaluator if valid
    if ((functionIndex >= 0) && (functionIndex < g_numCurveEvaluators))
    {
        // g_curveEvaluators is a table of function pointers, each entry 0xC bytes
        CurveEvaluatorFunc evaluator = *(CurveEvaluatorFunc*)(g_curveEvaluators + 4 + functionIndex * 0xC);
        if (evaluator != (CurveEvaluatorFunc)0)
        {
            evaluator(evaluatorContext, functionIndex, &localValue);
        }
    }

    // Output buffer descriptor: output->data is float*, output->capacity is second word
    uint outputIndex = keyframe[3];       // index into output array

    if ((uint)output[1] <= outputIndex)   // check capacity (output[1] == size)
    {
        int growRequested = 0;
        resizeBuffer(&growRequested);    // trigger buffer growth (FUN_00591c00)
    }

    // Write normalized result: (localValue - keyframe[1]) / keyframe[2]
    float base = (float)keyframe[1];
    float range = (float)keyframe[2];
    output->data[outputIndex] = (localValue - base) / range;
}