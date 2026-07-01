// FUNC_NAME: NetSession::maybeProcessAsyncOperation
void __fastcall NetSession::maybeProcessAsyncOperation(int this)
{
  undefined4 asyncOpResult;
  int isAsyncOpPending;
  
  asyncOpResult = *(undefined4 *)(this + 0x58); // +0x58: pendingAsyncOpResult
  isAsyncOpPending = FUN_007ff880(); // likely some session state check
  if (isAsyncOpPending != 0) {
    FUN_00878dc0(asyncOpResult); // processes the async operation result
  }
  return;
}