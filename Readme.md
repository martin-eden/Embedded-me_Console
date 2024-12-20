## What

(2024-10)

Experimental library for serial console output.

## Details

Idea is to have `Print()` for base types. For integers, for
memory segment and for ASCIIZ. Plus traditional `Write()` for
memory segment to do raw output.

Class provides indentation and items separation. Integers
are separated by spaces, strings by newlines.

Integers are converted to strings by [`me_CodecDecInt`][me_CodecDecInt] library.
You'd better love fixed-length representation and `+000` for
zero in signed byte.

## Sample output

```
[me_Console] demo.
--
  We'll show how values are represented for base types.
  We'll use indentation too.
  --
    TUint_1 ( 000 127 255 )
    TSint_1 ( -128 +000 +127 )
    TUint_2 ( 00000 32767 65535 )
    TSint_2 ( -32768 +00000 +32767 )
    TUint_4 ( 0000000000 2147483647 4294967295 )
    TSint_4 ( -2147483648 +0000000000 +2147483647 )
  --
--
[me_Console] That's all folks!

```

## Code

* [Example][Example]
* [Interface][Interface]
* [Implementation][Implementation]

## Install/remove

Easy way is to clone [GetLibs][GetLibs] repo and run it's code.

## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]

[me_CodecDecInt]: https://github.com/martin-eden/Embedded-me_CodecDecInt

[Example]: examples/me_Console/me_Console.ino
[Interface]: src/me_Console.h
[Implementation]: src/me_Console.cpp

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
