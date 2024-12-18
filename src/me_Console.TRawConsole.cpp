// Raw data console implementation

/*
  Author: Martin Eden
  Last mod.: 2024-12-18
*/

#include <me_Console.h>

#include <me_WorkMemory.h>
#include <me_ProgramMemory.h>
#include <me_Uart.h>
#include <me_MemorySegment.h>
#include <me_SegmentProcessor.h>

using namespace me_Console;

using
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
    if (!me_Uart::GetByte(&Byte))
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
  return
    me_SegmentProcessor::CopyFrom(
      Data,
      Data,
      me_WorkMemory::Op_GetByte,
      me_Uart::Op_PutByte
    );
}

/*
  Send data from segment in program memory to UART
*/
TBool TRawConsole::PutProgmemSegment(
  TMemorySegment Data
)
{
  return
    me_SegmentProcessor::CopyFrom(
      Data,
      Data,
      me_ProgramMemory::Op_GetByte,
      me_Uart::Op_PutByte
    );
}

/*
  2024-12-18
*/
