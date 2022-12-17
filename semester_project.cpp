#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>

using namespace std;

const int N = 100; 

class LongNumber {
public:
	int *a;
	LongNumber()
	{
		a = new int[N];
		for (int i = 0; i < N; ++i)
			a[i] = 0;
	}

	LongNumber(string b)
	{
		int n = b.length();
		if (b[0] != '-')
		{
			a = new int[N];
			for (int i = n - 1; i >= 0; i--)
			{
				a[i] = b[n - i - 1] - '0';
			}
			for (int i = n; i < N; i ++)
			{
				a[i] = 0;
			}

			for (int i = n; i < N; i++)
			{
				a[i] = 0;
			}
		}

		if (b[0] == '-')
		{
			a = new int[N];
			for (int i = n - 2; i >= 0; i--)
			{
				a[i] = b[n - i - 1] - '0';
			}
			for (int i = n; i < N; i ++)
			{
				a[i] = 0;
			}
			a[n - 2] = -a[n - 2];

			for (int i = n - 1; i < N; i++)
			{
				a[i] = 0;
			}
		}
	}

	LongNumber(const LongNumber& second) {
		a = new int[N];
		for (int i = 0; i < N; ++i)
			a[i] = second[i];
	}

    const int LL = 10;

	LongNumber(int noun) {
		a = new int[N];
		long long int ten = 1;
		for (int i = 0; i < LL; ++i) {
			a[i] = (noun / ten) % 10;
			ten = ten * 10;
		}
		for (int i = LL; i < N; ++i)
			a[i] = 0;
	}

	~LongNumber() {
		delete[]a;
	}


	int length() const {
		int i = N - 1;
		while (a[i] == 0 && i > 0) i--;
		return i + 1;
	}

	int& operator[](int i) const {
		return a[i];
	}

	bool operator == (const LongNumber& second) const {
		for (int i = 0; i < N; ++i)
			if (a[i] != second[i]) return false;
		return true;
	}

	bool operator != (const LongNumber& second) const {
		for (int i = 0; i < N; ++i)
			if (a[i] != second[i]) return true;
		return false;
	}

	bool operator > (const LongNumber& second) const {
		for (int i = N - 1; i >= 0; --i) {
			if (a[i] > second[i]) return true;
			if (a[i] < second[i]) return false;
		}
		return false;
	}

	bool operator < (const LongNumber& second) const {
		for (int i = N - 1; i >= 0; --i) {
			if (a[i] > second[i]) return false;
			if (a[i] < second[i]) return true;
		}
		return false;
	}

	bool operator >= (const LongNumber& second) const {
		return *this > second || *this == second;
	}

	bool operator <= (const LongNumber& second) const {
		return *this < second || *this == second;
	}

	friend ostream& operator << (ostream& out, LongNumber& first) {
		int i = N - 1;
		while (i >= 0 && first[i] == 0)
			i--;
		if (i == -1) cout << 0;
		else
			for (int j = i; j >= 0; --j)
				out << first[j];
		return out;
	}

	friend istream& operator >> (istream& sin, LongNumber& first) {
		char c;
		char buff[N];
		int i = 0;
		while (c = getchar()) {
			if (c == ' ' || c == '\0' || c == '\n' || c == '\t')
				break;
			buff[i] = c;
			i++;
		}
		bool b = false;
		for (int j = 0; j < i; ++j) {
			if (buff[i - j - 1] == '-')
				b = true;
			else
				first[j] = (int)buff[i - j - 1] - (int)'0';
		}
		if (b == true)
			first[first.length() - 1] *= -1;
		return sin;
	}

	LongNumber abs()
	{
		LongNumber num_2;
		for (int i = 0; i < N; i++)
		{
			if (a[i] < 0)
			{
				num_2[i] = -a[i];
			}
			else
			{
				num_2[i] = a[i];
			}
		}
		return num_2;
	}

	LongNumber operator + (const LongNumber& second) const {
		LongNumber c, one = *this, two = second;
		int sum;

		if (*this > 0 && second < 0) {
			two[two.length() - 1] *= -1;
			return one - two;
		}
		if (*this < 0 && second > 0) {
			one[one.length() - 1] *= -1;
			return two - one;
		}

		bool b = false;
		if (*this < 0 && second < 0) {
			one[one.length() - 1] *= -1;
			two[two.length() - 1] *= -1;
			b = true;
		}

		for (int i = 0; i < N - 1; ++i) {
			sum = one[i] + two[i] + c[i];
			c[i] = sum % 10;
			c[i + 1] = sum / 10;
		}
		if (b == true)
			c[c.length() - 1] *= -1;
		return c;
	}

