#include <../../hdr/util/FileStream.h>
#include "../../hdr/util/buffer/string.h"
#include "../../hdr/util/memory.h"
#include <../../hdr/logger.h>
#include <cstdio>
#include <direct.h>
#include <filesystem>
#include <sys/stat.h>
#include <io.h>
#include <share.h>

namespace FS
{
    bool createFile(const char* path)
    {
        if (path == nullptr)
        {
            return false;
        }
        int result = _creat(path, _S_IREAD | _S_IWRITE);
        if (result == -1 || !checkExistFile(path))
        {
            return false;
        }
        return true;
    }

    bool removeFile(const char* path)
    {
        if (path == nullptr || remove(path) != 0)
        {
            return false;
        }
        return true;
    }

    bool checkExistFile(const char* path)
    {
        if (path == nullptr)
        {
            return false;
        }
        return _access(path, 00) != -1;
    }

    bool renameFile(const char* path, const char* newName)
    {
        if (path == nullptr || newName == nullptr)
        {
            return false;
        }
        if (!checkExistFile(path))
        {
            return false;
        }
        if (rename(path, newName) != 0) {
            return false;
        }
        return true;
    }

    ui64 getFileSize(const char* path)
    {
        struct stat buf {};
        int c = stat(path, &buf);
        return c == 0 ? buf.st_size : 0;
    }

    bool createDir(const char* dirPath)
    {
        if (checkExistDir(dirPath))
        {
            return false;
        }
        return (_mkdir(dirPath) == 0);
    }

    bool removeDir(const char* dirPath)
    {
        if (!checkExistDir(dirPath))
        {
            return false;
        }
        return (_rmdir(dirPath) == 0);
    }

    bool checkExistDir(const char* dirPath)
    {
        if (dirPath == nullptr) return false;
        struct stat sb{};
        return (stat(dirPath, &sb) == 0 && (S_IFDIR & sb.st_mode) != 0);
    }

    void createDirIfNotExist(const char* dir)
    {
        //TODO: rewrite with String class
        std::string fullDirPath(dir);
        std::string dirPath;
        i64 position = 0;

        while (fullDirPath.size() >= position)
        {
            size_t off = fullDirPath.find('/', position);
            if(off == std::string::npos)
            {
                position = fullDirPath.end() - fullDirPath.begin();
                createDir(fullDirPath.c_str());
                return;
            }

            position = (i64)off;

            dirPath = std::string(fullDirPath.begin(), fullDirPath.begin() + position);
            createDir(dirPath.c_str());
            position++;
        }
    }

    bool checkIfDirContainsFiles(const char* dir)
    {
        return !std::filesystem::is_empty(dir);
    }

    uint64_t getFileCountFromDir(const char* dir)
    {
        uint64_t count = 0;
        for (auto entry : std::filesystem::directory_iterator(dir))
        {
            count++;
        }
        return count;
    }

    String getFileName(const char* filePath)
    {
        if(filePath == nullptr)
        {
            return {""};
        }

        String name(filePath);
        auto pos = name.find("/");
        if(pos.empty())
        {
            pos = name.find("\\");
            if(pos.empty())
            {
                return "Failed to get name from file!";
            }
        }
        ui64 offset = pos.back();
        name.remove(0, offset + 1);
        offset = name.find(".").back();
        name.remove(offset, name.length());
        return name;
    }

    String getFileNameExtension(const char* filePath)
    {
        if(filePath == nullptr)
        {
            return {""};
        }

        String nameExt(filePath);
        ui64 offset = nameExt.find("/").back();
        nameExt.remove(0, offset + 1);
        return nameExt;
    }

    std::vector<String> getFileNamesFromDir(const char* dir)
    {
        std::vector<String> fileNames;
        for (const auto& entry : std::filesystem::directory_iterator(dir))
        {
            auto path = entry.path().generic_string();
            uint64_t offset = path.find_last_of('/');
            path.erase(path.begin(), path.begin() + (long long)offset + 1);
            fileNames.emplace_back(path);
        }
        return fileNames;
    }

