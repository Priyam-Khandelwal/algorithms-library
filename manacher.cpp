//https://codeforces.com/blog/entry/12143

vector<int> Manacher(string s, bool parity) {
  int n = s.size(), z = parity, l = 0, r = 0;
  vector<int> ret(n - !z, 0);
  
  for (int i = 0; i < n - !z; ++i) {
    if (i + !z < r) ret[i] = min(r - i, ret[l + r - i - !z]);
    int L = i - ret[i] + !z, R = i + ret[i];
    while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1])
      ++ret[i], --L, ++R;
    if (R > r) l = L, r = R;
  }
  
  return ret;
}
 