	LongNumber operator * (const LongNumber& second) const {
		LongNumber c, one = *this, two = second;
		bool check = false;

		if (*this < 0 && second > 0) {
			one[one.length() - 1] *= -1;
			check = true;
		}
		if (second < 0 && *this > 0) {
			two[two.length() - 1] *= -1;
			check = true;
		}
		if (*this < 0 && second < 0) {
			one[one.length() - 1] *= -1;
			two[two.length() - 1] *= -1;
		}

		for (int i = 0; i < N / 2; ++i)
			for (int j = 0; j < N / 2 - 1; ++j)
				c[i + j] = c[i + j] + one[i] * two[j];

		for (int i = 0; i < N - 1; ++i) {
			c[i + 1] = c[i + 1] + c[i] / 10;
			c[i] = c[i] % 10;
		}

		if (check == true)
			c[c.length() - 1] *= -1;
		return c;
	}

	LongNumber& operator = (const LongNumber& second) {
		if (this == &second) return *this;
		for (int i = 0; i < N; ++i)
			a[i] = second[i];
		return *this;
	}

	LongNumber operator - (const LongNumber& second) const {
		LongNumber c;
		bool choose = false;

		if (*this < LongNumber(0) && second < LongNumber(0)) {
			LongNumber tempfirst = *this;
			LongNumber tempsecond = second;
			tempfirst[length() - 1] *= -1;
			cout << endl <<  tempfirst << endl;
			tempsecond[second.length() - 1] *= 1;
			cout << tempsecond << endl;
			LongNumber Return = tempfirst + tempsecond;
			Return[Return.length() - 1] *= -1;
			return Return;
		}

		if (second < 0 && *this > 0) {
			LongNumber temp = second;
			temp[temp.length() - 1] *= -1;
			LongNumber Return = temp + *this;
			return Return;
		}

		if (second > 0 && *this < 0) {
			LongNumber temp = *this;
			temp[temp.length() - 1] *= -1;
			LongNumber c = temp + second;
			c[c.length() -1] *= -1;
			return c;
		}

		LongNumber one = *this, two = second;
		if (*this < second) {
			swap(one, two);
			choose = true;
		}

		for (int i = 0; i < N - 1; ++i) {
			c[i] = c[i] + 10 + one[i] - two[i];
			c[i + 1] = (c[i] >= 10) ? 0 : -1;
			c[i] = c[i] % 10;
		}

		int i = N - 1;
		while (c[i] != 0) {
			c[i] = 0;
			i--;
		}

		if (choose == true)
			c[c.length() - 1] *= -1;
		return c;
	}

	LongNumber operator -= (const LongNumber& second)
	{
		LongNumber c = *this;
		LongNumber b = second;
		*this = c - second;
		return *this;
	}

    LongNumber operator += (const LongNumber& second)
	{
		LongNumber c = *this;
		LongNumber b = second;
		*this = c + second;
		return *this;
	}

	void LevelUp()
	{
		for (int i = length(); i >= 1; i--)
			a[i] = a[i - 1];
	}

	LongNumber operator / (const LongNumber& second) const
	{
		LongNumber res;
		LongNumber curValue;
		LongNumber one = *this, two = second;

        if (one < LongNumber(0) && two < LongNumber(0))
		{
			one = LongNumber(0) - one;
			two = LongNumber(0) - two;
		}

		bool check = false;

		if (*this < 0 && second > 0) {
			one[one.length() - 1] *= -1;
			check = true;
		}
		if (*this > 0 && second < 0) {
			two[two.length() - 1] *= -1;
			check = true;
		}

		for (int i = one.length() - 1; i >= 0; i--)
		{
			curValue.LevelUp(); 
			curValue[0] = one.a[i];
		
			int x = 0;
			int l = 0, r = 10;
			while (l <= r)
			{
				int m = (l + r) >> 1;
				LongNumber cur = two * m;
				if (cur <= curValue)
				{
					x = m;
					l = m + 1;
				}
				else
					r = m - 1;
			}
			res[i] = x;
			curValue = curValue - two * x;
		}
		
		int pos = length();
		while (pos >= 0 && !res[pos])
			pos--;
		if (check == true)
			res[res.length() - 1] *= -1;
		return res;
	}


