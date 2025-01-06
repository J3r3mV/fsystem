/**
 * Source .c for creating a module for Lua to have system features on file.
 * I will add to this file as my new needs arise, to date:
 * - readdirFile() : Reads file names from the specified directory.
 * Author: J3r3m - https://github.com/J3r3mV
 * Version : 0.9
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <lua5.4/lua.h>
#include <lua5.4/lualib.h>
#include <lua5.4/lauxlib.h>

/**
 * @Description : Holds file names read from a directory.
 * @var pFiles : Array of strings containing file names.
 * @var nbFiles : Number of files in the array.
 */
typedef struct
{
    char **pFiles;
    int nbFiles;
} stFiles;

/**
 * @Description : Frees pointers to structure
 * @var stFile : A struct stFiles
 */
void freeStFile(stFiles stFiles)
{
    for (int i = 0; i < stFiles.nbFiles; i++)
    {
        free(stFiles.pFiles[i]);
    }
    free(stFiles.pFiles);
}

/**
 * @Description Reads file names from the specified directory.
 * This function uses the dirent.h library to read all files in the specified directory.
 * Only regular files are included in the result.
 * @param path : Path to the directory to read.
 * @return : Structure stFiles, containing an array of file names and the number of files.
 */
stFiles readdirFile_c(const char *path)
{
    DIR *pDirectory = opendir(path);

    if (pDirectory == NULL)
    {
        perror("Error ");
        exit(1);
    }

    stFiles stFilesDir;
    stFilesDir.pFiles = NULL;
    stFilesDir.nbFiles = 0;

    struct dirent *pDirectoryEntity = NULL;

    while ((pDirectoryEntity = readdir(pDirectory)) != NULL)
    {
        if (pDirectoryEntity->d_type == 8) // DT_REG = Regular files
        {
            // For each new file, the array is enlarged by a string pointer to place its name there.
            stFilesDir.pFiles = realloc(stFilesDir.pFiles, (stFilesDir.nbFiles + 1) * sizeof(char *));
            stFilesDir.pFiles[stFilesDir.nbFiles] = malloc(strlen(pDirectoryEntity->d_name) + 1);
            strcpy(stFilesDir.pFiles[stFilesDir.nbFiles], pDirectoryEntity->d_name);
            stFilesDir.nbFiles++;
        }
    }

    if (closedir(pDirectory) == -1)
    {
        perror("Error ");
        freeStFile(stFilesDir);
        exit(-1);
    }

    return stFilesDir;
}

/**
 * @Description : Lua function wrapper for readdirFile_c.
 * This function reads the directory path passed from Lua, uses readdirFile_c to get file names,
 * and returns a Lua table containing the names.
 * @param : L Lua state.
 * @return Number of results pushed onto the Lua stack (1 table).
 */
int readdirFile(lua_State *L)
{
    const char *sPath = luaL_checkstring(L, 1);

    stFiles stFilesDir = readdirFile_c(sPath);

    lua_newtable(L);

    // Push each file name onto the stack
    for (int i = 0; i < stFilesDir.nbFiles; i++)
    {
        lua_pushstring(L, stFilesDir.pFiles[i]);
        lua_rawseti(L, -2, i + 1);
    }

    freeStFile(stFilesDir);

    return 1;
}

/**
 * @Description : Lua module entry point.
 * Registers the functions provided by this module for use in Lua.
 * The module is opened with `require('fsystem')`.
 * @param L : Lua state.
 * @return : Number of results pushed onto the Lua stack (1 table).
 */
int luaopen_fsystem(lua_State *L)
{
    static const struct luaL_Reg mesFonctions[] = {
        {"readdirFile", readdirFile},
        {NULL, NULL}};

    luaL_newlib(L, mesFonctions);
    return 1;
}
