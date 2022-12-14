#include "../hdr/core.h"
#include "../hdr/util/memory.h"
#include "../hdr/util/buffer/string.h"
#include "../hdr/util/FileStream.h"

void exitFunc()
{
    if(MemoryPrintStack())
    {
        system("pause");
    }
}

void CoreInit()
{
    PREP_CONSOLE_LOG
    atexit(exitFunc);
}

String GetTime()
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
	return buffer;
}

String GetDate()
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%y-%m-%d", timeinfo);
	return buffer;
}

bool EndsWith(const String& filepath, const String& ending)
{
    return ending == FS::getFileName(filepath.c_str());
}

int vasprintf(char **strp, const char *fmt, va_list ap)
{
    int r = -1, size;

    va_list ap2;
    va_copy(ap2, ap);

    size = vsnprintf(0, 0, fmt, ap2);

    if ((size >= 0) && (size < INT_MAX))
    {
        *strp = (char *)Malloc(size+1); //+1 for null
        if (*strp)
        {
            r = vsnprintf(*strp, size+1, fmt, ap);  //+1 for null
            if ((r < 0) || (r > size))
            {
                free(*strp);
                r = -1;
            }
        }
    }
    else { *strp = 0; }

    va_end(ap2);

    return(r);
}

int asprintf(char **strp, const char *fmt, ...)
{
    int r;
    va_list ap;
    va_start(ap, fmt);
    r = vasprintf(strp, fmt, ap);
    va_end(ap);
    return(r);
}