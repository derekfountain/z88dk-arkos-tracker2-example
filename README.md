# z88dk-arkos-tracker2-example
Small example of playing music from Arkos Tracker 2 on the ZX Specturm using z88dk C code.

(Arkos Tracker 2)[http://www.julien-nevo.com/arkostracker/] ("AT2") is a music creation tool for 8-bit micros.
It includes support for the AY-3-8912 sound chip as found in the ZX Spectrum.

AT2 doesn't support the (z88dk C development kit)[https://z88dk.org/site/] or the z80asm assembler
z88dk uses, so getting a C program to play AT2 derived music is a bit of a wrestling match. I made
it work, and this repository is a brief demonstration of how to do it. The example works on Linux;
Windows users will have port it.

AT2 uses the (rasm assembler)[https://github.com/EdouardBERGE/rasm] and you'll need a copy of that.
Go and get it, build it, and ensure rasm.exe is in your PATH:

```
>rasm.exe
RASM v1.5 (build xx/07/2021) (c) 2017 Edouard BERGE (use -n option to display all licenses / -autotest for self-testing)
LZ4 (c) Yann Collet / ZX0 & ZX7 (c) Einar Saukas / Exomizer 2 (c) Magnus Lind / LZSA & AP-Ultra (c) Emmanuel Marty

SYNTAX: rasm <inputfile> [options]

use option -h for help
```

Then you should be able to type 'make' to build the example project. It produces a TAP file which
Fuse plays correctly. That's a much testing as I've done. :)

Distributed under the MIT licence, as that's what the included AT2 'hocuspocus' music is distributed under.
