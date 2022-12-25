#include "FormulaTree.h"

bool isOperator(char x) {
    if (x == '*' || x == '-' || x == '+')
        return true;
    return false;
}

char derivative(char s)
{
    if (s == 'x')
    {
        return '1';
    }
    else return '0';
}

void printTree(const Tree& T)
{
    if (T != 0)
    {
        printTree(T->left);
        std::cout << T->info;
        printTree(T->right);
    }
}
Tree copyTree(const Tree& node)
{
    if (node == nullptr)
        return nullptr;

    Tree copy = new NODE(node->info);
    copy->left = copyTree(node->left);
    copy->right = copyTree(node->right);
    return copy;
}

Tree derivativeTree(const Tree& node)
{
    if (node == nullptr)
        return nullptr; 
    Tree tmp = new NODE(node->info);
    std::cout << node->info;
    tmp->left = derivativeTree(node->left);
    tmp->right = derivativeTree(node->right);
    if (isOperator(tmp->info) && tmp->info != '*')
    {
        if(!isOperator(tmp->left->info))
            tmp->left->info = derivative(tmp->left->info);
        if (!isOperator(tmp->right->info))
            tmp->right->info = derivative(tmp->right->info);
    }
    else if (tmp->info == '*')
    {
        Tree t = new NODE('+');

        Tree tmpCopy = copyTree(tmp);

        t->left = tmp;
        t->right = tmpCopy;
        if(!isOperator(t->left->left->info))
            t->left->left->info = derivative(t->left->left->info);
        else
        {
            Tree tll = copyTree(t->left->left);
            t->left->left = derivativeTree(tll);
            delete tll;
        }
        if (!isOperator(t->right->right->info))
            t->right->right->info = derivative(t->right->right->info);
        else
        {
            Tree trr = copyTree(t->right->right);
            t->right->right = derivativeTree(trr);
            delete trr;
        }
        tmp = t;      
    }
    return tmp;
}

bool task1(const Tree& T, Tree& T1, char derivativeVar)
{
    bool result = true;
    if (isOperator(T->info))
        T1 = derivativeTree(T);
    else T1 = new NODE(derivative(T->info));
    if (!T1)
        result = false;
    return result;
}

int main()
{
    std::stringstream ss;
    std::ifstream file("formula.txt");
    Tree T = Build_Formula(file);
    Tree T1;
    /*std:: cout << T->info;*/

    if (task1(T, T1, 'x'))
    {
        std::cout << "\nT1: \n" << treeFormulaToString(T1, ss);
    }
    else std::cout << "T1 was not created...";
}
