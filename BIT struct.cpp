template<typename T>
struct BIT
{
    int N;
    vector<T> bit;
 
    void init(int n)
    {
        N = n;
        bit.assign(n + 1, 0);
    }
 
    void update(int idx, T val)
    {
        while(idx <= N)
        {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }
 
 
    T pref(int idx)
    {
        T ans = 0;
        while(idx > 0)
        {
            ans += bit[idx];
            idx -= idx & -idx;
        }
        return ans;
    }
 
    T query(int l, int r)
    {
        return pref(r) - pref(l - 1);
    }
 
    
};