    std::vector<String> getFilePathsFromDir(const char* dir)
    {
        std::vector<String> filePaths;
        for (const auto& entry : std::filesystem::directory_iterator(dir))
        {
            filePaths.emplace_back(entry.path().generic_string());
        }
        return filePaths;
    }

    bool WriteToFile(const void* data, const ui64& bufLen, const char* filePath)
    {
        if(!data)
        {
            LOG_ERROR({}, "Failed to write to file with path'%S'! buffer is nullptr!", filePath);
            return false;
        }

        if(!checkExistFile(filePath))
        {
            if(!createFile(filePath))
            {
                LOG_ERROR({}, "Failed to create file and write to file with path'%S'!", filePath);
                return false;
            }
        }

        if(bufLen <= 0)
        {
            LOG_ERROR({}, "Failed to write to file, buffer is empty!");
            return false;
        }

        FILE* file = _fsopen(filePath, "wb", _SH_DENYNO);;
        if(!file)
        {
            LOG_ERROR({}, "Failed to open file with path'%s'", filePath);
            return false;
        }

        size_t result = fwrite(data, bufLen, 1, file);
        fclose(file);
        if(result != 1)
        {
            LOG_ERROR({}, "Failed to write to file with path'%s'", filePath);
            return false;
        }
        return true;
    }

    bool ReadFromFile(void** data, const char* filePath, const bool& nullTerm)
    {
        if(!checkExistFile(filePath))
        {
            LOG_ERROR({}, "File with path'%s' not found!", filePath);
            return false;
        }

        ui64 fileSize = getFileSize(filePath);
        if(fileSize <= 0)
        {
            LOG_ERROR({}, "File with path'%s' is empty!", filePath);
            return false;
        }

        FILE* file = _fsopen(filePath, "rb", _SH_DENYNO);;
        if(!file)
        {
            LOG_ERROR({}, "Failed to open file with path'%s'", filePath);
            return false;
        }

        if(nullTerm)
        {
            fileSize++;
        }

        *data = Malloc(fileSize);
        if(*data == nullptr)
        {
            LOG_ERROR({}, "Failed to allocate memory for file with path'%s'", filePath);
            return false;
        }

        size_t result = fread_s(*data, fileSize, fileSize - 1, 1, file);
        fclose(file);

        if(result == 0)
        {
            LOG_ERROR({}, "Failed to read data from file with path'%s'", filePath);
            Free(*data);
            *data = nullptr;
            return false;
        }
        char* cData;
        if(nullTerm)
        {
            cData = (char*)*data;
            cData[fileSize - 1] = '\0';
        }

        return true;
    }

    File::File()
        :mPath(""), mName(""), mEnding(""), mSource(0), mExist(false)
    {}

    File::File(const char* path, int flags)
        :mPath(path), mName(getFileName(path)), mEnding(getFileNameExtension(path)), mSource(0),mExist(checkExistFile(path))
    {
        if ((flags & FILE_CRT) == FILE_CRT)
        {
           createDirsAndFile();
        }

        if ((flags & FILE_READ) == FILE_READ)
        {
            read();
        }

        if ((flags & FILE_CLR) == FILE_CLR)
        {
            mSource.clear();
        }
    }

    File::~File()
    {
        mExist = false;
    }

    void File::read()
    {
        const char* filePath = (const char *)mPath.getSource();
        char* buffer = nullptr;
        ReadFromFile((void**)&buffer ,filePath, true);
        if(buffer)
        {
            mSource.add(buffer, true);
            Free(buffer);
        }
    }

    void File::write()
    {
        const char* filePath = (const char *)mPath.getSource();
        WriteToFile(mSource.getSource(), mSource.length(), filePath);
    }

    const String& File::getPath() const
    {
        return mPath;
    }

    const String& File::getName() const
    {
        return mName;
    }

    const String& File::getFileEnding() const
    {
        return mEnding;
    }

    BinaryBuffer &File::getData() {
        return mSource;
    }

    const ui64& File::capacity() const
    {
        return mSource.capacity();
    }

    const ui64& File::length() const
    {
        return mSource.length();
    }

    bool File::exist() const
    {
        return mExist;
    }

