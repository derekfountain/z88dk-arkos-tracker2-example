#include <arch/zx.h>
#include <intrinsic.h>
#include <string.h>
#include <z80.h>
#include <input.h>

/* These are in the AT2 code, called via the rasm_wrapper assembly language */
extern void ply_akg_init(unsigned int * songdata, unsigned int subSong) __z88dk_callee;
extern void ply_akg_play();
extern void ply_akg_stop();

/* Song data, also in the rasm_wrapper */
extern int hocuspocus[];

uint8_t flicker=0;

int main()
{
  /* Initialise music */
  ply_akg_init(hocuspocus, 0);

  while(1)
  {
    *(uint8_t*)(0x4000) = flicker++;
    intrinsic_di();
    ply_akg_play();
    intrinsic_ei();
    intrinsic_halt();
  }
}
