//sudo ln /Applications/Pd-0.55-0.app/Contents/Resources/src/m_pd.h m_pd.h
//snad je to ok udelat takhle no

#include <m_pd.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <stdio.h>


#define MATRIX_SIZE 7
#define TRANSM_SIZE (MATRIX_SIZE * MATRIX_SIZE * 3)
#define ZVUKAR 0.707106781187 //use if you dont want to sqrt number 2 or divide by 2, works better maybe

#define INS_OFF 2
#define OUTS_OFF (INS_OFF + MATRIX_SIZE)


static t_class *simple_matrix_tilde_class;

typedef struct _simple_matrix_tilde
{
  t_object x_obj;

  int val, posx, posy;

  int m_state[MATRIX_SIZE][MATRIX_SIZE];

  t_inlet *sym_in_on;
  t_symbol *sgo;

  t_inlet *ins[MATRIX_SIZE - 1];
  t_outlet *outs[MATRIX_SIZE];

  t_float some;

} t_simple_matrix_tilde;


void simple_matrix_tilde_oscin(t_simple_matrix_tilde *x, t_symbol *s)
{
  //int k;
  //int l;
  
  
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

  //if(s->s_name[0] == 'c') memset((void *)x->m_state, 0, sizeof(x->m_state)); return; //:)
  
  x->val = s->s_name[0] - '0';
  x->posx = s->s_name[1] - '0';
  x->posy = s->s_name[2] - '0';
  
  x->m_state[x->posy][x->posx] = x->val;

  for(int g = 0; g < MATRIX_SIZE; g++)
  {
    for(int h = 0; h < MATRIX_SIZE; h++)
    {
      if(h == 6) printf("%d\n", x->m_state[g][h]); else printf("%d", x->m_state[g][h]);
    }
  }
  printf("\n\n");
}

t_int *simple_matrix_tilde_perform(t_int *w)
{
  int xx,yy,o,k;


  t_simple_matrix_tilde *x = (t_simple_matrix_tilde *)(w[1]); //sorry for variable naming
  t_float *out;
  t_float *inu; //in

  int len = (int)(w[16]);
  //2-8 9-15
  
  for(xx = 0; xx < MATRIX_SIZE; xx++)
  {
    out = (t_float *)(w[OUTS_OFF + xx]);
    memset(out, 0, sizeof(t_float) * len);
    
    out = (t_float *)(w[OUTS_OFF + xx]);
    for(yy = 0; yy < MATRIX_SIZE; yy++)
    {
      inu = (t_float *)(w[INS_OFF + yy]);
      for(o = 0; o < len; o++)
      {
        out[o] += (inu[o] * (1/sqrtf(2.0))) * (t_float)x->m_state[yy][xx];
      }
    }
  }

  return (w+17);
}


void simple_matrix_tilde_dsp(t_simple_matrix_tilde *x, t_signal **sp)
{

  dsp_add(simple_matrix_tilde_perform, 16, 
    x, 
    sp[0]->s_vec, //in 
    sp[1]->s_vec, 
    sp[2]->s_vec, 
    sp[3]->s_vec, 
    sp[4]->s_vec, 
    sp[5]->s_vec,  
    sp[6]->s_vec, 
    sp[7]->s_vec, //out
    sp[8]->s_vec, 
    sp[9]->s_vec, 
    sp[10]->s_vec, 
    sp[11]->s_vec, 
    sp[12]->s_vec, 
    sp[13]->s_vec, 
    sp[0]->s_n); 
    //ummm
    //
}


void *simple_matrix_tilde_new(/*t_symbol *s, int argc, t_atom *argv*/)
{
  int j;

  t_simple_matrix_tilde *x = (t_simple_matrix_tilde *)pd_new(simple_matrix_tilde_class);
  //memset((void *)x->m_state, 0, sizeof(x->m_state));
  memset(x->m_state, 0, sizeof(x->m_state));

  //wall,
  //wall,
  for(j = 0; j < (MATRIX_SIZE - 1); j++) //i think the -1 is caused by MAINSIGNALIN
  {
    x->ins[j] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  }

  for(j = 0; j < MATRIX_SIZE; j++)
  {
    x->outs[j] = outlet_new(&x->x_obj, &s_signal);
  }
  
  x->sym_in_on = inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("symbol"), gensym("oscin"));

  return (void *) x;
}

void simple_matrix_tilde_freedom(t_simple_matrix_tilde *x)
{
  int j;

  inlet_free(x->sym_in_on);

  for(j = 0; j < MATRIX_SIZE; j++) { outlet_free(x->outs[j]); }
  for(j = 0; j < (MATRIX_SIZE - 1); j++) { inlet_free(x->ins[j]); }
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