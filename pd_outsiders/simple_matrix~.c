//sudo ln /Applications/Pd-0.55-0.app/Contents/Resources/src/m_pd.h m_pd.h
//snad je to ok udelat takhle no

#include "m_pd.h" 


#define MATRIX_SIZE 7
#define TRANSM_SIZE 3


static t_class *simple_matrix_class;

typedef struct _simple_matrix
{
  t_object x_obj;

  int m_state[MATRIX_SIZE][MATRIX_SIZE]; //stav peč desky

  t_inlet *m_data_in;

  t_float signal_val;

  t_inlet *sig_one_in, *sig_two_in, *sig_tri_in, *sig_qud_in, *sig_fiv_in, *sig_six_in, *sig_sev_in; 
  t_outlet *sig_one_out, *sig_two_out, *sig_tri_out,  *sig_qud_out, *sig_fiv_out, *sig_six_out, *sig_sev_out;
} t_simple_matrix;

void simple_matrix_bang(t_simple_matrix *x)
{
  post("hi from simple matrix %d", 4);
}

void simple_matrix_osc_recv(t_simple_matrix *x)
{
  //aktualizce dat
  //nejak zpracovat a zapsat do m_state
  char recv[TRANSM_SIZE]; //snad to nevybouchne
  int val = recv[0] - '0';
  int posx = recv[1] - '0';
  int posy = recv[2] - '0';

  x->m_state[posx][posy] = val;

  
}

void *simple_matrix_new(void)
{
  t_simple_matrix *x = (t_simple_matrix *)pd_new(simple_matrix_class);

  inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("list"), gensym("bound"));

  signalinlet_new(&x->x_obj, x->signal_val);
  
  x->sig_one_out = outlet_new(&x->x_obj, &s_signal);

  return (void *) x;
}

void simple_matrix_setup(void)
{
  simple_matrix_class = class_new(
    gensym("simple_m~"),
    (t_newmethod)simple_matrix_new,
    0,
    sizeof(t_simple_matrix),
    CLASS_DEFAULT,
    0
  );

  //class_addbang(simple_matrix_class, simple_matrix_bang);
  class_addsymbol(simple_matrix_class, simple_matrix_osc_recv);
}
