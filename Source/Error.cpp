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
#elif __linux__
        return errno;
#endif
    }

    EXPORT int GetSocketErrorCode()
    {
#ifdef _WIN32
        return WSAGetLastError();
#elif __linux__
        return errno;
#endif
    }

    EXPORT bool TryGetErrorMessage(int errorCode, char **errorMessage)
    {
#ifdef _WIN32
        LPSTR buffer = nullptr;
        DWORD size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer, 0, NULL);
        bool messageFound = size > 0;

        if (messageFound)
        {
            *errorMessage = _strdup(buffer);

            LocalFree(buffer);
        }

        return messageFound;
#elif __linux__
        *errorMessage = strerror(errorCode);

        return *errorMessage && strlen(*errorMessage) > 0;
#endif
    }

    EXPORT bool ShouldDeleteErrorMessage()
    {
#ifdef _WIN32
        return true;
#elif __linux__
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