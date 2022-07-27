#include "../hdr/core.h"

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
    ui32 pos = name.find_last_of("\\") + 1;
    name.erase(name.begin(), name.begin() + pos);
    return name;
}

std::string GetFormatedString(const char* fmt, ...)
{
    char* str;
    va_list args;
    va_start(args, fmt);

    if (0 > vasprintf(&str, fmt, args))
    {
        return std::string("");
    }

    va_end(args);
    std::string string;
    string.append(str);
    free(str);

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

void PrintColorPattern()
{
    log_msg("some msg");
    log_info("some info");
    log_warning("some warning");
    log_error("some error");
    log_assert(true, "some assert");

    printf("\n");
    printf("\x1B[31mTexting\033[0m\t\t");
    printf("\x1B[32mTexting\033[0m\t\t");
    printf("\x1B[33mTexting\033[0m\t\t");
    printf("\x1B[34mTexting\033[0m\t\t");
    printf("\x1B[35mTexting\033[0m\n");

    printf("\x1B[36mTexting\033[0m\t\t");
    printf("\x1B[36mTexting\033[0m\t\t");
    printf("\x1B[36mTexting\033[0m\t\t");
    printf("\x1B[37mTexting\033[0m\t\t");
    printf("\x1B[93mTexting\033[0m\n");

    printf("\033[3;42;30mTexting\033[0m\t\t");
    printf("\033[3;43;30mTexting\033[0m\t\t");
    printf("\033[3;44;30mTexting\033[0m\t\t");
    printf("\033[3;104;30mTexting\033[0m\t\t");
    printf("\033[3;100;30mTexting\033[0m\n");

    printf("\033[3;47;35mTexting\033[0m\t\t");
    printf("\033[2;47;35mTexting\033[0m\t\t");
    printf("\033[1;47;35mTexting\033[0m\t\t");
    printf("\t\t");
    printf("\n");
}

int vasprintf(char** strp, const char* fmt, va_list ap) {

    int len = _vscprintf(fmt, ap);
    if (len == -1)
    {
        return -1;
    }
    size_t size = (size_t)len + 1;
    char* str = (char*)malloc(size);
    if (!str)
    {
        return -1;
    }

    int r = vsprintf(str, fmt, ap);
    if (r == -1)
    {
        free(str);
        return -1;
    }
    *strp = str;
    return r;
}