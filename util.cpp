#include <list>
#include <string.h>

using std::list;

bool withinList(list<char *> *l, char *c)
{
    for (list<char *>::const_iterator it = l->begin(); it != l->end(); ++it)
    {
        if (strcmp(*it, c) == 0)
            return true;
    }
    return false;
}

int findWithinList(list<char *> *l, char *c)
{
    int i = 0;
    for (list<char *>::const_iterator it = l->begin(); it != l->end(); ++it)
    {
        if (strcmp(*it, c) == 0)
            return i;
        i++;
    }
    return -1;
}

