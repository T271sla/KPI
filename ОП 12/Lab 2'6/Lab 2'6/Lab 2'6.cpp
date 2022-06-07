#include <iostream>
using namespace std;

struct node
{
    int info;
    node* l, * r;
};

node* tree = NULL;

void push(int a, node** t)
{
    if ((*t) == NULL)
    {
        (*t) = new node;
        (*t)->info = a;
        (*t)->l = (*t)->r = NULL;
        return;
    }

    if (a > (*t)->info) {
        push(a, &(*t)->r);
    }
    else
    {
        push(a, &(*t)->l);
    }
}

int inOrder(node* tree, int& max)
{
    if (tree != NULL)
    {
        if (tree->r == NULL)
        {
            max = tree->info;
        }
        inOrder(tree->r, max);
    }
    return max;
}

int main()
{
    int n;
    int s;
    cout << "How many elements: ";
    cin >> n;


    node* tree = NULL;
    for (int i = 0; i < n; ++i)
    {
        cout << "Enter element: ";
        cin >> s;
        push(s, &tree);
    }

    int max = 0;
    int res = inOrder(tree, max);
    cout << "Max element: " << res;
}
