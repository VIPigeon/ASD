
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <cmath>

template<typename T>
class BinTree
{
public:
    struct Node;
    Node* root;
    Node* _end;
private:
    char depth;

    void _removeNode(Node* node)
    {
        if (node->right == nullptr && node->left == nullptr)
        {
            if (node != root)
            {
                if (node->parent->right == node)
                    node->parent->right = nullptr;
                else node->parent->left = nullptr;
            }
            else root = nullptr;
            delete node;
            return;
        }
        if (node->right != nullptr && node->left == nullptr)
        {
            if (node != root)
            {
                if (node->parent->right == node)
                    node->parent->right = node->right;
                else node->parent->left = node->right;
                node->right->parent = node->parent;
            }
            else
            {
                node->right->parent = nullptr;
                root = node->right;
            }

            delete node;
            return;
        }
        if (node->right == nullptr && node->left != nullptr)
        {
            if (node != root)
            {
                if (node->parent->right == node)
                    node->parent->right = node->left;
                else node->parent->left = node->left;
                node->left->parent = node->parent;
            }
            else
            {
                node->left->parent = nullptr;
                root = node->left;
            }

            delete node;
            return;
        }
        Node* minRightNode = _minUnderNode(node->right);
        node->data = minRightNode->data;
        _removeNode(minRightNode);

    }

