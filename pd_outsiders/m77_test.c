//sudo ln /Applications/Pd-0.55-0.app/Contents/Resources/src/m_pd.h m_pd.h
//snad je to ok udelat takhle no

#include "m_pd.h" 

static t_class *helloworld_class;

typedef struct _helloworld {
  t_object  x_obj;
} t_helloworld;

void helloworld_bang(t_helloworld *x)
{
  post("Hello world !!");
}

void *helloworld_new(void)
{
  t_helloworld *x = (t_helloworld *)pd_new(helloworld_class);

  return (void *)x;
}

void helloworld_setup(void) {
  helloworld_class = class_new(gensym("helloworld"),
        (t_newmethod)helloworld_new,
        0, sizeof(t_helloworld),
        CLASS_DEFAULT, 0);
  class_addbang(helloworld_class, helloworld_bang);
}
