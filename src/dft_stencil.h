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
#define TRUE  1
#if !defined(_CON_CONST_H_)
#define _CON_CONST_H_
#endif
#if !defined(TRUE) && !defined(_CON_CONST_H_)
#define TRUE  1
#endif
#define FALSE 0
#if !defined(FALSE) && !defined(_CON_CONST_H_)
#define FALSE 0
#endif
#define PERIODIC     1
#define NDIM_MAX  3
extern int Type_bc[NDIM_MAX][2];
extern double Size_x[NDIM_MAX];
int round_to_int(double x);
int ijk_to_isten_index(int *ijk,int *el_in_radius);
extern double Jac_threshold;
int stencil_quadBoundaryEl_switch(int sten);
void distribute_weight_to_nodes(double weight,double *qp,double *el_weights,int ig,int jg,int kg);
double stencil_GetWeight_switch(int sten,int icomp,int jcomp,double rsq,double sten_rad,int ngpu,double *gpu,double *gwu);
void set_gauss_quad(int ngp,double *gp,double *gw);
int stencil_quadGaussIntegrand_switch(int sten,double r);
int stencil_quadGauss_switch(int sten,double r);
void print_out_stencil(int isten,int izone,int icomp,int jcomp,FILE *ifp);
typedef struct Stencil_Struct Stencil_Struct;
void renormalize_stencil(struct Stencil_Struct *sten,double vol_sten);
#define NO_RENORMALIZATION_FLAG -888
void shorten_stencil(struct Stencil_Struct *sten);
#define U_ATTRACT      2
extern int Lcut_jac;
void safe_free(void **ptr);
void safe_free(void **ptr);
void merge_load_stencil(struct Stencil_Struct *sten,int **el_offsets,double *el_weights,int *el_in_radius,int *index_sten);
void calc_sten_weight_el_on_boundary(int isten,double sten_rad,int icomp,int jcomp,double r_center_sq,double *x_left,double *esize_zone,double *el_weights);
void calc_sten_weight_el_in_radius(int isten,double sten_rad,int icomp,int jcomp,double r_center_sq,double *x_left,double *esize_zone,double *el_weights);
int stencil_deltaLogical(int sten);
int calc_in_out_on(double *x_l,double *x_r,double sten_rad);
void setup_stencil_offsets(int i,int j,int k,int **el_offsets);
extern int Lhard_surf;
double stencil_radius_switch(int sten,int icomp,int jcomp);
double stencil_volume_switch(int sten,int icomp,int jcomp);
int stencil_Njcomp_switch(int sten);
#define NSTEN        8
extern int Sten_Type[NSTEN];
#if defined(DEC_ALPHA)
#define POW_INT powii
#endif
#if !(defined(DEC_ALPHA))
#define POW_INT (int)pow
#endif
extern double Esize_x[NDIM_MAX];
extern double Jac_grid;
extern int Coarser_jac;
extern int Max_sten_length[3];
extern int Ndim;
extern int Nnodes_per_el_V;
extern int Ncomp;
extern int Nzone;
#if defined(__STDC__)
void *array_alloc(int numdim,...);
#endif
void *array_alloc(int numdim,...);
#if !(defined(__STDC__))
void *array_alloc(...);
#endif
extern struct Stencil_Struct ***Stencil;
#define VERBOSE      3 
#define NO_SCREEN    2 
extern int Iwrite;
extern int Proc;
#if defined(DEBUG)
extern int Proc;
#endif
struct Stencil_Struct {
  int        Length;      /* Number of nodes that interact with current 
                             node through this stencil                    */
  int      **Offset;      /* 2D array to be set to size [Length][Ndim] that
                             gives relative position of interacting node  */
  double    *Weight;      /* 1D array of size [Length] that gives weight
                             of interacting node to total stencil         */
  double   **HW_Weight;   /* 2D array of size [Length][Nnodes_per_el] that
                             holds the weights based on what element they
                             are being contributed from. Only used for Hard
                             Walls when stencil point is a boundary node  */
};
void calc_stencils(void);