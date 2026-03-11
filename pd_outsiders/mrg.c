//ass567890
#include <m_pd.h>

#define MATRIX_SIZE 7

static t_class *mrg_class;

typedef struct _mrg {
    t_object x_obj;
    
    t_inlet *mx_in;
    t_outlet *n_out;

    int selector;
    int step;

    t_float *mx_row;
} t_mrg;

void mrg_matrix(t_mrg *x, t_symbol *s, int argc, t_atom *argv)
{
    int l, offs, ix;

    offs = MATRIX_SIZE * x->selector;

    for(l = 0; l < MATRIX_SIZE; l++)
    {
        ix = offs + l;
        x->mx_row[l] = atom_getfloat(argv + l);
    }
}

void mrg_bang(t_mrg *x)
{   
    if(x->step < MATRIX_SIZE)
    {
        if(x->mx_row[(int)x->step])
        {
            outlet_float(x->n_out, x->mx_row[(int)x->step] * x->step);
        } else 
        { 
            outlet_float(x->n_out, MATRIX_SIZE + 1); 
        }
        x->step++;
    } else 
    {
        x->step = 0;
    }
}

void *mrg_new(t_floatarg f)
{
    int j;
    t_mrg *x = (t_mrg *)pd_new(mrg_class);
    
    x->mx_row = (t_float *)getbytes(MATRIX_SIZE * sizeof(t_float));
    for(j = 0; j < MATRIX_SIZE; j++){ x->mx_row[j] = 0; }

    x->step = 0;
    x->selector = ((int)f < MATRIX_SIZE) ? (int)f : 0;

    x->mx_in = inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("list"), gensym("matrix"));
    x->n_out = outlet_new(&x->x_obj, &s_float);

    return (void *)x;
}

void mrg_free(t_mrg *x)
{
    inlet_free(x->mx_in);
    outlet_free(x->n_out);
    freebytes(x->mx_row, MATRIX_SIZE * sizeof(t_float));
}


void mrg_setup(void)
{
    mrg_class = class_new(
        gensym("mrg"), 
        (t_newmethod)mrg_new, 
        (t_method)mrg_free, 
        sizeof(t_mrg), 
        CLASS_DEFAULT, 
        A_DEFFLOAT,
    0);
    
    class_addbang(mrg_class, (t_method)mrg_bang);
    class_addmethod(mrg_class, (t_method)mrg_matrix, gensym("matrix"), A_GIMME, 0);
}