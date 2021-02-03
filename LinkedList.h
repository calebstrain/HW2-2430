#pragma once
#include <iostream>
#include <fstream>

template<class T>
class Node
{
private:
	T data;
	Node<T>* next;
	Node<T>(Node<T>* next, T data)
	{
		this->next = next;
		this->data = data;
	}
	template<class T> friend class LinkedList;
	
};

template<class T>
class LinkedList
{
private:
	Node<T>* head;
	Node<T>* tail;
	int size;
	void deallocate() 
	{
		Node<T>* i = head;
		Node<T>* temp;
		while (i != NULL)
		{
			temp = i->next;
			delete i;
			i = temp;
		}
	}
	void divideList(Node<T>*, Node<T>*&);
	void recMergeSort(Node<T>*&, bool);
	Node<T>* mergeListByAlpha(Node<T>*, Node<T>*);
	Node<T>* mergeListByLength(Node<T>*, Node<T>*);
public:
	LinkedList();
	~LinkedList();
	void insert(T);
	void insertByAlpha(T);
	void insertByLength(T);
	void insertEnd(T);
	void remove(T);
	void add(int, T);
	void mergeSort(bool);
	void output(std::ofstream&);

};

template<class T>
void LinkedList<T>::divideList(Node<T>* first1, Node<T>*& first2)
{
	Node<T>* middle;
	Node<T>* current;

	if (first1 == NULL)
		first2 = NULL;
	else if (first1->next == NULL)
		first2 = NULL;
	else
	{
		middle = first1;
		current = first1->next;

		if (current != NULL)
			current = current->next;
		while (current != NULL)
		{
			middle = middle->next;
			current = current->next;
			if (current != NULL)
				current = current->next;
		}

		first2 = middle->next;
		middle->next = NULL;
	}
}

template<class T>
void LinkedList<T>::recMergeSort(Node<T>*& head, bool f)
{
	Node<T>* otherHead;
	if (head != NULL)
		if (head->next != NULL)
		{
			divideList(head, otherHead);
			recMergeSort(head, f);
			recMergeSort(otherHead, f);
			if (f)
				head = mergeListByAlpha(head, otherHead);
			else
				head = mergeListByLength(head, otherHead);
		}
}

template<class T>
Node<T>* LinkedList<T>::mergeListByAlpha(Node<T>* first1, Node<T>* first2)
{
	Node<T>* lastSmall, * newHead;
	if (first1 == NULL)
		return first2;
	else if (first2 == NULL)
		return first1;
	else
	{
		if (first1->data < first2->data)
		{
			newHead = first1;
			first1 = first1->next;
			lastSmall = newHead;
		}
		else
		{
			newHead = first2;
			first2 = first2->next;
			lastSmall = newHead;
		}
		while (first1 != NULL && first2 != NULL)
		{
			if (first1->data < first2->data)
			{
				lastSmall->next = first1;
				lastSmall = lastSmall->next;
				first1 = first1->next;
			}
			else
			{
				lastSmall->next = first2;
				lastSmall = lastSmall->next;
				first2 = first2->next;
			}
		}
		if (first1 == NULL)
			lastSmall->next = first2;
		else
			lastSmall->next = first1;

		return newHead;
	}
}

template<class T>
Node<T>* LinkedList<T>::mergeListByLength(Node<T>* first1, Node<T>* first2)
{
	Node<T>* lastSmall, * newHead;
	if (first1 == NULL)
		return first2;
	else if (first2 == NULL)
		return first1;
	else
	{
		if (first1->data.length() < first2->data.length())
		{
			newHead = first1;
			first1 = first1->next;
			lastSmall = newHead;
		}
		else
		{
			newHead = first2;
			first2 = first2->next;
			lastSmall = newHead;
		}
		while (first1 != NULL && first2 != NULL)
		{
			if (first1->data.length() < first2->data.length())
			{
				lastSmall->next = first1;
				lastSmall = lastSmall->next;
				first1 = first1->next;
			}
			else
			{
				lastSmall->next = first2;
				lastSmall = lastSmall->next;
				first2 = first2->next;
			}
		}
		if (first1 == NULL)
			lastSmall->next = first2;
		else
			lastSmall->next = first1;

		return newHead;
	}
}

