/* ---------------------------------------------------------
Routines to Calculate the thermodynamic properties of hard sphere fluids.
Two routines are included for hard sphere properties -
(1) is based on the Percus-Yevick compressibilty equation of state.
the other (2) uses the same notation as the DFT Euler-Lagrange fill later 
in the code.  These should give the same results.
------------------------------------------------------------*/
#include "dft_globals_const.h"
#include "rf_allo.h"
#include "mpi.h"

void sum_rhobar(double,int, double *);

/********************************************************************************
calc_hs_properties_new:  This routine calculates the pressure and excess chemical 
                         potential for hard spheres at the density of interest 
                         using notation consistent with the DFT code PY equations. */

/*double calc_hs_properties_new(double *betamu_hs,double *rho)
{
   int icomp;
   double hs_diam_cubed, n_o,n_1,n_2,n_3;
          betap_hs;

   *  Determine the effective hard sphere diameters 
    For now we will set these to unity, but in the future we
    can define a temperature dependent diameter. Doing so
    offers a way to provide a better mean field equation of
    state. In essence, for  an attractive (e.g LJ) fluid (mixture)
    we can use the effective hard sphere diameter to off set the 
    shortcomings of the PY + mean field approximation. See the
    work by Telo da Gama et al.. 
   *

   * calculate the hard sphere diamtere ... this can be 
      turned into a T-dependent diameter *

   for (icomp=0; icomp<Ncomp; ++icomp) Hs_diam[icomp] = 1.0;   * note that the HS_diam parameter should be d/sigma_ref since
                                                                  all bulk densities are in rho*sigma_ref^3. *

   *  calculate the constants xsi and introduce some shorthand *

   hs_diam_cubed = POW_DOUBLE_INT(Hs_diam[icomp],3);
   n3 = Rhobar_b[0]*hs_diam_cubed;  * note that in the code the order of the nonlocal densities is reversed *
   n2 = Rhobar_b[1]*hs_diam_cubed;
   n1 = Rhobar_b[2]*hs_diam_cubed;
   n0 = Rhobar_b[3]*hs_diam_cubed;

   y1 = 1.0 - n3;
   y2 = y1 * y1;
   y3 = y1 * y1 * y1;

   * the hard sphere excess chemical potential in units of kT *
   for (icomp=0; icomp<Ncomp;icomp++){
      Betamu_hs_ex[icomp] = -log(1-n3)-(n0/y1)+(n2/y1)+(n1/y1)+(n1*n2)/(y2)+1/(24.*PI*y2)+ n2/
   }


   * the hard sphere pressure in units of kT and Sigma_ff[1]^3 *

   betap_hs = (1.0/pi6) * (xsi0/y1 + 3.0 * xsi1 * xsi2/y2 +
                                     3.0 * POW_DOUBLE_INT(xsi2,3)/y3  );


   for (icomp=0; icomp<Ncomp; ++icomp) 
      Betamu_hs_ex[icomp] = - log(y1) +
              pi6 * betap_hs * POW_DOUBLE_INT(Sigma_ff[icomp][icomp],3) +
              3.0 * xsi2 * Sigma_ff[icomp][icomp]/y1 +
              3.0 * xsi1 * POW_DOUBLE_INT(Sigma_ff[icomp][icomp],2)/y1 +
              4.5 * POW_DOUBLE_INT((xsi2 * Sigma_ff[icomp][icomp]),2)/y2 ;

   * 
    * add the ideal gas term to give
    * the hard sphere chemical potential in units of kT 
    *
   for (icomp=0; icomp<Ncomp; ++icomp) {
      betamu_hs[icomp]  =  Betamu_hs_ex[icomp]; 
   }

   return (betap_hs);
}*/
/*************************************************************
/********************************************************************************
calc_hs_properties:  This routine calculates the pressure and excess chemical 
                     potential for hard spheres at the density of interest 
                     using the PY equations.            */

