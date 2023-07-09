#pragma once
#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <iomanip>
#include "csv_nodes.h"

using namespace std;
typedef pair <string, string> Table_Pair;
class csv_table
{
private:
	vector<csv_nodes> _node_groups;
	void _extend_graph(string nodeA, string nodeB, csv_nodes& group);
	void _generation_step(int depth, const int max_depth, const int max_children, unordered_map<string, string> allowed, csv_nodes& group);

	map<string, string> _data;
	vector<string> _rows;
	vector<string> _cols;
	const int operators_count = 4;
	const char operators[4] = { '+', '-', '/', '*' };
	exception _csv_exception(string message, int row = -1, int col = -1);
	string _get_cel_address(int row, int col);

public:
	csv_table();
	csv_table(const int columns_count, const int rows_count);
	void Print();
	void Save(string file_path);
	void Load(string file_path);

	void Generate_Graph(int max_depth, int max_children, bool avoid_others=false);
	static vector<string> Split_Line(string line);

	vector<int> Get_Rows();
	vector<string> Get_Columns();
	int Get_RowsCount();
	int Get_ColumsCount();

	string Get_Data(int row, string column);
};

