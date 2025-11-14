#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crouter.h"
#include "common.h"

void crouter(PyObject *py_routes) {
   printf("Parsing route...\n");

   RegisteredRoute *single_route = registered_routes_init("/", "home");
   int err = registered_routes_insert(single_route, "/blogs", "blog_handler");

   if (err != REGISTERED_ROUTER_ALLOCATION_ERROR)
      printf("Successfully stored route\n");

   while (single_route->next != NULL)
   {
      if (single_route->next != NULL)
      {
         free(single_route->path);
         free(single_route->handler_name);
         single_route = single_route->next;
      }
   }
   free(single_route);
}

RegisteredRoute *registered_routes_init(const char *path, const char *handler_name)
{
   RegisteredRoute *r = NULL;
   r = malloc(sizeof(RegisteredRoute));
   if (r == NULL)
      return NULL;
   r->next = NULL;
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
      temp_r = temp_r->next;

   RegisteredRoute *newNode = malloc(sizeof(RegisteredRoute));
   if (newNode == NULL)
      return REGISTERED_ROUTER_ALLOCATION_ERROR;

   newNode->path = malloc(sizeof(char) * PATH_SIZE);
   if (newNode->path == NULL)
   {
      free(newNode);
      return REGISTERED_ROUTER_ALLOCATION_ERROR;
   }
   strcpy(newNode->path, path);

   newNode->handler_name = malloc(sizeof(char) * HANDLER_NAME_SIZE);
   if (newNode->handler_name == NULL)
   {
      free(newNode->path);
      free(newNode);
      return REGISTERED_ROUTER_ALLOCATION_ERROR;
   }
   strcpy(newNode->handler_name, handler_name);
   temp_r->next = newNode;
   return 0;
}
