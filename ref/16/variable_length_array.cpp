#include <iostream>


template <class T>
class VariableArray
{
private:
	unsigned int len=0;
	T *dat=nullptr;

	VariableArray(const VariableArray<T> &incoming);
	VariableArray<T> &operator=(const VariableArray<T> &incoming);
public:
	VariableArray();
	~VariableArray();
	void clear(void);

	void push_back(const T &incoming);
	void pop_back(void);

	void copy_from(const VariableArray<T> &incoming);

	const T *data(void) const;
	T *data(void);
};

template <class T>
VariableArray<T>::VariableArray()
{
}

template <class T>
VariableArray<T>::~VariableArray()
{
	clear();
}

template <class T>
void VariableArray<T>::clear(void)
{
	len=0;
	if(nullptr!=dat)
	{
		delete [] dat;
	}
	dat=nullptr;
}

template <class T>
void VariableArray<T>::push_back(const T &incoming)
{
	int newLen=len+1;

	T *newData=new T [newLen];
	for(int i=0; i<len; ++i)
	{
		newData[i]=dat[i];
	}
	newData[len]=incoming;

	clear();

	len=newLen;
	dat=newData;
}

template <class T>
void VariableArray<T>::pop_back(void)
{
	if(0<len)
	{
		int newLen=len-1;

		if(0==newLen)
		{
			clear();
		}
		else
		{
			T *newData=new T [newLen];
			for(int i=0; i<newLen; ++i)
			{
				newData[i]=dat[i];
			}

			clear();

			len=newLen;
			dat=newData;
		}
	}
}

template <class T>
void VariableArray<T>::copy_from(const VariableArray<T> &incoming)
{
	if(this!=&incoming)
	{
		clear();

		if(0<incoming.len)
		{
			this->len=incoming.len;
			this->data=new T [incoming.len];
			for(int i=0; i<incoming.len; ++i)
			{
				this->data[i]=incoming.data[i];
			}
		}
	}
}

template <class T>
const T *VariableArray<T>::data(void) const
{
	return dat;
}

template <class T>
T *VariableArray<T>::data(void)
{
	return dat;
}




class TextString : public VariableArray<char>
{
public:
	const char *data(void) const;
	char *data(void);

	void push_back(char c);
	void pop_back(void);
};

const char *TextString::data(void) const
{
	auto dat=VariableArray<char>::data();
	if(nullptr==dat)
	{
		return "";
	}
	return dat;
}
char *TextString::data(void)
{
	auto dat=VariableArray<char>::data();
	if(nullptr==dat)
	{
		return "";
	}
	return dat;
}
void TextString::push_back(char c)
{
	VariableArray<char>::pop_back();
	VariableArray<char>::push_back(c);
	VariableArray<char>::push_back(0);
}
void TextString::pop_back(void)
{
	VariableArray<char>::pop_back();
	VariableArray<char>::pop_back();
	VariableArray<char>::push_back(0);
}




int main(void)
{
	TextString a;
	a.push_back('C');
	a.push_back('M');
	a.push_back('U');
	a.push_back('\n');

	std::cout << a.data();

	return 0;
}
