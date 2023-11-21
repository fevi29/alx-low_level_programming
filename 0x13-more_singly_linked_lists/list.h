
#ifndef _CB_LIST_H_
#define _CB_LIST_H_
#include<stddef.h>
/*
 * reference : linux2.6 include/linux/list.h
 * reference : http://adrianhuang.blogspot.com/2007/10/linux-kernel-listhead.html
 */

typedef struct cb_list
{
    struct cb_list *next,*prev;
}cb_list;
   
#define cb_list_head(_l) {&(_l),&(_l)}

static inline cb_list_init(cb_list *list)
{
    list->next = list;
    list->prev = list;
}

static inline void cb_list_add_(cb_list *n,cb_list *prev,cb_list *next)
{
    next->prev = n;
    n->next = next;
    n->prev = prev;
    prev->next = n;
}

static inline void cb_list_insert(cb_list *list,cb_list *node)
{
    cb_list_add_(node,list->prev,list);
}

static inline void cb_list_add(cb_list *list,cb_list *node)
{
    cb_list_add_(node,list,list->next);
}

static inline void cb_list_catnode(cb_list *prev,cb_list *next)
{
    prev->next = next;
    next->prev = prev;
}

static inline void cb_list_del(cb_list *node)
{
    cb_list_catnode(node->prev,node->next);
}

#define cb_list_entry(_p,_t,_m) ((_t*)((char*)(_p)-(unsigned long)(&((_t*)0)->_m)))

#define cb_list_push(_head,_node) cb_list_insert((_head).next,_node)
#define cb_list_append(_head,_node) cb_list_insert(&(_head),_node)
#define cb_list_isempty(_head) (&(_head) == _head.next)
#define cb_list_islast(_head,_node) ((_node)->next == (_head))
cb_list* cb_list_pop(cb_list head);
#define cb_list_popt(_head,_t,_m) cb_list_entry(cb_list_pop(_head),_t,_m)

#define cb_list_foreach(_head,_p) for(_p=(_head).next;_p!=&(_head);_p=_p->next)
#define cb_list_rforeach(_head,_p) for(_p=(_head).prev;_p!=&(_head);_p=_p->prev)

#define cb_list_foreachs(_head,_p,_n) for(_p=(_head).next,_n=_p->next;\
                                          _p!=&(_head);\
                                          _p=_n,_n=_p->next)
#define cb_list_rforeachs(_head,_p,_n) for(_p=(_head).prev,_n=_p->prev;\
                                           _p!=&(_head);\
                                           _p=_n,_n=_p->prev)

#define cb_list_eforeach(_head,_p,_m) for(_p=cb_list_entry((_head).next,typeof(*_p),_m);\
                                          &_p->_m!=&(_head);\
                                          _p=cb_list_entry(_p->_m.next,typeof(*_p),_m))

#define cb_list_erforeach(_head,_p,_m) for(_p=cb_list_entry((_head).prev,typeof(*_p),_m);\
                                          &_p->_m!=&(_head);\
                                          _p=cb_list_entry(_p->_m.prev,typeof(*_p),_m))

void cb_list_catlist(cb_list *p,cb_list *n);
void cb_list_cutlist(cb_list *p,cb_list *n,cb_list *nhead);

void cb_list_rrotate(cb_list *p);
void cb_list_lrotate(cb_list *p);
#endif
