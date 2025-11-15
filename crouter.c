#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crouter.h"
#include "common.h"


// Static definitions
static void get_class_methods(PyObject *handler_class, char *methods[MAX_METHODS]);
static void init_methods(char *methods[MAX_METHODS]);


void crouter(PyObject *py_routes) {
   if (!PyList_Check(py_routes))
      return;

   Py_ssize_t listSize = PyList_Size(py_routes);

   for (Py_ssize_t i = 0; i < listSize; i++)
   {
      const char *methods[MAX_METHODS];
      PyObject *tuple_item = PyList_GetItem(py_routes, i);
      if (!PyTuple_Check(tuple_item))
         return; // TODO think about this...

      Py_ssize_t tuple_size = PyTuple_Size(tuple_item);
      if (tuple_size != 2)
         return; // TODO improve...

      PyObject *path = PyTuple_GetItem(tuple_item, 0);
      PyObject *handlerClass = PyTuple_GetItem(tuple_item, 1);

      if (!PyUnicode_Check(path))
         return; // TODO improve...

      const char *c_path = PyUnicode_AsUTF8(path);

      // handler
      PyObject *name_attr = PyObject_GetAttrString(handlerClass, "__name__");
      const char *handler_class_name = PyUnicode_AsUTF8(name_attr);

      // get handler class methods
      init_methods(methods);
      get_class_methods(handlerClass, methods);

   }
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

static void get_class_methods(PyObject *handler_class, char *methods[MAX_METHODS])
{
   int index = 0;
   if (PyObject_HasAttrString(handler_class, "get"))     methods[index++] = "GET";
   if (PyObject_HasAttrString(handler_class, "post"))    methods[index++] = "POST";
   if (PyObject_HasAttrString(handler_class, "delete"))  methods[index++] = "DELETE";
   if (PyObject_HasAttrString(handler_class, "put"))     methods[index++] = "PUT";
   if (PyObject_HasAttrString(handler_class, "patch"))   methods[index]   = "PATCH";
}



static void init_methods(char *methods[MAX_METHODS])
{
   for (int i = 0; i < MAX_METHODS; i++)
      methods[i] = NULL;
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
