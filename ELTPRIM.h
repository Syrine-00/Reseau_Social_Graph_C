#ifndef ELTPRIM_H_INCLUDED
#define ELTPRIM_H_INCLUDED


//primitives du TDA ELEMENT
ELEMENT elementLire();
void elementAfficher(ELEMENT *);
void elementAffecter(ELEMENT*, ELEMENT);
void elementCopier(ELEMENT*, ELEMENT);
void elementComparer(ELEMENT, ELEMENT);
ELEMENT elementCreer(void);
void elementDetruire(ELEMENT);



#endif // ELTPRIM_H_INCLUDED
