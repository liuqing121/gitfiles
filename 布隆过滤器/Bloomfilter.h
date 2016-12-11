#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct HashFunc1
{
	size_t operator()(const char* str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
	    {
			hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..      
		}
		    return hash;
	}
};

struct HashFunc2
{
	size_t operator()(const char* str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
				        //hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		}
		return hash;
	}
};

struct HashFunc3
{
	size_t operator()(const char* str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};

struct HashFunc4
{
	size_t operator()(const char* str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
			    hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
	    }
		return hash;
	}
};

struct HashFunc5
{
	size_t operator()(const char* str)
	{
		if (!*str)        
		   return 0;
		register size_t hash = 1315423911;
	    while (size_t ch = (size_t)*str++)
		{
		    hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}
};
//一个字符串类型的布隆过滤器
template<class T=string,class _HashFunc1=HashFunc1,
	    class _HashFunc2=HashFunc2,class _HashFunc3=HashFunc3,
		class _HashFunc4=HashFunc4, class _HashFunc5=HashFunc5>
class BloomFilter
{
public:
	BloomFilter(int num)
		:_range(num * 5)
	{
		_RefBloomfilter.resize(_range);
	}

	void Set(const char* str)
	{
		//分别通过5个字符串hash函数得到5个对应的位置
		size_t hash1 = HashFunc1()(str) %_range; 
		size_t hash2 = HashFunc2()(str) % _range;
		size_t hash3 = HashFunc3()(str) % _range;
		size_t hash4 = HashFunc4()(str) % _range;
		size_t hash5 = HashFunc5()(str) % _range;
		_RefBloomfilter[hash1]++;
		_RefBloomfilter[hash2]++;
		_RefBloomfilter[hash3]++;
		_RefBloomfilter[hash4]++;
		_RefBloomfilter[hash5]++;
		printf("%d,%d,%d,%d,%d", hash1, hash2, hash3, hash4, hash5);  //可以输出5个位置看一看
		cout << endl;
	}

	bool ReSet(const char* str)  //删除
	{
		size_t hash1 = HashFunc1()(str) % _range;
		size_t hash2 = HashFunc2()(str) % _range;
		size_t hash3 = HashFunc3()(str) % _range;
		size_t hash4 = HashFunc4()(str) % _range;
		size_t hash5 = HashFunc5()(str) % _range;
		if (_RefBloomfilter[hash1] == 0 || _RefBloomfilter[hash2] == 0 
			|| _RefBloomfilter[hash3] == 0 || _RefBloomfilter[hash4] == 0 
			|| _RefBloomfilter[hash5] == 0)
			return false;
		_RefBloomfilter[hash1]--;
		_RefBloomfilter[hash2]--;
		_RefBloomfilter[hash3]--;
		_RefBloomfilter[hash4]--;
		_RefBloomfilter[hash5]--;
		return true;
	}

	bool Test(const char* str)  //查找
	{
		size_t hash1 = HashFunc1()(str) % _range;
		size_t hash2 = HashFunc2()(str) % _range;
		size_t hash3 = HashFunc3()(str) % _range;
		size_t hash4 = HashFunc4()(str) % _range;
		size_t hash5 = HashFunc5()(str) % _range;
		if (_RefBloomfilter[hash1]&&
			_RefBloomfilter[hash2] && 
			_RefBloomfilter[hash3] && 
			_RefBloomfilter[hash4] && 
			_RefBloomfilter[hash5])//都不为0则存在
			return true;
		else
			return false;
	}
protected:
	vector<size_t> _RefBloomfilter;  //为了支持删除，直接使用一个size_t 的vector来做引用计数
	size_t _range;
};

void TestBloomfilter()
{
	BloomFilter<> bf(100);
	string url1("http://write.blog.csdn.net/postedit/53088473");
	string url2("http://blog.csdn.net/pointer_y/article/details/52926334");
	string url3("http://blog.csdn.net/pointer_y/article/details/52776595");
	bf.Set(url1.c_str());
	bf.Set(url2.c_str());
	bf.Set(url3.c_str());
	cout << bf.Test(url1.c_str()) << endl;
	bf.ReSet(url1.c_str());
	cout << bf.Test(url1.c_str())<<endl;
}