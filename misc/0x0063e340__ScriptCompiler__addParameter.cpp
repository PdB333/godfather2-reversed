// FUNC_NAME: ScriptCompiler::addParameter

void ScriptCompiler::addParameter(int isFunctionDefinition)
{
  int *functionData = *(int **)(this + 0x1c);                    // +0x1c: mFunctionData
  beginParameterCheck();                                          // FUN_0063def0: validate state
  if (functionData[0xd] > 100) {                                 // +0x34: mNumParameters
    char *errorMsg = formatString("too many %s (limit=%d)", "parameters", 100); // FUN_00636c00
    reportCompilerError(errorMsg);                               // FUN_00638b80
  }
  char *node = (char *)*functionData;                            // *functionData: mCurrentAstNode
  node[0x45] = (char)functionData[0xd];                         // +0x45: mParameterCount (byte)
  node[0x46] = (char)isFunctionDefinition;                      // +0x46: mIsDefinition (byte)
  if (isFunctionDefinition != 0) {
    finalizeNode();                                              // FUN_0063dfb0: commit definition
  }
  int complexity = functionData[9];                             // +0x24: mComplexity
  int totalComplexity = complexity + functionData[0xd];
  if ((unsigned char)node[0x47] < totalComplexity) {            // +0x47: mMaxComplexity (byte)
    if (totalComplexity > 0xf9) {
      reportCompilerError("function or expression too complex"); // FUN_00638b80
    }
    node[0x47] = (char)totalComplexity;
  }
  functionData[9] = complexity + functionData[0xd];             // mComplexity += mNumParameters
}