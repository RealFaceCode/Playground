#include "../hdr/core.h"
#include "../hdr/util/memory.h"

std::string GetTime()
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    std::string time(buffer);
	return time;
}

std::string GetDate()
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%y-%m-%d", timeinfo);
    std::string date(buffer);
	return date;
}

std::string GetFileName(const char* fileName)
{
    std::string name(fileName);
    ui32 pos = name.find_last_of('\\') + 1;
    name.erase(name.begin(), name.begin() + pos);
    return name;
}

std::string GetFormatedString(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char* str;
    if (0 > asprintf(&str, fmt, args))
    {
        return std::string("");
    }
    va_end(args);

    std::string string;
    string.append(str);
    Free(str);

    return string;
}

std::string ToString(const char* str)
{
    return std::string(str);
}

std::string ToString(std::string str)
{
    return str;
}

std::string ToString(int i)
{
    return std::string(std::to_string(i));
}

std::string ToString(unsigned int ui)
{
    return std::string(std::to_string(ui));
}

std::string ToString(float f)
{
    return std::string(std::to_string(f));
}

std::string ToString(double d)
{
    return std::string(std::to_string(d));
}

bool EndsWith(const char* filepath, const char* ending)
{
    std::string path(filepath);
    const size_t pos = path.find_last_of(".");
    path.erase(path.begin(), path.begin() + pos);
    return (strcmp(path.c_str(), ending) == 0);
}

void PrintColorPattern(){}

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