    ui8* File::getData(const ui64& len)
    {
        return (ui8*)mSource.pop(len);
    }

    i8 File::getI8()
    {
        return mSource.getI8();
    }

    ui8 File::getUI8()
    {
        return mSource.getUi8();
    }

    i16 File::getI16()
    {
        return mSource.getI16();
    }

    ui16 File::getUI16()
    {
        return mSource.getUi16();
    }

    i32 File::getI32()
    {
        return mSource.getI32();
    }

    ui32 File::getUI32()
    {
        return mSource.getUi32();
    }

    i64 File::getI64()
    {
        return mSource.getI64();
    }

    ui64 File::getUI64()
    {
        return mSource.getUi64();
    }

    bool File::getBool()
    {
        return (bool)mSource.getI8();
    }

    f32 File::getFloat()
    {
        return mSource.getF32();
    }

    f64 File::getDouble()
    {
        return mSource.getF64();
    }

    String File::getString(const bool& withoutLen)
    {
        return mSource.getString(withoutLen);
    }

    void File::addData(void* dat, const ui64& len)
    {
        mSource.push(len, dat);
    }

    void File::addI8(const i8& dat)
    {
        mSource.add(dat);
    }

    void File::addUI8(const ui8& dat)
    {
        mSource.add(dat);
    }

    void File::addI16(const i16& dat)
    {
        mSource.add(dat);
    }

    void File::addUI16(const ui16& dat)
    {
        mSource.add(dat);
    }

    void File::addI32(const i32& dat)
    {
        mSource.add(dat);
    }

    void File::addUI32(const ui32& dat)
    {
        mSource.add(dat);
    }

    void File::addI64(const i64& dat)
    {
        mSource.add(dat);
    }

    void File::addUI64(const ui64& dat)
    {
        mSource.add(dat);
    }

    void File::addBool(const bool& dat)
    {
        mSource.add((i8)dat);
    }

    void File::addF32(const f32& dat)
    {
        mSource.add(dat);
    }

    void File::addF64(const f64& dat)
    {
        mSource.add(dat);
    }

    void File::addString(const String& dat, const bool& withoutLen)
    {
        mSource.add(dat, withoutLen);
    }

    void File::addString(const std::string& dat, const bool& withoutLen)
    {
        mSource.add(dat, withoutLen);
    }

    void File::addString(const char* dat, const bool& withoutLen)
    {
        mSource.add(dat, withoutLen);
    }

    void File::createDirsAndFile()
    {
        if(!mExist)
        {
            ui64 lenRemove = mName.length() + mEnding.length() + 2;
            String dirPath(mPath);
            dirPath.remove(dirPath.length() - lenRemove, dirPath.length());
            createDirIfNotExist(dirPath.c_str());
            if(!(mExist = createFile(mPath.c_str())))
            {
                LOG_ASSERT(false, {}, "Failed to create file with path: %s", mPath.c_str())
            }
        }
    }

    Serializer::Node::Node()
        :mNext(nullptr), mNodeName(String()), mValues({})
    {
    }

    Serializer::Node::Node(const String &string)
        :mNext(nullptr), mNodeName(string), mValues({})
    {
    }

    Serializer::Node::~Node()
    {

    }

    String Serializer::Node::ToString(const Serializer::Node &node, ui64& depth)
    {
        String rStr;
        for(ui64 i = 0; i < depth; i++)
        {
            rStr.add("\t");
        }
        rStr.add("[");
        rStr.add(node.mNodeName);
        rStr.add("]\n");
        for(ui64 i = 0; i < depth; i++)
        {
            rStr.add("\t");
        }
        rStr.add("{\n");

        for(const String& str : node.mValues)
        {
            for(ui64 i = 0; i < depth + 1; i++)
            {
                rStr.add("\t");
            }
            rStr.add("= ");
            rStr.add(str);
            rStr.add(";\n");
        }

        if(node.mNext)
        {
            depth++;
            rStr += ToString(*node.mNext, depth);
            depth--;
        }

        for(ui64 i = 0; i < depth; i++)
        {
            rStr.add("\t");
        }
        rStr.add("}\n");

        return rStr;
    }

