#pragma once

#pragma warning(disable:4996)
#include<cassert>
#include<Windows.h>
#include<string>
#include<iostream>
#include"Huffman.hpp"
typedef long long type;
struct weight    //权值里应该包含字符出现的次数以及对应的字符和Huffman编码
{
	unsigned char _ch;
	type _count;
	string _code;

	weight(type count = 0)
		: _ch(0)
		,_count(count)
		, _code("")
	{}
	weight operator+(const weight& w)
	{
		type tmp = _count + w._count;
		return weight(tmp);
	}
	bool operator<(const weight& w)
	{
		return _count < w._count;
	}
	bool operator!=(const weight& w)
	{
		return !(_count == w._count);
	}

};

class HuffmanPress
{
public:
	HuffmanPress()
	{
		for (int i = 0; i < 256; i++)
		{
			_infos[i]._ch = (unsigned char)i;
		}
	}

	bool FilePress(const char* filename)
	{
		//统计出每个字符出现的次数。
		FILE* fOut = fopen(filename, "rb");   
		assert(fOut);
		int ch = fgetc(fOut);
		type charcount = 0;  //统计出字符出现的总次数
		while (ch != EOF)
		{
			if (feof(fOut))
				break;
			_infos[ch]._count++;
			ch = fgetc(fOut);
			charcount++;
		}
		weight invalid(0);
		HuffmanTree<weight> hf(_infos, 256,invalid);    //用得到的权重数组构建一个Huffman树
		HuffmanTreeNode<weight>* root = hf.GetRoot();
		//得到Huffman编码
		string code;
		_GetCodeR(root, code);
		//开始压缩,创建压缩后的文件
		string CompressFilename = filename;
		CompressFilename += ".huffman";
		FILE* fIn = fopen(CompressFilename.c_str(), "wb");
		assert(fIn);
		//统计完次数使得文件指针指向了最后，所以需要使指针指向文件头
		fseek(fOut, 0, SEEK_SET);
		//向压缩文件里写入Huffman编码
		int pos = 0;
		char value = 0;
		int ch1 = fgetc(fOut);
		while (ch1 != EOF)
		{
			if (feof(fOut))
				break;
			string& code = _infos[ch1]._code;
			for (size_t i = 0; i < code.size(); i++)
			{
				value <<= 1;
				if (code[i] == '1')  //得到二进制的1
				{
					value |= 1;
				}
				if (++pos == 8)   //满8位写入文件
				{
					fputc(value, fIn);
					value = 0;
					pos = 0;
				}
			}
			
			ch1 = fgetc(fOut);
		}
		if (pos)    //最后的编码不满足一个字节
		{
			value =value<<(8 - pos);
			fputc(value, fIn);
		}
		//将字符和字符出现的次数写进配置文件，文件解压时会用到
		string ConfigFilename = filename;
		ConfigFilename += ".config";
		FILE* fConfig = fopen(ConfigFilename.c_str(), "wb");
		assert(fConfig);
		char countStr[20];  //字符出现的次数
		//先把所有字符出现的总次数写进配置文件，为防止超过int范围，charcount使用的是long long 所以要分两步写入
		itoa(charcount >> 32, countStr, 10);  //转换高位
		fputs(countStr, fConfig);  //写入
		fputc('\n', fConfig);
		itoa(charcount & 0Xffffffff, countStr, 10); //转换低位
		fputs(countStr, fConfig);  //写入
		fputc('\n', fConfig);
		for (int i = 0; i < 256; i++)
		{
			string put;
			if (_infos[i]!=invalid)
			{
				fputc(_infos[i]._ch,fConfig);//必须先把ch放进去，如果把ch作为string的字符最后转换为C的字符，会导致'\0'没有处理
				put.push_back(',');
				itoa(_infos[i]._count, countStr, 10);
				put += countStr;
				fputs(put.c_str(), fConfig);
				fputc('\n', fConfig);
			}
		}
		fclose(fOut);
		fclose(fIn);
		fclose(fConfig);
		return true;
	}
	bool FileUncompress(char* filename)  //这里给的是压缩文件名
	{
		//1.读取配置文件
		string ConfigFilename = filename;
		int count = ConfigFilename.rfind('.');
		ConfigFilename = ConfigFilename.substr(0, count);
		string UnCompressname = ConfigFilename + ".unpress"; 
		FILE* fUnCompress = fopen(UnCompressname.c_str(), "wb"); //创建解压缩文件
		ConfigFilename += ".config";
		FILE* fconfig = fopen(ConfigFilename.c_str(),"rb");
		assert(fconfig);
		assert(fUnCompress);
		FILE* fpress = fopen(filename, "rb");  //打开压缩好的文件
		assert(fpress);

		type charcount = 0; //先读出字符出现的总次数
		string line;
		_ReadLine(fconfig,line);
		charcount = atoi(line.c_str());
		charcount <<= 32;   
		line.clear();
		_ReadLine(fconfig, line);
		charcount += atoi(line.c_str());
		line.clear();
		while (_ReadLine(fconfig,line))  //文件结束时feof会返回0
		{
			if (!line.empty())
			{
				char ch = line[0];
				_infos[(unsigned char)ch]._count = atoi(line.substr(2).c_str());
				line.clear();
			}
			else  //若读到一个空行，对应的字符为换行符
			{
				line += '\n';
			}
		}
		//2.再次构建Huffman树
		weight invalid(0);
		HuffmanTree<weight> hf(_infos, 256, invalid);    //用得到的权重数组构建一个Huffman树
		HuffmanTreeNode<weight>* root = hf.GetRoot();
		HuffmanTreeNode<weight>* cur = root;
		char ch = fgetc(fpress);
		int pos = 8;
		while (1)
		{
			--pos;
			if ((ch >> pos) & 1)
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}

			if (cur->_left == NULL&&cur->_right == NULL)
			{
				fputc(cur->_weight._ch, fUnCompress);
				cur = root;   //再次从根节点遍历
				charcount--;
			}
			if (pos == 0)
			{
				ch = fgetc(fpress);
				pos = 8;
			}
			if (charcount == 0)  //不读取压缩时为了凑够一个字节而加进去的比特位
				break;   
		}

