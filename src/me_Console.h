// UART text console

/*
  Author: Martin Eden
  Last mod.: 2025-08-21
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

namespace me_Console
{
  /*
    Raw console

    Internal interface to read/write data.

    Base data types:

      * byte (TUint_1)
      * memory segment (TMemorySegment)

    Supported directions:

      UART -> RAM: Receive..()
      RAM -> UART: Send..()
      Flash -> UART: EmitProgmem..()
  */
  class TRawConsole
  {
    public:
      TBool Init();

      TBool ReceiveByte(TUint_1 * Byte);
      TBool SendByte(TUint_1 Byte);

      TUint_2 ReceiveSegment(me_MemorySegment::TMemorySegment Data);
      TBool SendSegment(me_MemorySegment::TMemorySegment Data);
      TBool SendProgmemSegment(me_MemorySegment::TMemorySegment Data);
  };

  /*
    Item type

    Internal

    Used in detection what delimiter we should emit between two items.
  */
  enum TItemType
  {
    Chunk,
    Line,
    Number,
    Nothing
  };

  /*
    Text console

    Provides built-in indentation and delimiting.

    Supported data types:

      * Boolean
      * Integers
      * Memory segment (TMemorySegment)
      * Constant strings (TAsciiz)

    Supported methods:

      (
        Print (prints newlines after strings, spaces after numbers)
        Write (no newlines after strings, spaces after numbers)
        EndLine
      )
      (
        Indent
        Unindent
      )
  */
  class TConsole
  {
    public:
      // Setup UART to typical speed. Optional
      void Init();

      // ( Indents!

      // Increase indent
      void Indent();
      // Decrease indent
      void Unindent();

      // )

      // ( Write data

      // Data is memory segment
      void Write(me_MemorySegment::TMemorySegment Data);
      // Data is ASCIIZ pointer
      void Write(const TAsciiz String);
      // Data is character
      void Write(TUnit Unit);
      // Data is segment in program memory
      void WriteProgmem(me_MemorySegment::TMemorySegment Data);

      // )

      // ( Print data on standalone line

      // Data is memory segment
      void Print(me_MemorySegment::TMemorySegment Data);
      // Data is ASCIIZ pointer
      void Print(const TAsciiz Asciiz);
      // Data is segment in program memory
      void PrintProgmem(me_MemorySegment::TMemorySegment Data);

      // )

      // Print newline if not on empty line
      void EndLine();

      // ( Custom printers for base types

      // Print TUint_1
      void Print(TUint_1 Uint_1);
      // Print TUint_2
      void Print(TUint_2 Uint_2);
      // Print TUint_4
      void Print(TUint_4 Uint_4);
      // Print TSint_1
      void Print(TSint_1 Sint_1);
      // Print TSint_2
      void Print(TSint_2 Sint_2);
      // Print TSint_4
      void Print(TSint_4 Sint_4);
      // Print TBool
      void Print(TBool Bool);

      // )

    private:
      /*
        Internal mechanics to avoid double spaces and heading/trailing
        spaces in output.
      */
      // Raw UART I/O
      TRawConsole RawConsole;

      // Last item type
      TItemType PrevItemType = TItemType::Nothing;

      // Indentation level
      TUint_1 IndentLev = 0;

      // Print delimiter
      void PrintDelimiter(TItemType CurItemType);

      // Print indentation
      void PrintIndent(TItemType CurItemType);

      // Print delimiter and maybe indent before item
      void PrintDelimiterBefore(TItemType CurItemType);
  };
}

/*
  Exported class instance for shared use

  Because you want to keep indentation in call chain of functions
  that are using this module.

  Assigned in "me_Console.cpp".
*/
extern me_Console::TConsole Console;

/*
  2024-10 # # # # # #
  2024-12 # # # #
  2025-08-14 TBool printing
  2025-08-21 Init()
*/
