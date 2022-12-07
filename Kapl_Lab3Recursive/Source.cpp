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

    Tree T1 = new NODE(node->info);
    std::cout << node->info;
    T1->left = copyTree(node->left);
    T1->right = copyTree(node->right);
    if (isOperator(T1->info) && T1->info != '*')
    {
        if (!isOperator(T1->left->info) && !isOperator(T1->right->info)) //change basic tree u'+v'
        {
            T1->left->info = derivative(T1->left->info);
            T1->right->info = derivative(T1->right->info);
        }
        //operator|operand cases
        else if ((isOperator(T1->left->info) && !isOperator(T1->right->info)) ||
            (!isOperator(T1->left->info) && isOperator(T1->right->info)))
        {
            if (isOperator(T1->left->info))
                T1->right->info = derivative(T1->right->info);
            else T1->left->info = derivative(T1->left->info);
        }
    }
    else if (T1->info == '*')
    {
        if (!isOperator(T1->left->info) && !isOperator(T1->right->info)) //change basic tree u'v+uv'
        {
            Tree newT1ptr = new NODE('+');

            newT1ptr->left = new NODE('*');
            newT1ptr->right = new NODE('*');

            newT1ptr->left->left = new NODE(derivative(T1->left->info));
            newT1ptr->left->right = new NODE(T1->right->info);

            newT1ptr->right->left = new NODE(T1->left->info);
            newT1ptr->right->right = new NODE(derivative(T1->right->info));

            T1 = newT1ptr;
        }
        //operator|operand cases
        else if ((isOperator(T1->left->info) && !isOperator(T1->right->info)) ||
            (!isOperator(T1->left->info) && isOperator(T1->right->info)))
        {
            if (isOperator(T1->left->info))
            {
                Tree rememberT1LEFT = T1->left;
                Tree rememberT1RIGHT = T1->right;
                T1->info = '+';

                T1->left = new NODE('*');
                T1->left->left = copyTree(rememberT1LEFT); // LEFT PART DERIVATIVE. NEED TO GET (+)NEW NODE AND + V TO THE RIGHT
                T1->left->right = rememberT1RIGHT;

                T1->right = new NODE('*');
                T1->right->left = rememberT1LEFT;
                T1->right->right = new NODE(derivative(rememberT1RIGHT->info));
            }
            else if (isOperator(T1->right->info))
            {
                Tree rememberT1LEFT = T1->left;
                Tree rememberT1RIGHT = T1->right;
                T1->info = '+';

                T1->left = new NODE('*');
                T1->left->left = rememberT1RIGHT; // LEFT PART DERIVATIVE. NEED TO GET (+)NEW NODE AND + V TO THE RIGHT
                T1->left->right = new NODE(derivative(rememberT1LEFT->info));

                T1->right = new NODE('*');
                T1->right->left = copyTree(rememberT1RIGHT);
                T1->right->right = rememberT1LEFT;
            }
        }
    }

    return T1;

}

bool task1(const Tree& T, Tree& T1, char derivativeVar)
{
    bool result = true;
    T1 = copyTree(T);
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
