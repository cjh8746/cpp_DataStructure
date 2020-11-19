#include <iostream>
using namespace std;
#define MAX 100

class BinaryNode
{
protected:
    int data;
    BinaryNode *left;
    BinaryNode *right;

public:
    BinaryNode(int val = 0, BinaryNode *l = NULL, BinaryNode *r = NULL)
    {
        data = val;
        left = l;
        right = r;
    }
    void setData(int val)
    {
        data = val;
    }
    void setLeft(BinaryNode *l)
    {
        left = l;
    }
    void setRight(BinaryNode *r)
    {
        right = r;
    }
    int getData()
    {

        return data;
    }
    BinaryNode *getLeft() { return left; }
    BinaryNode *getRight() { return right; }
    bool isLeaf()
    {
        return left == NULL && right == NULL;
    }
};

class CircularQueue
{
private:
    int front;
    int rear;
    BinaryNode *data[MAX];

public:
    CircularQueue() { front = rear = 0; }
    bool isEmpty() { return front == rear; }
    bool isFull() { return (rear + 1) % MAX == front; }
    void enqueue(BinaryNode *n)
    {
        if (isFull())
        {
            cout << "큐가 포화상태입니다." << endl;
        }
        else
        {
            rear = (rear + 1) % MAX;
            data[rear] = n;
        }
    }

    BinaryNode *dequeue()
    {
        if (isEmpty())
        {
            cout << "큐가 비어있습니다." << endl;
        }
        else
        {
            front = (front + 1) % MAX;
            return data[front];
        }
    }
};

class BinaryTree : public BinaryNode
{
protected:
    BinaryNode *root;

public:
    BinaryTree() : root(NULL) {}
    void setRoot(BinaryNode *node)
    {
        root = node;
    }
    BinaryNode *getRoot()
    {
        return root;
    }
    bool isEmpty()
    {
        return root == NULL;
    }
    void inorder()
    {
        cout << endl
             << " inorder: ";
        inorder(root);
    }
    void inorder(BinaryNode *node)
    {
        if (node != NULL)
        {
            inorder(node->getLeft());
            cout << " [ " << (char)node->getData() << " ] ";
            inorder(node->getRight());
        }
    }
    void preorder()
    {
        cout << endl
             << " preorder: ";
        preorder(root);
    }
    void preorder(BinaryNode *node)
    {
        if (node != NULL)
        {
            cout << " [ " << (char)node->getData() << " ] ";
            preorder(node->getLeft());
            preorder(node->getRight());
        }
    }
    void postorder()
    {
        cout << endl
             << " postorder: ";
        postorder(root);
    }

    void postorder(BinaryNode *node)
    {
        if (node != NULL)
        {
            postorder(node->getLeft());
            postorder(node->getRight());
            cout << " [ " << (char)node->getData() << " ] ";
        }
    }

    void levelorder()
    {
        cout << endl
             << " levelorder: ";
        if (!isEmpty())
        {
            CircularQueue q;
            q.enqueue(root);
            while (!q.isEmpty())
            {
                BinaryNode *n = q.dequeue();
                if (n != NULL)
                {
                    cout << " [ " << (char)n->getData() << " ] ";
                    q.enqueue(n->getLeft());
                    q.enqueue(n->getRight());
                }
            }
        }
        cout << endl;
    }

    //노드의 개수를 구하는 함수
    int getCount()
    {
        return isEmpty() ? 0 : getCount(root);
    }
    int getCount(BinaryNode *node)
    {
        if (node == NULL)
        {
            return 0;
        }

        return 1 + getCount(node->getLeft()) + getCount(node->getRight()); //여기서 1을 더해주는 이유는, root노드의 개수도 포함시키기 위한 것.
    }

    // 단말 노드의 개수를 구하는 함수
    int getLeafCount()
    {
        return isEmpty() ? 0 : getLeafCount(root);
    }
    int getLeafCount(BinaryNode *node)
    {
        if (node == NULL)
            return 0;
        if (node->isLeaf())
            return 1; //루트노드만 있을경우 1. 루트노드가 단말 노드이기 때문에
        else
            return getLeafCount(node->getLeft()) + getLeafCount(node->getRight());
    }
    // 트리의 높이를 구하는 함수
    int getHeight()
    {
        return isEmpty() ? 0 : getHeight(root);
    }
    int getHeight(BinaryNode *node)
    {
        if (node == NULL)
            return 0;
        int hLeft = getHeight(node->getLeft());
        int hRight = getHeight(node->getRight());
        return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
    }
};


//이진트리 탐색 시작.
class BinSrchTree : public BinaryTree
{

public:
    BinSrchTree(void) {}
    ~BinSrchTree(void) {}

    BinaryNode *search(int key)
    {
        BinaryNode *node = searchRecur(root, key);
        if (node != NULL)
        {
            cout << "탐색성공: 키값이 " << node->getData() << "인 노드 = " << node << endl;
        }
        else
        {
            cout << "탐색실패: 키값이 " << key << "인 노드없음 " << endl;
        }
        return node;
    }

    BinaryNode *searchRecur(BinaryNode *n, int key)
    {
        if (n == NULL)
            return NULL;
        if (key == n->getData())
        {
            return n;
        }
		// 순환의 개념을 사용하여 key와 n을 비교함.
        else if (key < n->getData()) 
        {	//key값이 n보다 작으면 
            return searchRecur(n->getLeft(), key);
        }
        else
        {
            return searchRecur(n->getRight(), key);
        }
    }

