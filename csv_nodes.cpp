#include "csv_nodes.h"

void csv_nodes::Clear()
{
	_nodes.clear();
}

void csv_nodes::Add(string node)
{
	if (_nodes.size() != 0)
		throw exception("������������ ������ ��� ���������� ������� ��������!");

	_nodes.insert(Nodes_Pair(node, csv_node()));
}

void csv_nodes::Add(string node, vector<string> parents, vector<string> children)
{
	unordered_set<string> parents_set;
	unordered_set<string> children_set;

	if (Contains(node))
		throw exception("��� ��������!");

	int size = parents.size();
	for (int i = 0; i < size; i++)
	{
		string parent = parents[i];
		if (_nodes.find(parent) == _nodes.end())
			throw exception("�������� �� ������!");

		// ���������� �������� � �������
		if (parents_set.find(parent) == parents_set.end())
		{
			_nodes[parent].Children.insert(node);
			parents_set.insert(parent);
		}

		// ����������� ���������� � ���������
		for (string grandpa : _nodes[parent].Parents)
		{
			if (grandpa == node)
				throw exception("���������� ��������!");

			if (parents_set.find(grandpa) == parents_set.end())
			{
				_nodes[grandpa].Children.insert(node);
				parents_set.insert(grandpa);
			}
		}
	}

	size = children.size();
	for (int i = 0; i < size; i++)
	{
		string child = children[i];
		if (parents_set.find(child) != parents_set.end())
			throw "���������� ��������!";

		if (Contains(child) == false)
			throw "������� �� ������!";

		// ���������� �������� � �������
		if (children_set.find(child) == children_set.end())
		{
			_nodes[child].Parents.insert(node);
			children_set.insert(child);
		}

		// ����������� ���������� � ��������� ��������
		for (string grandchild : _nodes[child].Children)
		{
			if (grandchild == node)
				throw exception("���������� ��������!");

			if (parents_set.find(grandchild) != parents_set.end())
				throw exception("���������� ��������!");

			if (children_set.find(grandchild) == children_set.end())
			{
				_nodes[grandchild].Parents.insert(node);
				children_set.insert(grandchild);
			}
		}
	}

	_nodes.insert(Nodes_Pair(node, csv_node(parents_set, children_set)));
}

bool csv_nodes::Contains(string node)
{
	return _nodes.find(node) != _nodes.end();
}

bool csv_nodes::Child_To(string node, string parent)
{
	if (Contains(node) == false)
		throw exception("������� �����������!");

	if (Contains(parent) == false)
		throw exception("������� �����������!");

	return _nodes[node].Has_Parent(parent);
}

bool csv_nodes::Parent_To(string node, string child)
{
	if (Contains(node) == false)
		throw exception("������� �����������!");

	if (Contains(child) == false)
		throw exception("������� �����������!");

	return _nodes[node].Has_Child(child);
}

vector<string> csv_nodes::Get_Children(string node)
{
	if (Contains(node) == false)
		throw exception("������� �����������!");

	vector<string> children;

	for (string child : _nodes[node].Children)
		children.push_back(child);

	return children;
}

vector<string> csv_nodes::Get_Parents(string node)
{
	if (Contains(node) == false)
		throw exception("������� �����������!");

	vector<string> parents;

	for (string parent : _nodes[node].Parents)
		parents.push_back(parent);

	return parents;
}
