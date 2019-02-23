#pragma once

#define MUNGUS __declspec(dllexport)

#ifdef _DEBUG
#define MLOG(x) std::cout << x << "\n";
#define MASSERT(x, y) if (!(x)) {MLOG(y)}
#define REPEAT(x, y) x; for (int i = 0; i < y; i++) { x } 
#else
#define MLOG(x)
#define MASSERT(x, y)
#define REPEAT(x, y) x
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

#define A_KEY		1
#define B_KEY		2
#define C_KEY		3
#define D_KEY		4
#define E_KEY		5
#define F_KEY		6
#define G_KEY		7
#define H_KEY		8
#define I_KEY		9
#define J_KEY		10
#define K_KEY		11
#define L_KEY		12
#define M_KEY		13
#define N_KEY		14
#define O_KEY		15
#define P_KEY		16
#define Q_KEY		17
#define R_KEY		18
#define S_KEY		19
#define T_KEY		20
#define U_KEY		21
#define V_KEY		22
#define W_KEY		23
#define X_KEY		24
#define Y_KEY		25
#define Z_KEY		26
#define ZERO_KEY	27
#define ONE_KEY		28
#define TWO_KEY		29
#define THREE_KEY	30
#define FOUR_KEY	31
#define FIVE_KEY	32
#define SIX_KEY		33
#define SEVEN_KEY	34
#define EIGHT_KEY	35
#define NINE_KEY	36
#define ESCAPE_KEY	37
#define SPACE_KEY	38
#define LMB_KEY		39
#define RMB_KEY		40
