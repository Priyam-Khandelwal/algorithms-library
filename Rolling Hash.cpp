
template<typename T = int>
struct Hashs  {
    vector<T> hashs;
    vector<T> pows;
    T P;
    T MOD;
 
    Hashs() {}
 
    Hashs(string &s, T P, T MOD) : P(P), MOD(MOD) {
        int n = s.size();
        pows.resize(n + 1, 0);
        hashs.resize(n + 1, 0);
        pows[0] = 1;
        for(int i = n - 1; i >= 0; i--) {
            hashs[i] = (1LL * hashs[i + 1] * P + s[i] - 'a' + 1) % MOD;
            pows[n - i] = (1LL * pows[n - i - 1] * P) % MOD;
        }
        pows[n] = (1LL * pows[n - 1] * P) % MOD;
    }
    T get_hash(int l, int r) {
        int ans = hashs[l] + MOD - (1LL * hashs[r + 1] * pows[r - l + 1]) % MOD;
        ans %= MOD;
        return ans;
    }
};	