    std::vector<Serializer::Node> Serializer::Node::ToNode(String &string)
    {
        std::vector<Serializer::Node> nodeTree;
        std::vector<String> nodes = toNodeString(string);

        for(String str : nodes)
        {
            Node node;
            fillNode(&node, str);
            nodeTree.emplace_back(node);
        }

        return nodeTree;
    }

    std::vector<String> Serializer::Node::toNodeString(String &string)
    {
        std::vector<String> nodes;
        while(!string.empty())
        {
            ui64 oBrack = 0;
            ui64 cBrack = 0;
            bool fBrack = false;
            ui64 pos = 0;

            for(; pos < string.length(); pos++)
            {
                if(string.at(pos) == '{')
                {
                    oBrack++;
                    if(!fBrack)
                    {
                        fBrack = true;
                    }
                }
                if(string.at(pos) == '}')
                {
                    cBrack++;
                }

                if(oBrack == cBrack && fBrack)
                {
                    break;
                }
            }
            StringView view = string.createStringView(0, pos);
            string.remove(0, pos + 2);
            nodes.emplace_back((const char*)view.getView());
        }
        return nodes;
    }

    Serializer::Node *Serializer::Node::createNodePtr()
    {
        return (Node*)MemReg(new Node());
    }

    void Serializer::Node::destroyNode()
    {
        mValues.clear();
        mNodeName.destroy();
        cleanNodes(mNext);
    }

    void  Serializer::Node::fillNode(Node* node, String& string)
    {
        if(string.empty() || !node)
        {
            return;
        }
        ui64 posBeginName = string.findFirst("[") + 1;
        ui64 posEndName = string.findFirst("]") - 1;

        node->mNodeName = (const char*)string.createStringView(posBeginName, posEndName).getView();
        string.remove(posBeginName - 1, posEndName + 2);

        fillNodeData(node, string);

        ui64 posBeginNameInD = string.findFirst("[");
        if(posBeginNameInD != UINT64_MAX)
        {
            node->mNext = createNodePtr();
            fillNode(node->mNext,string);
        }
    }

    void Serializer::Node::fillNodeData(Serializer::Node *node, String &string)
    {
        std::vector<ui64> posValue = string.find("=");
        ui64 offset = 0;
        for(ui64 pV : posValue)
        {
            ui64 posBeginNameInD = string.findFirst("[");
            pV -= offset;

            if(pV > posBeginNameInD)
            {
                break;
            }

            if(pV < posBeginNameInD)
            {
                ui64 posValueEnd = string.findFirst(";");
                StringView view = string.createStringView(pV + 2, posValueEnd - 1);
                string.remove(0, posValueEnd + 1);
                node->mValues.emplace_back((const char*)view.getView());
                offset += posValueEnd + 1;
            }
        }
    }

    void Serializer::Node::cleanNodes(Serializer::Node* node)
    {
        if(!node)
        {
            return;
        }
        cleanNodes(node->mNext);
        node->mNodeName.destroy();
        node->mValues.clear();
        Free(node);
    }

    Serializer::Serializer(const char *path)
        :mFile(path, FILE_CRT), mNodes()
    {
    }

    Serializer::~Serializer()
    {
        while (!mNodes.empty())
        {
            auto p = mNodes.extract(mNodes.begin());
            p.key().destroy();
            p.mapped().destroyNode();
        }
        mNodes.clear();
    }

    void Serializer::write()
    {
        serialize();
        mFile.write();
    }

    void Serializer::load()
    {
        mFile.read();
        deserialize();
    }

    bool Serializer::addNewNode(const String &nodePath)
    {
        std::vector<String> tokens = nodePath.tokenize('/');

        Node* node = findBaseNode(*tokens.begin().base());

        if(!node)
        {
            mNodes[*tokens.begin()] = Node();
            node = &mNodes.at(*tokens.begin());
            node->mNodeName = *tokens.begin();
        }
        tokens.erase(tokens.begin());
        Node* lastNode = findLastNode(node->mNext, tokens);
        if(!lastNode)
        {
           lastNode = node;
        }
        createNode(&lastNode->mNext, tokens);
        return true;
    }

