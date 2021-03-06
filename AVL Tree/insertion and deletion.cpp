/**
    **Code to insert and delete the node from AVL Tree
*/

#include <bits/stdc++.h>
using namespace std;

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
    int height;
} node;

//creating newnode
node *newnode(node *root, int data)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 1;
    return newnode;
}

//function for finding the height of node
int getheight(node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

//function to find max
int max(int x, int y)
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

//function to find the value of balance factor
int balancefactor(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return getheight(root->left) - getheight(root->right);
}

//function for right rotation
struct node *rightrotation(node *root)
{
    node *extranode = root->left;
    node *garbage = extranode->right;

    //rotation occurs
    extranode->right = root;
    root->left = garbage;

    //updating height of root and extranode
    root->height = 1 + (max(getheight(root->left), getheight(root->right)));
    extranode->height = 1 + (max(getheight(extranode->left), getheight(extranode->right)));

    //returning new node
    return extranode;
}

//function for left rotation
struct node *leftrotation(node *root)
{
    node *extranode = root->right;
    node *garbage = extranode->left;

    //rotation occurs
    extranode->left = root;
    root->right = garbage;

    //updating height of root and extranode
    root->height = 1 + (max(getheight(root->left), getheight(root->right)));
    extranode->height = 1 + (max(getheight(extranode->left), getheight(extranode->right)));

    //returning new node
    return extranode;
}

//inserting function
struct node *insertnode(node *root, int data)
{
    if (root == NULL)
    {
        return newnode(root, data);
    }
    else if (data < root->data)
    {
        root->left = insertnode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insertnode(root->right, data);
    }
    else
    {
        return NULL;
    }

    //getting height of node
    root->height = 1 + (max(getheight(root->left), getheight(root->right)));

    //checking balance factor here
    int balance;
    balance = balancefactor(root);

    //LL rotation case;
    if (balance > 1 && data < root->left->data)
    {
        return rightrotation(root);
    }
    //RR rotation case
    else if (balance < -1 && data > root->right->data)
    {
        return leftrotation(root);
    }
    //LR rotation case
    else if (balance > 1 && data > root->left->data)
    {
        root->left = leftrotation(root->left);
        return rightrotation(root);
    }
    //RL rotation case
    else if (balance < -1 && data < root->right->data)
    {
        root->right = rightrotation(root->right);
        return leftrotation(root);
    }

    return root;
}

node *maximum(node *root) //function to find max node
{
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
}

node *deletenode(node *root, int data)
{
    node *temp;
    if (root == NULL)
    {
        printf("Elements not exist!!\n");
        return NULL;
    }
    if (root->data > data)
    {
        root->left = deletenode(root->left, data);
    }
    else if (root->data < data)
    {
        root->right = deletenode(root->right, data);
    }
    else //it implements when element founds
    {
        if (root->left && root->right) //for both children
        {
            temp = maximum(root->left);
            root->data = temp->data;
            root->left = deletenode(root->left, root->data);
        }
        else // one or no child
        {

            temp = root;
            if (root->left == NULL)
            {
                root = root->right;
            }
            else if (root->right == NULL)
            {
                root = root->left;
            }
            free(temp);
        }
    } //end of else

    if (root != NULL) //This is to update AVL tree when its condition is violated
    {

        root->height = 1 + max(getheight(root->left), getheight(root->right));

        int balance;
        balance = balancefactor(root);

        //LL rotation case
        if (balance > 1 && data < root->left->data)
        {
            return rightrotation(root);
        }
        //RR rotation case
        else if (balance < -1 && data > root->right->data)
        {
            return leftrotation(root);
        }
        //LR rotation case
        else if (balance > 1 && data > root->left->data)
        {
            root->left = leftrotation(root->left);
            return rightrotation(root);
        }
        //RL rotation case
        else if (balance < -1 && data < root->right->data)
        {
            root->right = rightrotation(root->right);
            return leftrotation(root);
        }
    }
    return root;
}

void inorder(node *root)
{
    if (root == NULL)
    {
        return;
    }
    inorder(root->left);
    printf("%d  ", root->data);
    inorder(root->right);
}

int main()
{
    node *root = NULL;
    //inserting element
    int num, data;
    printf("Enter how many elements you want to enter: ");
    scanf("%d", &num);
    printf("Enter elements:");
    for (int i = 0; i < num; i++)
    {
        scanf("%d", &data);
        root = insertnode(root, data);
    }

    printf("Now inorder arrangement of this AVL search tree is:");
    inorder(root);
    printf("\n");

    cout << "Enter the element you want to delete from this AVL Tree:";
    cin >> data;
    deletenode(root, data);

    printf("Now inorder arrangement of this AVL search tree is:");
    inorder(root);
    printf("\n");
    return 0;
}
