#pragma once

#define MUNGUS __declspec(dllexport)

#ifdef _DEBUG
#define MLOG(x) std::cout << x << "\n";
#define MASSERT(x, y) if (!(x)) {MLOG(y)}
#else
#define MLOG(x)
#define MASSERT(x, y)
#endif


#define MVERTICES 1
#define MPOSX 2
#define MPOSY 3
#define MPOSZ 4
#define MPOSW 5
#define MPRIMITIVES 6
#define MPRIMITIVETYPE 7
#define MVERTEXINDICES 8
#define MSURFACENORMAL 9
#define MSURFACECOLOR 10
#define MSHADERSTOUSE 11
#define MVERTEXSHADERS 12
#define MFRAGMENTSHADERS 13
#define MTRIANGLE 14
#define MACTOR 15
