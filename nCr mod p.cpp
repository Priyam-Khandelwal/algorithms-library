//todo - improve code and indent
const int N = 1e6 + 5;
long long fac[N],invfac[N]; 
 
long long mul(long long x,long long y,long long z){
    long long res = 0;
    while(y){
        if(y&1)
            res = (res+x)%z;
        x = (2*x)%z;
        y /= 2;
    }
    return res;
}
 
long long power(long long x, long long y, long long p){
    long long res = 1;     
    x=x%p;           
    while (y) {
        if (y & 1)
            res = mul(res,x,p)%p ; 
        x=mul(x,x,p)%p;
        y/=2;
    }
    return res;
}
 
 
long long modInverse(long long n, long long p) 
{ 
    return power(n, p-2, p); 
} 
void pre(int n){
 
    fac[0] = 1; 
    for (long long i = 1 ; i <= n; i++) 
        fac[i] = (fac[i-1] * i) % mod; 
 
    invfac[n] = power(fac[n],mod-2,mod);
    for(int i = n; i >= 1; i--) {
        invfac[i-1] = (i * invfac[i]) % mod;   
    }
}
 
long long NCR(long long n, long long r, long long p) { 
 
 
    if (r > n)
        return 0;
    if(r < 0)
	return 0;
    if (r == 0)     
        return 1; 
 
    return ( ((fac[n] * invfac[r]) % p) * invfac[n-r]) % p; 
}  