// UART text console

/*
  Author: Martin Eden
  Last mod.: 2024-12-19
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

namespace me_Console
{
  /*
    Raw console

    We're reading and writing data to/from memory from/to UART without
    processing.

    Base data types:

      * byte (TUint_1)
      * memory segment (TMemorySegment)
      * program memory segment (TMemorySegment also)

    Supported input/output:

            Output > | Memory    UART
      --Input--------+----------------------
              Memory |  ---      Put..()
      Program memory |  ---      PutProgmem..()
                UART |  Get..()  ---
  */
  class TRawConsole
  {
    public:
      TBool GetByte(TUint_1 * Byte);
      TBool PutByte(TUint_1 Byte);

      TUint_2 GetSegment(me_MemorySegment::TMemorySegment Data);
      TBool PutSegment(me_MemorySegment::TMemorySegment Data);
      TBool PutProgmemSegment(me_MemorySegment::TMemorySegment Data);
  };

  /*
    Item type

    Used in detection what delimiter we should emit between two
    items.

    Can be "chunk", "line", "number" or "nothing".
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

    Functional scope

      Provide implicit indentation and values delimiting.

    Supported data types:

      * Integer types (6 types, TUint_1, TSint_1, ..., TSint_4)
      * Memory segment (TMemorySegment)
      * Constant strings (TAsciiz)

    Supported methods:

      (
        Print
        Write (no indentation and delimiting)
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
      // ( Indents!

      // Increase indent
      void Indent();
      // Decrease indent
      void Unindent();

      // ) Indents!

      // ( Write data

      // Data is memory segment
      void Write(me_MemorySegment::TMemorySegment Data);
      // Data is ASCIIZ pointer
      void Write(const TAsciiz String);
      // Data is character
      void Write(TUnit Unit);
      // Data is segment in program memory
      void WriteProgmem(me_MemorySegment::TMemorySegment Data);

      // ) Write

      // ( Print data on standalone line

      // Data is memory segment
      void Print(me_MemorySegment::TMemorySegment Data);
      // Data is ASCIIZ pointer
      void Print(const TAsciiz Asciiz);
      // Data is segment in program memory
      void PrintProgmem(me_MemorySegment::TMemorySegment Data);

      // ) Print

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

      // ) Custom printers

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
  2024-10 ######
  2024-12-12
  2024-12-15
  2024-12-18
  2024-12-19
*/