    /*BinaryNode* searchIter(BinaryNode* n, int key) {
		while (n != NULL) {
			if (key == n->getData()) {
				return this;
			}
			else if (key < n->getData()) {
				n = n->getLeft();
			}
			else
				n = n->getRight();
		}
		return NULL;
	}*/

    void insert(BinaryNode *n)
    {
        if (n == NULL)
            return;
        if (isEmpty())
            root = n;
        else
            insertRecur(root, n);
    }

    void insertRecur(BinaryNode *r, BinaryNode *n)
    {
        if (n->getData() == r->getData()) //root의 값과 n의 값이 값으면 인서트를 해줄 필요가 없어서 바로 리턴해준다. [예외처리]
        {
            return;
        }
        else if (n->getData() < r->getData())//Root의 값과 N의 값을 비교.  즉 넣을려는 값이 작으면 코드 진행
        {
            if (r->getLeft() == NULL) //root가  비어있으면 루트에 n을 바로 넣어줌.
            {
                r->setLeft(n);
            }
            else // 이때 root가 비어있지 않다면 그 하위 왼쪽 자식노드에 n을 넣어주고 순환 반복.
            {
                insertRecur(r->getLeft(), n);
            }
        }
        else  // 반대로 root 값이 n보다 큰경우 위와 같이 오른쪽 노드로 순환 반복.
        {
            if (r->getRight() == NULL)
            {
                r->setRight(n);
            }
            else
            {
                insertRecur(r->getRight(), n);
            }
        }
    }
	
    void remove(int key)
    {
        if (isEmpty())
            return;
        BinaryNode *parent = NULL;
        BinaryNode *node = root;

        while (node != NULL && node->getData() != key)
        {
            parent = node;
            node = (key < node->getData()) ? node->getLeft() : node->getRight();
        }
        if (node == NULL)
        {
            cout << "Error: key is not in the tree!" << endl;
            return;
        }
        else
        {
            remove(parent, node);
        }
    }

    void remove(BinaryNode *parent, BinaryNode *node)
    {
        if (node->isLeaf())
        {

            if (parent == NULL)
            {
                root = NULL;
            }

            else
            {
                if (parent->getLeft() == node)
                {
                    parent->setLeft(NULL);
                }
                else
                {
                    parent->setRight(NULL);
                }
            }
        }

        else if (node->getLeft() == NULL || node->getRight() == NULL)
        {
            BinaryNode *child = (node->getLeft() != NULL) ? node->getLeft() : node->getRight();
            if (node == root)
            {
                root = child;
            }
            else
            {
                if (parent->getRight() == node)
                {
                    parent->setLeft(child);
                }
                else
                {
                    parent->setRight(child);
                }
            }
        }

        else
        {
            BinaryNode *succp = node;
            BinaryNode *succ = node->getRight();
            while (succ->getLeft() != NULL)
            {
                succp = succ;
                succ = succ->getLeft();
            }
            if (succp->getLeft() == succ)
            {
                succp->setLeft(succ->getRight());
            }
            node->setData(succ->getData());
            node = succ;
        }
        delete node;
    }
    int main()
    {
        BinSrchTree tree;

        tree.insert(new BinaryNode(35));
        tree.insert(new BinaryNode(18));
        tree.insert(new BinaryNode(7));
        tree.insert(new BinaryNode(26));
        tree.insert(new BinaryNode(12));
        tree.insert(new BinaryNode(3));
        tree.insert(new BinaryNode(68));
        tree.insert(new BinaryNode(22));
        tree.insert(new BinaryNode(30));
        tree.insert(new BinaryNode(99));

        cout << "노드의 개수 = " << tree.getCount() << endl;
        cout << "단말의 개수 = " << tree.getLeafCount() << endl;
        cout << "트리의 높이 = " << tree.getHeight() << endl;

        tree.inorder();
        tree.preorder();
        tree.postorder();
        tree.levelorder();

        tree.search(26);
        tree.search(25);
        cout << "CASE1 ==> 노드 3 삭제" << endl;
        tree.remove(3);
        tree.levelorder();
        cout << "CASE2 ==> 노드 68 삭제" << endl;
        tree.remove(68);
        tree.levelorder();
        cout << "CASE3 ==> 노드 18 삭제" << endl;
        tree.remove(18);
        tree.levelorder();
        cout << "CASE3 ==> 노드 35 삭제" << endl;
        tree.remove(35);
        tree.levelorder();

        cout << "노드의 개수 = " << tree.getCount() << endl;
        cout << "단말의 개수 = " << tree.getLeafCount() << endl;
        cout << "트리의 높이 = " << tree.getHeight() << endl;
    }
};

int main()
{
    BinaryTree tree;
    BinaryNode *i = new BinaryNode('I', NULL, NULL);
    BinaryNode *g = new BinaryNode('G', NULL, NULL);
    BinaryNode *h = new BinaryNode('H', i, NULL);
    BinaryNode *e = new BinaryNode('E', g, h);
    BinaryNode *f = new BinaryNode('F', NULL, NULL);
    BinaryNode *c = new BinaryNode('C', e, f);
    BinaryNode *d = new BinaryNode('D', NULL, NULL);
    BinaryNode *b = new BinaryNode('B', d, NULL);
    BinaryNode *a = new BinaryNode('A', b, c);

    tree.setRoot(a);
    tree.levelorder();
    cout << "노드의 개수 : " << tree.getCount() << endl;
    cout << "단말의 개수 : " << tree.getLeafCount() << endl;
    cout << "트리의 높이 : " << tree.getHeight() << endl;
}