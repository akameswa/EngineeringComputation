#include <iostream>


class TextString
{
protected:
	char *str=nullptr;
public:
	TextString();
	TextString(const char incoming[]);
	TextString(const TextString &incoming);
	TextString &operator=(const TextString &incoming);
	~TextString();
	void CleanUp(void);

	size_t size(void) const;
	void push_back(char c);
	void pop_back(void);
	const char *c_str(void) const;
	void set(const char incoming[]);
	void copy_from(const TextString &incoming);
};

TextString::TextString()
{
}
TextString::TextString(const char incoming[])
{
	set(incoming);
}
TextString::TextString(const TextString &incoming)
{
	copy_from(incoming);
}
TextString &TextString::operator=(const TextString &incoming)
{
	copy_from(incoming);
	return *this;
}
TextString::~TextString()
{
	CleanUp();
}
void TextString::CleanUp(void)
{
	delete [] str;
	str=nullptr;
}

size_t TextString::size(void) const
{
	if(nullptr==str)
	{
		return 0;
	}
	else
	{
		int i;
		for(i=0; 0!=str[i]; ++i)
		{
		}
		return i;
	}
}

void TextString::push_back(char c)
{
	auto len=size();
	auto newLen=len+1;

	char *newStr=new char [newLen+1]; // +1 for terminator

	for(int i=0; i<len; ++i)
	{
		newStr[i]=str[i];
	}
	newStr[len]=c;
	newStr[newLen]=0;

	CleanUp();  // Prevent memory leak

	str=newStr;
}

void TextString::pop_back(void)
{
	auto len=size();
	if(0<len)
	{
		auto newLen=len-1;
		char *newStr=new char [newLen+1];
		for(int i=0; i<newLen; ++i)
		{
			newStr[i]=str[i];
		}
		newStr[newLen]=0;

		CleanUp();

		str=newStr;
	}
}

const char *TextString::c_str(void) const
{
	if(nullptr!=str)
	{
		return str;
	}
	return "";
}

void TextString::set(const char incoming[])
{
	if(nullptr==incoming)
	{
		CleanUp();
		return;
	}

	if(incoming!=str)
	{
		int i;
		for(i=0; 0!=incoming[i]; ++i)
		{
		}
		size_t len=i;
		char *newStr=new char [i+1];
		for(int i=0; i<len; ++i)
		{
			newStr[i]=incoming[i];
		}
		newStr[len]=0;

		CleanUp();

		str=newStr;
	}
}

void TextString::copy_from(const TextString &incoming)
{
	set(incoming.c_str());
}


void Test(void)
{
	TextString mecheCopy2,mecheCopy3;
	TextString str;
	str.push_back('C');
	str.push_back('M');
	str.push_back('U');
	std::cout << str.c_str() << "\n";

	TextString meche("Mechanical Engineering");
	std::cout << meche.c_str() << "\n";

	TextString mecheCopy(meche);
	std::cout << mecheCopy.c_str() << "\n";

	mecheCopy3=mecheCopy2=meche;
	std::cout << mecheCopy2.c_str() << "\n";
	std::cout << mecheCopy3.c_str() << "\n";

	for(int i=0; i<5; ++i)
	{
		mecheCopy3.pop_back();
	}

	std::cout << mecheCopy3.c_str() << "\n";
}

int main(void)
{
	std::cout << "IN\n";
	Test();
	std::cout << "OUT\n";
	return 0;
}
