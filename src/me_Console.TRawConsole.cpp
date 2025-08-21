// Raw data console implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-21
*/

#include <me_Console.h>

#include <me_Uart.h>
#include <me_WorkMemory.h>
#include <me_ProgramMemory.h>
#include <me_MemorySegment.h>
#include <me_SegmentProcessor.h>

using namespace me_Console;

using
  me_MemorySegment::TMemorySegment,
  me_MemorySegment::TSegmentIterator;

/*
  Setup UART to typical speed
*/
TBool TRawConsole::Init()
{
  return me_Uart::Init(me_Uart::Speed_115k_Bps);
}

/*
  Read byte from UART
*/
TBool TRawConsole::ReceiveByte(
  TUint_1 * Byte
)
{
  return me_Uart::GetByte(Byte);
}

/*
  Write byte to UART
*/
TBool TRawConsole::SendByte(
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
TUint_2 TRawConsole::ReceiveSegment(
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

    if (!me_WorkMemory::SetByteTo(Addr, Byte))
      break;

    ++NumBytesProcessed;
  }

  return NumBytesProcessed;
}

/*
  Send data segment from memory to UART
*/
TBool TRawConsole::SendSegment(
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
  Send data from program memory segment to UART
*/
TBool TRawConsole::SendProgmemSegment(
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
  2025-08-21
*/
