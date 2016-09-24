#include <iostream>
#include <string>
#include <memory>
using namespace std;

struct Point
{
	Point(int a, int b) : x(a), y(b) { }
	int x, y;
};

template<class T>
class U_Ptr
{
private:
	template <class T>
	friend class SmartPtr;
	U_Ptr(T *p) :ptr(p), count(1) { }
	~U_Ptr() { delete ptr; }

	int count;
	T *ptr;
};

template<class T>
class SmartPtr
{
public:
	SmartPtr(T *ptr) :rp(new U_Ptr<T>(ptr)) { }

	SmartPtr(const SmartPtr &sp) :rp(sp.rp) { ++rp->count; }

	SmartPtr& operator=(const SmartPtr& rhs)
	{
		++rhs.rp->count;
		if (--rp->count == 0)
			delete rp;
		rp = rhs.rp;
		return *this;
	}
	const T &operator*() const
	{
		return *(rp->p);
	}
	T &operator*()
	{
		return *(rp->p);
	}
	T *operator->()
	{
		return rp->p;
	}
	const T *operator->() const
	{
		return rp->p;
	}
	~SmartPtr()
	{
		if (--rp->count == 0)
			delete rp;
		else
			cout << "还有" << rp->count << "个指针指向基础对象" << endl;
	}

private:
	U_Ptr<T> *rp;
};


int main()
{
	Point *p = new Point(19, 10);
	SmartPtr<Point> s(new Point(19, 10));
	SmartPtr<Point> s2 = s;
	SmartPtr<Point> s4 = s2;

	SmartPtr<Point> s3(new Point(131, 345));

	cout << s2->x << "\t" << s2->y << endl;
	s2 = s3;
	cout << s2->x << "\t" << s2->y << endl;

	cout << (*s2).x << "\t" << (*s2).y << endl;

	SmartPtr<string> str(new string("abcde"));
	SmartPtr<string> sss = str;
	cout << (*sss).length() << endl;

	shared_ptr<string> st(new string("wtf"));
	cout << (*st).length() << endl;
	return 0;
}
