#include <iostream>


class TextStringBase
{
private:
	char *str=nullptr;
protected:
	TextStringBase();
	~TextStringBase();
	void SetPointer(char *str);
	char *GetPointer(void);
	const char *GetPointer(void) const;
public:
	void CleanUp();
};

TextStringBase::TextStringBase()
{
}

TextStringBase::~TextStringBase()
{
	CleanUp();
}

void TextStringBase::CleanUp()
{
	delete [] str;
	str=nullptr;
}

void TextStringBase::SetPointer(char *incoming)
{
	str=incoming;
}

char *TextStringBase::GetPointer(void)
{
	return str;
}

const char *TextStringBase::GetPointer(void) const
{
	return str;
}



class TextString : public TextStringBase
{
public:
	TextString();
	TextString(const char incoming[]);
	TextString(const TextString &incoming);
	TextString &operator=(const TextString &incoming);
	~TextString();

	size_t size(void) const;
	void push_back(char c);
	void pop_back(void);
	const char *c_str(void) const;
	void set(const char incoming[]);
	void copy_from(const TextString &incoming);

	void Print(void) const;
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

size_t TextString::size(void) const
{
	auto str=GetPointer();
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

	auto *str=GetPointer();
	for(int i=0; i<len; ++i)
	{
		newStr[i]=str[i];
	}
	newStr[len]=c;
	newStr[newLen]=0;

	CleanUp();  // Prevent memory leak

	SetPointer(newStr);
}

void TextString::pop_back(void)
{
	auto len=size();
	if(0<len)
	{
		auto newLen=len-1;
		auto *str=GetPointer();
		char *newStr=new char [newLen+1];
		for(int i=0; i<newLen; ++i)
		{
			newStr[i]=str[i];
		}
		newStr[newLen]=0;

		CleanUp();

		SetPointer(newStr);
	}
}

const char *TextString::c_str(void) const
{
	auto str=GetPointer();
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

	if(incoming!=GetPointer())
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

		SetPointer(newStr);
	}
}

void TextString::copy_from(const TextString &incoming)
{
	set(incoming.c_str());
}

void TextString::Print(void) const
{
	std::cout << c_str();
}

void Test(void)
{
	TextString mecheCopy2,mecheCopy3;
	TextString str;
	str.push_back('C');
	str.push_back('M');
	str.push_back('U');
	str.Print();
	std::cout << "\n";

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
