#include <algorithm>
#include <vector>
using ll=long long;
using namespace std;

template <class S, S (*op)(S, S), S (*e)()> struct segtree{
    ll n, size, log;
    vector<S> d;
    void update(ll k){d[k] = op(d[2 * k], d[2 * k + 1]);}
    ll bit_ceil(ll y) {
        ll x = 1;
        while(x < y) x *= 2;
        return x;
    }
    ll countr_zero(ll y) {
        ll x = 0;
        while(!(y & (1 << x))) x++;
        return x;
    }
    segtree(int n = 0):segtree(vector<S>(n, e())){}
    segtree(const vector<S>& v):n(ll(v.size())){
        size = bit_ceil(n);
        log = countr_zero(size);
        d = vector<S>(2 * size, e());
        for(ll i = 0; i < n; i++) d[size + i] = v[i];
        for(ll i = size - 1; i >= 1; i--) update(i);
    }
    void set(ll p, S x) {
        p += size;
        d[p] = x;
        for(ll i = 1; i <= log; i++) update(p >> i);
    }
    S get(ll p){
        return d[p + size];
    }
    S prod(ll l, ll r){
        S sml = e(), smr = e();
        l += size;
        r += size;
        while(l < r){
            if(l & 1) sml = op(sml, d[l++]);
            if(r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }
    S all_prod(){ return d[1]; }
};