	LongNumber operator *= (const LongNumber& second)
	{
		LongNumber c = *this;
		LongNumber b = second;
		*this = c * second;
		return *this;
	}

    LongNumber operator /= (const LongNumber& second)
	{
		LongNumber c = *this;
		LongNumber b = second;
		*this = c / second;
		return *this;
	}

	LongNumber operator % (const LongNumber& second) const {
		return *this - (*this / second) * second;
	} 

    LongNumber prot()
	{
		LongNumber a, b;
		a = *this;
		b = LongNumber(0) - *this;
		*this = b;
		return * this;
	}

	void print()
    {
		int n = 0;
        for (int i = N - 1; i >= 0; i --)
        {
            if (a[i] != 0)
            {
                n = i;
                break;
            }
        }
        for (int i = n; i >= 0; i--)
        {
            cout << a[i];
        }
    }
};

template <typename Q>
class RationalNumber final
{
public:
    Q numerator;
    Q denominator;
    Q find_gcd()
    {
        Q a = numerator.abs();
        Q b = denominator.abs();
        if (a < b) 
        {
            Q c;
            c = a;
            a = b;
            b = c;
        }
        while (a % b != 0)
        {
            a = a % b;
            Q c;
            c = a;
            a = b;
            b = c;
        }
		return b;
    }
    void make_it_standart()
    {
        if(denominator < Q(0))
        {
            numerator = numerator.prot();
            denominator = denominator.prot();
        }
        if (numerator == Q(0))
        {
            denominator = Q(1);
        } 
        else
        {
            Q gcd = find_gcd();
            numerator = numerator / gcd;
            denominator = denominator / gcd;
        }
    }

    RationalNumber operator*=(RationalNumber other)
    {
        numerator *= other.numerator;
        denominator *= other.denominator;
        make_it_standart();
        return *this;
    }

    RationalNumber operator+=(RationalNumber other)
    {
        numerator = numerator * other.denominator + denominator * other.numerator;
        denominator *= other.denominator;
        make_it_standart();
        return *this;
    }

    RationalNumber operator/=(RationalNumber other)
    {
        if (other.numerator > Q(0))
        {
            denominator *= other.numerator;
            numerator *= other.denominator;
        }
        else
        {
            denominator *= other.numerator;
            numerator *= other.denominator;
        }
        make_it_standart();
        return *this;
    }

    RationalNumber& operator-=(RationalNumber& other)
    {
        numerator = numerator * other.denominator - denominator * other.numerator;
        denominator *= other.denominator;
        make_it_standart();
        return *this;
    }

public:
    RationalNumber(Q a, Q b) : numerator(a), denominator(b)
    {
        make_it_standart();
    }
    RationalNumber(Q a) : numerator(a), denominator(Q(1))
    {}

    RationalNumber operator*(RationalNumber other) const
    {
        RationalNumber temp = *this;
        temp *= other;
        return temp;
    }

    RationalNumber operator+(RationalNumber other) const
    {
        RationalNumber temp = *this;
        temp += other;
        return temp;
    }

    RationalNumber operator/(RationalNumber other) const
    {
        RationalNumber temp = *this;
        temp /= other;
        return temp;
    }


    RationalNumber operator-(RationalNumber other) const
    {
        RationalNumber temp = *this;
        temp -= other;
        return temp;
    }

    void print_rational_number()
    {
        cout << numerator << "/" << denominator;
    }
};




