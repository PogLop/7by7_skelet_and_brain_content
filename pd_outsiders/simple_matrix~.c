//sudo ln /Applications/Pd-0.55-0.app/Contents/Resources/src/m_pd.h m_pd.h
//snad je to ok udelat takhle no

#include <m_pd.h>
#include <string.h>
#include <pthread.h>
#include <stdarg.h>


#define MATRIX_SIZE 7
#define TRANSM_SIZE (MATRIX_SIZE * MATRIX_SIZE * 3)


static t_class *simple_matrix_tilde_class;

typedef struct _simple_matrix_tilde
{
  t_object x_obj;

  t_float some;

  int frame;

  int val;
  int posx;
  int posy;

  char recv[TRANSM_SIZE];

  volatile unsigned int m_state[MATRIX_SIZE][MATRIX_SIZE];
  //t_float stat;

  t_inlet *sym_in_on;
  t_symbol *sgo;

  pthread_mutex_t mutex;

  t_inlet *sig_one_in, *sig_two_in, *sig_tri_in, *sig_qud_in, *sig_fiv_in, *sig_six_in, *sig_sev_in; 
  t_outlet *sig_one_out, *sig_two_out, *sig_tri_out, *sig_qud_out, *sig_fiv_out, *sig_six_out, *sig_sev_out;

} t_simple_matrix_tilde;


void simple_matrix_tilde_oscin(t_simple_matrix_tilde *x, t_symbol *s)
{
  int k;
  int l;
  
  
  //memcpy(x->recv, s->s_name, TRANSM_SIZE); //null terminated, takze 3
  //sometimes the size is for some reason larger, maybe UDP? crazy guy
  //snad to nevybouchne
  /*
  for(l = 0; l < MATRIX_SIZE; l++)
  {
    for(k = 0; k < MATRIX_SIZE; k++)
    {
      x->val = x->recv[(l * MATRIX_SIZE) + k + 0] - '0';
      x->posx = x->recv[(l * MATRIX_SIZE) + k + 1] - '0';
      x->posy = x->recv[(l * MATRIX_SIZE) + k + 2] - '0';
      
      x->m_state[x->posx][x->posy] = x->val;
    }
  } 
  */
  
  x->val = s->s_name[0] - '0';
  x->posx = s->s_name[1] - '0';
  x->posy = s->s_name[2] - '0';
  
  x->m_state[x->posx][x->posy] = x->val;
  
}

t_int *simple_matrix_tilde_perform(t_int *w)
{
  t_simple_matrix_tilde *x =  (t_simple_matrix_tilde *)(w[1]);
  t_sample *sig_in =          (t_sample *)(w[2]);
  t_sample *sig_out =         (t_sample *)(w[3]);
  int len =                   (int)(w[4]); //lenght of sample

  for(int u = 0; u < len; u++)
  {
    *sig_out++ = (*sig_in++) * (t_sample)x->m_state[0][0];
  }

  return (w+5);
}

void simple_matrix_tilde_dsp(t_simple_matrix_tilde *x, t_signal **sp)
{
  dsp_add(simple_matrix_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void *simple_matrix_tilde_new(t_symbol *s, int argc, t_atom *argv, t_floatarg some)
{
  t_simple_matrix_tilde *x = (t_simple_matrix_tilde *)pd_new(simple_matrix_tilde_class);

  //pthread_mutex_init(&x->mutex, NULL); no more mutex
  
  x->sym_in_on = inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("symbol"), gensym("oscin"));
  //x->sym_in_on = symbolinlet_new(&x->x_obj, &x->sgo);
  
  //wall,
  //wall,
  //x->sig_one_in = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  //x->sig_two_in = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  //x->sig_tri_in = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  //x->sig_qud_in = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  //x->sig_fiv_in = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  //x->sig_six_in = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  //x->sig_sev_in = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  
  x->sig_one_out = outlet_new(&x->x_obj, &s_signal);
  //x->sig_two_out = outlet_new(&x->x_obj, &s_signal);
  //x->sig_tri_out = outlet_new(&x->x_obj, &s_signal);
  //x->sig_qud_out = outlet_new(&x->x_obj, &s_signal);
  //x->sig_fiv_out = outlet_new(&x->x_obj, &s_signal);
  //x->sig_six_out = outlet_new(&x->x_obj, &s_signal);
  //x->sig_sev_out = outlet_new(&x->x_obj, &s_signal);
  
  //memset(x->m_state, 0, sizeof(x->m_state) * MATRIX_SIZE * MATRIX_SIZE);
  memset(x->m_state, 0, sizeof(x->m_state));
  
  for(int a = 0; a < 7; a++)
  {
    for(int b = 0; b < 7; b++)
    {
      post("%d", x->m_state[a][b]);
    }
  }

  //post("size %d", sizeof(*x));

  return (void *) x;
}

void simple_matrix_tilde_freedom(t_simple_matrix_tilde *x)
{
  inlet_free(x->sym_in_on);

  //inlet_free(x->sig_one_in);
  //inlet_free(x->sig_two_in);
  //inlet_free(x->sig_tri_in);
  //inlet_free(x->sig_qud_in);
  //inlet_free(x->sig_fiv_in);
  //inlet_free(x->sig_six_in);
  //inlet_free(x->sig_sev_in);

  outlet_free(x->sig_one_out);
  //outlet_free(x->sig_two_out);
  //outlet_free(x->sig_tri_out);
  //outlet_free(x->sig_qud_out);
  //outlet_free(x->sig_fiv_out);
  //outlet_free(x->sig_six_out);
  //outlet_free(x->sig_sev_out);
}

void simple_matrix_tilde_setup(void)
{
  simple_matrix_tilde_class = class_new(
    gensym("simple_matrix~"),
    (t_newmethod)simple_matrix_tilde_new,
    (t_method)simple_matrix_tilde_freedom,
    sizeof(t_simple_matrix_tilde),
    CLASS_DEFAULT,
    0
  );

  class_addmethod(simple_matrix_tilde_class, (t_method)simple_matrix_tilde_oscin, gensym("oscin"), A_DEFSYMBOL, 0);
  
  class_addmethod(simple_matrix_tilde_class, (t_method)simple_matrix_tilde_dsp, gensym("dsp"), A_CANT, 0);
  CLASS_MAINSIGNALIN(simple_matrix_tilde_class, t_simple_matrix_tilde, some);
  
}