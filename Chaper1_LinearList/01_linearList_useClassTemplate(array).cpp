#include <iostream>
#include <exception>
#include <algorithm>

using namespace std;

//用于改变一维数组的长度
template<class T>
void changeLength1D(T* a,int oldlength,int newlength)
{
	if (newlength > 0)
	{
		T* extraBlocks = new T[newlength];    //用新长度先分配一块额外空间
		int copylen = min(oldlength, newlength);    //确认要拷贝的长度
		copy(a, a + copylen, extraBlocks);    //老数组的数据拷贝到新分配的空间
		delete []a;    //删除老数组的指针
		a = extraBlocks;    //指针指向新区域
	}
	else
	{
		throw 2;
	}

}

//抽象基类
template<class T>
class LinearList
{
public:
	virtual ~LinearList() {};
	virtual bool empty() const = 0;
	virtual T& get(int index) const = 0;
	virtual int indexof(const T& element) const = 0;
	virtual void erase(int index) const = 0;
	virtual void insert(const int index, const T& element) = 0;
	virtual void output() const = 0;

};

//数组类定义
template<class T>
class arraylist : LinearList<T>
{
public:
	arraylist(int initialCapacity = 10);
	arraylist(const arraylist<T>&);
	~arraylist() { delete[]element; }
	bool empty() const { return listSize == 0; }
	int size() const{ return listSize; }
	T& get(int index) const;
	int indexof(const T& element) const;
	void erase(int index) const;
	void insert(const int index, const T& element);
	void output() const;
	
	//新定义的方法
	int capacity()const { return arrayLength; }

protected:
	void checkIndex(int index)const;
	T* element;
	int arrayLength;
	int listSize;
};

//数组类实现
template<class T>
arraylist<T>::arraylist(int initialCapacity)    //默认构造函数，初始容量默认值为10
{
	if (initialCapacity < 1)
	{
		throw 0;    //抛出的异常用整形数字处理
	}
	else
	{
		//do nothing
	}

	arrayLength = initialCapacity;
	element = new T[arrayLength];    //分配数组空间
	listSize = 0;
}

template<class T>
arraylist<T>::arraylist(const arraylist<T>& theList)    //复制构造函数
{
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];    
	copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arraylist<T>::checkIndex(int index)const    //检查下标
{
	if (index < 0 || index >= listSize)
	{
		throw 1;
	}
	else
	{
		//do nothing
	}
}

template<class T>
T& arraylist<T>::get(int index) const    //获取某下标的元素
{
	checkIndex(index);
	return element[index];
}

template<class T>
int arraylist<T>::indexof(const T& theElement) const    //获取某元素的下标
{
	int foundindex = (int)(find(element, element + listSize, theElement) - element);

	if (foundindex == listSize)
		return -1;
	else return foundindex;
}

template<class T>
void arraylist<T>::erase(int index) const
{
	checkIndex(index);

	//从index+1开始，所有元素左移一格
	copy(element + index + 1, element + listSize, element + index);

	int sizeTemp = listSize;
	sizeTemp--;
	element[--sizeTemp].~T();    //调用析构函数删除元素

}

template<class T>
void arraylist<T>::insert(const int index, const T& theElement)    //特定位置插入元素
{
	if (index < 0 || index > listSize)
	{
		throw 1;
	}
	else
	{
		//do nothing
	}

	//数组长度达到容量，容量加倍
	if (listSize == arrayLength)
	{
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	else
	{
		//do nothing
	}

	copy_backward(element + index, element + listSize, element + listSize + 1);
	element[index] = theElement;
	listSize++;
}

template<class T>
void arraylist<T>::output() const
{
	for (int i = 0; i < listSize; i++)
	{
		cout << element[i] << " ";
	}
	cout << endl;
}
