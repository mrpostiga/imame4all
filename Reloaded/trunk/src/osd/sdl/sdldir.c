//============================================================
//
//  sdldir.c - SDL core directory access functions
//
//  Copyright (c) 1996-2007, Nicola Salmoria and the MAME Team.
//  Visit http://mamedev.org for licensing and usage restrictions.
//
//  SDLMAME by Olivier Galibert and R. Belmont
//
//============================================================
#include "osdcore.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define PATHSEPCH '/'

struct _osd_directory
{
	osd_directory_entry ent;
	struct dirent *data;
	DIR *fd;
};

static osd_dir_entry_type get_attributes_stat(const char *file)
{
	struct stat st;
	if(stat(file, &st))
		return 0;

	if (S_ISDIR(st.st_mode)) return ENTTYPE_DIR;

	return ENTTYPE_FILE;
}

static UINT64 osd_get_file_size(const char *file)
{
	struct stat st;
	if(stat(file, &st))
		return 0;

	return st.st_size;
}

//============================================================
//  osd_opendir
//============================================================

osd_directory *osd_opendir(const char *dirname)
{
	osd_directory *dir = NULL;
	char *tmpstr, *envstr;
	int i, j;

	dir = malloc(sizeof(osd_directory));
	if (dir)
	{
		memset(dir, 0, sizeof(osd_directory));
		dir->fd = NULL;
	}

	tmpstr = malloc(strlen(dirname)+1);
	strcpy(tmpstr, dirname);

	if (tmpstr[0] == '$')
	{
		char *envval;
		envstr = malloc(strlen(tmpstr)+1); 

		strcpy(envstr, tmpstr);

		i = 0;
		while (envstr[i] != PATHSEPCH && envstr[i] != 0 && envstr[i] != '.')
		{
			i++;
		}

		envstr[i] = '\0';

		envval = getenv(&envstr[1]);
		if (envval != NULL)
		{
			j = strlen(envval) + strlen(tmpstr) + 1;
			free(tmpstr);
			tmpstr = malloc(j);
	
			// start with the value of $HOME
			strcpy(tmpstr, envval);
			// replace the null with a path separator again
			envstr[i] = PATHSEPCH;
			// append it
			strcat(tmpstr, &envstr[i]);
		}
		else
			fprintf(stderr, "Warning: osd_opendir environment variable %s not found.\n", envstr);
		free(envstr);
	}

	dir->fd = opendir(tmpstr);

	if (dir && (dir->fd == NULL))
	{
		free(dir);
		dir = NULL;
	}

	if (tmpstr)
	  free(tmpstr);
	return dir;
}


//============================================================
//  osd_readdir
//============================================================

const osd_directory_entry *osd_readdir(osd_directory *dir)
{
	dir->data = readdir(dir->fd);

	if (dir->data == NULL)
		return NULL;

	dir->ent.name = dir->data->d_name;
	dir->ent.type = get_attributes_stat(dir->data->d_name);
	dir->ent.size = osd_get_file_size(dir->data->d_name);
	return &dir->ent;
}


//============================================================
//  osd_closedir
//============================================================

void osd_closedir(osd_directory *dir)
{
	if (dir->fd != NULL)
		closedir(dir->fd);
	free(dir);
}


//============================================================
//  osd_is_absolute_path
//============================================================

int osd_is_absolute_path(const char *path)
{
        int result;

        if ((path[0] == '/') || (path[0] == '\\'))
                result = TRUE;
        else if (path[0] == '.')
                result = TRUE;
        else
                result = FALSE;
        return result;
}


