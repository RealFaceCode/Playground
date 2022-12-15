#include "../hdr/filelogger.h"
#include "../hdr/util/FileStream.h"
#include "../hdr/util/memory.h"
#include "../hdr/logger.h"

static std::map<String, FILE*> files = {};

static FILE* GetFilePtr(const String& filepath)
{
    if(files.contains(filepath))
    {
        return files.find(filepath)->second;
    }
    return nullptr;
}

static FILE* CreateFilePtr(const String& filePath)
{
    FILE* f = fopen(filePath.c_str(), "ab+");
    if(!f)
    {
        return nullptr;
    }
    files[filePath] = f;
    return f;
}

void FileLog(const String &type,
        const String &fileWritePath,
        const String &filePath,
        const int &line,
        const String &format,
        ...)
{
    FILE* f = GetFilePtr(fileWritePath);
    if(!f)
    {
        f = CreateFilePtr(fileWritePath);
    }
    if(!f)
    {
        LOG_ERROR({}, "Failed to open file with path'%s'", fileWritePath.c_str());
        return;
    }

    char* str;
    va_list args;
    va_start(args, format.c_str());
    //Allocates dynamically memory for str. str hax to be freed later
    vasprintf(&str, format.c_str(), args);
    va_end(args);

    String userFormat(str);
    Free(str);

    const auto fName        = FS::getFileName(filePath.c_str());
    const auto date         = GetDate();
    const auto time         = GetTime();
    const char* fileName    = fName.c_str();

    //Allocates dynamically memory for str. str hax to be freed later
    asprintf(&str,
             "[%s][FILE:%s][LINE:%i][%s][%s]\t\t",
             type.c_str(),fileName,line, date.c_str(), time.c_str());
    String out(str);
    out.add(userFormat);
    out.add("\n");
    Free(str);
    str = nullptr;

    if(fwrite(out.c_str(), out.length(), 1, f) != 1)
    {
        LOG_ERROR({}, "Failed to log to file with file path'%s'", fileWritePath.c_str());
    }
    fflush(f);
}

void FileLogCleanup()
{
    for(auto& p : files)
    {
        auto& str =(String&)p.first;
        str.destroy();
        fclose(p.second);
    }
}
