#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
    int cw;
    int cv;
    int level;
};

struct Obj {
    double w;
    double v;
}objs[11];

queue<Node> q;
int bestv = 0, n, c;
double bound(int t, int cleft)
{
    for (int i = 1; i <= n; i++)
    {
        int sum = 0;
        if (objs[i].w <= cleft) {
            sum += objs[i].v;
            cleft -= objs[i].w;
        }
        else {
            sum += cleft * objs[i].v / objs[i].w;
        }
    }
}
bool cmp(Obj a, Obj b) {
    return a.v / a.w > b.v / b.w;
}
void bfs() {
    Node root;
    root.cv = 0;
    root.cw = 0;
    root.level = 1;
    q.push(root);
    while (!q.empty()) {
        Node node = q.front();
        q.pop();
        if (node.level > n) {
            if (node.cv > bestv)
                bestv = node.cv;
            continue;
        }
        if (node.cw + objs[node.level].w <= c) {
            Node nextNode;
            nextNode.level = node.level + 1;
            nextNode.cw = node.cw + objs[node.level].w;
            nextNode.cv = node.cv + objs[node.level].v;
            q.push(nextNode);
        }
        if (node.cv + bound(node.level + 1, c - node.cw) > bestv) {
            Node nextNode;
            nextNode.level = node.level + 1;
            nextNode.cw = node.cw;
            nextNode.cv = node.cv;
            q.push(nextNode);
        }
    }
}
int main() {
    cin >> n >> c;
    for (int i = 1; i <= n; i++)
        cin >> objs[i].w >> objs[i].v;
    sort(objs + 1, objs + 1 + n, cmp);
    bfs();
    cout << bestv << endl;
}