template<class T>
LinkedList<T>::LinkedList()
{
	head = tail = NULL;
	size = 0;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	deallocate();
}

template<class T>
void LinkedList<T>::insert(T data)
{
	Node<T>* n = new Node<T>(head, data);
	if (head == NULL)
		tail = n;
	head = n;
	size++;
}

template<class T>
void LinkedList<T>::insertByAlpha(T data)
{
	if (head == NULL || data < head->data)
	{
		Node<T>* n = new Node<T>(head, data);
		head = tail = n;
	}
	else
	{
		Node<T>* curr = head;
		while (curr->next != NULL && !(data < curr->next->data && data >= curr->data))
		{
			curr = curr->next;
		}
		if (curr->next == NULL)
		{
			Node<T>* n = new Node<T>(NULL, data);
			curr->next = n;
			tail = n;
		}
		else
		{
			Node<T>* n = new Node<T>(curr->next, data);
			curr->next = n;
		}
	}
	size++;
}

template<class T>
void LinkedList<T>::insertByLength(T data)
{
	if (head == NULL || data.length() < head->data.length())
	{
		Node<T>* n = new Node<T>(head, data);
		head = tail = n;
	}
	else
	{
		Node<T>* curr = head;
		while (curr->next != NULL && !(data.length() < curr->next->data.length() && data.length() >= curr->data.length()))
		{
			curr = curr->next;
		}
		if (curr->next == NULL)
		{
			Node<T>* n = new Node<T>(NULL, data);
			curr->next = n;
			tail = n;
		}
		else
		{
			Node<T>* n = new Node<T>(curr->next, data);
			curr->next = n;
		}
	}
	size++;
}

template<class T>
void LinkedList<T>::insertEnd(T data)
{
	Node<T>* n = new Node<T>(NULL, data);
	if (head == NULL)
		head = n;
	else
		tail->next = n;
	tail = n;
	size++;
}

template<class T>
void LinkedList<T>::remove(T str2)
{
	if (head != NULL)
	{
		Node<T>* curr = head;
		Node<T>* temp;
		std::string s;

		while (curr->next != NULL)
		{
			s = curr->next->data;
			if (s.find(str2) != std::string::npos)
			{
				temp = curr->next->next;
				delete curr->next;
				curr->next = temp;
				if (curr->next == NULL)
					tail = curr;
				size--;
			}
			else
				curr = curr->next;
		}

		s = head->data;
		if (s.find(str2) != std::string::npos)
		{
			temp = head->next;
			delete head;
			head = temp;
			size--;
		}
	}
}

template<class T>
void LinkedList<T>::add(int loc, T data)
{
	if (loc > size)
		return;
	if (loc == 0 || size == 0)
		insert(data);
	else if (loc == size)
		insertEnd(data);
	else
	{
		Node<T>* curr = head;
		for (int i = 1; i <= loc; i++)
		{
			if (i == loc)
			{
				Node<T>* n = new Node<T>(curr->next, data);
				curr->next = n;
				break;
			}
			curr = curr->next;
		}
		size++;
	}
}

template<class T>
void LinkedList<T>::mergeSort(bool f)
{
	recMergeSort(head, f);
	if (head == NULL)
		tail = NULL;
	else
	{
		tail = head;
		while (tail->next != NULL)
			tail = tail->next;
	}
}

template<class T>
void LinkedList<T>::output(std::ofstream& ofs)
{
	Node<T>* curr = head;
	while (curr != NULL)
	{
		ofs << curr->data << std::endl;
		curr = curr->next;
	}
}