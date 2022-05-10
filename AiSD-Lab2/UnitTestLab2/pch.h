#include <iostream>
using namespace std;

class HaffmanList {
private:
	class List {
	public:
		char key;
		int value;
		bool inTree;
		List* next;
	};
public:

	List* head;
	List* tail;
	bool twoElements;
	char getKey;
	HaffmanList()
	{
		head = NULL;
		tail = NULL;
	}
	int get_size()
	{
		List* list = head;
		int size = 0;
		while (list != tail->next)
		{
			size++;
			list = list->next;
		}
		return size;
	}
	void stringProcessing(int length, string test)
	{
		List* list = new List;
		twoElements = 1;
		for (int i = 0; i < length; i++)
		{
			list = head;
			if (list == NULL)
			{
				list = new List;
				list->value = 0;
				list->key = test[i];
				list->next = NULL;
				head = tail = list;
				for (int j = i; j < length; j++)
				{
					if (list->key == test[j])
					{
						list->value++;
					}
				}
			}
			else
			{
				bool isOnTheList = 0; // the key is in the list
				while (list != tail->next)
				{
					if (list->key == test[i])
					{
						isOnTheList = 1;
						break;
					}
					else
					{
						isOnTheList = 0;
					}
					list = list->next;
				}
				if (isOnTheList == 0)
				{
					list = tail;
					list->next = new List;
					list = list->next;
					list->key = test[i];
					list->value = 0;
					tail = list;
					for (int j = i; j < length; j++)
					{
						if (list->key == test[j])
						{
							list->value++;
						}
					}
				}
			}
		}
	}

	int HaffmanMin() // search element with min weigth
	{
		List* min_element = head;
		List* list = head;
		int minElement = 0;
		min_element = head;
		List* prev = head; // previous element of min
		List* remember = head;
		while (list != tail->next)
		{
			if (min_element->value > list->value)
			{
				remember = list;
				min_element = list;
			}
			list = list->next;
		}
		list = head;
		while (list->next != NULL)
		{
			if (remember == head)
			{
				head = list->next;
				if (remember == tail)
				{
					tail = list;
					tail->next = NULL;
					break;
				}
				break;
			}
			if (list->next == remember)
			{
				if (remember == tail)
				{
					tail = list;
					tail->next = NULL;
					break;
				}
				else
				{
					prev = list;
					list = list->next;
					prev->next = list->next;
					break;
				}
			}
			list = list->next;
		}

		minElement = min_element->value;
		getKey = min_element->key;
		return minElement;
	}
	void add(int value)
	{
		int length = 16;
		List* list = tail;
		if (get_size() == 1 && twoElements == 0)
		{
			head->value = value;
			tail = head;
		}
		else {
			if (get_size() == 1)
				twoElements = 0;
			list->next = new List;
			list = list->next;
			list->value = value;
			list->key = NULL;
			list->inTree = 1;
			list->next = NULL;
			tail = list;
		}
	}
	void print()
	{
		List* list = head;
		while (list != NULL)
		{
			cout << list->value << " ";
			list = list->next;
		}
	}
	void clear()
	{
		List* list = head;
		while (head != tail)
		{
			head = list->next;
		}
		head = NULL;
		tail = NULL;
	}
};


class AlgorithmHaffman
{
private:
	class Node
	{
	public:
		string key;
		int value;
		Node* next;
		Node* left;
		Node* right;
		Node* parent;
		char letter;
	};
	Node* root;
	Node* vertex;
	void HaffmanCoding()
	{
		Node* buffer = root;
		while (buffer != NULL)
		{
			buffer->key = "";
			buffer->right->key = "";
			buffer->left->key = "";
			buffer = buffer->next;
		}
		buffer = vertex;
		buffer->key = "";
		while (1)
		{
			if (buffer != NULL && buffer->right != NULL && buffer->right->key == "")
			{
				buffer->right->key = buffer->key + "1";
				buffer = buffer->right;
			}
			else
			{
				if (buffer != NULL && buffer->left != NULL && buffer->left->key == "")
				{
					buffer->left->key += buffer->key + "0";
					buffer = buffer->left;
				}
				else
				{
					if (buffer != NULL) {
						buffer = buffer->parent;
						if (buffer->left->key != "" && buffer->right->key != "")
						{
							buffer = buffer->parent;
							if (buffer == vertex && buffer->right->key != "" && buffer->left->key != "")
							{
								break;
							}
						}
					}
					else { break; }
				}
			}
		}
	}
	Node* findAndGet(Node* node, int value)
	{
		while (node != NULL)
		{
			if (node->value == value && node->parent == NULL)
			{
				return node;
			}
			node = node->next;
		}
	}
	bool find(Node* node, int value)
	{
		int count = 0;
		while (node != NULL)
		{
			if (node->value == value && node->parent == NULL)
			{
				count++;
			}
			node = node->next;
		}
		if (count != 0)
		{
			return 1;
		}
		else return 0;
	}

public:
	AlgorithmHaffman()
	{
		root = NULL;
		vertex = NULL;
	}

