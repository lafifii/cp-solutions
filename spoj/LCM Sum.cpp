const int maxn = 1e6 + 10;
long long lp[maxn + 5], phi[maxn + 5], pre[maxn + 5];
vector<int> pr;
void cal_phi()
{
    phi[1] = 1;
    for (int i = 2; i <= maxn; ++i)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            phi[i] = i - 1;
            pr.push_back(i);
        }
        else
        {
            if (lp[i] == lp[i / lp[i]]) phi[i] = phi[i / lp[i]] * lp[i];
            else phi[i] = phi[i / lp[i]] * (lp[i] - 1);
        }
        for (int j = 0; j < (int)pr.size() and pr[j] <= lp[i] and i * pr[j] <= maxn; ++j)
            lp[i * pr[j]] = pr[j];
    }
    // O(n)
} 
//calculate sum of d*phi(d), d is divisor of N
void allpairs(){ 
	cal_phi();
	for (int i = 1; i <= maxn; i++) { 
		for (int j = i; j <= maxn; j += i) 
            pre[j] += ((long long)i * phi[i]); 
    } 
} 
long long lcmsum(int n){ 
	// lcm sum of (i, N) = (sum + 1)*n/2
	return (pre[n] + 1)*n/2;
}
