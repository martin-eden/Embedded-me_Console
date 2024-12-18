// Raw data console implementation

/*
  Author: Martin Eden
  Last mod.: 2024-12-18
*/

#include <me_Console.h>

#include <me_WorkMemory.h>
#include <me_FlashMemory.h>
#include <me_Uart.h>
#include <me_MemorySegment.h>

using namespace me_Console;

using
  me_Console::TRawConsole,
  me_MemorySegment::TMemorySegment,
  me_MemorySegment::TSegmentIterator;

TBool TRawConsole::GetByte(
  TUint_1 * Byte
)
{
  return me_Uart::GetByte(Byte);
}

TBool TRawConsole::PutByte(
  TUint_1 Byte
)
{
  me_Uart::SendByte(Byte);

  return true;
}

/*
  Read data from UART into memory segment

  Maximum data that can be read is segment capacity.

  Returns number of units (bytes) read.
*/
TUint_2 TRawConsole::GetSegment(
  TMemorySegment Data
)
{
  TSegmentIterator Rator;
  TAddress Addr;
  TUint_1 Byte;
  TUint_2 NumBytesProcessed = 0;

  if (!Rator.Init(Data))
    return NumBytesProcessed;

  while (Rator.GetNext(&Addr))
  {
    if (!GetByte(&Byte))
      break;

    if (!me_WorkMemory::SetByte(Byte, Addr))
      break;

    ++NumBytesProcessed;
  }

  return NumBytesProcessed;
}

/*
  Send data from memory segment to UART
*/
TBool TRawConsole::PutSegment(
  TMemorySegment Data
)
{
  TSegmentIterator Rator;
  TAddress Addr;
  TUint_1 Byte;

  if (!Rator.Init(Data))
    return false;

  while (Rator.GetNext(&Addr))
  {
    if (!me_WorkMemory::GetByte(&Byte, Addr))
      return false;

    PutByte(Byte);
  }

  return true;
}

/*
  Send data from segment in program memory to UART
*/
TBool TRawConsole::PutProgmemSegment(
  TMemorySegment Data
)
{
  TSegmentIterator Rator;
  TAddress Addr;
  TUint_1 Byte;

  if (!Rator.Init(Data))
    return false;

  while (Rator.GetNext(&Addr))
  {
    if (!me_FlashMemory::GetByte(&Byte, Addr))
      return false;

    PutByte(Byte);
  }

  return true;
}

/*
  2024-12-18
*/