    void Serializer::addDataToNode(const String &nodePath, const i8 &data)
    {
        Node* node = getTargetedNode(nodePath);
        if(!node)
        {
            LOG_ERROR({}, "Failed do add data to node with path'%s", nodePath.c_str());
            return;
        }
        node->mValues.emplace_back(ToString(data));
    }

    void Serializer::addDataToNode(const String &nodePath, const i16 &data)
    {
        Node* node = getTargetedNode(nodePath);
        if(!node)
        {
            LOG_ERROR({}, "Failed do add data to node with path'%s", nodePath.c_str());
            return;
        }
        node->mValues.emplace_back(ToString(data));
    }

    void Serializer::addDataToNode(const String &nodePath, const i32 &data)
    {
        Node* node = getTargetedNode(nodePath);
        if(!node)
        {
            LOG_ERROR({}, "Failed do add data to node with path'%s", nodePath.c_str());
            return;
        }
        node->mValues.emplace_back(ToString(data));
    }

    void Serializer::addDataToNode(const String &nodePath, const i64 &data)
    {
        Node* node = getTargetedNode(nodePath);
        if(!node)
        {
            LOG_ERROR({}, "Failed do add data to node with path'%s", nodePath.c_str());
            return;
        }
        node->mValues.emplace_back(ToString(data));
    }

    void Serializer::addDataToNode(const String &nodePath, const ui8 &data)
    {
        Node* node = getTargetedNode(nodePath);
        if(!node)
        {
            LOG_ERROR({}, "Failed do add data to node with path'%s", nodePath.c_str());
            return;
        }
        node->mValues.emplace_back(ToString(data));
    }

    void Serializer::addDataToNode(const String &nodePath, const ui16 &data)
    {
        Node* node = getTargetedNode(nodePath);
        if(!node)
        {
            LOG_ERROR({}, "Failed do add data to node with path'%s", nodePath.c_str());
            return;
        }
        node->mValues.emplace_back(ToString(data));
    }

    void Serializer::addDataToNode(const String &nodePath, const ui32 &data)
    {
        Node* node = getTargetedNode(nodePath);
        if(!node)
        {
            LOG_ERROR({}, "Failed do add data to node with path'%s", nodePath.c_str());
            return;
        }
        node->mValues.emplace_back(ToString(data));
    }

    void Serializer::addDataToNode(const String &nodePath, const ui64 &data)
    {
        Node* node = getTargetedNode(nodePath);
        if(!node)
        {
            LOG_ERROR({}, "Failed do add data to node with path'%s", nodePath.c_str());
            return;
        }
        node->mValues.emplace_back(ToString(data));
    }

    void Serializer::addDataToNode(const String &nodePath, const f32 &data)
    {
        Node* node = getTargetedNode(nodePath);
        if(!node)
        {
            LOG_ERROR({}, "Failed do add data to node with path'%s", nodePath.c_str());
            return;
        }
        node->mValues.emplace_back(ToString(data));
    }

    void Serializer::addDataToNode(const String &nodePath, const f64 &data)
    {
        Node* node = getTargetedNode(nodePath);
        if(!node)
        {
            LOG_ERROR({}, "Failed do add data to node with path'%s", nodePath.c_str());
            return;
        }
        node->mValues.emplace_back(ToString(data));
    }

    void Serializer::addDataToNode(const String &nodePath, const String &data)
    {
        Node* node = getTargetedNode(nodePath);
        if(!node)
        {
            LOG_ERROR({}, "Failed do add data to node with path'%s", nodePath.c_str());
            return;
        }
        node->mValues.emplace_back(data);
    }

    i8 Serializer::getI8FromNode(const String &nodePath)
    {
        Node* node = getTargetedNode(nodePath);
        auto v = *node->mValues.begin()++;
        return ToValue<i8>(v);
    }

    i16 Serializer::getI16FromNode(const String &nodePath)
    {
        Node* node = getTargetedNode(nodePath);
        auto v = *node->mValues.begin()++;
        return ToValue<i16>(v);
    }

