// Console base implementation

/*
  Author: Martin Eden
  Last mod.: 2025-09-13
*/

/*
  This class exists to provide base methods under convenient names for
  higher-level methods.

  This class is ancestor for TConsole. So it has only "protected"
  methods. We can add them directly to TConsole but do not want
  to clutter it's interface.
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>

#include <me_StreamTools.h>
#include <me_StreamsCollection.h>

using namespace me_Console;

/*
  Write byte to output stream
*/
TBool TConsoleBase::SendByte(
  TUint_1 Byte
)
{
  return OutputStream->Write(Byte);
}

/*
  Send data segment from memory to output stream
*/
TBool TConsoleBase::SendSegment(
  TAddressSegment MemSeg
)
{
  me_StreamsCollection::TWorkmemInputStream MemsegStream;

  if (!MemsegStream.Init(MemSeg))
    return false;

  return me_StreamTools::CopyStreamTo(&MemsegStream, OutputStream);
}

/*
  Send data from program memory segment to UART
*/
TBool TConsoleBase::SendProgmemSegment(
  TAddressSegment ProgmemSeg
)
{
  me_StreamsCollection::TProgmemInputStream ProgmemStream;

  if (!ProgmemStream.Init(ProgmemSeg))
    return false;

  return me_StreamTools::CopyStreamTo(&ProgmemStream, OutputStream);
}

/*
  2024 #
  2025-08-21
  2025-08-25
  2025-08-26
  2025-09-01
  2025-09-13
*/