double calc_hs_properties(double *betamu_hs,double *rho)
{
   int icomp;
   double pi6, hs_diam_cubed, xsi0, xsi1, xsi2, xsi3, y1, y2, y3,
          betap_hs;

   xsi0=xsi1=xsi2=xsi3=0.0;
   pi6 = PI/6.0;                 /* shorthand  for pi/6                 */

   /*  Determine the effective hard sphere diameters 
    For now we will set these to unity, but in the future we
    can define a temperature dependent diameter. Doing so
    offers a way to provide a better mean field equation of
    state. In essence, for  an attractive (e.g LJ) fluid (mixture)
    we can use the effective hard sphere diameter to off set the 
    shortcomings of the PY + mean field approximation. See the
    work by Telo da Gama et al.. 
   */

   /* calculate the hard sphere diamtere ... this can be 
      turned into a T-dependent diameter */

   for (icomp=0; icomp<Ncomp; ++icomp) Hs_diam[icomp] = 1.0;  

   /*  calculate the constants xsi and introduce some shorthand */

   for (icomp=0; icomp<Ncomp; ++icomp) {
      hs_diam_cubed = POW_DOUBLE_INT(Hs_diam[icomp],3);
      xsi0 +=Fac_overlap_hs[icomp]*pi6 * rho[icomp] * hs_diam_cubed;
      xsi1 +=Fac_overlap_hs[icomp]*pi6 * rho[icomp] * hs_diam_cubed * Sigma_ff[icomp][icomp];
      xsi2 +=Fac_overlap_hs[icomp]*pi6 * rho[icomp] * hs_diam_cubed * POW_DOUBLE_INT(Sigma_ff[icomp][icomp],2);
      xsi3 +=Fac_overlap_hs[icomp]*pi6 * rho[icomp] * hs_diam_cubed * POW_DOUBLE_INT(Sigma_ff[icomp][icomp],3);
   }
   y1 = 1.0 - xsi3;
   y2 = y1 * y1;
   y3 = y1 * y1 * y1;

   /* the hard sphere pressure in units of kT and Sigma_ff[1]^3 */

   betap_hs = (1.0/pi6) * (xsi0/y1 + 3.0 * xsi1 * xsi2/y2 +
                                     3.0 * POW_DOUBLE_INT(xsi2,3)/y3  );

   /* the excess hard sphere chemical potential in units of kT */

   for (icomp=0; icomp<Ncomp; ++icomp) 
      Betamu_hs_ex[icomp] = - log(y1) +
              pi6 * betap_hs * POW_DOUBLE_INT(Sigma_ff[icomp][icomp],3) +
              3.0 * xsi2 * Sigma_ff[icomp][icomp]/y1 +
              3.0 * xsi1 * POW_DOUBLE_INT(Sigma_ff[icomp][icomp],2)/y1 +
              4.5 * POW_DOUBLE_INT((xsi2 * Sigma_ff[icomp][icomp]),2)/y2 ;

   /* 
    * add the ideal gas term to give
    * the hard sphere chemical potential in units of kT 
    */
   for (icomp=0; icomp<Ncomp; ++icomp) {
      betamu_hs[icomp]  =  Betamu_hs_ex[icomp]; 
   }

   return (betap_hs);
}
/*******************************************************************************/
/* compute_bulk_nonlocal_hs_properties: compute some additional bulk values of
   nonlocal densities.  It is convenient to compute these once up front.  */
