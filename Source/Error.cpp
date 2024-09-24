#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <errno.h>
#include <string.h>
#endif

#include "Source/Macros.h"

extern "C"
{
    EXPORT int GetErrorCode()
    {
#ifdef _WIN32
        return GetLastError();
#else
        return errno;
#endif
    }

    EXPORT int GetSocketErrorCode()
    {
#ifdef _WIN32
        return WSAGetLastError();
#else
        return errno;
#endif
    }

    EXPORT char *GetErrorMessage(int errorCode)
    {
#ifdef _WIN32
        LPSTR buffer = nullptr;

        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer, 0, NULL);

        char* errorMessage = _strdup(buffer);

        LocalFree(buffer);

        return errorMessage;
#else
        return strerror(errorCode);
#endif
    }

    EXPORT bool ShouldDeleteErrorMessage()
    {
#ifdef _WIN32
        return true;
#else
        return false;
#endif
    }

    EXPORT void DeleteErrorMessage(void *pointer)
    {
#ifdef _WIN32
        free(pointer);
#endif
    }
}