    Node* _minUnderNode(Node* start)
    {
        Node* node = start;
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    Node* _find(T value)
    {
        Node* node = root;
        while (node != nullptr && value != node->data)
        {
            if (value > node->data)
            {
                node = node->right;
            }
            else node = node->left;
        }
        return node;
    };

    void _recursivePrint(Node* node)
    {
        if (node == nullptr)
            return;
        std::cout << node->data << " ";
        _recursivePrint(node->left);
        _recursivePrint(node->right);
    }

    bool _recursiveCompare(const Node* node1, const Node* node2) const
    {
        if (node1 != nullptr and node2 == nullptr)
            return false;
        if (node1 == nullptr and node2 != nullptr)
            return false;
        if (node1 == nullptr and node2 == nullptr)
            return true;
        return _recursiveCompare(node1->right, node2->right) &&
                 _recursiveCompare(node1->left, node2->left);
    }

    void _copyConstructor(Node* current, Node* otherNode, bool isLeft)
    {
        if (otherNode == nullptr)
            return;
        if (isLeft)
        {
            current->left = new Node(current, otherNode->data);
            _copyConstructor(current->left, otherNode->left, true);
            _copyConstructor(current->left, otherNode->right, false);
        }
        else
        {
            current->right = new Node(current, otherNode->data);
            _copyConstructor(current->right, otherNode->left, true);
            _copyConstructor(current->right, otherNode->right, false);
        }
    }
public:
#if 1
    struct iterator
    {
        Node* node;
        bool operator!=(iterator other)
        {
            return node != other.node;
        }
        bool operator==(iterator other)
        {
            return node == other.node;
        }

        iterator operator++()
        {
            if (node->right != nullptr)
            {
                node = node->right;
                return *this;
            }
            while (node->isRight())
            {
                node = node->parent;
            }
            if (node->parent == nullptr)
                return node->left;
            node = node->parent;
            return *this;
        }

        iterator operator--()
        {
            if (*this == end())
            {
                return iterator(max());
            }
            if (node->left == nullptr)
            {
                node = node->left;
                return *this;
            }
            while (node->isLeft())
            {
                node = node->parent;
            }
            if (node == root)
            {
                node = end();
                return *this;
            }
            node = node->parent;
            return *this;
        }

        T operator*()
        {
            return node->data;
        }

        iterator(Node* n):node(n){};
    };
#endif
    struct Node
    {
        T data;
        Node* parent;
        Node* left;
        Node* right;
        char depth;
        Node(Node* p, T d):parent(p),left(nullptr),right(nullptr),data(d)
        {
            depth = (p == nullptr) ? 0 : (p->depth + 1);
        };
        bool isLeft()
        {
            if (parent == nullptr)
                return false;
            return parent->left == this;
        }
        bool isRight()
        {
            if (parent == nullptr)
                return false;
            return parent->right == this;
        }
    };

    iterator begin() const
    {
        return iterator(min());
    }

    iterator end() const
    {
        return iterator(_end);
    }

    BinTree(T value):depth(1){
        _end = new Node(nullptr, NULL);
        root = new Node(_end, value);
    };

    BinTree(const BinTree<T>& other):depth(other.depth)
    {
        if (other.empty())
        {
            root = nullptr;
            return;
        }
        root = new Node(nullptr, (other.root)->data);
        _copyConstructor(root, (other.root)->left, true);
        _copyConstructor(root, (other.root)->right, false);
    }

    int actualDepth()
    {
        depth = 0;
        std::stack<Node*> st;
        st.push(root);
        while (!st.empty())
        {
            Node* node = st.top();
            st.pop();
            if (node->right != nullptr)
                st.push(node->right);
            if (node->left != nullptr)
                st.push(node->left);
            depth = std::max(depth, node->depth);
        }
        return depth;
    }

    iterator insert(T value)
    {
        Node* node = root;
        char current_depth = 1;
        while (true)
        {
            current_depth++;
            if (value >= node->data)
            {
                if (node->right == nullptr)
                {
                    Node* nn = new Node(node, value);
                    node->right = nn;
                    depth = std::max(current_depth, depth);
                    return iterator(nn);
                }
                node = node->right;
            }
            else
            {
                if (node->left == nullptr)
                {
                    Node* nn = new Node(node, value);
                    node->left = nn;
                    depth = std::max(current_depth, depth);
                    return iterator(nn);
                }
                node = node->left;
            }
        }
    };

    bool empty() const
    {
        return root == nullptr;
    }

    iterator find(T value) const
    {
        Node* node = root;
        while (node != nullptr && value != node->data)
        {
            if (value > node->data)
            {
                node = node->right;
            }
            else node = node->left;
        }
        if (node == nullptr)
            return end();
        return iterator(node);
    };

    T lowerFind(T value)
    {
        Node* node = root;
        while (value < node->data)
        {
            node = node->left;
        }
        return node->data;
    }

    T upperFind(T value)
    {
        Node* node = root;
        while (value > node->data)
        {
            node = node->right;
        }
        return node->data;
    }

    Node* min()
    {
        Node* node = root;
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    };

    Node* max()
    {
        Node* node = root;
        while (node->right != nullptr)
        {
            node = node->right;
        }
        return node;
    };

    void remove(T value)
    {
        Node* node = _find(value);
        _removeNode(node);
    }

    void printInStack()
    {
        std::stack<Node*> st;
        st.push(root);
        while (!st.empty())
        {
            Node* node = st.top();
            st.pop();
            std::cout << node->data << " ";
            if (node->right != nullptr)
                st.push(node->right);
            if (node->left != nullptr)
                st.push(node->left);
        }
        std::cout << std::endl;
    }

    void printInRecursion()
    {
        _recursivePrint(root);
        std::cout << std::endl;
    }

    void printInQueue(std::string blank="")
    {
        std::queue<Node*> st;  // don't ask why queue is "st"
        st.push(root);
        // std::cout << root << std::endl;
        int nodes_in_row = 1;
        int counter = 0;
        while (nodes_in_row <= std::pow(2, depth - 1))
        {
            Node* node = st.front();
            // std::cout << node->data << std::endl;
            st.pop();
            if (node != nullptr)
            {
                std::cout << node->data << " ";
                st.push(node->left);
                st.push(node->right);
            }
            else
            {
                std::cout << blank;
                st.push(nullptr);
                st.push(nullptr);
            }
            if ((++counter) == nodes_in_row)
            {
                counter = 0;
                nodes_in_row *= 2;
                std::cout << std::endl;
            }
        }
        // std::cout << std::endl;
    }

#if 0
    // it doesn't work right
    void pprint()  // pretty print <3
    {
        std::queue<Node*> st;  // don't ask why queue is "st"
        st.push(root);
        // std::cout << root << std::endl;
        int nodes_in_row = 1;
        int tabs_in_row = std::pow(2, depth - 1);
        int counter = 0;
        while (nodes_in_row <= tabs_in_row)
        {
            Node* node = st.front();
            // std::cout << node->data << std::endl;
            for (int i = 0; i < tabs_in_row / nodes_in_row; i++)
                std::cout << "\t";
            st.pop();
            if (node != nullptr)
            {
                std::cout << node->data;
                st.push(node->left);
                st.push(node->right);
            }
            else
            {
                std::cout << "_";
                st.push(nullptr);
                st.push(nullptr);
            }
            for (int i = 0; i < tabs_in_row / nodes_in_row; i++)
                std::cout << "\t";
            if ((++counter) == nodes_in_row)
            {
                counter = 0;
                nodes_in_row *= 2;
                std::cout << std::endl;
            }
        }
    };
#endif

#if 1
    bool dataCompare(const BinTree<T>& _other) const
    {
        BinTree<T> other(_other);

        std::stack<Node*> st;
        st.push(root);
        while (!st.empty())
        {
            Node* node = st.top();
            st.pop();
            // std::cout << node->data << std::endl;
            // other.printInQueue("_ ");
            if (!other.find(node->data))
                return false;
            other.remove(node->data);
            if (node->right != nullptr)
                st.push(node->right);
            if (node->left != nullptr)
                st.push(node->left);
        }
        return true;
    }
#endif

    bool structureCompare(const BinTree<T>& other)
    {
        return _recursiveCompare(root, other.root);
    };

#if 1
    bool strictCompare(const BinTree<T>& other)
    {
        return structureCompare(other) && dataCompare(other);  // -_-
    };
#endif
};
