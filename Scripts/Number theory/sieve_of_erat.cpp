vc prime(n + 1, true);
prime[0] = prime[1] = false;
for (li i = 2; i * i <= n; ++i)
    if (prime[i])
        for (li j = i * i; j <= n; j += i)
            prime[j] = false;