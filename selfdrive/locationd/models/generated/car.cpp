#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_1402676562040383198) {
   out_1402676562040383198[0] = delta_x[0] + nom_x[0];
   out_1402676562040383198[1] = delta_x[1] + nom_x[1];
   out_1402676562040383198[2] = delta_x[2] + nom_x[2];
   out_1402676562040383198[3] = delta_x[3] + nom_x[3];
   out_1402676562040383198[4] = delta_x[4] + nom_x[4];
   out_1402676562040383198[5] = delta_x[5] + nom_x[5];
   out_1402676562040383198[6] = delta_x[6] + nom_x[6];
   out_1402676562040383198[7] = delta_x[7] + nom_x[7];
   out_1402676562040383198[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1091897287188278870) {
   out_1091897287188278870[0] = -nom_x[0] + true_x[0];
   out_1091897287188278870[1] = -nom_x[1] + true_x[1];
   out_1091897287188278870[2] = -nom_x[2] + true_x[2];
   out_1091897287188278870[3] = -nom_x[3] + true_x[3];
   out_1091897287188278870[4] = -nom_x[4] + true_x[4];
   out_1091897287188278870[5] = -nom_x[5] + true_x[5];
   out_1091897287188278870[6] = -nom_x[6] + true_x[6];
   out_1091897287188278870[7] = -nom_x[7] + true_x[7];
   out_1091897287188278870[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5989277925452116934) {
   out_5989277925452116934[0] = 1.0;
   out_5989277925452116934[1] = 0;
   out_5989277925452116934[2] = 0;
   out_5989277925452116934[3] = 0;
   out_5989277925452116934[4] = 0;
   out_5989277925452116934[5] = 0;
   out_5989277925452116934[6] = 0;
   out_5989277925452116934[7] = 0;
   out_5989277925452116934[8] = 0;
   out_5989277925452116934[9] = 0;
   out_5989277925452116934[10] = 1.0;
   out_5989277925452116934[11] = 0;
   out_5989277925452116934[12] = 0;
   out_5989277925452116934[13] = 0;
   out_5989277925452116934[14] = 0;
   out_5989277925452116934[15] = 0;
   out_5989277925452116934[16] = 0;
   out_5989277925452116934[17] = 0;
   out_5989277925452116934[18] = 0;
   out_5989277925452116934[19] = 0;
   out_5989277925452116934[20] = 1.0;
   out_5989277925452116934[21] = 0;
   out_5989277925452116934[22] = 0;
   out_5989277925452116934[23] = 0;
   out_5989277925452116934[24] = 0;
   out_5989277925452116934[25] = 0;
   out_5989277925452116934[26] = 0;
   out_5989277925452116934[27] = 0;
   out_5989277925452116934[28] = 0;
   out_5989277925452116934[29] = 0;
   out_5989277925452116934[30] = 1.0;
   out_5989277925452116934[31] = 0;
   out_5989277925452116934[32] = 0;
   out_5989277925452116934[33] = 0;
   out_5989277925452116934[34] = 0;
   out_5989277925452116934[35] = 0;
   out_5989277925452116934[36] = 0;
   out_5989277925452116934[37] = 0;
   out_5989277925452116934[38] = 0;
   out_5989277925452116934[39] = 0;
   out_5989277925452116934[40] = 1.0;
   out_5989277925452116934[41] = 0;
   out_5989277925452116934[42] = 0;
   out_5989277925452116934[43] = 0;
   out_5989277925452116934[44] = 0;
   out_5989277925452116934[45] = 0;
   out_5989277925452116934[46] = 0;
   out_5989277925452116934[47] = 0;
   out_5989277925452116934[48] = 0;
   out_5989277925452116934[49] = 0;
   out_5989277925452116934[50] = 1.0;
   out_5989277925452116934[51] = 0;
   out_5989277925452116934[52] = 0;
   out_5989277925452116934[53] = 0;
   out_5989277925452116934[54] = 0;
   out_5989277925452116934[55] = 0;
   out_5989277925452116934[56] = 0;
   out_5989277925452116934[57] = 0;
   out_5989277925452116934[58] = 0;
   out_5989277925452116934[59] = 0;
   out_5989277925452116934[60] = 1.0;
   out_5989277925452116934[61] = 0;
   out_5989277925452116934[62] = 0;
   out_5989277925452116934[63] = 0;
   out_5989277925452116934[64] = 0;
   out_5989277925452116934[65] = 0;
   out_5989277925452116934[66] = 0;
   out_5989277925452116934[67] = 0;
   out_5989277925452116934[68] = 0;
   out_5989277925452116934[69] = 0;
   out_5989277925452116934[70] = 1.0;
   out_5989277925452116934[71] = 0;
   out_5989277925452116934[72] = 0;
   out_5989277925452116934[73] = 0;
   out_5989277925452116934[74] = 0;
   out_5989277925452116934[75] = 0;
   out_5989277925452116934[76] = 0;
   out_5989277925452116934[77] = 0;
   out_5989277925452116934[78] = 0;
   out_5989277925452116934[79] = 0;
   out_5989277925452116934[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5951520236264327024) {
   out_5951520236264327024[0] = state[0];
   out_5951520236264327024[1] = state[1];
   out_5951520236264327024[2] = state[2];
   out_5951520236264327024[3] = state[3];
   out_5951520236264327024[4] = state[4];
   out_5951520236264327024[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5951520236264327024[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5951520236264327024[7] = state[7];
   out_5951520236264327024[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1308759087996720471) {
   out_1308759087996720471[0] = 1;
   out_1308759087996720471[1] = 0;
   out_1308759087996720471[2] = 0;
   out_1308759087996720471[3] = 0;
   out_1308759087996720471[4] = 0;
   out_1308759087996720471[5] = 0;
   out_1308759087996720471[6] = 0;
   out_1308759087996720471[7] = 0;
   out_1308759087996720471[8] = 0;
   out_1308759087996720471[9] = 0;
   out_1308759087996720471[10] = 1;
   out_1308759087996720471[11] = 0;
   out_1308759087996720471[12] = 0;
   out_1308759087996720471[13] = 0;
   out_1308759087996720471[14] = 0;
   out_1308759087996720471[15] = 0;
   out_1308759087996720471[16] = 0;
   out_1308759087996720471[17] = 0;
   out_1308759087996720471[18] = 0;
   out_1308759087996720471[19] = 0;
   out_1308759087996720471[20] = 1;
   out_1308759087996720471[21] = 0;
   out_1308759087996720471[22] = 0;
   out_1308759087996720471[23] = 0;
   out_1308759087996720471[24] = 0;
   out_1308759087996720471[25] = 0;
   out_1308759087996720471[26] = 0;
   out_1308759087996720471[27] = 0;
   out_1308759087996720471[28] = 0;
   out_1308759087996720471[29] = 0;
   out_1308759087996720471[30] = 1;
   out_1308759087996720471[31] = 0;
   out_1308759087996720471[32] = 0;
   out_1308759087996720471[33] = 0;
   out_1308759087996720471[34] = 0;
   out_1308759087996720471[35] = 0;
   out_1308759087996720471[36] = 0;
   out_1308759087996720471[37] = 0;
   out_1308759087996720471[38] = 0;
   out_1308759087996720471[39] = 0;
   out_1308759087996720471[40] = 1;
   out_1308759087996720471[41] = 0;
   out_1308759087996720471[42] = 0;
   out_1308759087996720471[43] = 0;
   out_1308759087996720471[44] = 0;
   out_1308759087996720471[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1308759087996720471[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1308759087996720471[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1308759087996720471[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1308759087996720471[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1308759087996720471[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1308759087996720471[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1308759087996720471[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1308759087996720471[53] = -9.8000000000000007*dt;
   out_1308759087996720471[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1308759087996720471[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1308759087996720471[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1308759087996720471[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1308759087996720471[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1308759087996720471[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1308759087996720471[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1308759087996720471[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1308759087996720471[62] = 0;
   out_1308759087996720471[63] = 0;
   out_1308759087996720471[64] = 0;
   out_1308759087996720471[65] = 0;
   out_1308759087996720471[66] = 0;
   out_1308759087996720471[67] = 0;
   out_1308759087996720471[68] = 0;
   out_1308759087996720471[69] = 0;
   out_1308759087996720471[70] = 1;
   out_1308759087996720471[71] = 0;
   out_1308759087996720471[72] = 0;
   out_1308759087996720471[73] = 0;
   out_1308759087996720471[74] = 0;
   out_1308759087996720471[75] = 0;
   out_1308759087996720471[76] = 0;
   out_1308759087996720471[77] = 0;
   out_1308759087996720471[78] = 0;
   out_1308759087996720471[79] = 0;
   out_1308759087996720471[80] = 1;
}
void h_25(double *state, double *unused, double *out_6923278227618494131) {
   out_6923278227618494131[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2092904441014244631) {
   out_2092904441014244631[0] = 0;
   out_2092904441014244631[1] = 0;
   out_2092904441014244631[2] = 0;
   out_2092904441014244631[3] = 0;
   out_2092904441014244631[4] = 0;
   out_2092904441014244631[5] = 0;
   out_2092904441014244631[6] = 1;
   out_2092904441014244631[7] = 0;
   out_2092904441014244631[8] = 0;
}
void h_24(double *state, double *unused, double *out_2165850182353595939) {
   out_2165850182353595939[0] = state[4];
   out_2165850182353595939[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5650830039816567767) {
   out_5650830039816567767[0] = 0;
   out_5650830039816567767[1] = 0;
   out_5650830039816567767[2] = 0;
   out_5650830039816567767[3] = 0;
   out_5650830039816567767[4] = 1;
   out_5650830039816567767[5] = 0;
   out_5650830039816567767[6] = 0;
   out_5650830039816567767[7] = 0;
   out_5650830039816567767[8] = 0;
   out_5650830039816567767[9] = 0;
   out_5650830039816567767[10] = 0;
   out_5650830039816567767[11] = 0;
   out_5650830039816567767[12] = 0;
   out_5650830039816567767[13] = 0;
   out_5650830039816567767[14] = 1;
   out_5650830039816567767[15] = 0;
   out_5650830039816567767[16] = 0;
   out_5650830039816567767[17] = 0;
}
void h_30(double *state, double *unused, double *out_7886016317837035135) {
   out_7886016317837035135[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4611237399521493258) {
   out_4611237399521493258[0] = 0;
   out_4611237399521493258[1] = 0;
   out_4611237399521493258[2] = 0;
   out_4611237399521493258[3] = 0;
   out_4611237399521493258[4] = 1;
   out_4611237399521493258[5] = 0;
   out_4611237399521493258[6] = 0;
   out_4611237399521493258[7] = 0;
   out_4611237399521493258[8] = 0;
}
void h_26(double *state, double *unused, double *out_6942506464935372700) {
   out_6942506464935372700[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1648598877859811593) {
   out_1648598877859811593[0] = 0;
   out_1648598877859811593[1] = 0;
   out_1648598877859811593[2] = 0;
   out_1648598877859811593[3] = 0;
   out_1648598877859811593[4] = 0;
   out_1648598877859811593[5] = 0;
   out_1648598877859811593[6] = 0;
   out_1648598877859811593[7] = 1;
   out_1648598877859811593[8] = 0;
}
void h_27(double *state, double *unused, double *out_511865206810206682) {
   out_511865206810206682[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2436474087721068347) {
   out_2436474087721068347[0] = 0;
   out_2436474087721068347[1] = 0;
   out_2436474087721068347[2] = 0;
   out_2436474087721068347[3] = 1;
   out_2436474087721068347[4] = 0;
   out_2436474087721068347[5] = 0;
   out_2436474087721068347[6] = 0;
   out_2436474087721068347[7] = 0;
   out_2436474087721068347[8] = 0;
}
void h_29(double *state, double *unused, double *out_236671144525700793) {
   out_236671144525700793[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5121468743835885442) {
   out_5121468743835885442[0] = 0;
   out_5121468743835885442[1] = 1;
   out_5121468743835885442[2] = 0;
   out_5121468743835885442[3] = 0;
   out_5121468743835885442[4] = 0;
   out_5121468743835885442[5] = 0;
   out_5121468743835885442[6] = 0;
   out_5121468743835885442[7] = 0;
   out_5121468743835885442[8] = 0;
}
void h_28(double *state, double *unused, double *out_4489808060850638963) {
   out_4489808060850638963[0] = state[0];
}
void H_28(double *state, double *unused, double *out_39069726766354868) {
   out_39069726766354868[0] = 1;
   out_39069726766354868[1] = 0;
   out_39069726766354868[2] = 0;
   out_39069726766354868[3] = 0;
   out_39069726766354868[4] = 0;
   out_39069726766354868[5] = 0;
   out_39069726766354868[6] = 0;
   out_39069726766354868[7] = 0;
   out_39069726766354868[8] = 0;
}
void h_31(double *state, double *unused, double *out_4062907081842169160) {
   out_4062907081842169160[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2274806980093163069) {
   out_2274806980093163069[0] = 0;
   out_2274806980093163069[1] = 0;
   out_2274806980093163069[2] = 0;
   out_2274806980093163069[3] = 0;
   out_2274806980093163069[4] = 0;
   out_2274806980093163069[5] = 0;
   out_2274806980093163069[6] = 0;
   out_2274806980093163069[7] = 0;
   out_2274806980093163069[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_1402676562040383198) {
  err_fun(nom_x, delta_x, out_1402676562040383198);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1091897287188278870) {
  inv_err_fun(nom_x, true_x, out_1091897287188278870);
}
void car_H_mod_fun(double *state, double *out_5989277925452116934) {
  H_mod_fun(state, out_5989277925452116934);
}
void car_f_fun(double *state, double dt, double *out_5951520236264327024) {
  f_fun(state,  dt, out_5951520236264327024);
}
void car_F_fun(double *state, double dt, double *out_1308759087996720471) {
  F_fun(state,  dt, out_1308759087996720471);
}
void car_h_25(double *state, double *unused, double *out_6923278227618494131) {
  h_25(state, unused, out_6923278227618494131);
}
void car_H_25(double *state, double *unused, double *out_2092904441014244631) {
  H_25(state, unused, out_2092904441014244631);
}
void car_h_24(double *state, double *unused, double *out_2165850182353595939) {
  h_24(state, unused, out_2165850182353595939);
}
void car_H_24(double *state, double *unused, double *out_5650830039816567767) {
  H_24(state, unused, out_5650830039816567767);
}
void car_h_30(double *state, double *unused, double *out_7886016317837035135) {
  h_30(state, unused, out_7886016317837035135);
}
void car_H_30(double *state, double *unused, double *out_4611237399521493258) {
  H_30(state, unused, out_4611237399521493258);
}
void car_h_26(double *state, double *unused, double *out_6942506464935372700) {
  h_26(state, unused, out_6942506464935372700);
}
void car_H_26(double *state, double *unused, double *out_1648598877859811593) {
  H_26(state, unused, out_1648598877859811593);
}
void car_h_27(double *state, double *unused, double *out_511865206810206682) {
  h_27(state, unused, out_511865206810206682);
}
void car_H_27(double *state, double *unused, double *out_2436474087721068347) {
  H_27(state, unused, out_2436474087721068347);
}
void car_h_29(double *state, double *unused, double *out_236671144525700793) {
  h_29(state, unused, out_236671144525700793);
}
void car_H_29(double *state, double *unused, double *out_5121468743835885442) {
  H_29(state, unused, out_5121468743835885442);
}
void car_h_28(double *state, double *unused, double *out_4489808060850638963) {
  h_28(state, unused, out_4489808060850638963);
}
void car_H_28(double *state, double *unused, double *out_39069726766354868) {
  H_28(state, unused, out_39069726766354868);
}
void car_h_31(double *state, double *unused, double *out_4062907081842169160) {
  h_31(state, unused, out_4062907081842169160);
}
void car_H_31(double *state, double *unused, double *out_2274806980093163069) {
  H_31(state, unused, out_2274806980093163069);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_init(car);
