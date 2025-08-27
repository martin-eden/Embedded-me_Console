// Raw data console implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-27
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>

#include <me_Uart.h>
#include <me_WorkMemory.h>
#include <me_ProgramMemory.h>
#include <me_MemorySegment.h>

#include <me_Streams.h>
#include <me_MemsegStreams.h>

using namespace me_Console;

/*
  Setup UART to typical speed
*/
TBool TRawConsole::Init()
{
  if (!me_Uart::Init(me_Uart::Speed_115k_Bps))
    return false;

  OutputStream.Init(me_Uart::Op_PutByte);

  return true;
}

/*
  Return pointer to output stream instance
*/
IOutputStream * TRawConsole::GetOutputStream()
{
  return &OutputStream;
}

/*
  Write byte to output stream
*/
TBool TRawConsole::SendByte(
  TUint_1 Byte
)
{
  return OutputStream.Write(Byte);
}

/*
  Send data segment from memory to output stream
*/
TBool TRawConsole::SendSegment(
  me_MemorySegment::TMemorySegment Data
)
{
  me_MemsegStreams::TMemsegInputStream MemoryInputStream;

  if (!MemoryInputStream.Init(Data, me_WorkMemory::Op_GetByte))
    return false;

  return me_Streams::CopyStreamTo(&MemoryInputStream, &OutputStream);
}

/*
  Send data from program memory segment to UART
*/
TBool TRawConsole::SendProgmemSegment(
  me_MemorySegment::TMemorySegment Data
)
{
  me_MemsegStreams::TMemsegInputStream MemoryInputStream;

  if (!MemoryInputStream.Init(Data, me_ProgramMemory::Op_GetByte))
    return false;

  return me_Streams::CopyStreamTo(&MemoryInputStream, &OutputStream);
}

/*
  2024 #
  2025-08-21
  2025-08-25
  2025-08-26
*/
