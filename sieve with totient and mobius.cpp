int phi[N];
int mu[N];
void EulerSieve(const int n, vector<int> &primes){
    phi[1] = 1;
    mu[1] = 1;
    vector<int> isPrime(n + 1, 1);
    for(int i = 2; i <= n;i++){
        if(isPrime[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for(const auto& j : primes) {
            ll num = 1LL*j*i;
            if(num > n)
                break;
            isPrime[num] = 0;
            if(i % j == 0) {
                phi[num] = phi[i] * j;
                mu[num] = 0;
                break;
            }
            else{
                phi[num] = phi[i] * (j - 1);
                mu[num] = -mu[i];
            }
        }
    }
    
}