//sudo ln /Applications/Pd-0.55-0.app/Contents/Resources/src/m_pd.h m_pd.h
//snad je to ok udelat takhle no

#include <m_pd.h>
#include <string.h>
//#include <stdarg.h>
#include <math.h>
#include <stdio.h>


#define MATRIX_SIZE 7
#define ZVUKAR 0.707106781187 //use if you dont want to sqrt number 2 or divide by 2, works better maybe
//whatever

static t_class *simple_matrix_tilde_class;

typedef struct _simple_matrix_tilde
{
  t_object x_obj;

  int m_state[MATRIX_SIZE][MATRIX_SIZE];
  int x_n;

  t_inlet *mx_list_in;

  t_float some, **ins_v, **outs_v, *ins_cp;

} t_simple_matrix_tilde;


static void simple_matrix_tilde_fudin(t_simple_matrix_tilde *x, t_symbol *s, int argc, t_atom *argv)
{
  int g, *_m_s = (int *)x->m_state; //decay into 1d array :o) decay!!!

  if(argc > (MATRIX_SIZE * MATRIX_SIZE)) 
  { 
    pd_error(x->x_obj.ob_pd, "matrix data too large %d (expected  %d or <)", argc, (MATRIX_SIZE * MATRIX_SIZE));
    return; 
  }

  for(g = 0; g < argc; g++)
  {
    _m_s[g] = atom_getint(argv + g);
  }
}


static t_int *simple_matrix_tilde_perform(t_int *w)
{
  int j, o, i, mul;
  t_simple_matrix_tilde *x = (t_simple_matrix_tilde *)(w[1]);
  t_float *ins = x->ins_cp;

  for(i = 0; i < MATRIX_SIZE; i++)
  {
    for(j = 0; j < x->x_n; j++)
      ins[i * x->x_n + j] = x->ins_v[i][j];
  }

  for(i = 0; i < MATRIX_SIZE; i++)
  { 
    for(j = 0; j < x->x_n; j++)
      x->outs_v[i][j] = 0;
  }
  

  for(i = 0; i < MATRIX_SIZE; i++)
  {
    for(j = 0; j < MATRIX_SIZE; j++)
    {
      for(o = 0; o < x->x_n; o++) //mix samples together, one by one
      {
        //trosku zbytecny, ale co kdyby nekdo do matrixu infiltroval velky cislo? hmmm? 
        //ma to hloubku clovece!
        mul = x->m_state[i][j] ? 1 : 0; 
        x->outs_v[j][o] += ins[i * x->x_n + o] * mul * ZVUKAR;
      }
    }
  }

  return (w + 2);
}


static void simple_matrix_tilde_dsp(t_simple_matrix_tilde *x, t_signal **sp)
{
  int i, n = sp[0]->s_n;
  t_signal **sig_p = sp;

  for(i = 0; i < MATRIX_SIZE; i++) //ins
  {
    *(x->ins_v+i) = (*sig_p++)->s_vec;
  }
  
  for(i = 0; i < MATRIX_SIZE; i++) //outs
  {
    *(x->outs_v+i) = (*sig_p++)->s_vec;
  }

  if(n != x->x_n)
  {
    x->ins_cp = (t_float *)resizebytes(x->ins_cp, x->x_n * MATRIX_SIZE * sizeof(t_float), 
    n * MATRIX_SIZE * sizeof(t_float));

    x->x_n = n;
  }

  dsp_add(simple_matrix_tilde_perform, 1, x);
}


static void *simple_matrix_tilde_new(/*t_symbol *s, int argc, t_atom *argv*/)
{
  int j;
  t_simple_matrix_tilde *x = (t_simple_matrix_tilde *)pd_new(simple_matrix_tilde_class);
  x->x_n = sys_getblksize();

  x->ins_v = (t_float **)getbytes(MATRIX_SIZE * sizeof(t_float *));
  x->outs_v = (t_float **)getbytes(MATRIX_SIZE * sizeof(t_float *));
  x->ins_cp = (t_float *)getbytes(MATRIX_SIZE * x->x_n * sizeof(t_float));
  
  memset(x->m_state, 0, sizeof(x->m_state));

  for(j = 0; j < (MATRIX_SIZE - 1); j++) //the -1 is caused by MAINSIGNALIN
  {
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  }

  for(j = 0; j < MATRIX_SIZE; j++)
  {
    outlet_new(&x->x_obj, &s_signal);
  }
  
  x->mx_list_in = inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("list"), gensym("fudin"));

  return (void *)x;
}


static void simple_matrix_tilde_freedom(t_simple_matrix_tilde *x)
{
  inlet_free(x->mx_list_in);

  freebytes(x->ins_v, MATRIX_SIZE * sizeof(t_float *));
  freebytes(x->outs_v, MATRIX_SIZE * sizeof(t_float *));
  freebytes(x->ins_cp, MATRIX_SIZE * x->x_n * sizeof(t_float *));

  return;
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

  
  class_addmethod(simple_matrix_tilde_class, (t_method)simple_matrix_tilde_fudin, gensym("fudin"), A_GIMME, 0); 
  class_addmethod(simple_matrix_tilde_class, (t_method)simple_matrix_tilde_dsp, gensym("dsp"), A_CANT, 0);
  CLASS_MAINSIGNALIN(simple_matrix_tilde_class, t_simple_matrix_tilde, some);
}