template <typename T>
class matrix
{
private:
    vector<vector<RationalNumber<T>>> a;
    int n = 0, m = 0;

public:
    matrix()
    {
        string str, str1, strinit;
        int n1 = 0, m1 = 0, len = 1, startflag = 0;
        vector<RationalNumber<T>> apart;

        cout << "Start input" << endl;

        do
        {
            n1 += 1;
            startflag += 1;
            str.clear();
            apart.clear();
            getline(cin, str, '\n');
            strinit = str;
            if (str.length() != 0)
            {
                m1 = 0;
                str1.clear();
                while (str.find(' ') != -1)
                {
                    m1 = m1 + 1;
                    str1 = str.substr(0, str.find(' '));
                    str = str.substr(str.find(' ') + 1, str.length() - str.find(' '));
                    if (str1.find('/') != -1)
                    {
                        apart.push_back(RationalNumber<T>(T(str1.substr(0, str1.find('/'))), T(str1.substr(str1.find('/') + 1, str1.length() - str1.find('/')))));
                    }
                    else
                        apart.push_back(RationalNumber<T>(T(str1)));
                }

                if (str.find('/') != -1)
                {
                    apart.push_back(RationalNumber<T>(T(str.substr(0, str.find('/'))), T(str.substr(str.find('/') + 1, str.length() - str.find('/')))));
                    str.clear();
                }
                else
                {
                    apart.push_back(RationalNumber<T>(T(str)));
                    str.clear();
                }


                m1 = m1 + 1;
                if (startflag == 1)
                    m = m1;
                else if (m1 != m)
                {
                    while (m1 != m)
                    {
                        m1 = m1 + 1;
                        apart.push_back(RationalNumber<T>(T("0")));
                    }
                    
                }
            }

            a.push_back(apart);
        } while (strinit.length() != 0);
        n = n1 - 1;
        cout << "end of input" << endl << endl;
    };

    matrix(vector<vector<RationalNumber<T>>> b): a(b)
    {
    };

public:
    bool iszero(int b, int c)
    {
        bool flag = true;
        for (int i = b; i < n; i++)
        {
            for (int j = c; j < m; j++)
                if (a[i][j].numerator != T(0))
                {
                    flag = false;
                    break;
                }
        }
        return(flag);
    };
    vector<int> column(int b, int c)
    {
        vector<int> number{ b,c };
        bool flag = false;
        for (int j = c; j < m; j++)
        {
            for (int i = b; i < n; i++)
                if (a[i][j].numerator != T(0))
                {
                    number[0] = i;
                    number[1] = j;
                    flag = true;
                    break;
                }
            if (flag == true)
                break;
        }
        return(number);
    }
    int line()
    {
        int str = n;
        int flag = 0;
        do
        {
            str = str - 1;
            for (int i = 0; i < m-1; i++)
            {
                if (a[str][i].numerator != T(0))
                    flag = 1;

            }
        } while (flag == 0);
        return(str);
    }

    void goback(int stolb, int str ,int end)
    {
        int vedelem;
        for (int j = stolb; j < end; j++)
        {
            if (a[str][j].numerator != T(0))
            {
                vedelem = j;
                break;
            }
        }
        for (int  i = 0; i < str; i++)
        {
            if (a[str][vedelem].numerator != T(0))
            {
                RationalNumber<T> koef = a[i][vedelem] / a[str][vedelem];
                for (int j = stolb; j < m; j++)
                    {
                        a[i][j] = a[i][j] - koef * a[str][j];
                    }
            }
        }
        if (stolb<vedelem)
            goback(stolb, str-1, vedelem);
    }
    
public:
    void forward(int b, int c)
    {
        if (!iszero(b, c))
        {
            swap(a[b], a[column(b, c)[0]]);
            for (int i = b + 1; i < n; i++)
            {
                if (a[i][column(b, c)[1]].numerator != T(0))
                {
                    RationalNumber<T> koef = a[i][column(b, c)[1]] / a[b][column(b, c)[1]];
                    for (int j = 0; j < m; j++)
                    {
                        a[i][j] = a[i][j] - koef * a[b][j];
                    }


                }
            }
            forward(b + 1, c);
        }
    };

    void back()
    {
        int stolb = column(0, 0)[1];
        int str = line();
        goback(stolb, str, m - 1);
    };

    bool operator==(matrix other) const
    {
        int flag = 0;
        if (n != other.n)
            return false;
        else if (m != other.m)
            return false;
        else {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (a[i][j].numerator != other.a[i][j].numerator or a[i][j].denominator != other.a[i][j].denominator)
                    {
                        flag += 1;
                        break;
                    }
                }
                if (flag == 0)
                    break;
            }
                return (flag == 0);
        }
    }

    void print()
    {
        cout << "start input" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                a[i][j].print_rational_number();
                cout << ' ';
            }
            cout << endl;
        }
        cout << "end of input" << endl << endl;
    };
};

int main()
{
	matrix<LongNumber> mat;
	mat.print();
	mat.forward(0, 0);
    mat.back();
	mat.print();
	return 0;
}