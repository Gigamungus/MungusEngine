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

#define MSTATIONARY 0
#define MCAMERA_FORWARD 1
#define MCAMERA_REVERSE -1
#define MPLANAR_FORWARD 2
#define MPLANAR_REVERSE -2

#define A_KEY 1
#define B_KEY 1
#define C_KEY 1
#define D_KEY 1
#define E_KEY 1
#define F_KEY 1
#define G_KEY 1
#define H_KEY 1
#define I_KEY 1
#define J_KEY 1
#define K_KEY 1
#define L_KEY 1
#define M_KEY 1
#define N_KEY 1
#define O_KEY 1
#define P_KEY 1
#define Q_KEY 1
#define R_KEY 1
#define S_KEY 1
#define T_KEY 1
#define U_KEY 1
#define V_KEY 1
#define W_KEY 1
#define X_KEY 1
#define Y_KEY 1
#define Z_KEY 1
#define ZERO_KEY 1
#define ONE_KEY 1
#define TWO_KEY 1
#define THREE_KEY 1
#define FOUR_KEY 1
#define FIVE_KEY 1
#define SIX_KEY 1
#define SEVEN_KEY 1
#define EIGHT_KEY 1
#define NINE_KEY 1
#define LMB_KEY 1
#define RMB_KEY 1