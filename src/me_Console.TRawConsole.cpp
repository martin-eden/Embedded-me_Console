// Raw data console implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-25
*/

#include <me_Console.h>

#include <me_MemorySegment.h>

#include <me_WorkMemory.h>
#include <me_ProgramMemory.h>
#include <me_Uart.h>

#include <me_Streams.h>
#include <me_MemsegStreams.h>

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
  Send data segment from memory to UART
*/
TBool TRawConsole::SendSegment(
  TMemorySegment Data
)
{
  me_MemsegStreams::TMemsegInputStream MemoryInputStream;
  me_Streams::TOutputStream UartOutputStream;

  if (!MemoryInputStream.Init(Data, me_WorkMemory::Op_GetByte))
    return false;

  UartOutputStream.Init(me_Uart::Op_PutByte);

  return me_Streams::Freetown::CopyTo(&UartOutputStream, &MemoryInputStream);
}

/*
  Send data from program memory segment to UART
*/
TBool TRawConsole::SendProgmemSegment(
  TMemorySegment Data
)
{
  me_MemsegStreams::TMemsegInputStream MemoryInputStream;
  me_Streams::TOutputStream UartOutputStream;

  if (!MemoryInputStream.Init(Data, me_ProgramMemory::Op_GetByte))
    return false;

  UartOutputStream.Init(me_Uart::Op_PutByte);

  return me_Streams::Freetown::CopyTo(&UartOutputStream, &MemoryInputStream);
}

/*
  2024-12-18
  2025-08-21
  2025-08-25
*/
