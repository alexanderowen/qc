/* Author: Alexander Owen
 *
 * Small utility functions
 *
 * */
#ifndef UTIL_H
#define UTIL_H

#include <list>

using std::list;

/* Is 'c' within the list 'l'?  */
bool withinList(list<char *> *l, char *c);

/* If 'c' is within the list 'l', return the index */
int findWithinList(list<char *> *l, char *c);

#endif
