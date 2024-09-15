#include <iostream>
#include <vector>

using namespace std;

int const N = 1e5 + 10;

int a[N], t[4 * N];

void build(int v, int vl, int vr) { //here we will build the vector t
    //we are standing at the vertex v, which is responsible for the segment from vl to vr inclusive  
    if (vl == vr) {
        t[v] = a[vl];
        return;
    }
    int vm = (vl + vr) / 2;
    build(2 * v + 1, vl, vm);
    build(2 * v + 2, vm + 1, vr);
    t[v] = t[2 * v + 1] + t[2 * v + 2];
}

int sum(int v, int vl, int vr, int l, int r) {
    if (vl > r || vr < l)
        return 0;
    if (l <= vl && vr <= r)
        return t[v];
    int vm = (vl + vr) / 2;
    int s1 = sum(2 * v + 1, vl, vm, l, r);
    int s2 = sum(2 * v + 2, vm + 1, vr, l, r);
    return s1 + s2;
}

void update(int v, int vl, int vr, int pos, int x) {
    if (vl == vr && vl == pos) {
        t[v] = x;
        return;
    }
    if (pos > vr || pos < vl)
        return;
    int vm = (vl + vr) / 2;
    update(2 * v + 1, vl, vm, pos, x);
    update(2 * v + 2, vm + 1, vr, pos, x);
    t[v] = t[2 * v + 1] + t[2 * v + 2];
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    build(0, 0, n - 1);
    for (int i = 0; i < 4 * n; i++)
        cout << i << " : " << t[i] << endl;
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        if (s == "sum") {
            int l, r; cin >> l >> r;
            l -= 1; r -= 1;
            cout << sum(0, 0, n - 1, l, r) << endl;
        }
        if (s == "update") {
            int pos, x; cin >> pos >> x;
            pos -= 1;
            update(0, 0, n - 1, pos, x);
        }
    }
}
