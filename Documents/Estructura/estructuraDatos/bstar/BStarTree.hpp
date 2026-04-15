#ifndef BSTAR_TREE_HPP
#define BSTAR_TREE_HPP

const int DEGREE = 5; // max keys = DEGREE - 1, max children = DEGREE

class BStarTree {
  private:
    struct Node {
        int keys[DEGREE - 1];
        Node* children[DEGREE];
        int numKeys;
        bool isLeaf;

        Node(bool leaf) {
            isLeaf = leaf;
            numKeys = 0;
            for (int i = 0; i < DEGREE; i++)
                children[i] = nullptr;
        }
    };

    Node* root;

    void insert(Node*& node, int key);
    void splitAndRedistribute(Node*& parent, int index, Node*& child);
    void insertNonFull(Node* node, int key);
    void printLevelOrder(Node* node) const;
    void deleteTree(Node* node);
    bool searchInNode(Node* node, int key) const;

    void remove(Node* node, int key);
    void removeFromLeaf(Node* node, int index);
    void removeFromNonLeaf(Node* node, int index);
    int getPredecessor(Node* node, int index);
    int getSuccessor(Node* node, int index);
    void fill(Node* node, int index);
    void borrowFromPrev(Node* node, int index);
    void borrowFromNext(Node* node, int index);
    void merge(Node* node, int index);
    void redistributeOrMerge(Node* node, int index);

  public:
    BStarTree();
    ~BStarTree();

    void insert(int key);
    void printByLevel() const;
    bool search(int key) const;
    void remove(int key);
};

#endif