void compute_bulk_nonlocal_hs_properties(char *output_file1)
{
  int i,loc_inode,loc_i,inode_box,inode,ijk[3],icomp,idim,iunk,printproc;
  int ibond,iseg,jseg,pol_number,type_jseg,nloop,iloop;
  double vol,area,x_dist;
  FILE *fp2=NULL;
  if (Proc==0) printproc = TRUE;
  else printproc=FALSE;
  if (printproc) fp2 = fopen(output_file1,"a+");

   /* compute bulk nonlocal densities needed for Rosenfeld terms */
  for (iunk=0; iunk<Nrho_bar; iunk++){
     Rhobar_b[iunk] = 0.0;
     Rhobar_b_LBB[iunk] = 0.0;
     Rhobar_b_RTF[iunk] = 0.0;
  }

  if (Type_poly==WTC) nloop=Nseg_tot;
  else             nloop=Ncomp;

  for (iloop=0; iloop<nloop; iloop++){
       if (Type_poly==WTC) icomp=Unk2Comp[iloop];
       else             icomp=iloop;

       if (Type_poly==WTC){
           sum_rhobar(Rho_seg_b[iloop],icomp,Rhobar_b);
       }
       else{
          if (Lsteady_state){
                 sum_rhobar(Rho_b_LBB[icomp],icomp,Rhobar_b_LBB);
                 sum_rhobar(Rho_b_RTF[icomp],icomp,Rhobar_b_RTF);
          }
          else if (Nwall ==0 && Iliq_vap==3){
                 sum_rhobar(Rho_coex[1],icomp,Rhobar_b_LBB);
                 sum_rhobar(Rho_coex[0],icomp,Rhobar_b_RTF);
          }
          else sum_rhobar(Rho_b[icomp],icomp,Rhobar_b);
   
       }
  }
  if (printproc){
        fprintf(fp2,"Rhobar_bulk, LBB, and RTF variables for Rosenfeld HS functionals:\n");
        fprintf(fp2,"Note that vector terms are strictly zero in the bulk!\n");
        fprintf(fp2,"\t i  Rhobar_b[i]  Rhobar_b_LBB[i]  Rhobar_b_RTF[i]\n");
        for (i=0;i<4;i++) fprintf(fp2,"\t %d \t %9.6f \t %9.6f \t %9.6f\n", i,
                 Rhobar_b[i], Rhobar_b_LBB[i], Rhobar_b_RTF[i]);
        if (Iwrite==VERBOSE){
           printf("Rhobar_bulk, LBB, and RTF variables for Rosenfeld HS functionals:\n");
           printf("Note that vector terms are strictly zero in the bulk!\n");
           printf("\t i  Rhobar_b[i]  Rhobar_b_LBB[i]  Rhobar_b_RTF[i]\n");
           for (i=0;i<4;i++) printf("\t %d \t %9.6f \t %9.6f \t %9.6f\n", i,
                 Rhobar_b[i], Rhobar_b_LBB[i], Rhobar_b_RTF[i]);
        }
  }
  return;
}
/*********************************************************************************************/
void sum_rhobar(double rho,int icomp, double *rhobar)
{
   double vol,area;
   int idim;

   vol = PI*Sigma_ff[icomp][icomp]*
           Sigma_ff[icomp][icomp]*Sigma_ff[icomp][icomp]/6.0;
   area = PI*Sigma_ff[icomp][icomp]*Sigma_ff[icomp][icomp];

   rhobar[0] += Fac_overlap_hs[icomp]*vol*rho;
   rhobar[1] += Fac_overlap_hs[icomp]*area*rho;
   rhobar[2] += Fac_overlap_hs[icomp]*area*rho*Inv_4pir[icomp];
   rhobar[3] += Fac_overlap_hs[icomp]*area*rho*Inv_4pirsq[icomp];
   for (idim=0; idim<Ndim; idim++){
       rhobar[4+idim] = 0.0;
       rhobar[4+Ndim+idim] = 0.0;
   }
   return;
}
/*************************************************************************
dp_drho_hs: the derivative of the hard sphere pressure with respect to rho*/
double dp_drho_hs(double *rho)
{
   int icomp;
   double Hs_diam[NCOMP_MAX],hs_diam_cubed,pi6;
   double xsi0,xsi1,xsi2,xsi3,y1,y2,y3,dy1_drho,dy2_drho,dy3_drho;
   double dp_drho;

   xsi0 = xsi1 = xsi2 = xsi3 = 0.0;
   pi6 = PI/6.0;                 /* shorthand  for pi/6                 */

   for (icomp=0; icomp<Ncomp; ++icomp) Hs_diam[icomp] = 1.0;  

   /*  calculate the constants xsi and introduce some shorthand */

   for (icomp=0; icomp<Ncomp; ++icomp) {
      hs_diam_cubed = POW_DOUBLE_INT(Hs_diam[icomp],3);
      xsi0 +=pi6 * rho[icomp] * hs_diam_cubed;
      xsi1 +=pi6 * rho[icomp] * hs_diam_cubed * Sigma_ff[icomp][icomp];
      xsi2 +=pi6 * rho[icomp] * hs_diam_cubed 
                 * POW_DOUBLE_INT(Sigma_ff[icomp][icomp],2);
      xsi3 +=pi6 * rho[icomp] * hs_diam_cubed 
                 * POW_DOUBLE_INT(Sigma_ff[icomp][icomp],3);
   }
   y1 = 1.0 - xsi3;
   y2 = y1 * y1;
   y3 = y1 * y1 * y1;

   dy1_drho = xsi3/rho[0];
   dy2_drho = 2*y1*dy1_drho;
   dy3_drho = 3*y1*y1*dy1_drho;

   dp_drho = (1.0/pi6) * (  xsi0/(rho[0]*y1) - xsi0*dy1_drho/(y1*y1) +
                           (3.0*xsi1*xsi2/y2)*( 2.0/rho[0] - dy2_drho/y2) +
                           (3.0*xsi2*xsi2*xsi2/y3) *(3.0/(rho[0]) - dy3_drho/y3) );
   return (dp_drho);
}
/*************************************************************************
dmu_drho_hs: the derivative of the hard sphere chemical potential 
             with respect to rho*/
