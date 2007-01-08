/* This file was automatically generated.  Do not edit! */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#if defined(HAS_VALUES_H)
#include <values.h>
#include <unistd.h>
#endif
#include "mpi.h"
#include "az_aztec.h"
#include "rf_allo.h"
#include "dft_basic_lin_prob_mgr_wrapper.h"
#include "dft_poly_lin_prob_mgr_wrapper.h"
#include "dft_hardsphere_lin_prob_mgr_wrapper.h"
#include "Tramonto_ConfigDefs.h"
#define NCOMP_MAX 5
extern double Pol[NCOMP_MAX];
#define NDIM_MAX  3
extern double Esize_x[NDIM_MAX];
extern int ***Surf_normal;
extern int **Nodes_2_boundary_wall;
#define KAPPA_H2O 78.5
#define PI    M_PI
extern double Temp_elec;
extern int Ndim;
extern int Lpolarize[NCOMP_MAX];
extern double Charge_f[NCOMP_MAX];
#define POISSON        3
extern int Nwall;
#define DIFFUSION      5
extern double Betamu[NCOMP_MAX];
#define NMER_MAX     100
extern double Betamu_seg[NMER_MAX];
extern double *Deltac_b;
extern double Betamu_wtc[NMER_MAX];
extern double Betamu_att[NCOMP_MAX];
#define LJ12_6       2
extern double Betamu_hs_ex[NCOMP_MAX];
#define IDEAL_GAS    0
extern int Ipot_ff_n;
extern int Iliq_vap;
extern int Lsteady_state;
extern double Rho_b[NCOMP_MAX];
extern double Rho_seg_b[NMER_MAX];
extern void *LinProbMgr_manager;
extern double VEXT_MAX;
extern double **Vext;
extern int **Zero_density_TF;
#define BONDWTC       7
extern int *Pol_Sym;
extern int **Poly_to_Unk_SegAll;
extern int *Nbonds_SegAll;
double load_polyTC_cavityEL(int iunk,int loc_inode,int inode_box,int icomp,int izone,int *ijk_box,double **x,int resid_only_flag);
double load_polyTC_bondEL(int iunk,int loc_inode,int inode_box,int icomp,int izone,int *ijk_box,double **x,int resid_only_flag);
double load_polyTC_diagEL(int iunk,int loc_inode,int inode_box,int icomp,int izone,int *ijk_box,double **x,int resid_only_flag);
#define THETA_CHARGE   3
#define DELTAC     1 
#define U_ATTRACT      2
double load_mean_field(int sten_type,int iunk,int loc_inode,int icomp,int izone,int *ijk_box,double **x,int resid_only_flag);
extern int Type_attr;
#define THETA_FN       1
#define DELTA_FN       0
typedef struct RB_Struct RB_Struct;
double load_nonlocal_hs_rosen_rb(int sten_type,int iunk,int loc_inode,int inode_box,int icomp,int izone,int *ijk_box,double **x,struct RB_Struct *dphi_drb,int resid_only_flag);
extern int Type_func;
#define FLAG_PBELEC -777
double fill_EL_elec_field(int iunk,int icomp,int loc_inode,int inode_box,double **x,int resid_only_flag);
#define NONE       -1
#define NONE      -1
#define NONE -1
extern int Type_coul;
double fill_EL_ext_field(int iunk,int icomp,int loc_inode);
double fill_EL_chem_pot(int iunk,int icomp,int iseg,int loc_inode,int inode_box,int mesh_coarsen_flag_i,double **x,int resid_only_flag);
double fill_EL_ideal_gas(int iunk,int icomp,int loc_inode,int inode_box,double **x,int resid_only_flag);
double fill_sym_WTC(int iunk,int iseg,int loc_inode,int inode_box,double **x,int resid_only_flag);
extern int *Pol_Sym_Seg;
double fill_bulk_density(int iunk,int icomp,int iseg,int loc_inode,int inode_box,double **x,int resid_only_flag);
#define TRUE  1
#if !defined(_CON_CONST_H_)
#define _CON_CONST_H_
#endif
#if !defined(TRUE) && !defined(_CON_CONST_H_)
#define TRUE  1
#endif
#define FLAG_BULK   -888
#define FALSE 0
#if !defined(FALSE) && !defined(_CON_CONST_H_)
#define FALSE 0
#endif
double fill_zero_value(int iunk,int loc_inode,int inode_box,double **x,int resid_only_flag);
int check_zero_density_EL(int iunk,int icomp,int iseg,int loc_inode,int inode_box,double **x);
extern int Unk2Comp[NMER_MAX];
#define WTC          3
extern int Type_poly;
#define DENSITY        0
#define NEQ_TYPE       8
extern int Phys2Unk_first[NEQ_TYPE];
struct RB_Struct {
  double    S0;      /*   1/(4*pi*Ri*Ri) * Delta_fn   */
  double    S1;      /*   1/(4*pi*Ri)    * Delta_fn   */
  double    S2;      /*                    Delta_fn   */
  double    S3;      /*                    Theta_fn   */
  double    V1[NDIM_MAX];      /*  1/(4*pi*Ri) * unit_vec * Delta_Fn   */
  double    V2[NDIM_MAX];      /*                unit_vec * Delta_Fn   */
};
double load_euler_lagrange(int iunk,int loc_inode,int inode_box,int *ijk_box,int izone,double **x,struct RB_Struct *dphi_drb,int mesh_coarsen_flag_i,int resid_only_flag);
