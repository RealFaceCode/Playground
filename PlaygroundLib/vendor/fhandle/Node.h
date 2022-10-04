#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "File.h"

namespace FHandle
{
	struct Node
	{
		Node() = default;
		~Node() = default;
	private:
		std::string nodeName;
		std::unordered_map<std::string, Node> nodes;
		std::vector<std::string> data;
		bool track;

	private:
		void printNode(Node* rootNode, int tab);
		void packNotes(Node* rootNode, File* file, int tab);

	public:
		void printNodes();
		void write(const char* path);
		void trackTypes(bool b);

		int getAsInt(size_t at);
		float getAsFloat(size_t at);
		std::string getAsString(size_t at);

		bool empty();

	public:
		Node& operator[] (std::string key);
		void operator= (int value);
		void operator= (float value);
		void operator= (const char* value);

	public:
		static Node loadNode(const char* path);
	};
}