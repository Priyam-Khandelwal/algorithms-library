int fac[N],invf[N];
inline int add(int x, int y) { 
    return x + y >= mod ? x + y - mod : x + y; 
}
inline int sub(int x, int y) { 
    return x - y >= 0 ? x - y : x - y + mod; 
}
inline int power(int x, int y, int res = 1) {
    while(y) {
        if(y & 1)
            res = 1ll * res * x % mod;
        
        x = 1ll * x * x % mod;
        y >>= 1;
    }
    return res;
}
void initcombi(int n) {
    for (int i = fac[0] = 1; i <= n; i++) { 
        fac[i] = 1ll * fac[i - 1] * i % mod; 
    }
    
    invf[n] = power(fac[n], mod - 2);
    
    for (int i = n; i; i--) { 
        invf[i - 1] = 1ll * invf[i] * i % mod; 
    }
}
 
inline int NCR(int n, int m) {
    if (n < m)
        return 0;
    
    return 1ll * fac[n] * invf[m] % mod * invf[n - m] % mod;
}


