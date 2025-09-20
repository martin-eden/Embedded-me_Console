// UART text console

/*
  Author: Martin Eden
  Last mod.: 2025-09-20
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>
#include <me_StreamsCollection.h>

namespace me_Console
{
  /*
    Raw console

    Internal interface to write data.

    Base data types:

      * byte (TUint_1)
      * memory segment (TAddressSegment)
  */
  class TConsoleBase
  {
    protected:
      IInputStream * InputStream;
      IOutputStream * OutputStream;

      TBool SendByte(TUint_1 Byte);

      TBool SendSegment(TAddressSegment Data);
      TBool SendProgmemSegment(TAddressSegment Data);
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
      * Memory segment (TAddressSegment)
      * Constant strings (TAsciiz)

    Supported methods:

      (
        Print (newlines after strings, spaces between other values)
        Write (spaces between values)
        EndLine
      )
      (
        Indent
        Unindent
      )
  */
  class TConsole : protected TConsoleBase
  {
    public:
      // Setup
      void Init();

      // ( Assignable streams
      IInputStream * GetInputStream();
      void SetInputStream(IInputStream *);

      IOutputStream * GetOutputStream();
      void SetOutputStream(IOutputStream *);
      // )

      // ( Indents!
      // Increase indent
      void Indent();
      // Decrease indent
      void Unindent();
      // )

      // ( Write data
      // Data is memory segment
      void Write(TAddressSegment Data);
      // Data is ASCIIZ pointer
      void Write(const TAsciiz String);
      // Data is character
      void Write(TUnit Unit);
      // Data is segment in program memory
      void WriteProgmem(TAddressSegment Data);
      // )

      // ( Print data on standalone line
      // Data is memory segment
      void Print(TAddressSegment Data);
      // Data is ASCIIZ pointer
      void Print(const TAsciiz Asciiz);
      // Data is segment in program memory
      void PrintProgmem(TAddressSegment Data);
      // )

      // Print newline if not on empty line
      void EndLine();

      // ( Custom printers for base types
      // TUint_1
      void Print(TUint_1 Uint_1);
      // TUint_2
      void Print(TUint_2 Uint_2);
      // TUint_4
      void Print(TUint_4 Uint_4);
      // TSint_1
      void Print(TSint_1 Sint_1);
      // TSint_2
      void Print(TSint_2 Sint_2);
      // TSint_4
      void Print(TSint_4 Sint_4);
      // TBool
      void Print(TBool Bool);
      // )

      // ( Custom readers for base types
      // TUint_1
      TBool Read(TUint_1 * Uint_1);
      // TUint_2
      TBool Read(TUint_2 * Uint_2);
      // TBool
      TBool Read(TBool * Bool);
      // )

    private:
      // ( Default input and output streams
      me_StreamsCollection::TUartInputStream UartInputStream;
      me_StreamsCollection::TUartOutputStream UartOutputStream;
      // )

      // ( Internal mechanics to avoid double spaces and
      //    heading/trailing spaces in output.
      TItemType PrevItemType = TItemType::Nothing;
      TUint_1 IndentLev = 0;

      // Print delimiter
      void PrintDelimiter(TItemType CurItemType);
      // Print indentation
      void PrintIndent(TItemType CurItemType);
      // Print delimiter and maybe indent before item
      void PrintDelimiterBefore(TItemType CurItemType);
      // )
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
  2024 # # # # # # # # # #
  2025-08-14 TBool printing
  2025-08-21 Init()
  2025-08-26
  2025-09-01
  2025-09-04
  2025-09-13
  2025-09-20 TBool reading
*/
