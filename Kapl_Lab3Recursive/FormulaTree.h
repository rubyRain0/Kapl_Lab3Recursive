#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "Stack.h"

using TInfo = char;

struct NODE
{
	TInfo info;
	NODE* left, * right;
	int count = 1;
	NODE() {}
	NODE(TInfo info, NODE* left = nullptr, NODE* right = nullptr) : info(info), left(left), right(right) {}
	~NODE()
	{
		left = nullptr;
		right = nullptr;
	}
};

using Tree = NODE*;

Tree Build_Balans(std::ifstream& file, int count)
{
	Tree result = nullptr;
	if (count)
	{
		int count_left = count / 2;
		int count_right = count - count_left - 1;
		int x;
		file >> x;
		result = new NODE(x);
		result->left = Build_Balans(file, count_left);
		result->right = Build_Balans(file, count_right);
	}
	return result;
}

void Clear(Tree& t)
{
	if (t)
	{
		Clear(t->left);
		Clear(t->right);
		delete t;
		t = nullptr;
	}
}

void Print(Tree t, int level)
{
	if (t)
	{
		Print(t->right, level + 1);
		for (int i = 0; i < level; i++)
			std::cout << ' ';
		std::cout << t->info << '\n';
		Print(t->left, level + 1);
	}
}

int count_even(Tree t)
{
	int result = 0;
	if (t)
		result = (t->info % 2 == 0 ? 1 : 0) + count_even(t->right) + count_even(t->left);
	return result;
}

using TElem = Tree;

void add(Tree& t, TInfo elem)
{
	if (!t)
		t = new NODE(elem);
	else
		if (elem < t->info)
			add(t->left, elem);
		else
			if (elem > t->info)
				add(t->right, elem);
			else
				t->count++;
}

Tree search(const Tree& root, TInfo elem)
{
	Tree t = root, ptr = nullptr;
	while (t && !ptr)
	{
		if (elem < t->info)
			t = t->left;
		else
			if (elem > t->info)
				t = t->right;
			else
				ptr = t;
	}
	return ptr;
}

Tree Build_Search(std::string file_name)
{
	std::ifstream file(file_name);
	Tree root = nullptr;
	int elem;
	while (file >> elem)
		add(root, elem);
	file.close();
	return root;
}

void print_order(Tree t)
{
	if (t)
	{
		print_order(t->left);
		for (int i = 1; i <= t->count; ++i)
			std::cout << t->info << ' ';
		print_order(t->right);
	}
}

void find_element(Tree& r, Tree& q)
{
	if (r->right)
		find_element(r->right, q);
	else
	{
		q->info = r->info;
		q->count = r->count;
		q = r;
		r = r->left;
	}
}

bool delete_element(Tree& t, TInfo elem)
{
	bool result = false;
	if (t)
	{
		if (elem < t->info)
			result = delete_element(t->left, elem);
		else
			if (elem > t->info)
				result = delete_element(t->right, elem);
			else
			{
				if (t->count > 1)
					t->count--;
				else
				{
					Tree q = t;
					if (!t->right)
						t = q->left;
					else
						if (!t->left)
							t = q->right;
						else
							find_element(q->left, q);
					delete q;
				}
				result = true;
			}
	}
	return result;
}

Tree Build_Formula(std::ifstream& file)
{
	char c = file.get();
	Tree root = new NODE(' ');
	if (c >= '0' && c <= '9' || c == 'x' || c == 'X'
		|| c == 'y' || c == 'Y' || c == 'z' || c == 'Z')
		root->info = c;
	else
	{
		root->left = Build_Formula(file);
		root->info = file.get();
		root->right = Build_Formula(file);
		c = file.get();
	}
	return root;
}

std::string print_to_string(const Tree& t)
{
	std::string result = "";
	if (!t->left && !t->right)
		result += t->info;
	else
		result = '(' + print_to_string(t->left) + std::to_string(t->info) + print_to_string(t->right) + ')';
	return result;
}

std::string treeFormulaToString(Tree& root, std::stringstream& buffer, std::string result = "")
{
	if (root)
	{
		if (!(root->info >= '0' && root->info <= '9'))
			buffer << '(';
		treeFormulaToString(root->left, buffer, result);
		buffer << root->info;
		treeFormulaToString(root->right, buffer, result);
		if (!(root->info >= '0' && root->info <= '9'))
			buffer << ')';
	}
	return buffer.str();
}

void postorder(Tree root)
{
	if (root)
	{
		postorder(root->left);
		postorder(root->right);
		std::cout << root->info;
	}
}

int calc(const Tree& t)
{
	int result;
	if (!t->left && !t->right)
		result = t->info - '0';
	else
	{
		int left = calc(t->left);
		int right = calc(t->right);
		switch (t->info)
		{
		case '+': result = left + right;
			break;
		case '*': result = left * right;
			break;
		case '-': result = left - right;
			break;
		case '^': result = left ^ right;
			break;
		}
	}
	return result;
}