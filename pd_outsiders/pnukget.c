#include <m_pd.h>

#define PNUKU_TOLIK_JEST 3

static t_class *pnukget_class;

typedef struct _pnukget
{
    t_object x_obj;
    
    t_outlet *v_out[PNUKU_TOLIK_JEST];
    
    t_float pos_x, pos_y;
} t_pnukget;

void pnukget_list(t_pnukget *x, t_symbol *s, int argc, t_atom *argv)
{
    //x y id val
    if(atom_getint(argv + 0) == x->pos_x && atom_getint(argv + 1) == x->pos_y)
    {
        outlet_float(x->v_out[atom_getint(argv + 2)], (t_float)atom_getint(argv + 3));
    }
}

void *pnukget_new(t_symbol *s, int argc, t_atom *argv)
{
    int f;
    t_pnukget *x = (t_pnukget *)(pd_new(pnukget_class));

    for(f = 0; f < PNUKU_TOLIK_JEST; f++){ x->v_out[f] = outlet_new(&x->x_obj, &s_float); }

    x->pos_x = atom_getint(argv + 0);
    x->pos_y = atom_getint(argv + 1);

    return (void *)x;
}

void pnukget_free(t_pnukget *x)
{
    int k;
    for(k = 0; k < PNUKU_TOLIK_JEST; k++){ outlet_free(x->v_out[k]); }
}

void pnukget_setup(void)
{
    pnukget_class = class_new(gensym("pnukget"),
        (t_newmethod)pnukget_new,
        (t_method)pnukget_free,
        sizeof(t_pnukget),
        CLASS_DEFAULT,
        A_GIMME,
        0);

    class_addlist(pnukget_class, (t_method)pnukget_list);
}