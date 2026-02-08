#include <m_pd.h>
#include <string.h>

static t_class *changes_class;

typedef struct _changes {
    t_object x_obj;

    t_symbol *rpev;

    t_outlet *sout;
} t_changes;

void changes_symbol(t_changes *x, t_symbol *s)
{
    if (!s || s == &s_){ return; }

    if (x->rpev != s)
    {
        x->rpev = s;
        outlet_symbol(x->sout, s);
        post(s->s_name);
    }
}

void *changes_new()
{
    t_changes *x = (t_changes *)pd_new(changes_class);

    x->sout = outlet_new(&x->x_obj, &s_symbol);

    return (void *)x;
}


void changes_setup(void)
{
    changes_class = class_new(
        gensym("changes"), 
        (t_newmethod)changes_new, 
        0, 
        sizeof(t_changes), 
        CLASS_DEFAULT, 
        0);
    
    class_addsymbol(changes_class, (t_method)changes_symbol);
}