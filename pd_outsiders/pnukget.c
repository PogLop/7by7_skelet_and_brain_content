#include <m_pd.h>


#define PNUKU_TOLIK_JEST 3
#define MATRIX_SIZE 7

static t_class *pnukget_class;

typedef struct _pnukget
{
    t_object x_obj;
    t_outlet *v_out[PNUKU_TOLIK_JEST];
    //int m_data[MATRIX_SIZE][MATRIX_SIZE][PNUKU_TOLIK_JEST];
    t_float pos_x, pos_y;
} t_pnukget;

void pnukget_symbol(t_pnukget *x, t_symbol *s)
{
    post("%f, %f", x->pos_x, x->pos_y);
}

void *pnukget_new(t_floatarg px, t_floatarg py)
{
    int s;
    t_pnukget *x = (t_pnukget *)(pd_new(pnukget_class));

    for(s = 0; s < PNUKU_TOLIK_JEST; s++){ x->v_out[s] = outlet_new(&x->x_obj, &s_float); }

    x->pos_x = px;
    x->pos_y = py;

    return (void *)x;
}

void pnukget_setup(void)
{
    pnukget_class = class_new(gensym("pnukget"),
        (t_newmethod)pnukget_new,
        0,
        sizeof(t_pnukget),
        CLASS_DEFAULT,
        A_FLOAT,
        A_FLOAT,
        0);

    class_addsymbol(pnukget_class, (t_method)pnukget_symbol);
}