#ifdef DEBUG

// comment this line so it won't run performances logs
#define MEASURE_PERF

// uncomment this line to show the tile's boundings and positions (dev & debug)
// #define TILE_DEBUG

#ifdef WINDOWS

#define BOX_TL "+"
#define BOX_TR "+"
#define BOX_BL "+"
#define BOX_BR "+"
#define BOX_VL "|"
#define BOX_HL "-"
#define BOX_CR BOX_VL
#define BOX_CL BOX_VL

#define SBL_MICRO "u"

#else // UNIX

#define BOX_TL "┌"
#define BOX_TR "┐"
#define BOX_BL "└"
#define BOX_BR "┘"
#define BOX_VL "│"
#define BOX_HL "─"
#define BOX_CR "├"
#define BOX_CL "┤"

#define SBL_MICRO "µ"

#endif // WINDOWS

#endif // DEBUG