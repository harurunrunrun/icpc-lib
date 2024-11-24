#include <algorithm>
#include <vector>
using namespace std;
using ll=long long;

struct dsu {
    ll n;
    vector<ll> par;
    dsu(ll n = 0):n(n), par(n, -1){}
    ll merge(ll x, ll y){
        x = leader(x);
        y = leader(y);
        if(x == y)return x;
        if(par[x] > par[y])swap(x, y);
        par[x] += par[y];
        return par[y] = x;
    }
    bool same(ll x, ll y) {
        return leader(x) == leader(y);
    }
    ll leader(ll x) {
        if(par[x] < 0)return x;
        return par[x] = leader(par[x]);
    }
    ll size(ll x) {
        return -par[leader(x)];
    }
    vector<vector<ll>> groups(){
        vector<vector<ll>> res(n);
        for(ll i = 0; i < n; i++){
            res[leader(i)].emplace_back(i);
        }
        res.erase(remove_if(res.begin(), res.end(), [&](vector<ll> v){return v.empty();}));
        return res;
    }
};