		fclose(fconfig);
		fclose(fpress);
		fclose(fUnCompress);
		return true;
	}

protected:
	bool _ReadLine(FILE* filename,string& line)
	{
		assert(filename);
		if (feof(filename))
			return false;
		unsigned char ch = fgetc(filename);

		while (ch != '\n')
		{
			line += ch;
			ch = fgetc(filename);

			if (feof(filename))
				//break;
				return false;
		}
		return true;
	}

	void _GetCodeR(HuffmanTreeNode<weight>* root, string code)
	{
		if (NULL == root)
			return;
		if (root->_left == NULL&& root->_right == NULL)
		{
			_infos[root->_weight._ch]._code = code;
		
		}
		_GetCodeR(root->_left, code + '0');
		_GetCodeR(root->_right, code + '1');

	}
private:
	weight _infos[256];
};

void TestCompress()
{
	HuffmanPress hft;
	int begin = GetTickCount();
//	hft.FilePress("test1.txt");
	//hft.FilePress("git.txt");
//	hft.FilePress("1.jpg");
//	hft.FilePress("8.pdf");
	//hft.FilePress("Input.BIG");
	hft.FilePress("listen.mp3");
	int end = GetTickCount();
	cout << end-begin << endl;
}

void TestUnCompress()
{
	HuffmanPress hf;
	int begin = GetTickCount();
//	hf.FileUncompress("test1.txt.huffman");
//	hf.FileUncompress("1.jpg.huffman");
//	hf.FileUncompress("git.txt.huffman");
//	hf.FileUncompress("8.pdf.huffman");
	//hf.FileUncompress("Input.BIG.huffman");
	hf.FileUncompress("listen.mp3.huffman");
	int end = GetTickCount();
	cout << end - begin << endl;
}