#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crouter.h"
#include "common.h"

void crouter(void) {
   printf("Parsing route...\n");
   RegisteredRoute *single_route = registered_routes_init("/", "home");
   int err = registered_routes_insert(single_route, "/blogs", "blog_handler");

   if (err != REGISTERED_ROUTER_ALLOCATION_ERROR)
      printf("Successfully stored route\n");

   free(single_route->next->path);
   free(single_route->next->handler_name);
   free(single_route->path);
   free(single_route->handler_name);
   free(single_route);
}

RegisteredRoute *registered_routes_init(const char *path, const char *handler_name)
{
   RegisteredRoute *r = NULL;
   r = malloc(sizeof(RegisteredRoute));
   if (r == NULL)
      return NULL;
   r->path = NULL;
   r->path = malloc(sizeof(char) * PATH_SIZE);
   if (r->path == NULL)
   {
      free(r);
      return NULL;
   }
   strcpy(r->path, path);
   r->handler_name = NULL;
   r->handler_name = malloc(sizeof(char) * HANDLER_NAME_SIZE);
   if (r->handler_name == NULL)
   {
      free(r->path);
      free(r);
      return NULL;
   }
   strcpy(r->handler_name, handler_name);
   return r;
}


int registered_routes_insert(RegisteredRoute *const r, const char *path, const char *handler_name)
{
   RegisteredRoute *temp_r = r;
   while (temp_r->next != NULL)
   {
      temp_r = temp_r->next;
   }
   temp_r->next = NULL;
   temp_r->next = malloc(sizeof(RegisteredRoute));
   if (temp_r->next == NULL)
      return REGISTERED_ROUTER_ALLOCATION_ERROR;
   temp_r->path = NULL;
   temp_r->path = malloc(sizeof(char) * PATH_SIZE);
   if (temp_r->path == NULL)
      return REGISTERED_ROUTER_ALLOCATION_ERROR;
   temp_r->handler_name = NULL;
   temp_r->handler_name = malloc(sizeof(char) * HANDLER_NAME_SIZE);
   if (temp_r->handler_name == NULL)
      return REGISTERED_ROUTER_ALLOCATION_ERROR;
   temp_r->next = NULL;
   return 0;
}
