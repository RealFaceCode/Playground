#include "Node.h"
#include <iostream>

namespace FHandle
{
	void Node::printNode(Node* rootNode, int tab)
	{
		Node& node = *rootNode;

		if (!node.nodeName.empty())
		{
			for (int i = 0; i < tab; i++)
			{
				std::cout << "\t";
			}

			std::cout << node.nodeName << ":" << std::endl;
			for (auto dat : node.data) {
				for (int i = 0; i < tab; i++)
				{
					std::cout << "\t";
				}
				std::cout << "   -\t" << dat << std::endl;
			}

			for (auto cn : node.nodes)
			{
				tab++;
				printNode(&cn.second, tab);
				tab--;
			}
		}
	}

	void Node::packNotes(Node* rootNode, File* file, int tab)
	{
		Node& node = *rootNode;

		if (!node.nodeName.empty())
		{
			size_t datSize = node.data.size();
			size_t nameSize = node.nodeName.size();
			size_t reserveSize = tab + (tab * datSize) + (6 * datSize) + 2 + nameSize;
			file->reserve(reserveSize);

			for (int i = 0; i < tab; i++)
			{
				file->addStringWithoutLen("\t");
			}

			file->addStringWithoutLen(node.nodeName.c_str());
			file->addStringWithoutLen(":\r\n");
			for (auto& dat : node.data)
			{
				for (int i = 0; i < tab; i++)
				{
					file->addStringWithoutLen("\t");
				}

				file->addStringWithoutLen("   -\t");
				file->addStringWithoutLen(dat.c_str());
				file->addStringWithoutLen("\r\n");
			}

			for (auto& cn : node.nodes)
			{
				tab++;
				packNotes(&cn.second, file, tab);
				tab--;
			}
		}
	}

	void Node::printNodes()
	{
		int tab = 0;
		for (auto& n : nodes) {
			printNode(&n.second, tab);
		}
	}

	void Node::write(const char* path)
	{
		File file((char*)path, FILE_CRT);

		int tab = 0;
		for (auto& n : nodes) {
			packNotes(&n.second, &file, tab);
		}

		file.write();
	}

	void Node::trackTypes(bool b)
	{
		track = b;
	}

	int Node::getAsInt(size_t at)
	{
		return std::stoi(this->data.at(at));
	}

	float Node::getAsFloat(size_t at)
	{
		return std::stof(this->data.at(at));
	}

	std::string Node::getAsString(size_t at)
	{
		return this->data.at(at);
	}

	bool Node::empty()
	{
		return nodes.empty();
	}

	Node& Node::operator[] (std::string key)
	{
		if (nodes.find(key) != nodes.end())
		{
			return nodes.at(key);
		}

		nodes[key].nodeName = key;
		return nodes[key];
	}

	void Node::operator= (int value)
	{
		data.emplace_back(std::to_string(value));
	}

	void Node::operator=(float value)
	{
		data.emplace_back(std::to_string(value));
	}

	void Node::operator=(const char* value)
	{
		data.emplace_back(value);
	}

	Node Node::loadNode(const char* path)
	{
		File file(path, FILE_READ);

		if (file.getData() == nullptr)
		{
			return Node();
		}

		char* tmpString = (char*)file.getData(file.getDataLen());
		tmpString[file.getDataLen()] = '\0';
		std::string fileData(tmpString);

		std::vector<std::string> lines;
		size_t prevTabs = 0;

		Node node, * next = &node; {};
		Node* prevNode = &node;
		std::string prevKey;

		while (fileData.size() != 0)
		{
			auto pos = fileData.find_first_of("\r\n");
			char* line = new char[pos + 1];

			if (line == nullptr)
			{
				return Node();
			}

			memcpy(line, &fileData[0], pos);
			line[pos] = '\0';
			fileData.erase(fileData.begin(), fileData.begin() + pos + 2);

			size_t tabs = 0;
			std::string lineData(line);
			for (auto& c : lineData)
			{
				if (c == '\t')
				{
					tabs++;
				}
			}

			if (lineData.at(lineData.size() - 1) == ':')
			{
				lineData.erase(lineData.end() - 1, lineData.end());

				prevKey = lineData;

				if (lineData.find('\t') != SIZE_MAX)
				{
					auto pos = lineData.find_last_of('\t') + 1;
					auto begin = lineData.begin();
					lineData.erase(begin, begin + pos);

					if (prevTabs == tabs)
					{
						Node& n = *prevNode;
						prevTabs = tabs;
						next = &n[lineData];
						goto DEL;
					}
					else
					{
						Node& n = *next;
						prevTabs = tabs;
						prevNode = &n;
						next = &n[lineData];
						goto DEL;
					}
				}
				else
				{
					prevTabs = tabs;
					prevNode = &node;
					next = &node[lineData];
				}
			}
			else
			{
				auto pos = prevKey.find_last_of('\t') + 1;
				auto begin = prevKey.begin();
				prevKey.erase(begin, begin + pos);

				pos = lineData.find_last_of('\t') + 1;
				begin = lineData.begin();
				lineData.erase(begin, begin + pos);

				next->data.push_back(lineData);
			}

		DEL:
			delete[] line;
		}

		return node;
	}
}