	void print()
	{
		Node* buffer = root;
		int i = 1;
		while (buffer != NULL)
		{
			cout << i << ". " << buffer->value << endl;
			if (buffer->parent != NULL)
				cout << "Parent: " << buffer->parent->value << endl;
			else cout << "Parent: NULL" << endl;
			cout << "Key: " << buffer->key << endl;
			cout << "Left: " << buffer->left->value << endl;
			cout << "Right: " << buffer->right->value << endl;
			if (buffer->left->letter != ' ')
			{
				cout << "Left letter: " << buffer->left->letter << endl;
			}
			if (buffer->right->letter != ' ')
			{
				cout << "Right letter: " << buffer->right->letter << endl;
			}
			i++;
			buffer = buffer->next;
		}
	}
	void printTableOfFrequencyAndCodes()
	{
		Node* buffer = root;
		while (buffer != vertex)
		{
			if (buffer->left->letter != NULL)
			{
				cout << buffer->left->letter << "    ";
			}
			if (buffer->right->letter != NULL)
			{
				cout << buffer->right->letter << "    ";
			}
			buffer = buffer->next;
		}
		buffer = root;
		cout << endl;
		while (buffer != vertex)
		{
			if (buffer->left->letter != NULL)
			{
				cout << buffer->left->value << "    ";
			}
			if (buffer->right->letter != NULL)
			{
				cout << buffer->right->value << "    ";
			}
			buffer = buffer->next;
		}
		buffer = root;
		cout << endl;
		while (buffer != vertex)
		{
			if (buffer->left->letter != NULL)
			{
				cout << buffer->left->key << " ";
			}
			if (buffer->right->letter != NULL)
			{
				cout << buffer->right->key << " ";
			}
			buffer = buffer->next;
		}
		cout << endl;
	}

	string resultOfCoding(string test)
	{
		Node* buffer;
		string codedString = "";
		for (int i = 0; i < test.length(); i++)
		{
			buffer = root;
			while (buffer->right->letter != test[i] || buffer->left->letter != test[i])
			{
				if (buffer->left->letter == test[i])
				{
					codedString += buffer->left->key;
					codedString += " ";
					break;
				}
				if (buffer->right->letter == test[i])
				{
					codedString += buffer->right->key;
					codedString += " ";
					break;
				}
				buffer = buffer->next;
				if (buffer == NULL)
				{
					break;
				}
			}
		}
		return codedString;
	}
	string resultOfDecoding(string test)
	{
		Node* buffer;
		string helpDecodedString = "";
		string decodedString = "";

		for (int i = 0; i < test.length(); i++)
		{
			buffer = root;
			while (test[i] != ' ')
			{
				helpDecodedString += test[i];
				i++;
			}
			while (buffer->left->letter != ' ' || buffer->right->letter != ' ')
			{
				if (buffer->left->key == helpDecodedString)
				{
					decodedString += buffer->left->letter;
					helpDecodedString = "";
					break;
				}
				else
				{
					if (buffer->right->key == helpDecodedString)
					{
						decodedString += buffer->right->letter;
						helpDecodedString = "";
						break;
					}
					else
					{
						buffer = buffer->next;
					}
				}

			}

		}
		return decodedString;
	}
	void Algorithm(string test, int length)
	{
		HaffmanList list;
		list.stringProcessing(length, test);

		while (list.head != list.tail && list.get_size() != 1)
		{
			int minElement = list.HaffmanMin();
			char Key1 = list.getKey;
			int minElement2 = list.HaffmanMin();
			char Key2 = list.getKey;
			Node* buffer = root;
			Node* prev = buffer;
			if (root == NULL)
			{
				buffer = new Node;
				buffer->value = minElement + minElement2;
				buffer->next = NULL;
				buffer->letter = NULL;
				buffer->left = new Node;
				buffer->right = new Node;
				buffer->parent = NULL;
				buffer->left->value = minElement;
				buffer->left->letter = Key1;
				buffer->right->value = minElement2;
				buffer->right->letter = Key2;
				buffer->left->parent = buffer->right->parent = buffer;
				list.add(buffer->value);
				root = vertex = buffer;
			}
			else {
				buffer = prev = root;
				while (buffer != NULL)
				{
					prev = buffer;
					buffer = buffer->next;

				}
				buffer = new Node;
				buffer->value = minElement + minElement2;
				buffer->letter = NULL;
				buffer->parent = NULL;
				buffer->next = NULL;
				prev->next = buffer;
				if (find(root, minElement) && (findAndGet(root, minElement)->parent == NULL))
				{
					buffer->left = findAndGet(root, minElement);
					if (Key1 != NULL)
						buffer->left->letter = NULL;
					else buffer->left->letter = Key1;
					buffer->left->parent = buffer;
					if (find(root, minElement2))
					{
						buffer->right = findAndGet(root, minElement2);
						if (Key2 == NULL)
							buffer->right->letter = NULL;
						else buffer->right->letter = Key2;
						buffer->right->parent = buffer;
					}
					else
					{
						buffer->right = new Node;
						buffer->right->value = minElement2;
						buffer->right->letter = Key2;
						buffer->right->parent = buffer;
					}
				}
				else
				{
					if (find(root, minElement2) && (findAndGet(root, minElement2)->parent == NULL))
					{
						buffer->left = findAndGet(root, minElement2);
						if (Key2 == NULL)
							buffer->left->letter = NULL;
						else buffer->left->letter = Key2;
						buffer->left->parent = buffer;
					}
					else
					{
						buffer->left = new Node;
						buffer->left->value = minElement2;
						buffer->left->letter = Key2;
						buffer->left->parent = buffer;
					}
					buffer->right = new Node;
					buffer->right->value = minElement;
					buffer->right->letter = Key1;
					buffer->right->parent = buffer;

				}
				list.add(buffer->value);
				vertex = buffer;
				buffer = root;
			}
		}
		HaffmanCoding();
	}
	float encodedSize(string test)
	{
		float size = 0;
		int i = 0;
		while (i != test.length())
		{
			if (test[i] != ' ')
			{
				size++;
			}
			i++;
		}
		return size;
	}


};
