// FUNC_NAME: TNLConnection::handlePingResponse
undefined4 TNLConnection::handlePingResponse(undefined4 param_1)

{
  u_short uVar1;
  undefined4 uVar2;
  u_long uVar3;
  undefined8 *unaff_ESI;
  u_long local_4;
  
  local_4 = ntohl(*(u_long *)((int)unaff_ESI + 4));
  uVar2 = FUN_0065d130(param_1,&local_4);
  *unaff_ESI = 0;
  unaff_ESI[1] = 0;
  *(undefined2 *)unaff_ESI = 2;
  uVar1 = htons(0);
  *(u_short *)((int)unaff_ESI + 2) = uVar1;
  uVar3 = htonl(local_4);
  *(u_long *)((int)unaff_ESI + 4) = uVar3;
  return uVar2;
}