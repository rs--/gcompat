#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _FTS FTS;
typedef struct _FTSENT FTSENT;

FTS* fts_open(
    char* const* path_argv,
    int options,
    int (*compar)(const FTSENT**, const FTSENT**))
{
    assert("unhandled" == NULL);
    abort();
    return NULL;
}

int fts_close(FTS* ftsp)
{
    fprintf(stderr, "%s() unhandled\n", __FUNCTION__);
    abort();
    return 0;
}

FTSENT* fts_read(FTS* ftsp)
{
    assert("unhandled" == NULL);
    abort();
    return NULL;
}

int fts_set(FTS* ftsp, FTSENT* f, int options)
{
    assert("unhandled" == NULL);
    abort();
    return 0;
}

FTSENT* fts_children(FTS* ftsp, int options)
{
    assert("unhandled" == NULL);
    abort();
    return NULL;
}