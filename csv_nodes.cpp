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

void csv_nodes::Add(string parent, string node)
{
	unordered_set<string> parents_set;
	unordered_set<string> children_set;

	if (Contains(node))
		throw exception("��� ��������!");

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

	_nodes.insert(Nodes_Pair(node, csv_node(parents_set, children_set)));
}

// �� ���������� ������� �������� �������� other_nodes, � ���� �� �����������
void csv_nodes::Union(string self, string other, csv_nodes other_nodes)
{
	// ����� ������ ��������� ���� ����������� ��������
	if (Contains(self) == false)
		throw "������� ���������!";
	if (other_nodes.Contains(other) == false)
		throw "������� ���������!";

	// ����� �� ������ ��������� ����� ����������� ��������
	// �������� ������� ���� ����� ��������� �������
	if (Contains(other))
		throw "����� ��� ��������! ������� ��������!";
	if (other_nodes.Contains(self))
		throw "����� ��� ��������! ������� ��������!";


	// �������� ���� �� other_nodes � ������� ����
	for (Nodes_Pair node : other_nodes._nodes)
	{
		_nodes.insert(node);
	}

	// ��������� ��� ����� ������ ��������
	Connect(self, other);
}

void csv_nodes::Connect(string nodeA, string nodeB)
{
	// ��� ���� ������ ������������ �����
	if (Contains(nodeA) == false)
		throw "������� ���������!";
	if (Contains(nodeB) == false)
		throw "������� ���������!";

	csv_node& node_a = _nodes[nodeA];
	csv_node& node_b = _nodes[nodeB];

	// ���� �� ������ ����� ����������� �����
	// �������� ������� nodeB � ��������� node_a ���������
	if (node_b.Has_Child(nodeA))
		throw "���������� ��������!";

	vector<string> parents = Get_Parents(nodeA);
	vector<string> children = Get_Children(nodeB);


	// ��������� node_b ��������� node_a + nodeA
	node_b.Parents.insert(nodeA);
	for (string parent : parents)
		node_b.Parents.insert(parent);

	// ��������� node_a �������� node_b + nodeB
	node_a.Children.insert(nodeB);
	for (string child : children)
		node_a.Children.insert(child);

	// ��������� �������� node_b ��������� node_a + nodeA
	for (string child : children)
	{
		csv_node* child_node = &_nodes[child];

		child_node->Parents.insert(nodeA);
		for (string parent : parents)
			child_node->Parents.insert(parent);
	}

	// ��������� ��������� node_a �������� node_b + nodeB
	for (string parent : parents)
	{
		csv_node* parent_node = &_nodes[parent];

		parent_node->Children.insert(nodeB);
		for (string child : children)
			parent_node->Children.insert(child);
	}
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

vector<string> csv_nodes::Get_Contained()
{
	vector<string> nodes;

	for (Nodes_Pair pair : _nodes)
		nodes.push_back(pair.first);

	return nodes;
}

