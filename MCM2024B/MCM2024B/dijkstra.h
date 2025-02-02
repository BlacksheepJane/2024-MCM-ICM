#pragma once
#include "base.h"

inline void add_Edge(int from, int to, double length, vector<Edge>* adj)
{
	adj[from].push_back(Edge{ from, to, length });
}
static int dijkstra(int s, int t, int numv, vector<Edge>* adj, unordered_map<pair<int, int>, Edge, pair_hash>& map)//D(s,t)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	int d[maxV];
	bool visited[maxV];
	for (int i = 0; i < numv; i++)
		d[i] = maxD;
	memset(visited, 0, sizeof(visited));
	d[s] = 0;
	int mind = maxD;
	int now = 0;
	q.push({ 0, s });
	while (1) {
		mind = maxD;
		auto x = q.top();
		q.pop();
		int now = x.second, mind = x.first;
		if (visited[now])
			continue;
		if (now == t)
			return d[t];
		visited[now] = 1;
		for (int i = 0; i < adj[now].size(); i++) {
			int to = adj[now][i].end;
			if (d[now] + map[{now, to}].weight < d[to])
			{
				d[to] = d[now] + map[{now, to}].weight;
				q.push({ d[to], to });
			}
		}
	}

}
inline void dijkstra(int s, int* d, int numv, vector<Edge>* adj, unordered_map<pair<int, int>, Edge, pair_hash>& map)//D(s,t)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	bool visited[maxV];
	for (int i = 0; i < numv; i++)
		d[i] = maxD;
	memset(visited, 0, sizeof(visited));
	d[s] = 0;
	int mind = maxD;
	int now = 0;
	q.push({ 0, s });
	while (1) {
		mind = maxD;
		if (q.empty())
			return;
		auto x = q.top();
		q.pop();
		int now = x.second, mind = x.first;
		if (visited[now])
			continue;
		visited[now] = 1;
		for (int i = 0; i < adj[now].size(); i++) {
			int to = adj[now][i].end;
			if (d[now] + map[{now, to}].weight < d[to])
			{
				d[to] = d[now] + map[{now, to}].weight;
				q.push({ d[to], to });
			}
		}
	}

}
struct pa {
	double a, b, c;
};
inline double calculate_weight(pa parameters, double pr, double length, double line) {
	double ans = int(parameters.a * 60 / pr + 0.02 * parameters.b * length + 0.05 * parameters.c);
	return max(1.0,ans);
}
inline double line(pair<int, int> e, vector<Point>& v) {
	double x1 = v[e.first].x;
	double y1 = v[e.first].y;
	double x2 = v[e.second].x;
	double y2 = v[e.second].y;
	double dy = 78.125 * (y1 - y2);
	double dx = 85.714 * (x1 - x2);
	return 1000 * sqrt(dy * dy + dx * dx);
}
inline void cal_weight(pa now, unordered_map<pair<int, int>, Edge, pair_hash>& weight, unordered_map<pair<int, int>, Edge, pair_hash>& pr, unordered_map<pair<int, int>, Edge, pair_hash>& length, vector<Point>& v) {
	for (auto& it : pr) {
		weight[it.first].weight = calculate_weight(now, pr[it.first].weight, length[it.first].weight, line(it.first, v));
	}
}
inline double update_parameter(double now) {
	double dnow = ((double)rand() / RAND_MAX - 0.5) * 0.3;
	return abs(now + dnow);
}
static pa update(pa now) {
	pa ans = now;
	ans.a = update_parameter(ans.a);
	ans.b = update_parameter(ans.b);
	ans.c = update_parameter(ans.b);
	return ans;
}
static void Page_Rank(vector<Edge>* adj, vector<Edge>* antiadj, int numv, double* b, double a) {
	vector <Edge>new_Adj[maxV];
	vector <Edge>new_Antiadj[maxV];
	for (int i = 0; i < numv; i++) {
		double pr = 0;
		for (int k = 0; k < antiadj[i].size(); k++)
			pr += antiadj[i][k].weight;
		pr *= a;
		pr += b[i];
		pr /= adj[i].size();
		for (int j = 0; j < adj[i].size(); j++)
		{
			add_Edge(i, adj[i][j].end, pr, new_Adj);
			add_Edge(adj[i][j].end, i, pr, new_Antiadj);
		}
	}
	for (int i = 0; i < numv; i++)
	{
		for (int j = 0; j < adj[i].size(); j++)
			adj[i][j] = new_Adj[i][j];
		for (int j = 0; j < antiadj[i].size(); j++)
			antiadj[i][j] = new_Antiadj[i][j];
	}
}
static void output(vector<Edge>* adj, int numv) {
	std::ofstream myfile;
	myfile.open("example.csv");
	for (int i = 0; i < numv; i++)
		for (int j = 0; j < adj[i].size(); j++)
		{
			myfile << i;
			myfile << ",";
			myfile << adj[i][j].end;
			myfile << ",";
			myfile << adj[i][j].weight;
			myfile << ",\n";
		}
	myfile.close();
}
