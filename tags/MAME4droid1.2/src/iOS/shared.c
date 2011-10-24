#include "shared.h"
#include <stdio.h>

const char* get_resource_path(char* file)
{
  static char resource_path[1024];

  sprintf(resource_path, "/Applications/iMAME4all.app/%s", file);

  return resource_path;
}

const char* get_documents_path(char* file)
{
    static char documents_path[1024];
    sprintf(documents_path, IMAMEBASEPATH "/%s", file);

    return documents_path;
}
