#ifndef USE_MIPS32

unsigned int mcd(unsigned int m, unsigned int n){
    if (n == 0) return m;
    return mcd(n, m % n);
}

unsigned int mcm(unsigned int m, unsigned int n) {
    int numerator = m * n;
    unsigned int denominator = mcd(m, n);
    return numerator/denominator;
}

#endif /* USE_MIPS32 */ 