double dmu_drho_hs(double *rho)
{
   int icomp;
   double Hs_diam[NCOMP_MAX],hs_diam_cubed,pi6;
   double xsi0,xsi1,xsi2,xsi3,y1,y2,y3,dy1_drho,dy2_drho,dy3_drho;
   double dmu_drho;

   xsi0 = xsi1 = xsi2 = xsi3 = 0.0;
   pi6 = PI/6.0;                 /* shorthand  for pi/6                 */

   for (icomp=0; icomp<Ncomp; ++icomp) Hs_diam[icomp] = 1.0;  

   /*  calculate the constants xsi and introduce some shorthand */

   for (icomp=0; icomp<Ncomp; ++icomp) {
      hs_diam_cubed = POW_DOUBLE_INT(Hs_diam[icomp],3);
      xsi0 +=pi6 * rho[icomp] * hs_diam_cubed;
      xsi1 +=pi6 * rho[icomp] * hs_diam_cubed * Sigma_ff[icomp][icomp];
      xsi2 +=pi6 * rho[icomp] * hs_diam_cubed 
                 * POW_DOUBLE_INT(Sigma_ff[icomp][icomp],2);
      xsi3 +=pi6 * rho[icomp] * hs_diam_cubed 
                 * POW_DOUBLE_INT(Sigma_ff[icomp][icomp],3);
   }
   y1 = 1.0 - xsi3;
   y2 = y1 * y1;
   y3 = y1 * y1 * y1;

   dy1_drho = xsi3/rho[0];
   dy2_drho = 2*y1*dy1_drho;
   dy3_drho = 3*y1*y1*dy1_drho;

   dmu_drho = - dy1_drho/y1 + 
        pi6 * dp_drho_hs(rho) * POW_DOUBLE_INT(Sigma_ff[0][0],3) +
       (3.0 * xsi2 * Sigma_ff[0][0]/y1)
                                 *( 1.0/rho[0] - dy1_drho/y1) +
       (3.0 * xsi1 * POW_DOUBLE_INT(Sigma_ff[0][0],2)/y1)
                                 *( 1.0/rho[0] - dy1_drho/y1) +
       (9.0 * POW_DOUBLE_INT((xsi2 * Sigma_ff[0][0]),2)/y2)
                                 *( 1.0/rho[0] - 0.5*dy2_drho/y2) +
       (1.0/rho[0]);

   return(dmu_drho);
}
/*************************************************************************/