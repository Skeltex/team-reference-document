istream& operator>>(istream& in, __int128& a) {
    string s; in >> s;
    a = 0;
    if (s == "0") return in;
    for (short i = (s[0] == '-'); i < s.size(); i++)
        a = a * 10 + (s[i] - '0');
    if (s[0] == '-') a *= -1;
    return in;
}

ostream& operator<<(ostream& out, __int128 a) {
    __int128 b = a;
    if (b < 0)
        out << '-', b *= -1;
    string s;
    do {
        s.push_back(b % 10 + '0');
        b /= 10;
    } while (b > 0);
    for (int i = sz(s) - 1; i >= 0; i--)
        out << s[i];
    return out;
}