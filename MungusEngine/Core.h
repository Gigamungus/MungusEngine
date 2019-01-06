#pragma once

#define MUNGUS __declspec(dllexport)

#ifdef _DEBUG
#define MLOG(x) std::cout << x << "\n";
#define MASSERT(x, y) if (!(x)) {MLOG(y)}
#else
#define MLOG(x)
#define MASSERT(x, y)
#endif


#define MPOINT 1
#define MLINE 2
#define MTRIANGLE 3

#define MACTOR 1
