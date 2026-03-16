#include "m_pd.h"

static t_class *gridlocke_class;

static void *gridlocke_new(void)
{
    t_object *x = (t_object *)pd_new(gridlocke_class);
    return (x);
}

void changes_setup(void);
void mrg_setup(void);
void pnukget_setup(void);
void simple_matrix_tilde_setup(void);

void gridlocke_setup(void)
{
    changes_setup();
    mrg_setup();
    pnukget_setup();
    simple_matrix_tilde_setup();
    
    post(".     interaction library for 77 synthesizer  .");
    post(".        by Porkop Shcovamec 2026             .");
    post(".        report bugs to /dev/null             .");
}