    i32 Serializer::getI32FromNode(const String &nodePath)
    {
        Node* node = getTargetedNode(nodePath);
        auto v = *node->mValues.begin()++;
        return ToValue<i32>(v);
    }

    i64 Serializer::getI64FromNode(const String &nodePath)
    {
        Node* node = getTargetedNode(nodePath);
        auto v = *node->mValues.begin()++;
        return ToValue<i64>(v);
    }

    ui8 Serializer::getUi8FromNode(const String &nodePath)
    {
        Node* node = getTargetedNode(nodePath);
        auto v = *node->mValues.begin()++;
        return ToValue<ui8>(v);
    }

    ui16 Serializer::getUi16FromNode(const String &nodePath)
    {
        Node* node = getTargetedNode(nodePath);
        auto v = *node->mValues.begin()++;
        return ToValue<ui16>(v);
    }

    ui32 Serializer::getUi32FromNode(const String &nodePath)
    {
        Node* node = getTargetedNode(nodePath);
        auto v = *node->mValues.begin()++;
        return ToValue<ui32>(v);
    }

    ui64 Serializer::getUi64FromNode(const String &nodePath)
    {
        Node* node = getTargetedNode(nodePath);
        auto v = *node->mValues.begin()++;
        return ToValue<ui64>(v);
    }

    f32 Serializer::getF32FromNode(const String &nodePath)
    {
        Node* node = getTargetedNode(nodePath);
        auto v = *node->mValues.begin()++;
        return ToValue<f32>(v);
    }

    f64 Serializer::getF64FromNode(const String &nodePath)
    {
        Node* node = getTargetedNode(nodePath);
        auto v = *node->mValues.begin()++;
        return ToValue<f64>(v);
    }

    String Serializer::getStringFromNode(const String &nodePath)
    {
        Node* node = getTargetedNode(nodePath);
        auto v = *node->mValues.begin()++;
        return v;
    }

    void Serializer::serialize()
    {
        for(const auto& p : mNodes)
        {
            ui64 depth = 0;
            mFile.addString(Node::ToString(p.second, depth));
        }
    }

    void Serializer::deserialize()
    {
        String nodeStr((const char*)mFile.getData().getSource());
        std::vector<Node> nodes = Node::ToNode(nodeStr);
        for(const Node& n : nodes)
        {
            mNodes[n.mNodeName] = n;
        }
    }

    Serializer::Node* Serializer::getTargetedNode(const String& nodePath)
    {
        Node* node = nullptr;
        std::vector<String> tokens = nodePath.tokenize('/');

        if(mNodes.contains(tokens[0]))
        {
            Node& n = mNodes.at(tokens[0]);
            node = findNode(&n, tokens.back());
        }
        return node;
    }

    Serializer::Node* Serializer::findNode(Serializer::Node* node, const String& nodeName)
    {
        if(!node)
        {
            return nullptr;
        }
        if(node->mNodeName == nodeName)
        {
            return node;
        }
        return findNode(node->mNext, nodeName);
    }

    Serializer::Node* Serializer::findBaseNode(const String& nodeName)
    {
        if(mNodes.contains(nodeName))
        {
            return &mNodes.at(nodeName);
        }
        return nullptr;
    }

    Serializer::Node* Serializer::findLastNode(Node* node, std::vector<String>& tokens)
    {
        if(tokens.empty() || !node)
        {
            return nullptr;
        }
        String nodeName = *tokens.begin();
        tokens.erase(tokens.begin());
        if(node->mNodeName == nodeName)
        {
            Node* n = findLastNode(node->mNext, tokens);
            if(!n)
            {
                return node;
            }
        }
        return nullptr;
    }

    void Serializer::createNode(Node** node, std::vector<String>& tokens)
    {
       if(tokens.empty())
       {
           return;
       }
       String nodeName = *tokens.begin();
       tokens.erase(tokens.begin());
       *node = Node::createNodePtr();
       Node* n= *node;
       n->mNodeName = nodeName;
       createNode(&n->mNext, tokens);
    }

}