#ifndef CROUTER_LIBRARY_H
#define CROUTER_LIBRARY_H

// Structs
typedef struct RegisteredRoute_
{
     char *path;
     char *handler_name;
     struct RegisteredRoute_ *next;
} RegisteredRoute;

typedef struct CRouter_
{
     char *request_path;
     struct RegisterdRoute *routes;
} CRouter;

// Functions
void crouter(void);

/**
 * The caller has the responsibility to deallocate all memory unless NULL is returned.
 * @param path
 * @param handler_name
 * @return
 */
RegisteredRoute *registered_routes_init(const char *path, const char *handler_name);

/**
 *
 * @param r
 * @param path
 * @param handler_name
 * @return
 */
int registered_routes_insert(RegisteredRoute *const r, const char *path, const char *handler_name);


#endif // CROUTER_LIBRARY_H
