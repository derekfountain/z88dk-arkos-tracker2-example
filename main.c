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

/*
 * Boilerplate to put a IM2 jump table at 0xFC00. Be careful this table doesn't clash with
 * the music and player. The music and player have a hard coded origin.
 */
#define TABLE_HIGH_BYTE        ((unsigned int)0xfc)
#define JUMP_POINT_HIGH_BYTE   ((unsigned int)0xfb)

#define UI_256                 ((unsigned int)256)

#define TABLE_ADDR             ((void*)(TABLE_HIGH_BYTE*UI_256))
#define JUMP_POINT             ((unsigned char*)( (unsigned int)(JUMP_POINT_HIGH_BYTE*UI_256) + JUMP_POINT_HIGH_BYTE ))


/*
 * Each interrupt, play the next frame of music data.
 * Also flicker a screen address to show it's running.
 */
uint8_t playing = 1;
uint8_t flicker=0;
IM2_DEFINE_ISR(isr)
{
  *(uint8_t*)(0x4000) = flicker++;

  if( playing )
    ply_akg_play();
}

int main()
{
  /* Set up the interrupt */
  memset( TABLE_ADDR, JUMP_POINT_HIGH_BYTE, 257 );

  z80_bpoke( JUMP_POINT,   195 );
  z80_wpoke( JUMP_POINT+1, (unsigned int)isr );

  im2_init( TABLE_ADDR );

  /* Initialise music */
  ply_akg_init(hocuspocus, 0);

  /* Start playing, stop and start on keypress */
  intrinsic_ei();

  while(1)
  {
    if( in_key_pressed( IN_KEY_SCANCODE_SPACE ) )
    {
      while( in_key_pressed( IN_KEY_SCANCODE_SPACE ) );

      if( playing )
	ply_akg_stop();

      playing = !playing;
    }

  }

}
